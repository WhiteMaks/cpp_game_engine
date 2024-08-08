$env:GAME_ENGINE_PLATFORM="BROWSER"
mkdir build
cd build
$env:path
../emsdk/emsdk.exe activate
emcmake cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release -- -j8
pause