default:
	just --list

new-build-debug: clean-debug build-debug
new-build-release: clean-release build-release

build-and-run executable:
	just build-debug
	just run-debug {{executable}}

# Build
build-debug:
	cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/debug --parallel

build-release:
	cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release
	cmake --build build/release --parallel

# Run
run-debug executable:
	./build/debug/bin/{{executable}}

run-release executable:
	./build/release/bin/{{executable}}

# Clean
clean-debug:
	rm -rf build/debug

clean-release:
	rm -rf build/release
