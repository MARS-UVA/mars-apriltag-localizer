#include "camera.hpp"
#include <Eigen/Dense>

Eigen::Matrix3d CameraParameters::get_matrix() const{
    Eigen::Matrix3d camera_matrix; 
    camera_matrix << camera_intrinsics.fx, 0, camera_intrinsics.cx,
                    0, camera_intrinsics.fy, camera_intrinsics.cy,
                    0, 0, 1;
    return camera_matrix;
}

Eigen::Matrix<double, 5, 1> CameraParameters::get_distortion_vector() const{
    Eigen::Matrix<double, 5, 1> dist_vect;
    dist_vect << dist_vector.k1, dist_vector.k2, dist_vector.p1, dist_vector.p2, dist_vector.k3;
    return dist_vect;
}
