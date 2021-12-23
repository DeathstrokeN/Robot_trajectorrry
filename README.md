@DeathstrokeN, BELLILA Ahmed Nassim
# robot-trajectory project

This project provides a library to compute trajectories in Cartesian space.

## Objective

Using the [Eigen](eigen.tuxfamily.org/) (linear algebra) librarie, implement the algorithms required to compute Cartesian space trajectories composed of multiple waypoints with velocity/acceleration or time constraints between them. 

A code skeleton is provided. Fill all functions inside *src/robot_trajectory/{polynomial,trajectory_generator}.cpp* that are tagged with a `//TODO implement` comment. While implementing a function, remove any `[[maybe_unused]]` attribute as they are present only to avoid warnings.

You must **not** modify the existing `Polynomial` and `TrajectoryGenerator` classes public interfaces (functions, variables, types), but you are free to add any member function or variable. This makes sure that all unit tests in *tests/trajectory/{polynomial,trajectory}.cpp* can be compiled without any modification. If you add new public member functions, please try to add unit tests for them.

For simplification, consider that the velocities and accelerations at the waypoints are zero and that all six components are synchronized at each waypoint (the longest one dictate the duration of the other ones).

## Bonus objective

If you managed to complete everything that is listed above in time, you can try to generalize the approach by considering non-zero velocities and accelerations at the waypoints and different synchronization strategies. Each point can be implemented separately.

1. In contrast with null velocities and accelerations at the waypoints, the general case doesn't have an explicit solution for the minimum duration required to respect the velocity and acceleration limits. An iterative algorithm has to be implemented to find such minimum time.

2. The waypoint synchronization is one of different ways to synchronize the six components of the trajectory:
   1.  Whole trajectory synchronization: the only synchronization point is at the final waypoint. This can lead to shorter trajectories if synchronization at the waypoint level is not required
   2.  No synchronization: all components take the shortest amount of time to complete. This leads to the shortest possible trajectories if no sort of synchronization is required.

Refer to *docs/trajectory_generation.pdf* for the equations to implement these two strategies.

A successful implementation of either or both of these strategies will grant you bonus points.

## How to build and test the code
From the `build` folder:
1. Configure the project with tests enabled: `cmake -DENABLE_TESTING=ON ..` (you can remove the `-DENABLE_TESTING=ON` part if you don't care about testing)
2. Build the code: `cmake --build . --parallel`
3. To run the tests: `ctest`
4. To create a local reusable Conan package: `conan create .. user/channel` (e.g `conan create .. johndoe/stable`)

## Tips and tricks
* When you add new source files, don't forget to list them in the corresponding `CMakeLists.txt` file otherwise they won't be built
* If your IDE doesn't automatically format your code, you can run the `format.sh` script at the root of the project to do so
* You can generate the Doxygen documentation using the `doc` target: `cmake --build . --target doc`. Then just open the `build/docs/index.html` file in your browser to access it.
* To enforce good coding practice, the compiler is configured to generate more warnings and to treat all warnings as errors. Both of these aspects can be disabled using the `MORE_WARNINGS` and `WARNINGS_AS_ERRORS` CMake options.
* If a test fails, you can find its console output in `build/Testing/Temporary/LastTest.log`. Alternatively, you can run the test manually, e.g `./bin/my_test`. You can pass the `-s` option after the executable name to list successful tests
