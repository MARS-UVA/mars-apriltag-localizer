//
// Created by Ivan on 11/21/25.
//

#include "wrapper.hpp"

int apriltag::AprilTagDetection::id() const {
    return _detection->id;
}

Eigen::Vector2d apriltag::AprilTagDetection::center() const {
    return { _detection->c[0], _detection->c[1] };
}

std::array<Eigen::Vector2d, 4> apriltag::AprilTagDetection::corners() const {
    return {
        Eigen::Vector2d { _detection->p[0][0], _detection->p[0][1] },
        Eigen::Vector2d { _detection->p[1][0], _detection->p[1][1] },
        Eigen::Vector2d { _detection->p[2][0], _detection->p[2][1] },
        Eigen::Vector2d { _detection->p[3][0], _detection->p[3][1] },
    };
}
