#include <umrob/trajectory_generator.h>

#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/ostream.h>

#include <thread>
#include <chrono>

int main(int argc, char** argv) {
    constexpr auto time_step = 0.01;
    umrob::TrajectoryGenerator trajectory(time_step);

    Eigen::Vector6d vmax = Eigen::Vector6d::Ones();
    Eigen::Vector6d amax = Eigen::Vector6d::Ones();

    auto pose = Eigen::Affine3d::Identity();

    pose.translation() << 1, 2, 3;
    trajectory.startFrom(pose);

    pose.translation() << 2, 4, 1;
    trajectory.addWaypoint(pose, vmax, amax);

    pose.translation() << -1, 2, 5;
    trajectory.addWaypoint(pose, 1.);

    fmt::print("Trajectory length: {}\n", trajectory.duration());

    double print_timer{0};
    while (trajectory.state() !=
           umrob::TrajectoryGenerator::State::TrajectoryCompleted) {
        if (trajectory.update() ==
            umrob::TrajectoryGenerator::State::WaypointReached) {
            fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "\n{:*^50}\n",
                       " Waypoint reached ");
        }

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

        std::this_thread::sleep_for(std::chrono::duration<double>(time_step));
    }

    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "\n{:*^50}\n",
               " Trajectory completed ");
}
