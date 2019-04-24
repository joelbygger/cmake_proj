
# Why

This is a C++ template project, combining different SW development tools.

* Create new targets (or projects) faster.
* No need to google compile flags, sanitizers, test frameworks etc.
* All SW development performed via one tool (e.g. Make, via CMake) instead of separate script files/ command line things (less to remember by heart).
* I can and a curiosity in C++, CMake and all the cool tools C for embedded does (did) not have (how cool are sanitizers?). And that Jason Turner said to "use the tools available" <https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md>.

The structure of this template project may perhaps give the greatest benefit when creating many targets.

I have not found similar things online, but it may be due to googling skills. There will be drawbacks, if something is bad or missing it should be easy to add or adapt. This project is developed according to my needs.

# What

A CMake framework, a user performs one function call to create a library or an executable. The created target will then automatically get:

* All build flags
* These tools executed at every build/ added to target runtime:
  * [UBSAN](#UBSAN)
  * [IWYU](#IWYU)
  * [Cppcheck](#Cppcheck)
  * [Clang tidy](#Clang-tidy) (when using Clang)
* Additional helper-targets created for:
  * [Clang tidy](#Clang-tidy) (when using GCC)
* These tools executed at every build/ added to target runtime (if activated during CMake configuration, they add execution time/ not intended for release):
  * [ASAN](#ASAN)
  * [TSAN](#TSAN)
  * [Incorrect-STL-usage](#Incorrect-STL-usage)

The project will also have one target added for code formatting, formatting all the code using [Clang format](#Clang-format).

Unit tests are run with [Catch2](#Catch2).

If you are running a normal development environment (e.g. Ubuntu) and have the following tools installed, everything should work (if you don't it SHOULD work, the feature needing the framework will just be omitted with a warning during CMake configuration):

* CMake (tested with Make as build system)
* GCC (not required if you use Clang)
* LLVM, Clang (required if you use GCC, for e.g. clang-tidy)
* MAKE
* Cppcheck
* IWYU

If nothing else is stated, everything applies to both Clang and GCC.

There are some tests for the framework functionality, [Framework tests](#Framework-tests).

# How to use

Users should need to adapt and add very little to get up and running. Change the CMake project name and description and start adding targets via the factories.

## CMake configuration

Run as you normally would, e.g.:

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug  ..
```

or perhaps:

```bash
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=/usr/bin/clang++-7 ..
```

## Create targets

All targets you want to create should use the target factories. This will make sure correct build options are added and that all 3rd party tools are part of the build (or additional build targets are created).

Factories and usage instructions available in [factories](factories).

# Static analyzers

## Cppcheck

A static analysis tool. Increases build time and produces extra output (also when there are no findings). Example output:

```bash
[ 61%] Building CXX object src/a/CMakeFiles/a.dir/file1.cpp.o
Checking /home/joel/dev/cmake_proj/src/a/file1.cpp ...
[ 64%] Building CXX object src/a/CMakeFiles/a.dir/file2.cpp.o
Checking /home/joel/dev/cmake_proj/src/a/file2.cpp ...
Warning: cppcheck reported diagnostics:
[/home/joel/dev/cmake_proj/src/a/file2.hpp:17]: (style) Class 'decoder' has a constructor with 1 argument that is not explicit.
```

Without Cppcheck:

```bash
[ 61%] Building CXX object src/a/CMakeFiles/a.dir/file1.cpp.o
[ 64%] Building CXX object src/a/CMakeFiles/a.dir/file2.cpp.o
```

When a target is created it's possible to opt-out of Cppcheck. Nice if you build 3rd party stuff. If Cppcheck is too bloated it would be possible to create a special target for it, similar clang-tidy for GCC.

A configuration file is available in project root [CppCheckSuppressions.txt](CppCheckSuppressions.txt). For more info see [external/cppcheck.cmake](external/cppcheck.cmake).

## Clang tidy

A static analysis tool.
Requires Clang compiler etc. Can be used with GCC as main compiler. For more info see [external/clang_tidy.cmake](external/clang_tidy.cmake).

### Main compiler GCC

When using GCC a new taget will be created: `${targetName}_clang_tidy`. Since Clang tidy uses the Clang compiler, but the target was created with GCC compiler flags there will be some warnings about unknown compiler flags, e.g. ```warning: unknown warning option '-Wduplicated-branches' [clang-diagnostic-unknown-warning-option]```

### Main compiler Clang

Added as arguments to Clang, will be part of every build.

# Runtime checkers

## UBSAN

Undefined Behavior Sanitizer. Adds very little overhead to binary. Also see section [About sanitizers](#about-sanitizers). For more info see [factories/settings/flags.cmake](factories/settings/flags.cmake).

## ASAN

Address sanitizer, run time checks. Cannot be used at same time as TSAN. A custom CMake configuration define tells factories to add required compiler flags. Also see section [About sanitizers](#about-sanitizers). For more info see [factories/settings/flags.cmake](factories/settings/flags.cmake). To add it to all build targets:

```bash
cmake -DASAN=1 ..
```

## TSAN

Thread sanitizer, run time checks. Cannot be used at the same time as ASAN. May catch errors that ASAN would also catch. Note that all libraries you link to should be compiled with TSAN or you might get false positives etc. But i guess using it w/o proper libraries is better than nothing. A custom CMake configuration define tells factories to add required compiler flags. For more info see [factories/settings/flags.cmake](factories/settings/flags.cmake). To add it to all build targets:

```bash
cmake -DTSAN=1 ..
```

TSAN can be controlled with additional flags, I think defaults seems ok (as of today), see <https://github.com/google/sanitizers/wiki/ThreadSanitizerFlags>. Also see section [About sanitizers](#about-sanitizers).

## Incorrect STL usage

Only applicable if you use `libstdc++` (to my knowledge normally true on Linux, both for GCC and Clang). A custom CMake configuration define tells factories to add required compiler define.

* Finds stuff analyzers can't.
* May greatly increase execution time.
* Your entire application must be built with these flags (if you use things from outside this project).
* Should probably not be present in release.
* Drawback, IWYU might give you new warnings on STL code.

For background see <https://kristerw.blogspot.com/2018/03/detecting-incorrect-c-stl-usage.html>. For more info see [factories/settings/flags.cmake](factories/settings/flags.cmake). To add it to all build targets (independent on whether you use libstdc++ or not):

```bash
cmake -DLIBSTDCXX_CHECK=1 ..
```

## IWYU

Include What You use (IWYU). IWYU must be installed on your system. Will be executed on all builds. A configuration file is available in project root [iwyu.imp](iwyu.imp). For more info see [external/iwyu.cmake](external/iwyu.cmake).

### GCC

To my understanding IWYU is designed for Clang and has some issues understanding all GCC compiler flags, you might get some warnings on this, I choose to just ignore it as long as GCC is happy, e.g.:

```bash
Warning: include-what-you-use reported diagnostics:
error: unsupported argument 'pointer-compare' to option 'fsanitize='
warning: unknown warning option '-Wduplicated-cond'; did you mean '-Wduplicate-enum'? [-Wunknown-warning-option]
```

# Other tools

## Clang format

Code formatting. A configuration file is available in project root [.clang-format](.clang-format). For more info see [external/clang_format.cmake](external/clang_format.cmake) (in lack of imagination uses CMake glob feature, as a result CMake must be reconfigured when new source files are added).

# Testing

## Catch2

Unit test framework.
Included in repository, to save build time it's only built once and is linked to all created test executables. All tests are added to CTest, which makes them easy to execute. For more info see folder [external/catch2](external/catch2).

Tests are added via appropriate factory, see folder [factories](factories).

## Framework tests

There are a number of tests of the framework, to be sure that compiler and link flags are set correctly and that your compiled code is instrumented as expected. The tests will not in any way be exhaustive, they are only intended to make sure that e.g. ASAN is active for some scenario, not that ASAN finds all bugs ASAN can find. Tests located in folder [testsOfFramework](testsOfFramework). The following tests are available:

* [UBSAN](#UBSAN)
* [ASAN](#ASAN)
* [TSAN](#TSAN)
* [incorrect-STL-usage](#incorrect-STL-usage)

These tests does not rely on any testing framework. There is one binary consisting of a test runner, for each test it spawns a thread. The runner will only look on return value from a test (and print it to stdout), a test returning 0 will be considered ok. You as user must manually evaluate if this is the result you expected from this particular test. E.g. if you activate any sanitizers during CMake configuration the corresponding test should crash (return != 0).

These tests are not reported to CTest and must be started manually (opposed to tests created with the test factory). One reason is that they are expected to crash, which I don't think is "native" behavior to Catch2, another reason is that I don't think e.g. UBSAN always crashes the same way on all platforms (well, this project is perhaps not platform independent anyway...).

# About sanitizers

For proper stack traces with line numbers *SAN_SYMBOLIZER_PATH must be available, the easiest way (in Ubuntu) is to have llvm installed, and not e.g. llvm-7. Then you can find 'llvm-symbolizer' instead of 'llvm-symbolizer-7'.

*SAN can be controlled with additional flags, see e.g. <https://github.com/google/sanitizers/wiki/AddressSanitizerFlags>.

The list below is by no means complete and only for my convenience. Common to ASAN, TSAN and MSAN:

* strict_string_checks=true:full_address_space=true:decorate_proc_maps=true

For ASAN:

* print_stats=true # Print various statistics after printing an error message or if atexit=1.
* atexit=true # If set, prints ASan exit stats even after program terminates successfully.
* export ASAN_OPTIONS="halt_on_error=false:detect_invalid_pointer_pairs=2:detect_stack_use_after_return=true:check_initialization_order=true:strict_init_order=true:print_scariness=true:alloc_dealloc_mismatch=true"

# Disclaimers

This project is no 100% platform independent, e.g. some sanitizers might not work on Windows, if you get no complaints when configuring/ compiling it probably works...

## Notes on the CMake design

The factories are CMakeLists.txt files. The external tool files under [external](external) (e.g. [Clang tidy](external/clang_tidy.cmake)) are CMake include files. Simply because I did not get it to work in a nice way otherwise.

In some places CMake command `glob` is used, this is normally considered bad CMake style and could maybe be changed to something else.
