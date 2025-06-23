# === Project Settings ===

set(PROJECT_NAME "modern-cpp-programming-federico-busato")
set(CXX_STANDARD 20)
set(MINIMUM_CMAKE_VERSION 3.16)

set(EXECUTABLES
  data_types
)


# ===
# ===

# === CMake Initialization ===

cmake_minimum_required(VERSION ${MINIMUM_CMAKE_VERSION})
project(${PROJECT_NAME} CXX)


# === Build Configuration ===

set(CMAKE_CXX_STANDARD ${CXX_STANDARD})

# Use Debug build by default if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Enable compile_commands.json for tooling (e.g. clangd, LSPs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# === Targets ===

foreach(target IN ITEMS ${EXECUTABLES})
  add_executable(${target} src/${target}.cpp)
  target_compile_options(${target}
    PRIVATE
      -Wall
      -Wextra
      -Werror
      -pedantic
      -pedantic-errors
      -Wconversion
      -Wsign-conversion
  )
endforeach()

