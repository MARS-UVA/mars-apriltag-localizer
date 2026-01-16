//
// Created by Ivan on 1/12/26.
//

#include "localization/localizer.hpp"

apriltag::CameraLocalizationResult apriltag::CameraLocalizer::localize(const cv::Mat& image) const {
    CameraLocalizationResult result;
    result.detections = detector->detect(image);
    result.estimate = strategy->localize_from(result.detections);
    return result;
}
