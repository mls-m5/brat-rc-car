
project(rc-car)
cmake_minimum_required(VERSION 3.23)

add_subdirectory(
    simulator/lib/sdlpp
    )

add_executable(
    gui
    simulator/gui.cpp
    src/main.cpp
    )

target_include_directories(
    gui
    PRIVATE
    mockincludes/
    )

target_link_libraries(
    gui
    PRIVATE
    sdlpp
    )
