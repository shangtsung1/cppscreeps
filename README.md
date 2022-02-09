# cppscreeps

# Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git
# Enter that directory
cd emsdk
git pull
# Download and install the latest SDK tools.
./emsdk install latest
# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate latest
# Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh
# set #DEFINE USERNAME game_name
export USERNAME=game_name
# set source files.
./SourceFileList.sh
# compile
emcc --std=c++11 --bind -D$USERNAME -Wno-c++1z-extensions -gsource-map -s FILESYSTEM=0 -s BINARYEN_ASYNC_COMPILATION=0 -s ENVIRONMENT=shell -s ERROR_ON_UNDEFINED_SYMBOLS=1 -s ASSERTIONS=1 -s WASM=1 -s DISABLE_EXCEPTION_CATCHING=0 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=2 -s MODULARIZE=1 -s ALLOW_MEMORY_GROWTH=1 -Iinclude -Ilib -O1 -Wall -pedantic -s DEMANGLE_SUPPORT=1 $SRC_FILES -o build\loop.js
# copy
Copy dist folder contents to Screeps script folder.
