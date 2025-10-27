cmake_minimum_required(VERSION 3.15)
project(mars_apriltag_localizer)

find_package(apriltag REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_library(marslocalizer SHARED library.cpp)

target_link_libraries(marslocalizer apriltag)
