if(ENABLE_TESTING)
    # Compile Catch2 main function separately to share it across tests and speed up subsequent builds
    add_library(test_main STATIC common/main.cpp)
    target_link_libraries(test_main PUBLIC CONAN_PKG::catch2)

    # List all the source files composing the tests
    set(trajectory_test_FILES 
        trajectory/polynomial.cpp
        trajectory/trajectory.cpp
    )

    add_executable(trajectory_test ${trajectory_test_FILES})

    target_link_libraries(trajectory_test PUBLIC test_main robot_trajectory)

    add_test(NAME trajectory-test COMMAND trajectory_test)
endif()