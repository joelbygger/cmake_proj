# Build info for Catch, unit test framework. Intended to be used in a factory, to create test targets.

# Prepare "Catch" library for other executables.
add_library(Catch INTERFACE)

# Make sure that Catch header can be found by users.
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Special file with the define that will create a main(), required by Catch. Must only exist in one file.
# File takes a long time to compile, add it as a shared lib once instead as something to compile for every 
# utest target, seems to work.
new_cpp_library_shared(
        NAME catchMainlib
        SOURCES ${CMAKE_CURRENT_LIST_DIR}/catchMain.cpp
        NO_CPPCHECK YES)