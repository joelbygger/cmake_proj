
# Test that command line flag LIBSTDCXX_CHECK actually works, 
# application should crash when flag is active.
new_cpp_library_shared(
        NAME testTool_LIBSTDCXX_CHECK
        SOURCES libcxx_debug.cpp libcxx_debug.hpp
        INCLUDE_PUBLIC ${CMAKE_CURRENT_LIST_DIR}
        LINK_PUBLIC testTool_testBase)
