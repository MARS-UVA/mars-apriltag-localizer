//
// Created by Ivan on 1/12/26.
//

#ifndef MARSLOCALIZER_LOCALIZER_HPP
#define MARSLOCALIZER_LOCALIZER_HPP

#include "data.hpp"
#include "wrapper.hpp"
#include "localization/strategies.hpp"

namespace apriltag {



struct CameraLocalizationResult {
    Affine3dWithError estimate;
    std::vector<AprilTagDetection> detections;
};

class CameraLocalizer {

    std::unique_ptr<AprilTagDetector> detector;
    std::unique_ptr<CameraLocalizationStrategy> strategy;

public:

    [[nodiscard]] CameraLocalizationResult localize(const cv::Mat& image) const;

};

}

#endif //MARSLOCALIZER_LOCALIZER_HPP