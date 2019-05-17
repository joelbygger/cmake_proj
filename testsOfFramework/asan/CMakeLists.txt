
# Test that Address Sanitizer actually works, 
# application should crash.
new_cpp_library_shared(
        NAME testTool_ASAN
        SOURCES asan.cpp asan.hpp
        INCLUDE_PUBLIC ${CMAKE_CURRENT_LIST_DIR}
        LINK_PUBLIC testTool_testBase)
