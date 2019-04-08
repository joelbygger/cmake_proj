
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

## Create targets

All targets you want to create should use the target factories. This will make sure correct build options are added and that all 3rd party tools are part of the build (or additional build targets are created).

Factories and usage instructions available in [factories](factories).

## Tests

Tests for framework functionality: [testsOfFramework](testsOfFramework).

Your application should be placed under [src](src).

# Tools

Analyzes, tests or corrects your code.

When you create a target via the factory the tools below will be added automatically.
They will either be added to your target and executed every time you build or execute the target (depending on tool), or added as a new target.

Implemented in [external](external), called by the factories.

## Clang tidy

Added for executable and libs.
Requires Clang compiler etc. Can be used with GCC as main compiler.

For more info see [external/clang_tidy.cmake](external/clang_tidy.cmake).

### Main compiler GCC

When using GCC a new taget will be created: `${targetName}_clang_tidy`. Since Clang tidy uses the Clang compiler, but the target was created with GCC compiler flags there will be some warnings about unknown compiler flags, e.g. ```warning: unknown warning option '-Wduplicated-branches' [clang-diagnostic-unknown-warning-option]```

### Main compiler Clang

Added as arguments to Clang, will be part of every build.

## UBSAN

Undefined Behavior Sanitizer. Adds very little overhead to binary, always active. Currently only when using GCC.

For more info see [factories/settings/flags.cmake](factories/settings/flags.cmake).

## IWYU

Include What You use (IWYU). IWYU must be installed on your system. Added to all targets and will be executed on all builds. A configuration file is available in project root [iwyu.imp](iwyu.imp).

For more info see [external/iwyu.cmake](external/iwyu.cmake).

# Additional features

Some features are not always added to your targets (they add execution time, not intended for release..., of course one uses them as one wishes). The features are added with defines passed to CMake during configuration.

Implemented in [factories/settings/flags.cmake](factories/settings/flags.cmake), called by the factories.

* xxx (see section [ASAN](#ASAN))
* xxx (see section [TSAN](#TSAN))
* LIBSTDCXX_CHECK : Check STL usage (libstdc++) (see section [incorrect-STL-usage](#incorrect-STL-usage))

## ASAN

## TSAN

## Incorrect STL usage

Only applicable if you use `libstdc++` (to my knowledge normally true on Linux, both for GCC and Clang). A custom CMake configuration define adds compiler defines.

* Finds stuff analyzers can't.
* May greatly increase execution time.
* IWYU might give you new warnings.
* Your entire application must be built with these flags (if you use things from outside this project).
* Should probably not be present in release.

For background see <https://kristerw.blogspot.com/2018/03/detecting-incorrect-c-stl-usage.html>

To add it to your build target (independent on whether you use libstdc++ or not):

```bash
cmake -DLIBSTDCXX_CHECK=1 ..
```

# Framework tests

To be sure that the tools and additional checks are actually working with your setup there are a number of tests:

* [UBSAN](#UBSAN)
* [incorrect-STL-usage](#incorrect-STL-usage)

The tests consists of a test runner, for each test it spawns a thread. The runner will only look on return value from a test (and print it to stdout), a test returning 0 will be considered ok. You as user must evaluate if this is the result you expected from this particular test. E.g. if you activate any [Additional features](#additional-features) the corresponding test should crash (return != 0).

All tests located under: [testsOfFramework](testsOfFramework). Tests must be started manually, they are not part of CTest since I'm not sure one wants them always executed and I am not sure how to make the test result evaluation reliable (is my assumption of e.g. UBSAN tool always resulting in non-zero return value?).

The tests will not in any way be exhaustive, they are only intended to make sure that e.g. ASAN is active for some scenario, not that ASAN finds all bugs ASAN can find.

# Notes on the CMake design

The factories are CMakeLists.txt files. The external tool files under [external](external) (e.g. [Clang tidy](external/clang_tidy.cmake)) are CMake include files. Simply because I did not get it to work in a nice way otherwise.

In some places CMake command `glob` is used, this is normally considered bad CMake style and could maybe be changed to something else.