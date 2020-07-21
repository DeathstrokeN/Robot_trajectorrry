from conans import ConanFile, CMake, tools


class ProjectTemplateConan(ConanFile):
    name = "project-template"
    version = "1.0"
    license = "BSD"
    author = "Your name <your@email.com>"
    url = "you-git-project-homepage.com"
    description = "A Conan/CMake template project"
    topics = "C++", "Conan", "CMake"  # add/modify topics
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [
        True, False], "build_tests": [True, False]}
    default_options = {"shared": False, "fPIC": True, "build_tests": False}
    generators = "cmake"
    requires = "fmt/7.0.1"  # add/modify dependencies if needed
    exports_sources = "!.clangd*", "!.ccls-cache*", "!compile_commands.json", "*"

    def requirements(self):
        if self.options.build_tests:
            self.requires("cppcheck_installer/2.0@bincrafters/stable")
            self.requires("catch2/2.13.0")
            # add test dependencies here if needed

    def configure(self):
        if self.settings.compiler == 'Visual Studio':
            del self.options.fPIC

    def build(self):
        cmake = CMake(self)
        if self.options.build_tests:
            cmake.definitions["ENABLE_TESTING"] = True
        cmake.configure()
        cmake.build()
        if self.options.build_tests:
            cmake.test()
        cmake.install()

    def package(self):
        self.copy("bin/*", dst="bin", keep_path=False)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["hello"]
