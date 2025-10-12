# Ex:
# - Build one executable  - `just b basic_concepts_i`
# - Build all             - `just ba`
# - Run one executable    - `just r basic_concepts_i`
# - Build and run one     - `just br basic_concepts_ii`

default:
	just --list


alias br := build-and-run
build-and-run executable:
	just build {{executable}}
	just run {{executable}}


# Build

alias b := build
build executable:
	cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/debug --parallel --target {{executable}}

alias ba := build-all
build-all:
	cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/debug --parallel

build-release executable:
	cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release
	cmake --build build/release --parallel {{executable}}


# Run

alias r := run
run executable:
	./build/debug/bin/{{executable}}

run-release executable:
	./build/release/bin/{{executable}}


# Clean

clean:
	rm -rf build/debug

clean-release:
	rm -rf build/release
