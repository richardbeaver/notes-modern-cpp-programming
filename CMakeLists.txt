# === Project Settings ===

set(PROJECT_NAME "project_template")
set(TARGET_NAME "main" CACHE STRING "The name of the executable")
set(CXX_STANDARD 20)
set(MINIMUM_CMAKE_VERSION 3.16)

# List of source files
set(SOURCE_FILES
  src/main.cpp
  src/greeting.cpp
)

# List of include directories
set(INCLUDE_DIRS
  ${CMAKE_SOURCE_DIR}/include
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

add_executable(${TARGET_NAME} ${SOURCE_FILES})
target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIRS})

# Add compiler warnings
target_compile_options(${TARGET_NAME}
  PRIVATE
    -Wall
    -Wextra
    -Werror
    -pedantic
    -pedantic-errors
    -Wconversion
    -Wsign-conversion
)
