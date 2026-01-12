#include "pnp.hpp"

#include <algorithm>
#include <vector>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>


std::vector<apriltag::Affine3dWithError> apriltag::solve_pnp(const std::vector<Eigen::Vector3d>& object_points,
                                                       const std::vector<Eigen::Vector2d>& image_points,
                                                       const CameraInfo& camera_info,
                                                       PnPMethod method) {
    std::vector<cv::Point3d> object_points_cv(object_points.size());

    std::transform(object_points.cbegin(),
                   object_points.cend(),
                   object_points_cv.begin(),
                   [&](const Eigen::Vector3d& vec) {
        return cv::Point3d(vec.x(), vec.y(), vec.z());
    });

    std::vector<cv::Point2d> image_points_cv(image_points.size());
    std::transform(image_points.cbegin(),
                   image_points.cend(),
                   image_points_cv.begin(),
                   [&](const Eigen::Vector2d& vec) {
        return cv::Point2d(vec.x(), vec.y());
    });

    cv::Mat camera_matrix_cv;
    cv::eigen2cv(camera_info.matrix(), camera_matrix_cv);
    cv::Mat dist_coeffs_cv;
    cv::eigen2cv(camera_info.distortion_vector(), dist_coeffs_cv);

    std::vector<cv::Mat> rvecs_cv;
    std::vector<cv::Mat> tvecs_cv;
    std::vector<double> errors_cv;

    const int num_solutions = cv::solvePnPGeneric(
    object_points_cv,
            image_points_cv,
            camera_matrix_cv,
            dist_coeffs_cv,
            rvecs_cv,
            tvecs_cv,
            false,
            static_cast<cv::SolvePnPMethod>(method),
            cv::noArray(),
            cv::noArray(),
            errors_cv);

    // Sort indices by error
    std::vector<std::size_t> indices(num_solutions);
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(), [&](const std::size_t lhs, const std::size_t rhs) {
        return errors_cv.at(lhs) > errors_cv.at(rhs);
    });

    std::vector<Affine3dWithError> results(num_solutions);

    std::transform(indices.cbegin(), indices.cend(), results.begin(), [&](const std::size_t index) {
        cv::Mat rotation_matrix_cv;
        cv::Rodrigues(rvecs_cv.at(index), rotation_matrix_cv);

        const cv::Affine3d transform_cv { rvecs_cv.at(index), tvecs_cv.at(index) };

        Eigen::Affine3d transform;
        cv::cv2eigen(transform_cv.matrix, transform.matrix());

        return Affine3dWithError{ transform, errors_cv.at(index) };
    });

    return results;
}
