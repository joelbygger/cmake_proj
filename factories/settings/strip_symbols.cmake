# Strip symbols using the strip tool the system supplies (e.g. /usr/bin/strip).
# Clang doesen't support GCC '-s' flag, so to be compiler independent we use the strip tool the system supplies.
# The strip tool also supports different strip options.
# NOTE: The strip tool might not support all platforms if you cross-compile.

###
# Helper function for adding possibility to strip symbols from executables and libraries.
# Intended to be called from a factory.
# Usage:
#    strip_symbols(
#        NAME yourTargetName
#        INPUT nameOfThingToStrip)
###
function(strip_symbols)
    # Extract function params.
    set(options)
    set(oneValueArgs NAME INPUT)
    set(multiValueArgs)
    cmake_parse_arguments(STRIP "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Not sure how we can get an unparsed argument(s), but I think we want to inform user about it.
    if(LIB_UNPARSED_ARGUMENTS)
        message(WARNING "---- Unparsed arguments: " ${STRIP_UNPARSED_ARGUMENTS} " when trying to make target:" ${STRIP_NAME})
    endif()

    # Create an extra build-step where stripping is performed.
    add_custom_command(TARGET ${STRIP_NAME} POST_BUILD
            COMMAND ${CMAKE_STRIP} ${STRIP_INPUT})

endfunction()