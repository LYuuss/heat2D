cmake_minimum_required(VERSION 3.16)

project(Heat2D LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

include_directories(include)

add_executable(heat2d
    src/main.cpp
    src/Grid.cpp
    src/HeatSolver.cpp
)

target_link_libraries(heat2d PRIVATE Threads::Threads)