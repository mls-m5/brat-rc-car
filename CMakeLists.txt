
project(rc-car)
cmake_minimum_required(VERSION 3.23)

add_subdirectory(
    simulator/lib/sdlpp
    simulator/lib/glm
    )

add_executable(
    gui
    simulator/gui.cpp
    simulator/guiudp.cpp
    )

target_include_directories(
    gui
    PRIVATE
    mockincludes/
    #${GLM_INCLUDE_DIRS}"
    )

target_link_libraries(
    gui
    PRIVATE
    sdlpp
    )


find_package (Threads)
target_link_libraries (
    gui
    PRIVATE
    ${CMAKE_THREAD_LIBS_INIT}
    )
