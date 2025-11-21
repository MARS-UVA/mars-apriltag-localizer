//
// Created by Ivan on 10/28/25.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#include "tagStandard41h12.h"
#include "wrapper.hpp"

int main(const int argc, const char* argv[]) {
    if (argc < 2) {
        std::cerr << "Camera id not specified" << std::endl;
        return 1;
    }
    const auto family = std::make_shared<apriltag::AprilTagFamily>(
        tagStandard41h12_create(), tagStandard41h12_destroy);
    apriltag::AprilTagDetector detector;
    detector.nthreads() = 8;
    detector.add_family(family);

    const int camera_index = static_cast<int>(std::strtol(argv[1], nullptr, 10));
    cv::VideoCapture capture {camera_index};
    if (!capture.isOpened()) {
        std::cerr << "Could not open camera" << std::endl;
        return 1;
    }

    cv::Mat frame;
    cv::namedWindow("camera", cv::WINDOW_NORMAL);
    cv::Mat gray_frame;
    while (true) {
        if (capture.read(frame)) {
            cv::imshow("camera", frame);
        }
        if (const int key = cv::waitKey(10); key == 'q') {
            break;
        }
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
        if (std::vector<apriltag::AprilTagDetection> detections = detector.detect(gray_frame); !detections.empty()) {
            std::cout << "Detected " << detections.size() << " AprilTags:\n";
            for (auto it = detections.cbegin(); it != detections.cend(); ++it) {
                std::cout
                    << "\tID "
                    << it->id()
                    << ": center at ("
                    << it->center()(0)
                    << ", "
                    << it->center()(1)
                    << ")\n";
            }
        }
    }
    cv::destroyAllWindows();
    return 0;
}