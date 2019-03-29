
# Where the logic is.
new_cpp_library_shared(
        NAME day5lib
        SOURCES polymer.cpp polymer.hpp)

# For command line execution.
new_cpp_executeable(
        NAME day5
        SOURCES main.cpp
        LINK_PRIVATE day5lib)

# Tests for the logic.
new_cpp_utest_executeable(
        NAME day5libTest
        SOURCES test.cpp
        LINK_PRIVATE day5lib)