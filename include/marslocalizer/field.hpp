//
// Created by Ivan on 1/12/26.
//

#ifndef MARSLOCALIZER_FIELD_HPP
#define MARSLOCALIZER_FIELD_HPP

#include <fstream>
#include <string>
#include <unordered_map>
#include <Eigen/Geometry>

namespace apriltag {

class AprilTagField;

class AprilTagInfo {
    friend class AprilTagField;

    std::uint32_t _id;
    double _size;
    Eigen::Affine3d _pose;
    std::array<Eigen::Vector3d, 4> _corners{};

public:

    AprilTagInfo();

    std::uint32_t id() const { return _id; }

    double size() const { return _size; }

    const Eigen::Affine3d& pose() const { return _pose; }

private:

    std::uint32_t& id() { return _id; }

    double& size() { return _size; }

    void set_pose(const Eigen::Affine3d& pose);

};

class AprilTagField {

    std::string _name = "Unnamed AprilTag field";
    std::string _tag_family;
    std::unordered_map<std::uint32_t, AprilTagInfo> _fiducials;

public:

    static AprilTagField parse(std::ifstream& input);

    const AprilTagInfo* tag(const std::uint32_t tag_id) const {
        if (const auto entry = _fiducials.find(tag_id); entry != _fiducials.end()) {
            return &entry->second;
        }
        return nullptr;
    }

    const std::string& name() const {
        return _name;
    }

    const std::string& tag_family() const {
        return _tag_family;
    }

    const std::unordered_map<std::uint32_t, AprilTagInfo>& fiducials() const {
        return _fiducials;
    }

    template <typename T>
    std::vector<Eigen::Vector3d> get_corners(T tag_ids) const {
        std::vector<Eigen::Vector3d> corners;
        for (std::uint32_t tag_id : tag_ids) {
            if (auto entry = _fiducials.find(tag_id); entry != _fiducials.end()) {
                corners.insert(corners.end(),
                    entry->second._corners.cbegin(),
                    entry->second._corners.cend());
            }
        }
        return corners;
    }

};

}

#endif //MARSLOCALIZER_FIELD_HPP