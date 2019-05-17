

# Where the logic is.
new_cpp_library_shared(
        NAME day2lib
        SOURCES manager.cpp manager.hpp)

# For command line execution.
new_cpp_executable(
        NAME day2
        SOURCES main.cpp
        LINK_PRIVATE day2lib)

# Tests for the logic.
new_cpp_utest_executable(
        NAME day2libTest
        SOURCES test.cpp input.hpp
        LINK_PRIVATE day2lib)
