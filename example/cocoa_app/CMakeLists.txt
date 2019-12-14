
project(cocoa_app
    VERSION 0.0.1)

file(GLOB ALICEUI_COCOA_APP_HEADER_FILES ${CMAKE_CURRENT_LIST_DIR}/*.h)
file(GLOB ALICEUI_COCOA_APP_SOURCE_FILES ${CMAKE_CURRENT_LIST_DIR}/*.mm)

find_library(AppKit AppKit)
find_library(Foundation Foundation)

add_executable(cocoa_app MACOSX_BUNDLE
    ${ALICEUI_COCOA_APP_HEADER_FILES}
    ${ALICEUI_COCOA_APP_SOURCE_FILES}
    MainMenu.xib)

target_link_libraries(cocoa_app
    PRIVATE
        AliceUI
        ${AppKit}
        ${Foundation})

set_target_properties(cocoa_app PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_LIST_DIR}/plist.in)

set_source_files_properties(MainMenu.xib PROPERTIES
    MACOSX_PACKAGE_LOCATION Resources)

set_source_files_properties(${ALICEUI_COCOA_APP_SOURCE_FILES} PROPERTIES
    COMPILE_FLAGS "-fobjc-arc")

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
