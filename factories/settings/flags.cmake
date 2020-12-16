
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
if(ASAN AND TSAN)
    message(FATAL_ERROR "ASAN and TSAN cannot be used at the same time.")
endif()

# Set for all sanitizers.
set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
        # We want to stop all execution when an error occurs. Applies to all sanitizers that supports it, and if the lib has it enabled.
        -fno-sanitize-recover=all
        # To get proper stack traces. Allows the fast unwinder to function properly, get proper debug info in binary.
        # *SAN_SYMBOLIZER_PATH must be available and point to llvm-symbolizer.
        -fno-omit-frame-pointer)

# UBSAN 
# effects runtime & mem. very little, we let it always be active.
set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS} -fsanitize=undefined)
set(MY_EXTRA_LINKER_LIBS ${MY_EXTRA_LINKER_LIBS} -fsanitize=undefined)


if(ASAN) # True if CMake called with -DASAN=1.
    # Should use -01 or higher.
    # ASAN implicitly activates sanitize=leak.
    message("---- Compiling with address sanitizer.")
    set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS} -fsanitize=address -fsanitize-address-use-after-scope)

    # ASAN must come first in list!
    set(MY_EXTRA_LINKER_LIBS -fsanitize=address ${MY_EXTRA_LINKER_LIBS})
endif()

if(TSAN) # True if CMake called with -DTSAN=1.
    # Should use -02 or higher.
    message("---- Compiling with thread sanitizer.")
    set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS} -fsanitize=thread)

    set(MY_EXTRA_LINKER_LIBS ${MY_EXTRA_LINKER_LIBS} -fsanitize=thread)
endif()

###
# Compile options dependent on compiler.
####

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
            -Wall -Wextra -Wshadow -Wpedantic -Wunused -Wconversion -Wsign-conversion
            -Wduplicated-cond -Wduplicated-branches -Wlogical-op
            -Wnull-dereference -Wdouble-promotion -Wformat=2
            -Wpointer-arith -Wcast-qual
            -Wswitch-bool -Wswitch-enum
            -Winline -Wuseless-cast
            -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
            -Woverloaded-virtual
            -Wmissing-declarations -Wshadow
            )
    # I think it can be argued that the warnings below should only be part of Debug build,
    # but I think they can be part of release.
    set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
            -fstack-protector-all -Wstack-protector -fstack-check -D_FORTIFY_SOURCE=2)

    ###
    # Runtime sanitizers.
    ###
    # For UBSAN
    set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
            # Suboptions GCC doesen't add by default:
            -fsanitize=float-divide-by-zero
            -fsanitize=float-cast-overflow
            #-fsanitize-undefined-trap-on-error <- removes need for the UBSAN lib, as a consequence the crash report will give us very little.
            )

    if(ASAN)
        # Both these also req. ASAN_OPTIONS detect_invalid_pointer_pairs=2, seems like they don't exists in Clang? Defaulted?
        set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS} -fsanitize=pointer-compare -fsanitize=pointer-subtract)
    endif()

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(MY_CXX_COMPILE_FLAGS ${MY_CXX_COMPILE_FLAGS}
            # As long as all warnings works, I'll stick to it, can be changed alter, but easier and maybe safer this way.
            -Weverything
            -Wpedantic
            # If we are switcing on enum class I still want a default, to handle all cases. 
            -Wno-covered-switch-default
            # Ignore C++98 backwards compatibility and warnings about classes etc. being being padded.
            -Wno-c++98-compat
            -Wno-c++98-compat-pedantic
            -Wno-padded
            )
endif()
