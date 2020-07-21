add_executable(greeter ${CMAKE_CURRENT_SOURCE_DIR}/greeter/main.cpp)
target_link_libraries(greeter PUBLIC hello)