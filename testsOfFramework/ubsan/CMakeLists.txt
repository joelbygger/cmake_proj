
# Test that command line flag LIBSTDCXX_CHECK actually works, 
# application should crash when flag is active.
new_cpp_executable(
        NAME testTool_LIBSTDCXX_CHECK_1
        SOURCES app1.cpp)
new_cpp_executable(
        NAME testTool_LIBSTDCXX_CHECK_2
        SOURCES app1.cpp)        
