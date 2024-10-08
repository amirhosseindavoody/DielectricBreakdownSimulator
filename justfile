build-dir := "build"
export CONAN_HOME := justfile_directory() / ".conan"

default:
    @just --choose

clean:
    rm -rf ./{{ build-dir }}

justfile-format:
    just --fmt --unstable

cmake-format: justfile-format
    cmake-format CMakeLists.txt -i

conan-profile: cmake-format
    conan profile detect --force

conan-install: conan-profile
    conan install . --output-folder=build --build=missing

conan-generate: conan-install
    cmake -G Ninja -B ./{{ build-dir }} -S . -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release

build-all: conan-generate
    cd {{ build-dir }} && ninja

test-all: build-all
    cd {{ build-dir }} && ctest -C Debug

# Runs a single test module like this: MainTest
test-one test_name: build-all
    cd {{ build-dir }} && ctest -C Debug -R "{{ test_name }}"
