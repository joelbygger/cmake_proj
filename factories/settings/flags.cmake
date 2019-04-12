
# A sanity check, the flags set below might not exist in older compiler versions.
if( (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") AND (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.2.0"))
        OR (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") AND (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7.0.0")) )
    message(FATAL_ERROR "Configuring for " ${CMAKE_CXX_COMPILER_ID} " in a version I'm not sure will work, it might, it might not. If you want to try, remove this comment.")
endif()

###
# Settings & Compile options for all created targets, no matter compiler.
###

# Link What You Use (LWYU) is a CMake tool.
# - For some reason I don't think it works with Clang?
# - I get some warnings on things I don't know how to control, so comment
#   this out, you can comment in when you need it.
#set(CMAKE_LINK_WHAT_YOU_USE TRUE)

# When building for release, strip target binary. Works with Clang and GCC.
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")

# Check libstdc++ implementations. Some things cannot be found by sanitizers.
# Has a negative effect on execution time.
if(LIBSTDCXX_CHECK)
    message("---- Compiling with libstdc++ debug mode.")
    set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
            -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC)
endif()


###
# Runtime sanitizers.
###
# UBSAN effects runtime & mem. very little, we let it always be active.
set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
        -fsanitize=undefined)

# We want to stop all execution when an error occurs.
# Applies to all sanitizers that supports it, and if the lib has it enabled.
set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
        -fno-sanitize-recover=all)

set(EXTRA_LINKER_LIBS ${EXTRA_LINKER_LIBS} -fsanitize=undefined)


###
# Compile options dependent on compiler.
####

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
            -Wall -Wextra -Wshadow -pedantic -Wunused -Wconversion -Wsign-conversion
            -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op
            -Wnull-dereference -Wdouble-promotion -Wformat=2
            -Wrestrict -Wpointer-arith -Wcast-qual
            -Wswitch-bool -Wswitch-enum
            -Winline -Wuseless-cast)
    # I think it can be argued that the warnings below should only be part of Debug build,
    # but I think they can be part of release.
    set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
            -fstack-protector-all -Wstack-protector -fstack-check -D_FORTIFY_SOURCE=2)

    ###
    # Runtime sanitizers.
    ###
    set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
            # Suboptions GCC doesen't add by default:
            -fsanitize=float-divide-by-zero
            -fsanitize=float-cast-overflow
            #-fsanitize-undefined-trap-on-error <- removes need for the UBSAN lib, as a consequence the crash report will give us very little.
            )

    if(ASAN) # True if CMake called with -DASAN=1.
        message("---- Compiling with address sanitizers.")
        set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
                -fsanitize=address # Implicitly activates sanitize=leak.
                -fno-omit-frame-pointer
                -fno-common)

        # Also req. ASAN_OPTIONS detect_invalid_pointer_pairs=2
        set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS} -fsanitize=pointer-compare -fsanitize=pointer-subtract)

        # ASAN must come first in list.
        set(EXTRA_LINKER_LIBS -fsanitize=address ${EXTRA_LINKER_LIBS})

    elseif(TSAN) # True if CMake called with -DTSAN=1.
        # Maybe should use -02? https://github.com/google/sanitizers/wiki/ThreadSanitizerCppManual
        message("---- Compiling with thread sanitizers.")
        set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
                -fsanitize=thread
                -fno-omit-frame-pointer)

        set(EXTRA_LINKER_LIBS ${EXTRA_LINKER_LIBS} -fsanitize=thread)
    endif()

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # Ignore C++98 backwards compatibility and warings about classes etc. being being padded.
    set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
            -Weverything
            -Wno-c++98-compat
            -Wno-c++98-compat-pedantic
            -Wno-padded
            )
endif()
