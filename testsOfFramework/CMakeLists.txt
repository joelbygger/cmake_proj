
# Add the tests.
add_subdirectory(libstdcxx_check)
add_subdirectory(ubsan)

# This 'base lib' is used by all the test libs, to create a common interface.
new_cpp_library_shared(
        NAME testTool_testBase
        SOURCES test_base.cpp test_base.hpp
        INCLUDE_PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# The test runner.
new_cpp_executable(
        NAME testTool_main
        SOURCES main.cpp
        LINK_PRIVATE testTool_UBSAN)
