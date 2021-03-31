# Technical Documentation

Sokoban game design for the Motorola Science Cup 2020 competition
*Impostors* team

- Polish version of user documentation - [dok_uzyt](./dok_uzyt.md).
- English version of the user documentation - [doc_user](./doc_user.md).
- Polish version of technical documentation - [dok_tech](./dok_tech.md).

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
- cross-compilation for Windows via mingw(e.g. vcpkg sfml-audio pack was not correctly prepared, so we used soloud as music engine with backed-up sdl on linux and backed-up winmm on Windows)


***

#### The description of the functions used and their operation can be found in the comments in the code

***

### Repositories used

- VCPKG
- Nlohmann JSON
- SoLoud
- SFML
- NativeFileDialog
- Dear ImGui
- ImGui SFML Bindings
