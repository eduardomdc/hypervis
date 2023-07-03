cmake_minimum_required(VERSION 3.26)
project(hypervis)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(MY_SOURCES
    src/main.cpp
    src/hyper.cpp
    src/draw.cpp
    src/geometry.cpp
    src/algebra.cpp
)

add_executable(hypervis ${MY_SOURCES})

target_link_libraries(hypervis ${SDL2_LIBRARIES})
