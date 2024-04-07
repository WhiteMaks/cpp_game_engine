# cpp_game_engine
Game engine for creating 2D/3D games written in C++

## Related

Here are some related projects

* [GLAD](https://glad.dav1d.de/) is used to access the OpenGL function.
* [spdlog](https://github.com/gabime/spdlog.git) is used to display logs (connected as a git submodule to the project).
* [SDL](https://github.com/libsdl-org/SDL.git) is used to bind a window to convas in HTML (connected as a git submodule to the project).

## Features

Platforms:
- [x]  Windows
- [x]  Browser
- [ ]  Linux
- [ ]  MacOS

Graphics API:
- [x]  OpenGL
- [x]  WebGL
- [x]  DirectX 11
- [x]  DirectX 12
- [ ]  Metal
- [ ]  Vulkan

## Installation

Install CMake (for build project) https://cmake.org/

Install Emscripten (for compile the project in WASM) https://emscripten.org/   

## Run Locally

Clone the project

```bash
  git clone --recurse-submodules https://github.com/WhiteMaks/cpp_game_engine.git
```

Go to the project directory

```bash
  cd cpp_game_engine
```

Build solution

```bash
  build_windows.bat
```
The solution will be in the build folder