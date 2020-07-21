# List all the source files composing the library
set(hello_FILES 
    hello/hello.cpp
)

# will be a shared or static library depending on BUILD_SHARED_LIBS
add_library(hello ${hello_FILES})

target_include_directories(hello PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_compile_features(hello PUBLIC cxx_std_11)

target_link_libraries(hello PUBLIC CONAN_PKG::fmt)

install(
    TARGETS hello
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include 
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)