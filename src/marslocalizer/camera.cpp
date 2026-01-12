#include "camera.hpp"

#include <Eigen/Dense>

bool apriltag::RadialDistortionCoefficients::is_zero() const {
    return k1 == 0 && k2 == 0 && k3 == 0 && k4 == 0 && k5 == 0 && k6 == 0;
}

bool apriltag::TangentialDistortionCoefficients::is_zero() const {
    return p1 == 0 && p2 == 0;
}

bool apriltag::ThinPrismDistortionCoefficients::is_zero() const {
    return s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0;
}

Eigen::Matrix3d apriltag::CameraInfo::matrix() const {
    Eigen::Matrix3d camera_matrix; 
    camera_matrix << camera_intrinsics.fx, 0, camera_intrinsics.cx,
                    0, camera_intrinsics.fy, camera_intrinsics.cy,
                    0, 0, 1;
    return camera_matrix;
}

Eigen::VectorXd apriltag::CameraInfo::distortion_vector() const {
    if (!thin_prism_distortion_coefficients.is_zero()) {
        Eigen::VectorXd distortion_vector(12); // NOLINT(*-avoid-magic-numbers)
        distortion_vector <<
            radial_distortion_coefficients.k1,
            radial_distortion_coefficients.k2,
            tangential_distortion_coefficients.p1,
            tangential_distortion_coefficients.p2,
            radial_distortion_coefficients.k3,
            radial_distortion_coefficients.k4,
            radial_distortion_coefficients.k5,
            radial_distortion_coefficients.k6,
            thin_prism_distortion_coefficients.s1,
            thin_prism_distortion_coefficients.s2,
            thin_prism_distortion_coefficients.s3,
            thin_prism_distortion_coefficients.s4;
        return distortion_vector;
    }
    if (radial_distortion_coefficients.k4 != 0 || radial_distortion_coefficients.k5 != 0 ||
            radial_distortion_coefficients.k6 != 0) {
        Eigen::VectorXd distortion_vector(8); // NOLINT(*-avoid-magic-numbers)
        distortion_vector <<
            radial_distortion_coefficients.k1,
            radial_distortion_coefficients.k2,
            tangential_distortion_coefficients.p1,
            tangential_distortion_coefficients.p2,
            radial_distortion_coefficients.k3,
            radial_distortion_coefficients.k4,
            radial_distortion_coefficients.k5,
            radial_distortion_coefficients.k6;
        return distortion_vector;
    }
    if (radial_distortion_coefficients.k3 != 0) {
        Eigen::VectorXd distortion_vector(5); // NOLINT(*-avoid-magic-numbers)
        distortion_vector <<
            radial_distortion_coefficients.k1,
            radial_distortion_coefficients.k2,
            tangential_distortion_coefficients.p1,
            tangential_distortion_coefficients.p2,
            radial_distortion_coefficients.k3;
        return distortion_vector;
    }
    if (radial_distortion_coefficients.is_zero() && tangential_distortion_coefficients.is_zero()) {
        return Eigen::Vector<double, 0>();
    }
    Eigen::VectorXd distortion_vector(4); // NOLINT(*-avoid-magic-numbers)
    distortion_vector <<
        radial_distortion_coefficients.k1,
        radial_distortion_coefficients.k2,
        tangential_distortion_coefficients.p1,
        tangential_distortion_coefficients.p2;
    return distortion_vector;
}
