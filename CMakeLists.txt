cmake_minimum_required(VERSION 3.10) # This is a version tested to work, earlier versions probably work as well.

project(adventOfCode2018
        VERSION 0.0.0
        DESCRIPTION "My solution in C++ tp advent of code."
        LANGUAGES CXX)

# All compile commands are written to file "compile_commands.json".
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    message(WARNING "No build type set, default to Release. CMake can be run with e.g. -DCMAKE_BUILD_TYPE=Debug, Release, RelWithDebInfo.")
    set(CMAKE_BUILD_TYPE Release CACHE String "No build type set, we default to release." FORCE)
endif()


include(factories/settings/flags.cmake)
include(factories/settings/strip_symbols.cmake)
include(factories/utest.cmake)
include(factories/executable_and_lib.cmake)
include(external/clang_tidy.cmake)
include(external/iwyu.cmake)
include(external/clang_format.cmake)
include(external/cppcheck.cmake)

add_subdirectory(external/catch2)
add_subdirectory(testsOfFramework)
add_subdirectory(src)
