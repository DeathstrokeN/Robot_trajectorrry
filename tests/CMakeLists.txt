if(ENABLE_TESTING)
    # Compile Catch2 main function separately to share it across tests and speed up subsequent builds
    add_library(test_main STATIC common/main.cpp)
    target_link_libraries(test_main PUBLIC CONAN_PKG::catch2)

    # List all the source files composing the tests
    set(hello_test_FILES 
        hello/greeter.cpp
    )

    add_executable(hello_test ${hello_test_FILES})

    target_link_libraries(hello_test PUBLIC test_main hello)

    add_test(NAME hello-test COMMAND hello_test)
endif()