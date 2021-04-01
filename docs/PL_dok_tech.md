# Dokumentacja techniczna

Projekt gry Sokoban na konkurs Motorola Science Cup 2020 
zespół *Impostorzy*

- Polska wersja dokumentacji użytkownika - [PL_dok_uzyt](./PL_dok_uzyt.md).
- English version of the user documentation - [ENG_doc_user](./ENG_doc_user.md).
- English version of technical documentation - [ENG_doc_tech](./ENG_doc_tech.md).

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
 


***

#### Opis użytych funkcji oraz ich działanie znajduje się w komentarzach w kodzie 

***
#### Do systemów zapisu oraz do poziomów użyliśmy formatu JSON, w edytorze skorzystaliśmy z rozwiązania Immediate Mode GUI

### Użyte repozytoria

- **VCPKG** | https://github.com/microsoft/vcpkg.git
- **Nlohmann JSON** | https://github.com/nlohmann/json.git
- **SoLoud** | https://github.com/jarikomppa/soloud.git
- **SFML** | https://github.com/SFML/SFML.git
- **NativeFileDialog** | https://github.com/mlabbe/nativefiledialog.git
- **Dear ImGui** | https://github.com/ocornut/imgui.git
- **ImGui SFML Bindings** | https://github.com/eliasdaler/imgui-sfml.git

### Czcionki 

- **Minecraft** by Craftron Gaming [Minecraft](https://www.dafont.com/minecraft.font)
- **VT323** Designed by Peter Hull [VT323](https://fonts.google.com/specimen/VT323?preview.text_type=custom#standard-styles)

