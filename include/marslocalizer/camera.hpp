#ifndef MARSLOCALIZER_CAMERA_HPP
#define MARSLOCALIZER_CAMERA_HPP

#include <Eigen/Dense>

struct CameraIntrinsics{
    float fx, fy, cx, cy;
    //f: focal length
    //c: optical center coordinates

};
struct DistortionVector{
    float k1, k2, p1, p2, k3;
    //k: radial distortion
    //p: tangential distortion
};

class CameraParameters{
public:
    CameraIntrinsics camera_intrinsics;
    DistortionVector dist_vector;

    //default constructor with explicit floats
    CameraParameters(float fx, float fy, float cx, float cy, float k1, float k2, float p1, float p2, float k3)
        : camera_intrinsics{fx, fy, cx, cy},
        dist_vector{k1, k2, p1, p2, k3} {
    }
    //constructor taking in eigen matrix and vector
    CameraParameters(const Eigen::Matrix3f& input_matrix, const Eigen::Matrix<float, 5, 1>& input_vector)
        : camera_intrinsics{input_matrix(0,0) , input_matrix(1,1), input_matrix(0,2), input_matrix(1,2)},
        dist_vector{input_vector(0), input_vector(1), input_vector(2), input_vector(3), input_vector(4)} {
    }
    
    Eigen::Matrix3f get_matrix() const;
    Eigen::Matrix<float, 5, 1> get_distortion_vector() const;
     
};

#endif // MARSLOCALIZER_CAMERA_HPP
