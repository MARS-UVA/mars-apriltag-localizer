#include <Eigen/Dense>
#include "pnp.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>
#include "calcexception.hpp"
#include <vector>
#include <algorithm>



static std::vector<Eigen::Affine3d> PnP::solve_pnp(const Eigen::Matrix<double, Eigen::Dynamic, 3>& object_points, 
    const Eigen::Matrix<double, Eigen::Dynamic, 2>& image_points, 
    const CameraParameters& camera_params,
    PnPMethod method = PnPMethod::ITERATIVE
) {
    //Initialize cv inputs and copy over
    //object and image points need to be converted to vectors of points
    std::vector<cv::Point3d> obj_cv;
    obj_cv.reserve(object_points.rows());
    for (int i = 0; i < object_points.rows(); ++i) {
        obj_cv.emplace_back(
            object_points(i, 0),
            object_points(i, 1),
            object_points(i, 2)
        );  
    }
    std::vector<cv::Point2d> img_cv;
        img_cv.reserve(image_points.rows());
    for (int i = 0; i < image_points.rows(); ++i) {
        img_cv.emplace_back(
            image_points(i, 0),
            image_points(i, 1)
        );
    }

    cv::Mat camera_mat_cv, dist_coeffs_cv;
    cv::eigen2cv(camera_params.get_matrix(), camera_mat_cv);
    cv::eigen2cv(camera_params.get_distortion_vector(), dist_coeffs_cv);
    //initialize rotation and translation vectors, and errors (outputs)
    std::vector<cv::Mat> rvec, tvec;
    std::vector<double> errors;
    int numSolutions;

    //Call pnp method
    try{
        numSolutions = cv::solvePnPGeneric(obj_cv, img_cv, camera_mat_cv, dist_coeffs_cv, rvec, tvec, false,  method, cv::noArray(), cv::noArray(), errors);
    } catch (const cv::Exception& e){
        throw CalcException(e.what());
    }
    if (numSolutions <=0){
        throw CalcException("Failed to solve");
    }


    //Sort indices by error
    size_t n = errors.size();
    std::vector<size_t> idx(n);
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(), [&](size_t a, size_t b){ return errors[a] < errors[b]; });

    //Add affine3d transform objects to result using sorted indices
    std::vector<Eigen::Affine3d> result;
    for (size_t i = 0; i < n; ++i) {
        size_t k = idx[i];

        Eigen::Affine3d transform = Eigen::Affine3d::Identity();

        cv::Mat R_cv;
        Eigen::Matrix3d R_eigen;

        cv::Rodrigues(rvec[k], R_cv);
        cv::cv2eigen(R_cv, R_eigen);
        R_eigen = R_eigen.cast<double>();
        transform.linear() = R_eigen;

        Eigen::Vector3d t_eigen;
        cv::cv2eigen(tvec[k], t_eigen);
        t_eigen = t_eigen.cast<double>();
        transform.translation() = t_eigen;

        result.push_back(transform);
    }

    return result;
}
