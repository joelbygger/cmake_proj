# This file contains helper functions to the factories.

###
# Helper function to add stuff common to all factories.
# Called by factories, not called by user.
#    set_common_target_stuff(
#        NAME yourTargetName
#        SOURCES a.cpp priv.cpp priv.hpp
#        INCLUDE_PUBLIC pathToPublicIncludeFolder
#        INCLUDE_PRIVATE pathToPrivateIncludeFolder
#        LINK_PUBLIC different target withPublicLinkage
#        LINK_PRIVATE different target withPrivateLinkage
#        NO_CPPCHECK trueIfYouDontWantIt)
###
function(set_common_target_stuff)
    # Extract function params.
    set(options)
    set(oneValueArgs NAME NO_CPPCHECK)
    set(multiValueArgs SOURCES INCLUDE_PUBLIC INCLUDE_PRIVATE LINK_PUBLIC LINK_PRIVATE)
    cmake_parse_arguments(CMN "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Not sure how we can get an unparsed argument(s), but I think we want to inform user about it.
    if(CMN_UNPARSED_ARGUMENTS)
        message(WARNING "---- Unparsed arguments: " ${CMN_UNPARSED_ARGUMENTS} " when trying to make target:" ${CMN_NAME})
    endif()

    set_target_properties(${CMN_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON)
    # We must also actually define which C++ standard to use.
    set_target_properties(${CMN_NAME} PROPERTIES CXX_STANDARD 17)

    target_compile_options(${CMN_NAME} PRIVATE ${MY_CXX_COMPILE_FLAGS})
    target_link_libraries(${CMN_NAME} PRIVATE ${EXTRA_LINKER_LIBS})

    if(CMN_INCLUDE_PUBLIC)
        target_include_directories(${CMN_NAME} PUBLIC ${CMN_INCLUDE_PUBLIC})
    endif()
    if(CMN_INCLUDE_PRIVATE)
        target_include_directories(${CMN_NAME} PRIVATE ${CMN_INCLUDE_PRIVATE})
    endif()
    if(CMN_LINK_PUBLIC)
        target_link_libraries(${CMN_NAME} PUBLIC ${CMN_LINK_PUBLIC})
    endif()
    if(CMN_LINK_PRIVATE)
        target_link_libraries(${CMN_NAME} PRIVATE ${CMN_LINK_PRIVATE})
    endif()

    # Add clang-tidy.
    add_clang_tidy_to_target(
            NAME ${CMN_NAME}
            SOURCES ${CMN_SOURCES}
            INCLUDE_PUBLIC ${CMN_INCLUDE_PUBLIC}
            INCLUDE_PRIVATE ${CMN_INCLUDE_PRIVATE})
    # Add Include What You Use (IWYU).
    add_iwyu_to_target(NAME ${CMN_NAME})
    # Add Cppcheck.
    if(NOT CMN_NO_CPPCHECK)
        add_cppcheck_to_target(NAME ${CMN_NAME})
    endif()

endfunction()