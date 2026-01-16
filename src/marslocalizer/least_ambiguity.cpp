//
// Created by Ivan on 1/12/26.
//

#include <vector>

#include "data.hpp"
#include "wrapper.hpp"
#include "localization/strategies.hpp"

apriltag::Affine3dWithError apriltag::LeastAmbiguityStrategy::localize_from(const std::vector<AprilTagDetection>& detections) {
    std::min_element(detections.cbegin(), detections.cend(), [&](const AprilTagDetection& lhs, const AprilTagDetection& rhs) {
        lhs.
    })

    // std::vector<Eigen::Vector3d> object_points(detections.size() * 4);
    // std::vector<Eigen::Vector2d> image_points(detections.size() * 4);
    // for (const auto& detection : detections) {
    //     object_points.
    //     image_points.insert(image_points.end(), detection.corners().cbegin(), detection.corners().cend());
    // }
}
