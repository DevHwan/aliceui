cmake_minimum_required(VERSION 3.10)

file(GLOB ALICEUI_GLFW_SAMPLE_HEADER_FILES ${CMAKE_CURRENT_LIST_DIR}/*.h)
file(GLOB ALICEUI_GLFW_SAMPLE_SOURCE_FILES ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_executable(glfw_sample_app
    ${ALICEUI_GLFW_SAMPLE_HEADER_FILES}
    ${ALICEUI_GLFW_SAMPLE_SOURCE_FILES})
target_link_libraries(glfw_sample_app
    PRIVATE
        AliceUI
        CONAN_PKG::glfw
        CONAN_PKG::glew)

if(ALICEUI_SKIA_IS_COMPONENT_BUILD)
    get_target_property(ALICEUI_SKIA_COMPONENT_PATH skia IMPORTED_LOCATION)
    if(ALICEUI_SKIA_COMPONENT_PATH)
        message(STATUS "Now copying skia shared library...")
        message(STATUS "    - component path : ${ALICEUI_SKIA_COMPONENT_PATH}")
        message(STATUS "    - copying to : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
        file(COPY ${ALICEUI_SKIA_COMPONENT_PATH} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endif()
endif()
