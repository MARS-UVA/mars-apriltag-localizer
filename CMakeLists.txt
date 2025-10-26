cmake_minimum_required(VERSION 4.0)
project(mars_apriltag_localizer)

set(CMAKE_CXX_STANDARD 20)

add_library(marslocalizer SHARED library.cpp)
