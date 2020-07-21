# CMake/Conan project template

## How to use this template
1. Copy it and rename it as your project's name
2. Edit `CMakeLists.txt` and `conanfile.py` to edit the project's name, version, dependencies, etc.
3. Edit the content of `src` and `include` with your library/libraries
4. Edit the content of `test` to add unit tests for your library
5. Edit the content of `apps` to create at least one example application showing how to use the library

## How to build and test the code
From the `build` folder:
1. Configure the project with tests enabled: `cmake -DENABLE_TESTING=ON ..` (you can remove the `-DENABLE_TESTING=ON` part if you don't care about testing)
2. Build the code: `cmake --build . --parallel`
3. To run the tests: `ctest`
4. To create a local reusable Conan package: `conan create .. user/channel` (e.g `conan create .. johndoe/stable`)

## Tips and tricks
* When you add new source files, don't forget to list them in the corresponding `CMakeLists.txt` file otherwise they won't be built
* If your IDE doesn't automatically format your code, you can run the `format.sh` script at the root of the project to do so
* If a test fails, you can find its console output in `build/Testing/Temporary/LastTest.log`. Alternatively, you can run the test manually, e.g `./bin/my_test`. You can pass the `-s` option after the executable name to list successful tests