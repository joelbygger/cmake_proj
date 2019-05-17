
# This file contains a factory to generate build targets for unit tests, currently with Catch unit test framework.
# There is a lot of bioler plate, functionality to create target is reused from other factory, the main purpose of this
# factory is to remove the need to add the testing framework and register the created binary to CTest.

# Activate CTest.
enable_testing()


###
# Factory for generating executable test targets. Will add the Catch library automagically.
# The created binaries will be added to CTest.
# Usage (from some CMakeLists.txt file):
#    new_cpp_utest_executable(
#        NAME yourTargetName
#        SOURCES a.cpp priv.cpp priv.hpp
#        INCLUDE_PRIVATE pathToPrivateIncludeFolder
#        LINK_PRIVATE yourCUT and other target withPrivateLinkage
#        NO_CPPCHECK trueIfYouDontWantIt)
###
function(new_cpp_utest_executable)
    # Extract function params.
    set(options)
    set(oneValueArgs NAME NO_CPPCHECK)
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
            LINK_PRIVATE ${EXEC_LINK_PRIVATE} Catch catchMainlib # Here we add Catch library, if another utest framework is desired, change this.
            NO_CPPCHECK ${EXEC_NO_CPPCHECK})

    # Report executable to CTest.
    add_test(
            NAME ${EXEC_NAME}
            COMMAND ${EXEC_NAME})
endfunction()