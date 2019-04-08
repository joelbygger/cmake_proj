
# Test that Undefined Behaviour Sanitizer actually works, 
# application should crash.
new_cpp_library_shared(
        NAME testTool_UBSAN
        SOURCES ubsan.cpp ubsan.hpp
        INCLUDE_PUBLIC ${CMAKE_CURRENT_LIST_DIR}
        LINK_PUBLIC testTool_testBase)
