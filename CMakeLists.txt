cmake_minimum_required(VERSION 3.15)
project(marslocalizer
        VERSION 0.0.1
        DESCRIPTION "A library for camera-based localization with AprilTags."
)

include(GNUInstallDirs)

find_package(apriltag REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)
find_package(OpenCV REQUIRED)

include_directories(
        include/marslocalizer
        include/apriltag
        ${OpenCV_INCLUDE_DIRS}
)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME}
        src/marslocalizer/main.cpp
)
set_target_properties(${PROJECT_NAME} PROPERTIES
        PUBLIC_HEADER include/marslocalizer/wrapper.hpp
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
)
target_link_libraries(${PROJECT_NAME}
        apriltag
        Eigen3::Eigen
        ${OpenCV_LIBS}
)
configure_file(marslocalizer.pc.in marslocalizer.pc @ONLY)
install(
        TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIB_DIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
        FILES ${CMAKE_BINARY_DIR}/marslocalizer.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)