
# This file contains factorie(s) to generate executeables. Intended to make sure
# all build targetrs gets the correct global compilation options etc.


###
# "Global" compile options. Mostly valid also for GCC, not investigated which.
####
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    ###
    # Set for all created targets. LWYU is a CMake tool.
    # - For some reason I don't think it works with clang?
    # - I get some warnings on things I don't know how to control, so comment 
    #   this out, you can comment in when you need it.
    ###
    #set(CMAKE_LINK_WHAT_YOU_USE TRUE)

    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "7.0.0")
        set(MY_UNIV_COMPILE_FLAGS
            -Wall -Wextra -Wshadow -pedantic -Wunused -Wconversion -Wsign-conversion
            -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op
            -Wnull-dereference -Wdouble-promotion -Wformat=2
            -Wrestrict -Wpointer-arith -Wcast-qual
            -Wswitch-bool -Wswitch-enum
            -Winline )
        # I think it can be argued that the warnings below should only be part of Debug build,
        # but I think they can be part of release.
        set(MY_UNIV_COMPILE_FLAGS ${MY_UNIV_COMPILE_FLAGS}
            -fstack-protector-all -Wstack-protector -fstack-check -D_FORTIFY_SOURCE=2)

        ###
        # Runtime sanitizers.
        ###
        # UBSAN effects runtime & mem. very little, we let it always be active.
        set(MY_UNIV_COMPILE_FLAGS ${MY_UNIV_COMPILE_FLAGS}
            -fsanitize=undefined
            # UBSAN suboptions not added by default:
            -fsanitize=float-divide-by-zero
            -fsanitize=float-cast-overflow
            -fno-sanitize-recover=all # We want to stop all execution when an error occurs.
            #-fsanitize-undefined-trap-on-error <- won't need UBSAN on target, but the crash report will give us very little.
            )

        set(EXTRA_LINKER_LIBS ${EXTRA_LINKER_LIBS} -fsanitize=undefined)
        #set(MY_C_COMPILE_FLAGS ${MY_UNIV_COMPILE_FLAGS} -Wjump-misses-init  -Wstrict-prototypes -Wmissing-prototypes)
        set(MY_CXX_COMPILE_FLAGS ${MY_UNIV_COMPILE_FLAGS} -Wuseless-cast)
    endif()

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # Ignore C++98 backwards compatibility and warings about classes etc. being being padded.
    set(MY_CXX_COMPILE_FLAGS ${MY_UNIV_COMPILE_FLAGS}
        -Weverything
        -Wno-c++98-compat
        -Wno-padded
        )
endif()

# When building for release, strip target binary. Works with Clang and GCC.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")


###
# Factory for generating executable targets.
# Usage (from some CMakeLists.txt file):
#    new_cpp_executeable(
#        NAME yourTargetName
#        SOURCES a.cpp priv.cpp priv.hpp
#        INCLUDE_PRIVATE targetPrivateIncFolder)
###
function(new_cpp_executeable)
    # Extract function params.
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES INCLUDE_PRIVATE)
    cmake_parse_arguments(EXEC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_executable(${EXEC_NAME} ${EXEC_SOURCES})

    set_target_properties(${EXEC_NAME} PROPERTIES CXX_STANDARD_REQUIRED 17)
    # We must also actually define which C standard to use.
    set_target_properties(${EXEC_NAME} PROPERTIES CXX_STANDARD 17)

    target_compile_options(${EXEC_NAME} PRIVATE ${MY_CXX_COMPILE_FLAGS})
    target_link_libraries(${EXEC_NAME} PRIVATE ${EXTRA_LINKER_LIBS})

    if(EXEC_INCLUDE_PRIVATE)
        target_include_directories(${EXEC_NAME} PRIVATE ${EXEC_INCLUDE_PRIVATE})
    endif()

    # Add clang-tidy.
    add_clang_tidy_to_target(
        NAME ${EXEC_NAME}
        SOURCES ${EXEC_SOURCES}
        ${EXEC_INCLUDE_PRIVATE})
    # Add IWYU
    add_iwyu_to_target(NAME ${EXEC_NAME})


    # Not sure how we can get an unparsed argument(s), but I think we want to inform user about it.
    if(EXEC_UNPARSED_ARGUMENTS)
        message(WARNING "---- Unparsed arguments: " ${EXEC_UNPARSED_ARGUMENTS} " when trying to make target:" ${EXEC_NAME})
    endif()

endfunction()
