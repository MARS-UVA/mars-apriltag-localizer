#include "library.h"
#include "apriltag.h"

#include <iostream>

void hello() {
    apriltag_detector* detector = apriltag_detector_create();
    detector->nthreads = 2;
    apriltag_detector_detect(detector, nullptr);
    std::cout << "Hello, World!" << std::endl;
}