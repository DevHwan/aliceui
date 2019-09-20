cmake_minimum_required(VERSION 3.10)

# Skia path
set(ALICEUI_SKIA_SOURCE_PATH "" CACHE PATH "Skia include path (e.g. .../skia)")
set(ALICEUI_SKIA_LIBRARY_PATH "" CACHE PATH "Skia library path (e.g. .../skia/out/static")
option(ALICEUI_SKIA_IS_COMPONENT_BUILD "Skia is built with option 'is_component_build=true'" ON)

message(STATUS "Skia configurations...")
message(STATUS "    - source path : " ${ALICEUI_SKIA_SOURCE_PATH})
message(STATUS "    - library path : " ${ALICEUI_SKIA_LIBRARY_PATH})
message(STATUS "    - is component? : " ${ALICEUI_SKIA_IS_COMPONENT_BUILD})

if(ALICEUI_SKIA_IS_COMPONENT_BUILD)
    add_library(skia SHARED IMPORTED GLOBAL)
else()
    add_library(skia STATIC IMPORTED GLOBAL)
endif()
target_include_directories(skia
    INTERFACE
        ${ALICEUI_SKIA_SOURCE_PATH}
        ${ALICEUI_SKIA_SOURCE_PATH}/include
        ${CMAKE_CURRENT_LIST_DIR})
target_link_directories(skia
    INTERFACE ${ALICEUI_SKIA_LIBRARY_PATH})
target_link_libraries(skia
    INTERFACE skia)
