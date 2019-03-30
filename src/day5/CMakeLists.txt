
# Where the logic is.
new_cpp_library_shared(
        NAME day5lib
        SOURCES polymer.cpp polymer.hpp)

# For command line execution.
new_cpp_executable(
        NAME day5
        SOURCES main.cpp
        LINK_PRIVATE day5lib)

# Tests for the logic.
new_cpp_utest_executable(
        NAME day5libTest
        SOURCES test.cpp input.hpp
        LINK_PRIVATE day5lib)