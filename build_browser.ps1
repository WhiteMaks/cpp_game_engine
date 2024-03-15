$env:GAME_ENGINE_PLATFORM="BROWSER"
mkdir build
cd build
emsdk activate
emcmake cmake ..
cmake --build .
pause