# List all the source files composing the library
set(robot_trajectory_FILES 
    robot_trajectory/polynomial.cpp
    robot_trajectory/trajectory_generator.cpp
)

# will be a shared or static library depending on BUILD_SHARED_LIBS
add_library(robot_trajectory ${robot_trajectory_FILES})

target_include_directories(robot_trajectory PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_compile_features(robot_trajectory PUBLIC cxx_std_17)

add_warnings(robot_trajectory)

# Keep converage_config for coverage reports
target_link_libraries(
    robot_trajectory 
    PUBLIC 
        CONAN_PKG::fmt
        CONAN_PKG::eigen-extensions
        coverage_config 
)

install(
    TARGETS robot_trajectory
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include 
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)