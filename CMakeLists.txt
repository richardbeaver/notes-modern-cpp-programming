# === Project Settings ===

set(PROJECT_NAME "modern-cpp-programming-federico-busato")
set(CXX_STANDARD 26)
set(MINIMUM_CMAKE_VERSION 3.16)

set(SUBDIRECTORIES
  basic_concepts_i
  basic_concepts_ii
  basic_concepts_iii
  basic_concepts_iv
  basic_concepts_v
  oop_i
  oop_ii
  templates_metaprogramming_i
)


# ===
# ===

# === CMake Initialization ===

cmake_minimum_required(VERSION ${MINIMUM_CMAKE_VERSION})
project(${PROJECT_NAME} CXX)


# === Global Configuration ===

set(CMAKE_CXX_STANDARD ${CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Use Debug build by default if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Enable compile_commands.json for tooling (e.g. clangd, LSPs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# === Project-Wide Compiler Options ===

# (Not necessarily best practice for real projects)

add_compile_options(
  -Wall
  -Wextra
  # -Werror
  -pedantic
  -pedantic-errors
  -Wconversion
  -Wsign-conversion
  # -fsanitize=address
  # -fsanitize=leak
  # -fsanitize=undefined
)

# add_link_options(
#   -fsanitize=address
#   -fsanitize=leak
#   -fsanitize=undefined
# )

# === Add Subdirectories ===

foreach(subdir IN ITEMS ${SUBDIRECTORIES})
  add_subdirectory(src/${subdir})
endforeach()
