###
# This file will find IWYU (Include What You Use), set up some useful variables
# and create helper functions that are useful when creating new build targets.
###

find_program(iwyu_path
        NAMES include-what-you-use iwyu
        DOC "Path to IWYU executable.")

###
# If IWYU was found, configure some variables.
###
if(NOT iwyu_path)
    message("---- Cannot find the program \"include-what-you-use\", it will will not be added to target.")

else()
    set(iwyu_path_and_options
            ${iwyu_path}
            -Xiwyu
            --mapping_file=${CMAKE_SOURCE_DIR}/iwyu.imp)
endif()

###
# We could have set variable CXX_INCLUDE_WHAT_YOU_USE for all targets, but we don't we want flexibility.
###
function(add_iwyu_to_target)
    # Extract function params.
    set(options )
    set(oneValueArgs NAME)
    set(multiValueArgs )
    cmake_parse_arguments(TARGET_IWYU "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set_property(TARGET ${TARGET_IWYU_NAME} PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path_and_options})
endfunction()