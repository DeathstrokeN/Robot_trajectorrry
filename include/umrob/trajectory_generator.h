//! \file trajectory_generator.h
//! \author Benjamin Navarro
//! \brief Declaration of the TrajectoryGenerator class
//! \date 09-2020

#pragma once

#include <umrob/polynomial.h>

#include <Eigen/Dense>

#include <array>
#include <vector>

namespace Eigen {
using Vector6d = Eigen::Matrix<double, 6, 1>;
}

namespace umrob {

//! \brief Cartesian space trajectory generator
//!
//! The trajectory can be built using multiple segment and each segment is
//! either velocity/acceleration or time constrained
//!
class TrajectoryGenerator {
public:
    //! \brief Possible states of the trajectory generator
    //!
    enum class State {
        Idle,                //!< Default state
        ReachingWaypoint,    //!< Working to reach the next waypoint
        WaypointReached,     //!< Next waypoint reached
        TrajectoryCompleted, //!< Last waypoint reached
    };

    //! \brief Construct a trajectory generator using the given time step
    //!
    //! \param time_step The update time step, in seconds
    TrajectoryGenerator(double time_step);

    //! \brief Reset the trajectory and set its starting point.
    //!
    //! \param pose
    void startFrom(const Eigen::Affine3d& pose);

    //! \brief Add a new waypoint using velocity and acceleration constraints
    //!
    //! \param pose Waypoint pose
    //! \param max_velocity Maximum velocity on the segment, in [m/s,rad/s]
    //! \param max_acceleration Maximum acceleration on the segment, in
    //! [m/s²,rad/s²]
    void addWaypoint(const Eigen::Affine3d& pose,
                     const Eigen::Vector6d& max_velocity,
                     const Eigen::Vector6d& max_acceleration);

    //! \brief Add a new waypoint using a time constraint
    //!
    //! \param pose Waypoint pose
    //! \param duration The segment duration, in seconds
    void addWaypoint(const Eigen::Affine3d& pose, double duration);

    //! \brief Update the target pose, velocity and acceleration and advance one
    //! time step
    //!
    //! \return State The new trajectory generator state
    State update();

    //! \brief Read only access to the current target pose
    //!
    //! \return const Eigen::Affine3d& The target pose
    const Eigen::Affine3d& targetPose() const;

    //! \brief Read only access to the current target velocity
    //!
    //! \return const Eigen::Affine3d& The target velocity
    const Eigen::Vector6d& targetVelocity() const;

    //! \brief Read only access to the current target acceleration
    //!
    //! \return const Eigen::Affine3d& The target acceleration
    const Eigen::Vector6d& targetAcceleration() const;

    //! \brief Current trajectory generator state
    //!
    //! \return State
    State state() const;

    //! \brief Duration of the whole trajectory
    //!
    //! \return double The duration, in seconds
    double duration() const;

    //! \brief Reset the trajectory and the targets and remove all the waypoints
    //!
    void reset();

private:
    //! \brief Required data to represent a trajectory segment
    //!
    struct Segment {
        Segment() = default;
        Segment(const Eigen::Vector6d& max_velocity,
                const Eigen::Vector6d& max_acceleration);

        Eigen::Vector6d max_velocity{Eigen::Vector6d::Zero()};
        Eigen::Vector6d max_acceleration{Eigen::Vector6d::Zero()};
        std::array<Polynomial, 6> polynomials{};
        double duration{0};
        double current_time{0};
    };

    //! \brief Set a segment's constraints using the initial and final poses
    ////! \brief Set the Segment Constraints object
    //!
    //! \param from
    //! \param to
    //! \param segment
    //! \param to Final pose
    //! \param segment The segment
    void setSegmentConstraints(const Eigen::Affine3d& from,
                               const Eigen::Affine3d& to, Segment& segment);

    //! \brief Compute a segment duration based on its position, velocity and
    //! acceleration constraints
    //!
    //! \param segment The segment
    void computeSegmentDuration(Segment& segment);

    //! \brief Compute a segment's parameters using its constraints
    //!
    //! \param segment
    void computeSegmentParameters(Segment& segment);

    //! \brief Read/write access to the current segment
    //!
    //! \return Segment&
    Segment& currentSegment();

    State state_;
    Eigen::Affine3d last_waypoint_;
    std::vector<Segment> segments_;
    size_t current_segment_idx_;
    Eigen::Affine3d target_pose_;
    Eigen::Vector6d target_velocity_;
    Eigen::Vector6d target_acceleration_;

    const double time_step_;
};

} // namespace umrob