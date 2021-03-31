# Technical Documentation

Sokoban game design for the Motorola Science Cup 2020 competition
*Impostors* team

- Polish version of user documentation - [PL_dok_uzyt](./PL_dok_uzyt.md).
- English version of the user documentation - [ENG_doc_user](./ENG_doc_user.md).
- Polish version of technical documentation - [PL_dok_tech](./PL_dok_tech.md).

***
### Languages ​
- **C++20**
- **CMake**


***

### Problems encountered

- Compilation on Windows systems
- JSON update changed
- Compilation on Windows systems after extending the project with SFX and music
- Mingw compilation problems
- XML ​​rejection in favor of JSON for level compilation
- Texture format decision, use of tilemap
- Proper cache menagment, move semantics
- cross-compilation for Windows via mingw(e.g. vcpkg sfml-audio pack was not correctly prepared, so we used soloud as audio engine with backed-up sdl on linux and backed-up winmm on Windows)


***

#### The description of the functions used and their operation can be found in the comments in the code

***
#### For the saving system and for levels we used JSON, in the editor mode we implemented Immediate Mode GUI

### Repositories used

- **VCPKG** | https://github.com/microsoft/vcpkg.git
- **Nlohmann JSON** | https://github.com/nlohmann/json.git
- **SoLoud** | https://github.com/jarikomppa/soloud.git
- **SFML** | https://github.com/SFML/SFML.git
- **NativeFileDialog** | https://github.com/mlabbe/nativefiledialog.git
- **Dear ImGui** | https://github.com/ocornut/imgui.git
- **ImGui SFML Bindings** | https://github.com/eliasdaler/imgui-sfml.git
