# Alice UI Framework

AliceUI is a widget based UI middleware which can be used with other windowing systems. 

# Building AliceUI

You can build AliceUI on Windows 7 or above with CMake

Build Step
1. Clone AliceUI codebase
2. Create CMake build target directory (e.g. `..../build/`) and go to directory
3. Run conan command to install third party libraries (e.g. conan install `..../build`)
4. Build or download recent skia library
5. Run cmake command to configure cmake project with following input path options
    - ALICEUI_SKIA_SOURCE_PATH : Path to skia source directory (e.g. `..../depot_tools/skia`)
    - ALICEUI_SKIA_LIBRARY_PATH : Path to skia build directory (e.g. `..../out/dynamic`)
6. Generate builder & compile

# Using AliceUI

Simple `Hello World` project is included with solution.

You can also see advanced project configurations in `example` directory.

# License

This project is licensed under the MIT license.

