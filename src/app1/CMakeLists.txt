###
# This example builds a simple executeable, created using our custom factory.
###

new_cpp_executeable(
        NAME app1
        SOURCES main.cpp utils/utils.cpp
        INCLUDE_PRIVATE ${CMAKE_CURRENT_SOURCE_DIR/utils}) # Files in this folder are not of interest to anyone else, keep it private.

