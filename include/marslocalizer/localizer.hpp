//
// Created by Ivan on 1/12/26.
//

#ifndef MARSLOCALIZER_LOCALIZER_HPP
#define MARSLOCALIZER_LOCALIZER_HPP

#include "camera.hpp"
#include "data.hpp"
#include "field.hpp"
#include "pnp.hpp"
#include "wrapper.hpp"

namespace apriltag {

struct CameraLocalizationResult {
    Affine3dWithError estimate;
    std::vector<AprilTagDetection> detections;
};

class CameraLocalizer {

    AprilTagDetector _detector;
    cv::Mat _camera_intrinsics;
    cv::Mat _distortion_vector;
    std::shared_ptr<const AprilTagField> _field;
    PnPMethod _method;

public:

    CameraLocalizer(const CameraInfo& camera_info,
                    const std::shared_ptr<const AprilTagField>& field,
                    const PnPMethod method = PnPMethod::ITERATIVE)
        : _field(field), _method(method) {
        cv::eigen2cv(camera_info.matrix(), _camera_intrinsics);
        cv::eigen2cv(camera_info.distortion_vector(), _distortion_vector);
    }

    [[nodiscard]] const AprilTagDetector& detector() const;

    [[nodiscard]] AprilTagDetector& detector();

    [[nodiscard]] CameraInfo camera_info() const;

    [[nodiscard]] std::shared_ptr<const AprilTagField> field() const;

    [[nodiscard]] std::optional<CameraLocalizationResult> localize(const cv::Mat& image) const;

};

}

#endif //MARSLOCALIZER_LOCALIZER_HPP