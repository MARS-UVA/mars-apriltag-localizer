//
// Created by Ivan on 1/12/26.
//

#ifndef MARSLOCALIZER_STRATEGIES_HPP
#define MARSLOCALIZER_STRATEGIES_HPP



namespace apriltag {

class CameraLocalizationStrategy {
public:

    virtual ~CameraLocalizationStrategy() = default;

    [[nodiscard]] virtual Affine3dWithError localize_from(const std::vector<AprilTagDetection>& detections) = 0;

};

class LeastAmbiguityStrategy : public CameraLocalizationStrategy {

    Affine3dWithError localize_from(const std::vector<AprilTagDetection>& detections) override;

};

}

#endif //MARSLOCALIZER_STRATEGIES_HPP