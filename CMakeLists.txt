cmake_minimum_required(VERSION 3.15)
project(marslocalizer
        VERSION 0.0.1
        DESCRIPTION "A library for camera-based localization with AprilTags."
)

include(GNUInstallDirs)

find_package(apriltag REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(apriltag REQUIRED)

include_directories(
        include/marslocalizer
)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME}
        src/marslocalizer/family.cpp
        src/marslocalizer/detector.cpp
        src/marslocalizer/detection.cpp
        src/marslocalizer/overlays.cpp
)
add_executable(2d_detect
        examples/2d_detect.cpp
)
add_dependencies(2d_detect ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES
        PUBLIC_HEADER include/marslocalizer/wrapper.hpp
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
)
target_link_libraries(${PROJECT_NAME}
        PUBLIC apriltag
        PUBLIC Eigen3::Eigen
        PUBLIC ${OpenCV_LIBS}
)
target_link_libraries(2d_detect
        ${PROJECT_NAME}
)
configure_file(marslocalizer.pc.in marslocalizer.pc @ONLY)
install(
        TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
        TARGETS 2d_detect
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(
        FILES ${CMAKE_BINARY_DIR}/marslocalizer.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)