cmake_minimum_required(VERSION 3.10)

# Get all source files
file(GLOB ALICEUI_SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/AliceUI/*.cpp")
file(GLOB ALICEUI_HEADER_FILES "${CMAKE_CURRENT_LIST_DIR}/AliceUI/*.h")

# Windows Only
if(WIN32)
    file(GLOB ALICEUI_WIN32_SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/AliceUI/win32/*.cpp")
    file(GLOB ALICEUI_WIN32_HEADER_FILES "${CMAKE_CURRENT_LIST_DIR}/AliceUI/win32/*.h")
endif()

# Generate AliceUI static library
add_library(AliceUI STATIC
    ${ALICEUI_SOURCE_FILES}
    ${ALICEUI_HEADER_FILES}
    ${ALICEUI_WIN32_SOURCE_FILES}
    ${ALICEUI_WIN32_HEADER_FILES})
target_link_libraries(AliceUI
    PUBLIC
        skia
        CONAN_PKG::glm
        CONAN_PKG::rapidjson
    PRIVATE
        CONAN_PKG::icu)
target_compile_features(AliceUI
    PUBLIC
        cxx_std_17)
target_include_directories(AliceUI
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/AliceUI
        ${CMAKE_CURRENT_LIST_DIR}/../include)

