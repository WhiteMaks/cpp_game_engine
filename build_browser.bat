set GAME_ENGINE_PLATFORM="BROWSER"
mkdir build
cd build
emsdk activate
emcmake cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release -- -j8