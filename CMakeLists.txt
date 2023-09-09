cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)
project(Svg)

# svg config start
add_library(svg
        src/common.cpp
        src/document.cpp
        src/figures.cpp)

target_include_directories(svg PUBLIC include)
# svg config end
