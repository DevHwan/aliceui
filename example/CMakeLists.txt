cmake_minimum_required(VERSION 3.10)

add_subdirectory(glfw_sample_app)

if(APPLE)
    add_subdirectory(glfw_sample_metal_app)
endif()
