
# cmake_proj

A template to help you get quickly started with C++ projects using CMake and other tools you want to use. Currently for C++, but with minor adaptions works for C. Only tested with Make but everything should work with Ninja and whatnot.

The project is most beneficial when many targets with the same settings are to be created.

The project is written after my own ideas of what I think might be useful, it has not been vetted in the harsh reality of a real project or by other developers.

# How to use

Register what you want to build. Build flags, additional helper targets etc. are added created automagically. To use, from your CMakeLists.txt call e.g. function `new_cpp_executeable(...)` defined in file "cmake/target_factory.cmake". Everything else in folder "cmake" can be ignored.

# What it does

For each thing you register to build the following targets will be created (if the tool is installed):

* build
* run the build (for built binaries)
* clang tidy
* clang format

Additionally these tools will be part of the build process:

* IWYU (Include What You Use)
* LWYU (Link What You Use) (native to CMake, I've had issues with it so currently commented out)

Additional tools that are not part of CMake configuration:

* Clang static analyzer (run via "configurerun_clang_static_analyzer.sh", instructions in file)

## If you don't have some of the tools installed

For Clang tidy etc. CMake will try to find it on your system. If a tool can't be found a message is printed during CMake configuration and the target will not be created, this won't affect creation of targets where the tools isn't required. I.e. missing Clang tidy will only prevent the Clang tidy target to be created.

# Tested

... but not thoroughly or systematically or all the time...
Ubuntu, GCC, Clang.