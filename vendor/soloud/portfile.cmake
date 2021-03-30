# Common Ambient Variables:
#   CURRENT_BUILDTREES_DIR    = ${VCPKG_ROOT_DIR}\buildtrees\${PORT}
#   CURRENT_PACKAGES_DIR      = ${VCPKG_ROOT_DIR}\packages\${PORT}_${TARGET_TRIPLET}
#   CURRENT_PORT_DIR          = ${VCPKG_ROOT_DIR}\ports\${PORT}
#   CURRENT_INSTALLED_DIR     = ${VCPKG_ROOT_DIR}\installed\${TRIPLET}
#   DOWNLOADS                 = ${VCPKG_ROOT_DIR}\downloads
#   PORT                      = current port name (zlib, etc)
#   TARGET_TRIPLET            = current triplet (x86-windows, x64-windows-static, etc)
#   VCPKG_CRT_LINKAGE         = C runtime linkage type (static, dynamic)
#   VCPKG_LIBRARY_LINKAGE     = target library linkage type (static, dynamic)
#   VCPKG_ROOT_DIR            = <C:\path\to\current\vcpkg>
#   VCPKG_TARGET_ARCHITECTURE = target architecture (x64, x86, arm)
#   VCPKG_TOOLCHAIN           = ON OFF
#   TRIPLET_SYSTEM_ARCH       = arm x86 x64
#   BUILD_ARCH                = "Win32" "x64" "ARM"
#   MSBUILD_PLATFORM          = "Win32"/"x64"/${TRIPLET_SYSTEM_ARCH}
#   DEBUG_CONFIG              = "Debug Static" "Debug Dll"
#   RELEASE_CONFIG            = "Release Static"" "Release DLL"
#   VCPKG_TARGET_IS_WINDOWS
#   VCPKG_TARGET_IS_UWP
#   VCPKG_TARGET_IS_LINUX
#   VCPKG_TARGET_IS_OSX
#   VCPKG_TARGET_IS_FREEBSD
#   VCPKG_TARGET_IS_ANDROID
#   VCPKG_TARGET_IS_MINGW
#   VCPKG_TARGET_EXECUTABLE_SUFFIX
#   VCPKG_TARGET_STATIC_LIBRARY_SUFFIX
#   VCPKG_TARGET_SHARED_LIBRARY_SUFFIX
#
# 	See additional helpful variables in /docs/maintainers/vcpkg_common_definitions.md

# # Specifies if the port install should fail immediately given a condition
# vcpkg_fail_port_install(MESSAGE "soloud-test currently only supports Linux and Mac platforms" ON_TARGET "Windows")


#can't use sdl backend od when crossbuilding with mingw to windows, got some strange linking errors
if(VCPKG_TARGET_IS_LINUX)
    set(SOLOUD_BACKEND_SDL2 ON)
    set(SOLOUD_BACKEND_WINMM OFF)
    #pull requested patch(see https://github.com/jarikomppa/soloud/pull/312/commits/e6cf9f55f57b03faf844338e30ae4e5d61396bf3), not added yet so we need patch it manually
    set(SDL_INCLUDE_PATH "sdl2-include.patch")
else()
    set(SOLOUD_BACKEND_SDL2 OFF)
    set(SOLOUD_BACKEND_WINMM ON)
    set(SDL_INCLUDE_PATH "")
endif()

vcpkg_from_github(ARCHIVE
    OUT_SOURCE_PATH SOURCE_PATH
    REPO jarikomppa/soloud
    REF c8e339fdce5c7107bdb3e64bbf707c8fd3449beb 
    SHA512 b9975c97ccc027cecde52b3f843e72aeb29dd95c45fa80eab9e42e45c90ff94c7ba6df2c8023676a007903e5859278316343034eca560ce0022afac34e212d8f
    HEAD_REF master
    PATCHES
    ${SDL_INCLUDE_PATH}
)


if(VCPKG_LIBRARY_LINKAGE STREQUAL static)
    set(SOLOUD_STATIC 1)
else()
    set(SOLOUD_STATIC 0)
endif()



vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}/contrib
    PREFER_NINJA 
    OPTIONS -DSOLOUD_STATIC=${SOLOUD_STATIC}
    OPTIONS -DSOLOUD_BACKEND_SDL2=${SDL_BACKED}
    OPTIONS -DSOLOUD_BACKEND_WINMM=${SOLOUD_BACKEND_WINMM}
)

vcpkg_install_cmake()
if(VCPKG_TARGET_IS_WINDOWS)
    vcpkg_fixup_cmake_targets(CONFIG_PATH "cmake/")
endif()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/share")


# Handle copyright
file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/soloud RENAME copyright)
