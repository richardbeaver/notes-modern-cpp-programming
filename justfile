default:
    just --list

new-build: clean build

build:
    cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build
    cmake --build build --parallel

release-build:
    cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
    cmake --build build --parallel

run binary:
    ./build/{{binary}}

clean:
    rm -rf build
