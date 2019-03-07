cmake_minimum_required(VERSION 3.10) # This is a version tested to work, earlier versions probably work as well.

project(cmake_template_cpp_proj
        VERSION 0.0.0
        DESCRIPTION "CMake C++ template project with additinal useful tools."
        LANGUAGES CXX)

# All compile commands are written to file "compile_commands.json".
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    message(WARNING "No build type set, default to Release. CMake can be run with e.g. -DCMAKE_BUILD_TYPE=Debug, Release, RelWithDebInfo.")
    set(CMAKE_BUILD_TYPE Release CACHE String "No build type set, we default to release." FORCE)
endif()


include( cmake/clang_tidy.cmake)
include( cmake/iwyu.cmake)
include( cmake/clang_format.cmake )
include( cmake/target_factory.cmake )

add_subdirectory(src)
