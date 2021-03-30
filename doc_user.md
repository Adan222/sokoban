
#User documentation

Sokoban game design for the Motorola Science Cup 2020 competition
*Impostors* team

Polska wersja dokumentacji - [dok_uzyt](./dok_uzyt.md).
Technical documentation is available in the file [dok_tech](./dok_tech.md).


![logo](https://github.com/Adan222/sokoban/blob/master/res/graphics/game/player_all.png "Logo")

- ## Sokoban

Sokoban is a simple puzzle-type puzzle game in which the goal is to place the crates in the marked places. The task is made difficult by the multiple crates and the complexity of the labyrinth in which we are moving. The difficulty of the problem increases as you progress.
Each level is different so will require a different strategy.
***

- ## Game rules

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla a lobortis orci, sit amet malesuada justo. Nullam sagittis mauris purus, ut vehicula nibh lacinia id. Ut vitae suscipit metus. Vivamus enim nisl, pretium et fringilla et, porttitor eget nisi. Integer mollis rhoncus elementum. Duis a lacinia ipsum. Vivamus dapibus, nibh id porta fringilla, turpis lacus pretium ante, nec vestibulum tellus elit et massa. Mauris sodales, ligula eu imperdiet blandit, nunc massa posuere nisl, at vulputate odio ligula ac est.
***

- ## Preparing the game

To run the game on Windows systems, search for the file **sokoban.exe** in the build folder, similarly to Linux-based systems, then run the file **sokoban** from this folder.
***

- ## Building
```sh
git clone https://github.com/Adan222/sokoban
cd sokoban
git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.sh -disableMetrics
git reset --hard 9f6aaaccb70d6f114a967f0ab83eff42840614ed
```

We are reverting to ImGui 1.81 by reseting, because on mingw new version have problem with IMM linking. See https://github.com/microsoft/vcpkg/issues/16964

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

- ## How to play

In the game, we move the bulldozer with the WSAD keys, which are used to move up, down, left and right respectively.





