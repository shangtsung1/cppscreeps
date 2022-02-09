call emcc --std=c++11 --bind -D%USERNAME% -Wno-c++1z-extensions -gsource-map -s FILESYSTEM=0 -s BINARYEN_ASYNC_COMPILATION=0 -s ENVIRONMENT=shell -s ERROR_ON_UNDEFINED_SYMBOLS=1 -s ASSERTIONS=1 -s WASM=1 -s DISABLE_EXCEPTION_CATCHING=0 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=2 -s MODULARIZE=1 -s ALLOW_MEMORY_GROWTH=1 -Iinclude -Ilib -O1 -Wall -pedantic -s DEMANGLE_SUPPORT=1 %SRC_FILES% -o build\loop.js

Xcopy /Y build\loop.wasm dist\loop.wasm
Xcopy /Y build\loop.js dist\loop_mod.js
Xcopy /Y src\main.js dist\main.js
Xcopy /Y src\proto.js dist\proto.js
Xcopy /Y src\Traveler.js dist\Traveler.js
Xcopy /Y src\wasm_loader.js dist\wasm_loader.js
