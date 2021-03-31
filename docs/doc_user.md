
#User documentation

![icon](https://github.com/Adan222/sokoban/blob/master/res/graphics/icon2.png "Icon")<br>
Sokoban game designed for the Motorola Science Cup 2020 competition
*Impostors* team

- Polish version of user documentation - [dok_uzyt](./dok_uzyt.md).
- English version of technical documentation - [doc_tech](./doc_tech.md).
- Polish version of technical documentation - [dok_tech](./dok_tech.md).


![logo](https://github.com/Adan222/sokoban/blob/master/res/graphics/game/player.png "Logo")

## Authors
- Kacper Kosmal
    * Code creator
- Kamil Fugiel
    * Code creator
- Bartłomiej Kuleta
    * Textures
    * Level design
    * Logos
- Karol Basak
    * Music
    * Sounds
    * Tests
- Konrad Ucisko
    * Textures
    * Level design
    * Documentation
***

- ## Sokoban

Sokoban is a simple puzzle-type game which the goal is to place the crates in the marked places. The task is more difficult than it looks like because of multiple boxes and the intricacy of the labyrinth the game takes place in. The difficulty of the problem increases as you progress with levels.
Each level is unique and require a different strategy.
***

- ## Game rules
You control the bulldozer that push the boxes, with as few moves as possible place crates in the marked places, your score depend on the number of moves you make. You can only move the boxes with the front of the bulldozer (shovel), while driving the bulldozer remember that you can only move one box at the same time. There are 20 official map from us  with different levels of difficulty(Easy, Medium, Hard). Good luck!
***

- ## How to play

We move the bulldozer with the <kbd>W</kbd><kbd>S</kbd><kbd>A</kbd><kbd>D</kbd> keys, which are used to move up (W), down (S), left (A) and right (D).
For main menu press <kbd>ESC</kbd>.


- ## Menu <br>
#### Button <kbd style="background-color: red; color:white"> Graj</kbd> 
Przenosi nas w miejsce wyboru losowego poziomu z podziałem na poziom trudności: łatwy, średni, trudny. W tym miejscu możemy również wybrać <kbd style="background-color: red; color:white">All lvls</kbd> i wybrać który dokładnie poziom chcemy spróbować przejść. Przycisk <kbd style="background-color: lightblue;">Editor</kbd> przenosi nas do edytora map w którym możemy tworzyć własne mapy a także edytować już istniejące. Aby wyjść do menu głównego kliknij strzałkę w lewym, górnym rogu.

#### Button <kbd style="background-color: red; color:white"> Leaderboard</kbd> 
W tym miejscu możemy zobaczyć nasze wyniki z wszystkich map. Aby wyjść do menu głównego kliknij strzałkę w lewym, górnym rogu.

#### Button <kbd style="background-color: red; color:white"> Exit</kbd> 
Przycisk ten służy do wyłączenia gry, aby to zrobić możemy również użyć klawisza <kbd> ESC</kbd> 

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
If any error occures during `cmake` command(eg. freetype missing), please try rerunning.

```sh
./vcpkg install sfml imgui imgui-sfml nlohmann-json soloud --triplet x64-mingw-static
./vcpkg install nativefiledialog --head --triplet x64-mingw-static
cd ..
mkdir -p build && cd build
cmake .. -DVCPKG_TARGET_TRIPLET=x64-mingw-static -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=<absolute path to sokoban dir>/toolchain-mingw-x64.cmake -DVCPKG_APPLOCAL_DEPS=OFF
ln -s /usr/x86_64-w64-mingw32/lib/libopengl32.a /usr/x86_64-w64-mingw32/lib/libOpenGL32.a
make
```







