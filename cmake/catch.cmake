# Adds a target to run tests with Catch unit test framework.

# Activate CTest.
enable_testing()

# Prepare "Catch" library for other executables.
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR})
add_library(Catch INTERFACE) # Not using the factory and not getting all compiler flags etc., an issue?
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Create path to the special file with the define that will create a main(), required by Catch.
set(CATCH_MAIN_DEFINE_FILE ${CMAKE_CURRENT_LIST_DIR}/catchMainDefine.cpp)



###
# Factory for generating executable test targets. Will add the Catch library automagically.
# Usage (from some CMakeLists.txt file):
#    new_cpp_utest_executeable(
#        NAME yourTargetName
#        SOURCES a.cpp priv.cpp priv.hpp
#        INCLUDE_PRIVATE pathToPrivateIncludeFolder
#        LINK_PRIVATE yourCUT and other target withPrivateLinkage)
###
function(new_cpp_utest_executeable)
    # Extract function params.
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES INCLUDE_PRIVATE LINK_PRIVATE)
    cmake_parse_arguments(EXEC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Not sure how we can get an unparsed argument(s), but I think we want to inform user about it.
    if(EXEC_UNPARSED_ARGUMENTS)
        message(WARNING "---- Unparsed arguments: " ${EXEC_UNPARSED_ARGUMENTS} " when trying to make target:" ${EXEC_NAME})
    endif()

    new_cpp_executeable(
            NAME ${EXEC_NAME}
            SOURCES ${EXEC_SOURCES} ${CATCH_MAIN_DEFINE_FILE} # Add an extra file with the required Catch define.
            INCLUDE_PRIVATE ${EXEC_INCLUDE_PRIVATE}
            LINK_PRIVATE ${EXEC_LINK_PRIVATE} Catch) # Add the Catch library.

    # Report executable to CTest.
    add_test(
            NAME ${EXEC_NAME}
            COMMAND ${EXEC_NAME})
endfunction()