![icon](https://github.com/Adan222/sokoban/blob/master/res/graphics/icon3.png "Icon")<br>
# Sokoban - Motorola Science Cup

- Polish version of the user documentation - [PL_dok_uzyt](./docs/PL_dok_uzyt.md).
- English version of the user documentation - [ENG_doc_user](./docs/ENG_doc_user.md).
- Polish version of the code documentation - [PL_dok_tech](./docs/PL_dok_tech.md).
- English version of technical documentation - [ENG_doc_tech](./docs/ENG_doc_tech.md).

***

In build folder you will find prebuilt windows-x64 and linux-x64 binares.

Building was tested on Ubuntu 20.04. 
Primary packages:
```sh
sudo apt-get install git cmake gcc g++ libudev-dev libx11-dev xorg-dev freeglut3-dev
sudo apt-get install curl zip unzip tar

#crossbuild to windows
sudo apt-get install mingw-w64-x86-64-dev mingw-w64
sudo update-alternatives --config x86_64-w64-mingw32-g++ # set the default mingw32 g++ compiler option to posix


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

We are reverting to ImGui 1.81, because on vcpkg mingw triplet new version have problem with IMM linking. See https://github.com/ocornut/imgui/commit/edf135c18de82aa4112ef561ecfc1ed824b8859b
I opened issue https://github.com/microsoft/vcpkg/issues/16964

Install powershell, vcpkg requires it. See https://docs.microsoft.com/en-us/powershell/scripting/install/installing-powershell-core-on-linux?view=powershell-7.1

### For building Linux binares
```sh
./vcpkg install sfml imgui imgui-sfml nlohmann-json nativefiledialog soloud
cd ..
mkdir -p build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
make
```

### For cross building to Windows 
If any error occures during cmake command(eg. freetype missing), please try rerunning. We can't do nothing about it.

```sh
./vcpkg install sfml imgui imgui-sfml nlohmann-json soloud --triplet x64-mingw-static
./vcpkg install nativefiledialog --head --triplet x64-mingw-static #we need newer version of nfd,
cd ..
mkdir -p build && cd build
cmake .. -DVCPKG_TARGET_TRIPLET=x64-mingw-static -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=<absolute path to sokoban dir>/toolchain-mingw-x64.cmake -DVCPKG_APPLOCAL_DEPS=OFF
sudo ln -s /usr/x86_64-w64-mingw32/lib/libopengl32.a /usr/x86_64-w64-mingw32/lib/libOpenGL32.a
make
```
