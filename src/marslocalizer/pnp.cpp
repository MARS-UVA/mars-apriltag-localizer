#include <Eigen/Dense>
#include "pnp.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>
#include "calcexception.hpp"
#include <vector>



static std::vector<Eigen::Affine3f> PnP::solve_pnp(const Eigen::Matrix<float, Eigen::Dynamic, 3>& object_points, 
    const Eigen::Matrix<float, Eigen::Dynamic, 2>& image_points, 
    const CameraParameters& camera_params,
    PnPMethod method = PnPMethod::ITERATIVE
) {
    cv::Mat obj_cv, img_cv, camera_mat_cv, dist_coeffs_cv;
    cv::eigen2cv(object_points, obj_cv);
    cv::eigen2cv(image_points, img_cv);
    cv::eigen2cv(camera_params.get_matrix(), camera_mat_cv);
    cv::eigen2cv(camera_params.get_distortion_vector(), dist_coeffs_cv);
    std::vector<cv::Mat> rvec, tvec;
    std::vector<float> errors;

    try{
        int success = cv::solvePnPGeneric(obj_cv, img_cv, camera_mat_cv, dist_coeffs_cv, rvec, tvec, flags = method, reprojectionError = errors);
    } catch (const cv::Exception& e){
        throw CalcException(e.what());
    }
    if (!success){
        throw CalcException("Failed to solve");
    }
    std::vector<Eigen::Affine3f> result;
    while(errors.size() > 0){
        auto min_ptr = std::min_element(errors.begin(),errors.end());
        size_t min_index = std::distance(errors.begin(), min_ptr);
        errors.erase(min_ptr);

        Eigen::Affine3f transform = Eigen::Affine3f::Identity();

        cv::Mat r_cv;
        Eigen::Matrix3f R_eigen;

        cv::Rodrigues(rvec[min_index], r_cv);
        cv::cv2eigen(R_cv, R_eigen);
        R_eigen = R_eigen.cast<float>();
        transform.linear() = R_eigen;

        Eigen::Vector3f t_eigen;
        cv::cv2eigen(tvec[min_index], t_eigen); 
        t_eigen = t_eigen.cast<float>();
        transform.translation() = t_eigen;

        rvec.erase(rvec.begin() + min_index);
        tvec.erase(tvec.begin() + min_index);
        result.push_back(transform);
    }
    return result;
}
