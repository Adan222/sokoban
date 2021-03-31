# Dokumentacja techniczna

Projekt gry Sokoban na konkurs Motorola Science Cup 2020 
zespół *Impostorzy*

- Polska wersja dokumentacji użytkownika - [dok_uzyt](./dok_uzyt.md).
- English version of the user documentation - [doc_user](./doc_user.md).
- English version of technical documentation - [doc_tech](./doc_tech.md).

***
### Użyte języki 
- **C++20**
- **CMake**


***

### Napotkane problemy

- Kompilacja na systemach Windows
- Zmiana aktualizacji JSON'a
- Kompilacja na systamach Windows po rozszerzeniu projektu o SFX'y oraz muzykę
- Problemy kompilacyjne mingw
- Odrzucenie XML'a na rzecz JSON do kompliowania leveli
- Decyzja nad formatem tekstur, użycie tilemapy
- odpowiednie zarzadzanie pamięcią, semantyka przenoszenia
-  crosskompilacja do windowsa przy mingw(przykładowo paczka vcpkg sfml-audio jest nie prawidlowo przygotowana, dlatego     skorzystalismy z soloud jako silnika muzycznego z backedem na sdl na linuxie i backedem winmm na windowsie)
-  


***

#### Opis użytych funkcji oraz ich działanie znajduje się w komentarzach w kodzie 

***

### Użyte repozytoria

- VCPKG
- Nlohmann JSON
- SoLoud
- SFML
- NativeFileDialog
- Dear ImGui 
- ImGui SFML Bindings
