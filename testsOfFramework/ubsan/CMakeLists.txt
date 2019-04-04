
# Test that Undefined Behaviour Sanitizer actually works, 
# application should crash.
new_cpp_executable(
        NAME testTool_UBSAN
        SOURCES app1.cpp)      
