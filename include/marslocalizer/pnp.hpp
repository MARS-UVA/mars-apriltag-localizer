#ifndef MARSLOCALIZER_PNP_HPP
#define MARSLOCALIZER_PNP_HPP


#include <Eigen/Dense>
#include "camera.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

class PnP{
public:
    enum class PnPMethod : int {
        ITERATIVE = cv::SOLVEPNP_ITERATIVE,
        AP3P = cv::SOLVEPNP_AP3P,
        IPPE = cv::SOLVEPNP_IPPE_SQUARE,
        SQPNP = cv::SOLVEPNP_SQPNP
    };
    static std::vector<Eigen::Affine3f> solve_pnp(const Eigen::Matrix<float, Eigen::Dynamic, 3>& object_points, 
        const Eigen::Matrix<float, Eigen::Dynamic, 2>& image_points, 
        const CameraParameters& camera_params,
        PnPMethod method = PnPMethod::ITERATIVE
    );
};
#endif