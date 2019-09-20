cmake_minimum_required(VERSION 3.10)

project(AliceUI
    VERSION 1.0.0
    LANGUAGES CXX)

# Build examples
option(ALICEUI_BUILD_EXAMPLE_GLFW "Build examples" OFF)

# Setup conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(third_party)

add_subdirectory(src)

if(ALICEUI_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()
