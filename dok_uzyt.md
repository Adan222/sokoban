
#Dokumentacja użytkownika

Projekt gry Sokoban na konkurs Motorola Science Cup 2020 
zespół *Impostorzy*


English version of the documentation - [doc_user](./doc_user.md)
Dokumentacja techniczna dostępna jest w pliku [dok_tech](./dok_tech.md)


![logo](https://github.com/Adan222/sokoban/blob/master/res/graphics/game/player_all.png "Logo")

- ## Sokoban

Sokoban jest prostą grą logiczną typu łamigłówki, w której celem jest ustawienie skrzyń w zaznaczonych miejscach. Zadanie jest utrudnione poprzez wielokrotności skrzyń jak i złożoność labiryntu po którym się poruszamy. Trudność problemu zwiększa się wraz z twoim postępem.
Każdy poziom jest inny, więc będzie wymagał innej strategii.
***

- ## Zasady gry

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla a lobortis orci, sit amet malesuada justo. Nullam sagittis mauris purus, ut vehicula nibh lacinia id. Ut vitae suscipit metus. Vivamus enim nisl, pretium et fringilla et, porttitor eget nisi. Integer mollis rhoncus elementum. Duis a lacinia ipsum. Vivamus dapibus, nibh id porta fringilla, turpis lacus pretium ante, nec vestibulum tellus elit et massa. Mauris sodales, ligula eu imperdiet blandit, nunc massa posuere nisl, at vulputate odio ligula ac est.
***

- ## Przygotowanie gry

Aby uruchomić grę na systemach Windows wyszukujemy w folderze build plik **sokoban.exe**, podobnie jest w przypadku systemów opartych na Linuxie, z tego folderu uruchamiamy wówczas plik **sokoban**
***

- ## Kompilowanie
```sh
git clone https://github.com/Adan222/sokoban
cd sokoban
git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.sh -disableMetrics
git reset --hard 9f6aaaccb70d6f114a967f0ab83eff42840614ed
```

Wracamy do aktualizacji ImGui 1.81 przez resetowanie, ponieważ na mingw nowa wersja ma problem z linkowaniem IMM.
https://github.com/microsoft/vcpkg/issues/16964

Vcpkg potrzebuje powershell'a.
https://docs.microsoft.com/en-us/powershell/scripting/install/installing-powershell-core-on-linux?view=powershell-7.1

- ## Kompilowanie binarki dla Linuxa 
```sh
./vcpkg install sfml imgui imgui-sfml nlohmann-json nativefiledialog soloud
cd ..
mkdir -p build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
make

```
- ## Kompilowanie na Linuxie dla Windowsa
Jeżeli pojawią się jakiekolwiek problemy spróbuj ponownie uruchomić wykonać komendę `cmake`

```sh
./vcpkg install sfml imgui imgui-sfml nlohmann-json soloud --triplet x64-mingw-static
./vcpkg install nativefiledialog --head --triplet x64-mingw-static
cd ..
mkdir -p build && cd build
cmake .. -DVCPKG_TARGET_TRIPLET=x64-mingw-static -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=<absolute path to sokoban dir>/toolchain-mingw-x64.cmake -DVCPKG_APPLOCAL_DEPS=OFF
ln -s /usr/x86_64-w64-mingw32/lib/libopengl32.a /usr/x86_64-w64-mingw32/lib/libOpenGL32.a
make
```

- ## Jak grać

W grze poruszamy się buldożerem za pomocą klawiszy WSAD które odpowienio służą do poruszania się w górę, dół, lewo oraz prawo. Nasz buldożer przesuwa skrzynki które muszą trafić na miejsca zaznaczone krzyżykiem 





