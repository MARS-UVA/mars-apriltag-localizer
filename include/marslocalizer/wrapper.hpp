#ifndef MARSLOCALIZER_WRAPPER_HPP
#define MARSLOCALIZER_WRAPPER_HPP

#include <memory>
#include <Eigen/Dense>
#include <opencv2/core/mat.hpp>

#include "apriltag.h"

namespace apriltag {

namespace detail {

    template <auto fn>
    struct deleter_from_fn {
        template <typename T>
        constexpr void operator()(T* arg) const {
            fn(arg);
        }
    };

    template <typename T, auto fn>
    using wrapping_ptr = std::unique_ptr<T, deleter_from_fn<fn>>;

}

// template <auto creator_fn, auto deleter_fn>
// class AprilTagFamily {
// public:
//     static auto creator = creator_fn;
//     static auto deleter = deleter_fn;
//
//     AprilTagFamily() : _family(creator_fn()) {
//     }
//
//     detail::wrapping_ptr<apriltag_family_t, deleter_fn> raw() {
//         return _family.get();
//     }
//
// private:
//     detail::wrapping_ptr<apriltag_family_t, deleter_fn> _family;
// };
//
// using Tag36h11Family = AprilTagFamily<tag>
// using TagStandard41h12Family = AprilTagFamily<tagStandard41h12_create, tagStandard41h12_destroy>;

class AprilTagDetection {
public:

    AprilTagDetection(apriltag_detection_t *detection) : _detection(detection) {
    }

    int id() const;
    Eigen::Vector2d center() const;
    std::array<Eigen::Vector2d, 4> corners() const;

private:
    detail::wrapping_ptr<apriltag_detection_t, apriltag_detection_destroy> _detection;
};

class AprilTagDetector {
public:

    AprilTagDetector()
        : _detector(apriltag_detector_create()) {
    }

    // void add_family(apriltag_family_t *family);

    apriltag_detector_t *raw() {
        return _detector.get();
    }

    std::vector<AprilTagDetection> detect(const cv::Mat& image);

private:
    detail::wrapping_ptr<apriltag_detector_t, apriltag_detector_destroy> _detector;
};

}

#endif //MARSLOCALIZER_WRAPPER_HPP