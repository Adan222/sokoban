# Sokoban - Motorola Science Cup

- Polish version of the user documentation - [dok_uzyt](./docs/dok_uzyt.md).
- English version of the user documentation - [doc_user](./docs/doc_user.md).
- Polish version of the code documentation - [dok_tech](./docs/dok_tech.md).


In build folder you will find prebuilt windows-x64 and linux-x64 binares.
```sh
sudo cmake gcc g++ apt-get install libudev-dev libx11-dev xorg-dev freeglut3-dev
sudo apt-get install mingw-w64-x86-64-dev mingw-w64
sudo update-alternatives --config x86_64-w64-mingw32-g++ # Set the default mingw32 g++ compiler option to posix.


```


## Building
```sh
git clone https://github.com/Adan222/sokoban
cd sokoban
git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.sh -disableMetrics
git reset --hard 9f6aaaccb70d6f114a967f0ab83eff42840614ed
cp ../vendor/soloud ports/ -r
```

We are reveriting to ImGui 1.81, because on MinGW new version have problem with IMM linking. See https://github.com/microsoft/vcpkg/issues/16964

Vcpkg requires powershell. See https://docs.microsoft.com/en-us/powershell/scripting/install/installing-powershell-core-on-linux?view=powershell-7.1



### For building Linux binares
```sh
./vcpkg install sfml imgui imgui-sfml nlohmann-json nativefiledialog soloud
cd ..
mkdir -p build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
make

```
### For cross building to Windows 
If any error occures during cmake command(eg. freetype missing), please try rerunning.

```sh
./vcpkg install sfml imgui imgui-sfml nlohmann-json soloud --triplet x64-mingw-static
./vcpkg install nativefiledialog --head --triplet x64-mingw-static
cd ..
mkdir -p build && cd build
cmake .. -DVCPKG_TARGET_TRIPLET=x64-mingw-static -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=<absolute path to sokoban dir>/toolchain-mingw-x64.cmake -DVCPKG_APPLOCAL_DEPS=OFF
ln -s /usr/x86_64-w64-mingw32/lib/libopengl32.a /usr/x86_64-w64-mingw32/lib/libOpenGL32.a
make
```
