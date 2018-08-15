###
# This example builds an executeable but each folder is its own target, 
# increasing mudularity and keeping private things private.
# The idea is to show that we can keep a good modularity, not exposing 
# more than necessary from a target.
###
add_subdirectory(utils)

new_cpp_executeable(
    NAME app2
    SOURCES main.cpp
    LINK_PRIVATE utils) # Link our target to the shared library, this linkage is not of interest to anyone else, keep it private.

