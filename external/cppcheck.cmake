###
# This file will find Cppcheck, set up some useful variables and create helper 
# functions that are useful when creating new build targets.
###

find_program(cppcheck_path
        NAMES cppcheck
        DOC "Path to cppcheck executable.")

###
# If cppcheck was found, configure some variables.
###
if(NOT cppcheck_path)
    message("---- Cannot find \"cppcheck\" (you won't have this tool run when you build).")
else()
    message("---- Selected targets will be checked with Cppcheck.")
    # Configure checks to run.
    set(cppcheck_path_and_options ${cppcheck_path})
    # Some, not all possible(!) options are described below.
    list(APPEND cppcheck_path_and_options
            # Gives more output.
            "--enable=style"
            # Better messages on findings, but also other extra output.
            #"--verbose"
            # Gives a heads up when cppcheck is not sure, instread of silently ignore it.
            #"--inconclusive"
            # Executes all possible paths if there are #ifdefs, otherwise only the valid one and a limited amount. 
            "--force" 
            # Checks that stuff works, supresses other options.
            #"--check-config"
            # Supress warnings on system headers, mainly interesting when also using check-config.
            #"--suppress=missingIncludeSystem"
            # Our global suppressions file.
            "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt")

endif()


###
# We could have set variable CMAKE_CXX_CPPCHECK for all targets, but we don't we want flexibility.
###
function(add_cppcheck_to_target)
    # Extract function params.
    set(options )
    set(oneValueArgs NAME)
    set(multiValueArgs )
    cmake_parse_arguments(TARGET_CPPCHECK "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set_property(TARGET ${TARGET_CPPCHECK_NAME} PROPERTY CXX_CPPCHECK ${cppcheck_path_and_options})
endfunction()