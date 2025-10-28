#include "library.hpp"

#include <iostream>
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>

void hello() {
    Eigen::Matrix<double, 3, 3> mat;
    cv::Matx<double, 3, 3> result;
    cv::eigen2cv(mat, result);
    std::cout << "Hello, World!" << std::endl;
}
