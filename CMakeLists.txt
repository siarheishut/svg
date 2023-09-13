cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)
project(Svg)

# svg config start
add_library(svg
        src/common.cpp
        src/document.cpp
        src/figures.cpp)

target_include_directories(svg PUBLIC include/svg)
# svg config end

# tests start
include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(googletest)


add_executable(svg_tests
        src/common.cpp
        src/figures.cpp
        src/document.cpp
        tests/figures_tests.cpp
)

target_link_libraries(svg_tests GTest::gtest_main)
target_include_directories(svg_tests PUBLIC . include/svg)
gtest_discover_tests(svg_tests)
# tests end
