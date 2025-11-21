#include <exception>

#include "wrapper.hpp"

// Accessors

const int &apriltag::AprilTagDetector::nthreads() const {
    return _detector->nthreads;
}

int &apriltag::AprilTagDetector::nthreads() {
    return _detector->nthreads;
}

const float &apriltag::AprilTagDetector::quad_decimate() const {
    return _detector->quad_decimate;
}

float &apriltag::AprilTagDetector::quad_decimate() {
    return _detector->quad_decimate;
}

const float &apriltag::AprilTagDetector::quad_sigma() const {
    return _detector->quad_sigma;
}

float &apriltag::AprilTagDetector::quad_sigma() {
    return _detector->quad_sigma;
}

const bool &apriltag::AprilTagDetector::refine_edges() const {
    return _detector->refine_edges;
}

bool &apriltag::AprilTagDetector::refine_edges() {
    return _detector->refine_edges;
}

const double &apriltag::AprilTagDetector::decode_sharpening() const {
    return _detector->decode_sharpening;
}

double &apriltag::AprilTagDetector::decode_sharpening() {
    return _detector->decode_sharpening;
}

const bool &apriltag::AprilTagDetector::debug() const {
    return _detector->debug;
}

bool &apriltag::AprilTagDetector::debug() {
    return _detector->debug;
}

void apriltag::AprilTagDetector::add_family(const std::shared_ptr<AprilTagFamily> &family) {
    apriltag_detector_add_family(raw(), family->raw());
    _families.push_back(family);
}

void apriltag::AprilTagDetector::remove_family(const std::shared_ptr<AprilTagFamily> &family) {
    apriltag_detector_remove_family(raw(), family->raw());
    _families.erase(std::remove(_families.begin(), _families.end(), family), _families.end());
}

void apriltag::AprilTagDetector::clear_families() {
    apriltag_detector_clear_families(raw());
    _families.clear();
}

std::vector<apriltag::AprilTagDetection> apriltag::AprilTagDetector::detect(const cv::Mat &image) {
    if (image.dims != 2) {
        throw std::invalid_argument("Invalid image dimensions");
    }
    if (image.type() != CV_8U) {
        throw std::invalid_argument("Invalid image type");
    }
    image_u8_t cimage = {
        .width = image.cols,
        .height = image.rows,
        .stride = static_cast<std::int32_t>(image.step[0]),
        .buf = image.data
    };

    zarray_t *result = apriltag_detector_detect(raw(), &cimage);
    apriltag_detection_t *detection = nullptr;
    std::vector<AprilTagDetection> detections;
    for (int i = 0; i < zarray_size(result); i += 1) {
        zarray_get(result, i, &detection);  // this performs a copy
        detections.emplace_back(detection);
    }
    zarray_destroy(result);
    return detections;
}

const apriltag_detector_t *apriltag::AprilTagDetector::raw() const {
    return _detector.get();
}

apriltag_detector_t *apriltag::AprilTagDetector::raw() {
    return _detector.get();
}
