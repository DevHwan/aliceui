cmake_minimum_required(VERSION 3.10)

project(glfw_sample_app
    LANGUAGES CXX
    VERSION 0.0.1)

file(GLOB ALICEUI_GLFW_SAMPLE_HEADER_FILES ${CMAKE_CURRENT_LIST_DIR}/*.h)
file(GLOB ALICEUI_GLFW_SAMPLE_SOURCE_FILES ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_executable(glfw_sample_app
    ${ALICEUI_GLFW_SAMPLE_HEADER_FILES}
    ${ALICEUI_GLFW_SAMPLE_SOURCE_FILES})
target_link_libraries(glfw_sample_app
    PRIVATE
        AliceUI
        CONAN_PKG::glfw
        CONAN_PKG::glew
        CONAN_PKG::glm)

if(ALICEUI_SKIA_IS_COMPONENT_BUILD)
    if(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
        set(ALICEUI_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    else()
        set(ALICEUI_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    endif()
    get_target_property(ALICEUI_SKIA_COMPONENT_PATH skia IMPORTED_LOCATION)
    if(ALICEUI_SKIA_COMPONENT_PATH)
        message(STATUS "Now copying skia shared library...")
        message(STATUS "    - component path : ${ALICEUI_SKIA_COMPONENT_PATH}")
        message(STATUS "    - copying to : ${ALICEUI_RUNTIME_OUTPUT_DIRECTORY}")
        file(COPY ${ALICEUI_SKIA_COMPONENT_PATH} DESTINATION ${ALICEUI_RUNTIME_OUTPUT_DIRECTORY})
    endif()
endif()
