#ifndef MARSLOCALIZER_WRAPPER_HPP
#define MARSLOCALIZER_WRAPPER_HPP

#include <functional>
#include <memory>
#include <string>
#include <Eigen/Dense>
// ReSharper disable once CppUnusedIncludeDirective
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

class AprilTagFamily {
public:

    using Deleter = void(apriltag_family_t*);

    AprilTagFamily(apriltag_family_t *family, Deleter &deleter) : _family(family), _deleter(deleter) {
    }

    ~AprilTagFamily() {
        _deleter(_family);
    }

    [[nodiscard]] std::string_view name() const;
    [[nodiscard]] int width_at_border() const;
    [[nodiscard]] int total_width() const;
    [[nodiscard]] std::uint32_t minimum_hamming_distance() const;

    [[nodiscard]] const apriltag_family_t *raw() const;
    [[nodiscard]] apriltag_family_t *raw();

private:

    apriltag_family_t *_family;
    Deleter& _deleter;

};

class AprilTagDetection {
public:
    explicit AprilTagDetection(apriltag_detection_t *detection) : _detection(detection) {
    }

    [[nodiscard]] int id() const;
    [[nodiscard]] Eigen::Vector2d center() const;
    [[nodiscard]] std::array<Eigen::Vector2d, 4> corners() const;

private:

    detail::wrapping_ptr<apriltag_detection_t, apriltag_detection_destroy> _detection;

};

class AprilTagDetector {
public:

    AprilTagDetector()
        : _detector(apriltag_detector_create()) {
    }

    [[nodiscard]] const int &nthreads() const;
    [[nodiscard]] int &nthreads();

    [[nodiscard]] const float &quad_decimate() const;
    [[nodiscard]] float &quad_decimate();

    [[nodiscard]] const float &quad_sigma() const;
    [[nodiscard]] float &quad_sigma();

    [[nodiscard]] const bool &refine_edges() const;
    [[nodiscard]] bool &refine_edges();

    [[nodiscard]] const double &decode_sharpening() const;
    [[nodiscard]] double &decode_sharpening();

    [[nodiscard]] const bool &debug() const;
    [[nodiscard]] bool &debug();

    void add_family(const std::shared_ptr<AprilTagFamily> &family);
    void remove_family(const std::shared_ptr<AprilTagFamily> &family);
    void clear_families();

    std::vector<AprilTagDetection> detect(const cv::Mat &image);

    const apriltag_detector_t *raw() const;
    apriltag_detector_t *raw();

private:

    detail::wrapping_ptr<apriltag_detector_t, apriltag_detector_destroy> _detector;
    std::vector<std::shared_ptr<AprilTagFamily>> _families;

};

}

#endif //MARSLOCALIZER_WRAPPER_HPP