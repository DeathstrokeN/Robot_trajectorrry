#include <umrob/trajectory_generator.h>

#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/ostream.h>

#include <thread>
#include <chrono>

int main(int argc, char** argv) {
    constexpr auto time_step = 0.01;

    // Create a trajectory generator with a given time step
    umrob::TrajectoryGenerator trajectory(time_step);

    // Create the maximum velocites and acceleration vectors
    Eigen::Vector6d vmax = Eigen::Vector6d::Ones();
    Eigen::Vector6d amax = Eigen::Vector6d::Ones();

    // Create a default identity pose
    auto pose = Eigen::Affine3d::Identity();

    // Set its tanslation part
    pose.translation() << 1, 2, 3;
    // Set it as the starting pose
    trajectory.startFrom(pose);

    // Change its tanslation part
    pose.translation() << 2, 4, 1;
    // Add it as a waypoint with maximum velocity and acceleration specified
    trajectory.addWaypoint(pose, vmax, amax);

    // Change its tanslation part
    pose.translation() << -1, 2, 5;
    // Add it as a waypoint with the completion time specified
    trajectory.addWaypoint(pose, 1.);

    // Print how long it will take to execute the trajectory
    fmt::print("Trajectory length: {}\n", trajectory.duration());

    double print_timer{0};

    // Loop while we haven't reached the end of the trajectory
    while (trajectory.state() !=
           umrob::TrajectoryGenerator::State::TrajectoryCompleted) {
        // Print a message if we just reached a waypoint
        if (trajectory.update() ==
            umrob::TrajectoryGenerator::State::WaypointReached) {
            fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "\n{:*^50}\n",
                       " Waypoint reached ");
        }

        // Print the current position, velocity and acceleration targets every
        // 0.5s
        print_timer += time_step;
        if (print_timer > 0.5) {
            print_timer = 0;
            fmt::print("\n{:*^50}\n", " Current targets ");
            fmt::print("position: {}\n",
                       trajectory.targetPose().translation().transpose());
            fmt::print("velocity: {}\n",
                       trajectory.targetVelocity().head<3>().transpose());
            fmt::print("acceleration: {}\n",
                       trajectory.targetAcceleration().head<3>().transpose());
        }

        // Sleep for the duration of a time step
        std::this_thread::sleep_for(std::chrono::duration<double>(time_step));
    }

    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "\n{:*^50}\n",
               " Trajectory completed ");
}
