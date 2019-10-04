cmake_minimum_required(VERSION 3.15)

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

if(ALICEUI_SKIA_IS_COMPONENT_BUILD)
    if(WIN32)
        set_target_properties(skia PROPERTIES
            IMPORTED_LOCATION ${ALICEUI_SKIA_LIBRARY_PATH}/skia.dll
            IMPORTED_IMPLIB   ${ALICEUI_SKIA_LIBRARY_PATH}/skia.dll.lib)
    elseif(UNIX)
        set_target_properties(skia PROPERTIES
            IMPORTED_LOCATION ${ALICEUI_SKIA_LIBRARY_PATH}/libskia.so)
    endif()
else()
    if(WIN32)
        set_target_properties(skia PROPERTIES
            IMPORTED_IMPLIB   ${ALICEUI_SKIA_LIBRARY_PATH}/skia.lib)
    elseif(UNIX)
        set_target_properties(skia PROPERTIES
            IMPORTED_IMPLIB   ${ALICEUI_SKIA_LIBRARY_PATH}/libskia.a)
    endif()
endif()
