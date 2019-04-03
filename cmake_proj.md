
# Why

This is a template project, my attempt to get up and running faster when starting a new project. The goal is to always have all nice SW development tools available from the start, without needing to google compile flags, sanitizers, test frameworks etc. Maybe this template structure gives the greatest benefit when you create many targets, e.g. when you try to solve <https://adventofcode.com/>.

Also because Jason Turner said to "use the tools available" <https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md>.

# What

* Based on CMake
* Tested with GCC (mainly)
* Clang (partially)
* MAKE

# How to use

## CMake configuration

Run as you normally would, e.g.:

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug  ..
```

or perhaps:

```bash
make -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=/usr/bin/clang++-7 ..
```

## Additional features

Some features are not always added to your targets (adds execution time, not intended for release..., of course one uses them as one wishes). The features are added with defines passed to CMake during configuration.

* ASAN
* TSAN
* [LIBSTDCXX_CHECK](stdlibcxx_check)

## Create targets

All targets you want to create should use the target factories. This will make sure correct build options are added and that all 3rd party tools are part of the build (or additional build targets are created).

Factories and usage instructions available in [factories](factories).

# Tools

Analyzes, tests or corrects your code. When you create a target the tools below will (normally) be added automatically (in the factory).
They will either be added to your target and executed every time you build, or added as a new target.

## Clang tidy

Added for executable and libs.
Requires Clang compiler etc. Can be used with GCC as main compiler.

For more info see [external/clang_tidy.cmake](external/clang_tidy.cmake).

### Main compiler GCC

When using GCC a new taget will be created: `${targetName}_clang_tidy`. Since Clang tidy uses the Clang compiler, but the target was created with GCC compiler flags there will be some warnings about unknown compiler flags, e.g. ```warning: unknown warning option '-Wduplicated-branches' [clang-diagnostic-unknown-warning-option]```

### Main compiler Clang

Added as arguments to Clang, will be part of every build.

## IWYU

Include What You use (IWYU). IWYU must be installed on your system. Added to all targets and will be executed on all builds. A configuration file is available in project root [iwyu.imp](iwyu.imp).

For more info see [external/iwyu.cmake](external/iwyu.cmake).

## [Detecting incorrect C++ STL usage](#stdlibcxx_check)

Only applicable if you use `libstdc++` (which is at least true for GCC on Linux). A CMake custom configuration define adds compiler defines.

* Finds stuff analyzers can't.
* May greatly increase execution time.
* IWYU might give you new warnings.
* Your entire application must be built with these flags (if you use things from outside this project).
* Should probably not be present in release.

That flag works can be tested with [src/testsOfTools/libstdcxx_check](src/testsOfTools/libstdcxx_check). For background see <https://kristerw.blogspot.com/2018/03/detecting-incorrect-c-stl-usage.html>

To add it to your build target (independent on whether you use libstdc++ or not):

```bash
cmake -DLIBSTDCXX_CHECK=1 ..
```

# Notes on the CMake design

The factories are CMakeLists.txt files. The external tool files under [external](external) (e.g. [Clang tidy](external/clang_tidy.cmake)) are CMake include files. Simply because I did not get it to work in a nice way otherwise.

In some places CMake command `glob` is used, this is normally considered bad CMake style and could maybe be changed to something else.