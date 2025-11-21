#include "wrapper.hpp"

std::string_view apriltag::AprilTagFamily::name() const {
    return _family->name;
}

int apriltag::AprilTagFamily::width_at_border() const {
    return _family->width_at_border;
}

int apriltag::AprilTagFamily::total_width() const {
    return _family->total_width;
}

std::uint32_t apriltag::AprilTagFamily::minimum_hamming_distance() const {
    return _family->h;
}

const apriltag_family_t *apriltag::AprilTagFamily::raw() const {
    return _family;
}

apriltag_family_t *apriltag::AprilTagFamily::raw() {
    return _family;
}