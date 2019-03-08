
# Solutions to Advent of Code 2018

Project template based on (clone) <https://github.com/joelbygger/cmake_proj>
Questions from: <https://adventofcode.com/2018>

Project setup with CMake.
GCC and Clang (partly) used.

* IWYU is included when building.
* Available as build commands:
  * Clang format
  * Clang tidy (if GCC, will be auto part of compile when using Clang)

Clang static analyzer available as separate shell-script.

# Day1

Currently has issues building \<filesystem\> with Clang. More info in the targets CMakeLists.txt.
This also results in target day1_clang_tidy doesn't work.
