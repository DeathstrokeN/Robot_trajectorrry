#include <catch2/catch.hpp>

#include <umrob/trajectory_generator.h>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include <ctime>

TEST_CASE("TrajectoryGenerator") {
    std::srand(std::time(nullptr));

    constexpr auto time_step = 0.1;
    umrob::TrajectoryGenerator trajectory(time_step);
    REQUIRE(trajectory.duration() == 0.);

    auto random_pose = []() {
        auto pose = Eigen::Affine3d::Identity();
        pose.translation().setRandom();
        pose.linear() =
            Eigen::Quaterniond::fromAngles(Eigen::Vector3d::Random())
                .toRotationMatrix();
        return pose;
    };

    SECTION("State") {
        trajectory.addWaypoint(random_pose(), 1.);
        REQUIRE(trajectory.state() == umrob::TrajectoryGenerator::State::Idle);

        trajectory.update();
        REQUIRE(trajectory.state() ==
                umrob::TrajectoryGenerator::State::ReachingWaypoint);
    }

    SECTION("Output") {
        for (size_t i = 0; i < 100; i++) {
            Eigen::Vector6d vmax = Eigen::Vector6d::Random().cwiseAbs();
            Eigen::Vector6d amax = Eigen::Vector6d::Random().cwiseAbs();

            auto from = random_pose();
            trajectory.startFrom(from);

            trajectory.addWaypoint(random_pose(), vmax, amax);

            auto to = random_pose();
            trajectory.addWaypoint(to, vmax, amax);

            REQUIRE(trajectory.targetPose().matrix() == from.matrix());
            REQUIRE(trajectory.targetVelocity().isZero());
            REQUIRE(trajectory.targetAcceleration().isZero());

            for (double t = 0; t < trajectory.duration(); t += time_step) {
                trajectory.update();
                REQUIRE((vmax - trajectory.targetVelocity().cwiseAbs())
                            .minCoeff() >= 0.);
                REQUIRE((amax - trajectory.targetAcceleration().cwiseAbs())
                            .minCoeff() >= 0.);
            }

            REQUIRE(trajectory.update() ==
                    umrob::TrajectoryGenerator::State::TrajectoryCompleted);

            REQUIRE(trajectory.targetPose().matrix().isApprox(to.matrix()));
            REQUIRE(trajectory.targetVelocity().isZero());
            REQUIRE(trajectory.targetAcceleration().isZero());
        }
    }

    SECTION("Fixed duration segments") {
        auto durations = {1., 3., 10., 2.};
        trajectory.startFrom(random_pose());

        for (auto duration : durations) {
            trajectory.addWaypoint(random_pose(), duration);
        }

        REQUIRE(trajectory.duration() ==
                std::accumulate(durations.begin(), durations.end(), 0.));
    }
}