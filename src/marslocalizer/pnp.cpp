#include "pnp.hpp"

#include <algorithm>
#include <vector>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>


std::vector<apriltag::Affine3dWithError> apriltag::solve_pnp(cv::InputArray object_points,
                                                             cv::InputArray image_points,
                                                             cv::InputArray camera_intrinsics,
                                                             cv::InputArray distortion_vector,
                                                             PnPMethod method) {

    std::vector<cv::Mat> rvecs_cv;
    std::vector<cv::Mat> tvecs_cv;
    std::vector<double> errors_cv;

    const int num_solutions = cv::solvePnPGeneric(
    object_points,
            image_points,
            camera_intrinsics,
            distortion_vector,
            rvecs_cv,
            tvecs_cv,
            false,
            static_cast<cv::SolvePnPMethod>(method),
            cv::noArray(),
            cv::noArray(),
            errors_cv);

    std::vector<Affine3dWithError> results(num_solutions);
    cv::Mat rotation_matrix_cv;

    for (int i = 0; i < num_solutions; i += 1) {
        const cv::Affine3d transform_cv { rvecs_cv.at(i), tvecs_cv.at(i) };
        Affine3dWithError result;
        cv::cv2eigen(transform_cv.matrix, result.pose.matrix());
        result.reprojection_error = errors_cv.at(i);

        results.at(i) = (std::move(result));
    }

    return results;
}
