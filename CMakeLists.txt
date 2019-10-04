cmake_minimum_required(VERSION 3.15)

project(AliceUI
    VERSION 1.0.0
    LANGUAGES CXX)

# Build examples
option(ALICEUI_BUILD_EXAMPLES "Build glfw examples" OFF)

# Skia path
set(ALICEUI_SKIA_SOURCE_PATH "" CACHE PATH "Skia include path (e.g. .../skia)")
set(ALICEUI_SKIA_LIBRARY_PATH "" CACHE PATH "Skia library path (e.g. .../skia/out/dynamic")
option(ALICEUI_SKIA_IS_COMPONENT_BUILD "Skia is built with option 'is_component_build=true'" ON)
option(ALICEUI_BUILD_SHARED "Build as shared library" OFF)

# Setup conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(third_party)

add_subdirectory(src)

if(ALICEUI_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()
