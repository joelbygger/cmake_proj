
# Test that Thread Sanitizer actually works, 
# application should crash.
new_cpp_library_shared(
        NAME testTool_TSAN
        SOURCES tsan.cpp tsan.hpp
        INCLUDE_PUBLIC ${CMAKE_CURRENT_LIST_DIR}
        LINK_PUBLIC testTool_testBase)
