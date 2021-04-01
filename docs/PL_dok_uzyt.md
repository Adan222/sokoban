
## Dokumentacja użytkownika

![icon](https://github.com/Adan222/sokoban/blob/master/res/graphics/icon3.png "Icon")<br>
Projekt gry Sokoban na konkurs Motorola Science Cup 2020 
zespół *Impostorzy*



- English version of the documentation - [ENG_doc_user](./ENG_doc_user.md).
- Polska wersja dokumentacji technicznej - [PL_dok_tech](./PL_dok_tech.md).
- English version of the technical documentation - [ENG_doc_tech](./ENG_doc_tech.md).




![logo](https://github.com/Adan222/sokoban/blob/master/res/graphics/game/player.png "Logo")

 ## Autorzy 
- Kacper Kosmal
    * Twórca kodu
- Kamil Fugiel 
    * Twórca kodu
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

Buldożerem poruszamy się za pomocą klawiszy <kbd>W</kbd><kbd>S</kbd><kbd>A</kbd><kbd>D</kbd>, które odpowienio służą do poruszania się w górę, dół, lewo oraz prawo.
Aby wyjśc do menu będąc na poziomie mapy naciśnij klawisz <kbd>ESC</kbd>.

- ## Menu <br>
#### Przycisk <kbd style="background-color: red; color:white"> Graj</kbd> 
Przenosi nas w miejsce wyboru losowego poziomu z podziałem na poziom trudności: łatwy, średni, trudny. W tym miejscu możemy również wybrać <kbd style="background-color: red; color:white">All lvls</kbd> i wybrać który dokładnie poziom chcemy spróbować przejść. Przycisk <kbd style="background-color: lightblue;">Editor</kbd> przenosi nas do edytora map w którym możemy tworzyć własne mapy a także edytować już istniejące. Aby wyjść do menu głównego kliknij strzałkę w lewym, górnym rogu.
Zapis gry działa tylko w trybie <kbd style="background-color: red; color:white">All lvls</kbd>, po zapisaniu gry możemy użyć opcji kontynuuj lub wczytać zapisane poziomy.

#### Przycisk <kbd style="background-color: red; color:white"> Leaderboard</kbd> 
W tym miejscu możemy zobaczyć nasze wyniki z wszystkich map. Aby wyjść do menu głównego kliknij strzałkę w lewym, górnym rogu.

#### Przycisk <kbd style="background-color: red; color:white"> Exit</kbd> 
Przycisk ten służy do wyłączenia gry, aby to zrobić możemy również użyć klawisza <kbd> ESC</kbd> 
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







