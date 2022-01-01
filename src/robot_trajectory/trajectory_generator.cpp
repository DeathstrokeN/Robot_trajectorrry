#include "umrob/trajectory_generator.h"
#include <fmt/format.h>
#include <numeric>
#include <math.h>
#include <umrob/polynomial.h>
#include <iostream>


namespace umrob {

TrajectoryGenerator::Segment::Segment(const Eigen::Vector6d& max_velocity,
                                      const Eigen::Vector6d& max_acceleration)
    : max_velocity{max_velocity}, max_acceleration{max_acceleration} {
}

TrajectoryGenerator::TrajectoryGenerator(double time_step)
    : time_step_{time_step} {
    reset();
}

void TrajectoryGenerator::startFrom(const Eigen::Affine3d& pose) {
    reset();
    last_waypoint_ = pose;
    target_pose_ = pose;
}

void TrajectoryGenerator::addWaypoint(
    const Eigen::Affine3d& pose,
    const Eigen::Vector6d& max_velocity,
    const Eigen::Vector6d& max_acceleration) {
    // TODO implement
    target_pose_ = pose;
    target_velocity_ = max_velocity;
    target_acceleration_ = max_acceleration;
    currentSegment().max_velocity = max_velocity;
    currentSegment().max_acceleration = max_acceleration;
    computeSegmentDuration(currentSegment()); 
    computeSegmentParameters(currentSegment()); 
    current_segment_idx_++;
}

void TrajectoryGenerator::addWaypoint(
    const Eigen::Affine3d& pose,
    double duration) {
    // TODO implement
	
	target_pose_=pose;
    currentSegment().duration=duration;
    computeSegmentParameters(currentSegment());
    current_segment_idx_++;
}

TrajectoryGenerator::State TrajectoryGenerator::update() {
    if (state_ == State::TrajectoryCompleted) {
        return state_;
    } else {
        state_ = State::ReachingWaypoint;
    }

    auto evaluate = [this]() {
        Eigen::Vector6d next_pose_vec;

        // TODO evaluate the polynomial and its derivatives into next_pose_vec,
        // target_velocity_ and target_acceleration_
		for (size_t  p=0; p<6; p++){
			auto& poly = currentSegment().polynomials[p];
			
			for(int p=0 ; p<currentSegment().duration ; p+=time_step_){	
				next_pose_vec(p) = poly.evaluate(p);
				target_velocity_(p) =poly.evaluateFirstDerivative(p);
				target_acceleration_(p)=poly.evaluateSecondDerivative(p);
				state_ = State::ReachingWaypoint;
            }
        }

        target_pose_.translation() = next_pose_vec.head<3>();
        target_pose_.linear() =
            Eigen::Quaterniond::fromAngles(next_pose_vec.tail<3>())
                .toRotationMatrix();
    };

    evaluate();

    currentSegment().current_time += time_step_;
    if (currentSegment().current_time > currentSegment().duration) {
        // TODO switch to next segment and re-evaluate if needed
		current_segment_idx_++;
		state_ = State::WaypointReached;
    }
	else if (currentSegment().current_time == duration()) {
        state_ = State::TrajectoryCompleted;
        current_segment_idx_=0;
    }
	else{
        state_ = State::ReachingWaypoint;
    }
	

    return state_;
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
    double durationFinal=0;
    double *nombrSegm;
    nombrSegm = new double[current_segment_idx_];

    for (size_t i(0); i<current_segment_idx_; i++ ){
	   nombrSegm[i]=segments_.at(current_segment_idx_).duration;
	   durationFinal=durationFinal+nombrSegm[i];
	}
    return durationFinal;
}

void TrajectoryGenerator::reset() {
    state_ = State::Idle;
    last_waypoint_.setIdentity();
    segments_.clear();
    current_segment_idx_ = 0;

    target_pose_ = last_waypoint_;
    target_velocity_.setZero();
    target_acceleration_.setZero();
}

void TrajectoryGenerator::setSegmentConstraints(const Eigen::Affine3d& from,
                                                const Eigen::Affine3d& to,
                                                Segment& segment) {
    Eigen::Vector6d from_vec, to_vec;
    from_vec << from.translation(),
        Eigen::Quaterniond(from.linear()).getAngles();
    to_vec << to.translation(), Eigen::Quaterniond(to.linear()).getAngles();

    for (size_t i = 0; i < 6; i++) {
        auto& poly = segment.polynomials[i];
        auto& cstr = poly.constraints();
        cstr.xi = 0;
        cstr.xf = 0;
        cstr.yi = from_vec(i);
        cstr.yf = to_vec(i);
    }
}

//! Tmin_vel = 30Δy/16vmax
//! Tmin_acc = sqrt(10sqrt(3)Δy/3amax)
void TrajectoryGenerator::computeSegmentDuration(Segment& segment) {
    // TODO implement
	Eigen::Vector6d Tmin_vel;
    Eigen::Vector6d Tmin_acc;
    Eigen::Vector6d maxTemp;
    double deltaY;
   
    for (int i = 0; i < 6; i++) {
		deltaY = segment.polynomials[i].deltaY();
		Tmin_vel(i) = (30*deltaY)/(16*segment.max_velocity(i));
		Tmin_acc(i) = sqrt((10*sqrt(3)*(deltaY)/(3*segment.max_acceleration(i))));
		maxTemp(i) = std::max(Tmin_acc(i),Tmin_vel(i));
		segment.duration = maxTemp.MaxColsAtCompileTime; 
    }
}

void TrajectoryGenerator::computeSegmentParameters(Segment& segment) {
    // TODO compute the polynomials coefficients for the current duration
	setSegmentConstraints(last_waypoint_,target_pose_,segment);
	computeSegmentDuration(segment); 
    for (size_t i=0;i<6;i++){
		auto& poly = segment.polynomials[i];
		poly.computeCoefficients();
    }
	
}

TrajectoryGenerator::Segment& TrajectoryGenerator::currentSegment() {
    return segments_.at(current_segment_idx_);
}

} // namespace umrob