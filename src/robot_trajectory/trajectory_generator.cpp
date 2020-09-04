#include <umrob/trajectory_generator.h>

#include <fmt/format.h>

#include <numeric>

namespace umrob {

TrajectoryGenerator::Segment::Segment(
    [[maybe_unused]] const Eigen::Vector6d& max_velocity,
    [[maybe_unused]] const Eigen::Vector6d& max_acceleration) {
    // TODO implement
}

TrajectoryGenerator::TrajectoryGenerator(double time_step)
    : time_step_{time_step} {
    // TODO implement
}

void TrajectoryGenerator::startFrom([
    [maybe_unused]] const Eigen::Affine3d& pose) {
    // TODO implement
}

void TrajectoryGenerator::addWaypoint(
    [[maybe_unused]] const Eigen::Affine3d& pose,
    [[maybe_unused]] const Eigen::Vector6d& max_velocity,
    [[maybe_unused]] const Eigen::Vector6d& max_acceleration) {
    // TODO implement
}

void TrajectoryGenerator::addWaypoint(
    [[maybe_unused]] const Eigen::Affine3d& pose,
    [[maybe_unused]] double duration) {
    // TODO implement
}

TrajectoryGenerator::State TrajectoryGenerator::update() {
    // TODO implement
    return State::Idle;
}

const Eigen::Affine3d& TrajectoryGenerator::targetPose() const {
    return target_pose_;
}

const Eigen::Vector6d& TrajectoryGenerator::targetVelocity() const {
    return target_velocity_;
}

const Eigen::Vector6d& TrajectoryGenerator::targetAcceleration() const {
    return target_acceleration_;
}

TrajectoryGenerator::State TrajectoryGenerator::state() const {
    return state_;
}

double TrajectoryGenerator::duration() const {
    // TODO implement
    return 0;
}

void TrajectoryGenerator::reset() {
    // TODO implement
}

void TrajectoryGenerator::setSegmentConstraints(
    const Eigen::Affine3d& from, const Eigen::Affine3d& to,
    [[maybe_unused]] Segment& segment) {
    Eigen::Vector6d from_vec, to_vec;
    from_vec << from.translation(),
        Eigen::Quaterniond(from.linear()).getAngles();
    to_vec << to.translation(), Eigen::Quaterniond(to.linear()).getAngles();

    // TODO implement (use from_vec and to_vec for the initial and final
    // position values)
}

//! Tmin_vel = 30Δy/16vmax
//! Tmin_acc = sqrt(10sqrt(3)Δy/3amax)
void TrajectoryGenerator::computeSegmentDuration([
    [maybe_unused]] Segment& segment) {
    // TODO implement
}

void TrajectoryGenerator::computeSegmentParameters([
    [maybe_unused]] Segment& segment) {
    // TODO implement
}

TrajectoryGenerator::Segment& TrajectoryGenerator::currentSegment() {
    return segments_.at(current_segment_idx_);
}

} // namespace umrob