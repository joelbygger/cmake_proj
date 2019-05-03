# This file contains factories to generate build targets. Intended to make sure
# all build targets gets the correct global compilation options, tooling etc.

# First include functions needed by the factories.
# The functions will becode project global (since this file is included at top-level)
# but for "readability" I still include the sub-files in this file.
include(${CMAKE_CURRENT_LIST_DIR}/helpers/strip_symbols.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/helpers/set_common_target_stuff.cmake)

###
# Factory for generating executable targets.
# Usage (from some CMakeLists.txt file):
#    new_cpp_executable(
#        NAME yourTargetName
#        SOURCES a.cpp priv.cpp priv.hpp
#        INCLUDE_PUBLIC pathToPublicIncludeFolder
#        INCLUDE_PRIVATE pathToPrivateIncludeFolder
#        LINK_PUBLIC different target withPublicLinkage
#        LINK_PRIVATE different target withPrivateLinkage
#        NO_CPPCHECK trueIfYouDontWantIt)
###
function(new_cpp_executable)
    # Extract function params.
    set(options)
    set(oneValueArgs NAME NO_CPPCHECK)
    set(multiValueArgs SOURCES INCLUDE_PUBLIC INCLUDE_PRIVATE LINK_PUBLIC LINK_PRIVATE)
    cmake_parse_arguments(EXEC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Not sure how we can get an unparsed argument(s), but I think we want to inform user about it.
    if(EXEC_UNPARSED_ARGUMENTS)
        message(WARNING "---- Unparsed arguments: " ${EXEC_UNPARSED_ARGUMENTS} " when trying to make target:" ${EXEC_NAME})
    endif()

    add_executable(${EXEC_NAME} ${EXEC_SOURCES})

    set_common_target_stuff(
            NAME ${EXEC_NAME}
            SOURCES ${EXEC_SOURCES}
            INCLUDE_PUBLIC ${EXEC_INCLUDE_PUBLIC}
            INCLUDE_PRIVATE ${EXEC_INCLUDE_PRIVATE}
            LINK_PUBLIC ${EXEC_LINK_PUBLIC}
            LINK_PRIVATE ${EXEC_LINK_PRIVATE}
            NO_CPPCHECK ${EXEC_NO_CPPCHECK})

    if (CMAKE_BUILD_TYPE STREQUAL Release)
        strip_symbols(
                NAME ${EXEC_NAME}
                INPUT ${EXEC_NAME})
    endif ()

    # Create a command to execute built binary.
    add_custom_target(${EXEC_NAME}_run
            COMMAND ${EXEC_NAME}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Run generated binary in ${CMAKE_CURRENT_SOURCE_DIR}")

endfunction()



###
# Factory for generating library targets.
# Usage (from some CMakeLists.txt file):
#    new_cpp_library_shared(
#        NAME yourTargetName
#        SOURCES a.cpp priv.cpp priv.hpp
#        INCLUDE_PUBLIC pathToPublicIncludeFolder
#        INCLUDE_PRIVATE pathToPrivateIncludeFolder
#        LINK_PUBLIC different target withPublicLinkage
#        LINK_PRIVATE different target withPrivateLinkage
#        NO_CPPCHECK trueIfYouDontWantIt)
###
function(new_cpp_library_shared)
    # Extract function params.
    set(options)
    set(oneValueArgs NAME NO_CPPCHECK)
    set(multiValueArgs SOURCES INCLUDE_PUBLIC INCLUDE_PRIVATE LINK_PUBLIC LINK_PRIVATE)
    cmake_parse_arguments(LIB "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Not sure how we can get an unparsed argument(s), but I think we want to inform user about it.
    if(LIB_UNPARSED_ARGUMENTS)
        message(WARNING "---- Unparsed arguments: " ${LIB_UNPARSED_ARGUMENTS} " when trying to make target:" ${LIB_NAME})
    endif()

    add_library(${LIB_NAME} SHARED ${LIB_SOURCES})

    set_common_target_stuff(
            NAME ${LIB_NAME}
            SOURCES ${LIB_SOURCES}
            INCLUDE_PUBLIC ${LIB_INCLUDE_PUBLIC}
            INCLUDE_PRIVATE ${LIB_INCLUDE_PRIVATE}
            LINK_PUBLIC ${LIB_LINK_PUBLIC}
            LINK_PRIVATE ${LIB_LINK_PRIVATE}
            NO_CPPCHECK ${LIB_NO_CPPCHECK})

    if (CMAKE_BUILD_TYPE STREQUAL Release)
        strip_symbols(
                NAME ${LIB_NAME}
                INPUT ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${LIB_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}${CMAKE_EXTRA_SHARED_LIBRARY_SUFFIXES})
    endif ()

endfunction()
