# Sokoban - Motorola Science Cup

In build folder you will find prebuilt windows-x64 and linux-x64 binares.

## Building
```sh
git clone https://github.com/Adan222/sokoban
cd sokoban
git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.sh -disableMetrics
```
Vcpkg requires powershell. See https://docs.microsoft.com/en-us/powershell/scripting/install/installing-powershell-core-on-linux?view=powershell-7.1



### For building Linux binares
```sh
./vcpkg install sfml imgui imgui-sfml nlohmann-json nativefiledialog
cd ..
mkdir -p build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
make
```
### For cross building to Windows 
If any error occures during cmake command, please try rerunning.
```sh
./vcpkg install sfml imgui imgui-sfml nlohmann-json nativefiledialog --triplet x64-mingw-static
cd ..
mkdir -p build && cd build
cmake .. -DVCPKG_TARGET_TRIPLET=x64-mingw-static -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=<absolute path to sokoban dir>/toolchain-mingw-x64.cmake -DVCPKG_APPLOCAL_DEPS=OFF
ln -s /usr/x86_64-w64-mingw32/lib/libopengl32.a /usr/x86_64-w64-mingw32/lib/libOpenGL32.a
make
```
