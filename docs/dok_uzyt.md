
#Dokumentacja użytkownika

Projekt gry Sokoban na konkurs Motorola Science Cup 2020 
zespół *Impostorzy*


English version of the documentation - [doc_user](./docs/doc_user.md).
Polska wersja dokumentacji technicznej - [dok_tech](./docs/dok_tech.md).
English version of the technical documentation - [doc_tech](./docs/doc_tech.md).




![logo](https://github.com/Adan222/sokoban/blob/master/res/graphics/game/player.png "Logo")

 ## Autorzy 
- Kacper Kosmal
    * 
    * 
- Kamil Fugiel 
    * 
    * 
- Bartłomiej Kuleta 
    * Tekstury
    * Projektowanie poziomów
    * Loga
- Karol Basak 
    * Muzyka 
    * Dźwięki 
    * Testy
- Konrad Ucisko
    * Tekstury 
    * Projektowanie poziomów
    * Dokumentacja


***

- ## Sokoban

Sokoban jest prostą grą logiczną typu łamigłówki, w której celem jest ustawienie skrzyń w zaznaczonych miejscach. Zadanie jest utrudnione poprzez wielokrotności skrzyń jak i złożoność labiryntu po którym się poruszamy. Trudność problemu zwiększa się wraz z twoim postępem.
Każdy poziom jest inny, więc będzie wymagał innej strategii.
***

- ## Zasady gry

Kierujesz buldożerem ustawiającym skrzynki, przy jak najmniejszej liczbie ruchów umieść skrzynki w wyznaczonych miejscach, od liczby wykonanych ruchów będzie zależał twój wynik. Skrzynki możesz jedynie przesuwać przodem buldożera (łopatą), kierując buldożerem pamiętaj, że możesz przesunąć tylko jedną skrzynkę na raz. Przed tobą 20 poziomów z różnym poziomem trudności. Powodzenia!
***

- ## Jak grać

Buldożerem poruszamy się za pomocą klawiszy WSAD które odpowienio służą do poruszania się w górę, dół, lewo oraz prawo.
Aby wyjśc do menu naciśnij klawisz ESC.
***

- ## Przygotowanie gry

Aby uruchomić grę na systemach Windows wyszukujemy w folderze build plik **sokoban.exe**, podobnie jest w przypadku systemów opartych na Linuxie, z tego folderu uruchamiamy wówczas plik **sokoban**.
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







