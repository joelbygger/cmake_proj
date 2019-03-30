# Build info for Catch, unit test framework. Intended to be used in a factory, to create test targets.

# Prepare "Catch" library for other executables.
add_library(Catch INTERFACE)

# Make sure that Catch header can be found by users.
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Special file with the define that will create a main(), required by Catch. Must only exist in one file, so we add it to the Catch target.
target_sources(Catch INTERFACE ${CMAKE_CURRENT_LIST_DIR}/catchMainDefine.cpp)
