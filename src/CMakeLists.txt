cmake_minimum_required(VERSION 3.10)

# Get all source files
file(GLOB ALICEUI_SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/AliceUI/*.cpp")
file(GLOB ALICEUI_HEADER_FILES "${CMAKE_CURRENT_LIST_DIR}/AliceUI/*.h")

# Platform attachments
if(WIN32)
    file(GLOB ALICEUI_PLATFORM_SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/AliceUI/win32/*.cpp")
    file(GLOB ALICEUI_PLATFORM_HEADER_FILES "${CMAKE_CURRENT_LIST_DIR}/AliceUI/win32/*.h")
    file(GLOB ALICEUI_PLATFORM_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/AliceUI/win32")
elseif(APPLE)
    file(GLOB ALICEUI_PLATFORM_SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/AliceUI/darwin/*.mm")
    file(GLOB ALICEUI_PLATFORM_HEADER_FILES "${CMAKE_CURRENT_LIST_DIR}/AliceUI/darwin/*.h")
    file(GLOB ALICEUI_PLATFORM_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/AliceUI/darwin")
endif()

# Generate AliceUI static library
if(ALICEUI_BUILD_SHARED)
    add_library(AliceUI SHARED
        ${ALICEUI_SOURCE_FILES}
        ${ALICEUI_HEADER_FILES}
        ${ALICEUI_PLATFORM_SOURCE_FILES}
        ${ALICEUI_PLATFORM_HEADER_FILES})
    target_compile_definitions(AliceUI
        PUBLIC
            ALICEUI_SHARED=1
        PRIVATE
            ALICEUI_EXPORTS=1)
else()
    add_library(AliceUI STATIC
        ${ALICEUI_SOURCE_FILES}
        ${ALICEUI_HEADER_FILES}
        ${ALICEUI_PLATFORM_SOURCE_FILES}
        ${ALICEUI_PLATFORM_HEADER_FILES})
    target_compile_definitions(AliceUI
        PUBLIC
            ALICEUI_STATIC=1)
endif()
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
        ${CMAKE_CURRENT_LIST_DIR}/../include
        ${ALICEUI_PLATFORM_INCLUDE_DIR})

