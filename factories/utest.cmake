# Adds a target to run unit tests, currently with Catch unit test framework.

# Activate CTest.
enable_testing()


###
# Factory for generating executable test targets. Will add the Catch library automagically.
# Usage (from some CMakeLists.txt file):
#    new_cpp_utest_executable(
#        NAME yourTargetName
#        SOURCES a.cpp priv.cpp priv.hpp
#        INCLUDE_PRIVATE pathToPrivateIncludeFolder
#        LINK_PRIVATE yourCUT and other target withPrivateLinkage)
###
function(new_cpp_utest_executable)
    # Extract function params.
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES INCLUDE_PRIVATE LINK_PRIVATE)
    cmake_parse_arguments(EXEC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Not sure how we can get an unparsed argument(s), but I think we want to inform user about it.
    if(EXEC_UNPARSED_ARGUMENTS)
        message(WARNING "---- Unparsed arguments: " ${EXEC_UNPARSED_ARGUMENTS} " when trying to make target:" ${EXEC_NAME})
    endif()

    # Use existing factory to make sure all compiler warnings etc. are included.
    new_cpp_executable(
            NAME ${EXEC_NAME}
            SOURCES ${EXEC_SOURCES}
            INCLUDE_PRIVATE ${EXEC_INCLUDE_PRIVATE}
            LINK_PRIVATE ${EXEC_LINK_PRIVATE} Catch) # Here we add Catch library, if another utest framework is desired, change this.

    # Report executable to CTest.
    add_test(
            NAME ${EXEC_NAME}
            COMMAND ${EXEC_NAME})
endfunction()