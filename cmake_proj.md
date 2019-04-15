
# Why

This is a template project, a suite of SW development tools available from the start.

* Create new targets faster (also true for new projects).
* Not needing to google compile flags, sanitizers, test frameworks etc.
* Everything gathered in one place (CMake) instead of separate shell scripts/ command line things to remember by heart.
* I can. A curiosity in C++, CMake and all the cool tools embedded C does (did) not have (how cool are sanitizers?). And that Jason Turner said to "use the tools available" <https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md>.

Perhaps this structure gives the greatest benefit when creating many targets, e.g. when working on <https://adventofcode.com/>.

I have not found similar things online, but it may be due to googling skills. There will be drawbacks, perhaps one does not want Cppcheck executed on every build, but that's quite easy to fix. And the taste is like the bum...

# What

* Based on CMake
* Tested with GCC (mainly)
* Clang (partially)
* MAKE

If nothing else is stated, everything applies to both Clang and GCC.

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

## Cppcheck

A static analysis tool.
Must be installed on system. Increases build time and produces extra output, also when there are no findings. Example output:

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

A global configuration file is available in project root [CppCheckSuppressions.txt](CppCheckSuppressions.txt).

For more info see [external/cppcheck.cmake](external/cppcheck.cmake).

## Clang tidy

A static analysis tool.
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

Include What You use (IWYU). IWYU must be installed on your system. Will be executed on all builds.

A global configuration file is available in project root [iwyu.imp](iwyu.imp).

For more info see [external/iwyu.cmake](external/iwyu.cmake).

### GCC

To my understanding IWYU is designed for Clang and has some issues understanding all GCC compiler flags, you might get some warnings on this, I choose to just ignore it as long as GCC is happy, e.g.:

```bash
Warning: include-what-you-use reported diagnostics:
error: unsupported argument 'pointer-compare' to option 'fsanitize='
warning: unknown warning option '-Wduplicated-cond'; did you mean '-Wduplicate-enum'? [-Wunknown-warning-option]
```

# Additional features

Some features are not always added to your targets (they add execution time, not intended for release..., of course one uses them as one wishes). The features are added with defines passed to CMake during configuration.

Implemented in [factories/settings/flags.cmake](factories/settings/flags.cmake), called by the factories.

* ASAN (see section [ASAN](#ASAN))
* TSAN (see section [TSAN](#TSAN))
* LIBSTDCXX_CHECK : Check STL usage (libstdc++) (see section [incorrect-STL-usage](#incorrect-STL-usage))

## ASAN

Address sanitizer, run time checks. Cannot be used at same time as TSAN. A custom CMake configuration define tells factories to add required compiler flags. To add it to all build targets:

```bash
cmake -DASAN=1 ..
```

ASAN can be controlled with additional flags, see <https://github.com/google/sanitizers/wiki/AddressSanitizerFlags>, the list below is by no means complete and only for my convenience:

* Common to ASAN, TSAN and MSAN.
  * strict_string_checks=true:full_address_space=true:decorate_proc_maps=true
* print_stats=true # Print various statistics after printing an error message or if atexit=1.
* atexit=true # If set, prints ASan exit stats even after program terminates successfully.
* export ASAN_OPTIONS="halt_on_error=false:detect_invalid_pointer_pairs=2:detect_stack_use_after_return=true:check_initialization_order=true:strict_init_order=true:print_scariness=true:alloc_dealloc_mismatch=true"

## TSAN

Thread sanitizer, run time checks. Cannot be used at the same time as ASAN. May catch errors that ASAN would also catch. A custom CMake configuration define tells factories to add required compiler flags. To add it to all build targets:

```bash
cmake -DTSAN=1 ..
```

TSAN can be controlled with additional flags, I think defaults seems ok (as of today), see <https://github.com/google/sanitizers/wiki/ThreadSanitizerFlags>.

## Incorrect STL usage

Only applicable if you use `libstdc++` (to my knowledge normally true on Linux, both for GCC and Clang). A custom CMake configuration define tells factories to add required compiler define.

* Finds stuff analyzers can't.
* May greatly increase execution time.
* IWYU might give you new warnings.
* Your entire application must be built with these flags (if you use things from outside this project).
* Should probably not be present in release.

For background see <https://kristerw.blogspot.com/2018/03/detecting-incorrect-c-stl-usage.html>

To add it to all build targets (independent on whether you use libstdc++ or not):

```bash
cmake -DLIBSTDCXX_CHECK=1 ..
```

# Catch2

Unit test framework.
Included in repository, to save build time it's only built once and is linked to all created test executables. All tests are added to CTest, which makes them easy to execute.

Tests should be added via appropriate factory, see [factories](factories).

# Framework tests

To be sure that the tools and additional checks are actually working with your setup there are a number of tests:

* [UBSAN](#UBSAN)
* [ASAN](#ASAN)
* [incorrect-STL-usage](#incorrect-STL-usage)

The tests consists of a test runner, for each test it spawns a thread. The runner will only look on return value from a test (and print it to stdout), a test returning 0 will be considered ok. You as user must evaluate if this is the result you expected from this particular test. E.g. if you activate any [Additional features](#additional-features) the corresponding test should crash (return != 0).

All tests located under: [testsOfFramework](testsOfFramework). Tests must be started manually, they are not part of CTest since I'm not sure one wants them always executed and I am not sure how to make the test result evaluation reliable (is my assumption of e.g. UBSAN tool always resulting in non-zero return value?).

The tests will not in any way be exhaustive, they are only intended to make sure that e.g. ASAN is active for some scenario, not that ASAN finds all bugs ASAN can find.

# Notes on the CMake design

The factories are CMakeLists.txt files. The external tool files under [external](external) (e.g. [Clang tidy](external/clang_tidy.cmake)) are CMake include files. Simply because I did not get it to work in a nice way otherwise.

In some places CMake command `glob` is used, this is normally considered bad CMake style and could maybe be changed to something else.
