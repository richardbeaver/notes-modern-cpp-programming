# Get name of executable from CMake build process
binary := `grep TARGET_NAME build/CMakeCache.txt | cut -d '=' -f2`

default:
    just --list

new-build: clean build

build:
    cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build
    cmake --build build --parallel

release-build:
    cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
    cmake --build build --parallel

run:
    ./build/{{binary}}

clean:
    rm -rf build
