
# To use <filesystem> we need to add special linkage, it is an amendment to the standard?.
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(FILESYSTEM_LIB -lstdc++fs) # Won't be needed with GCC 9 (?).

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(WARNING "---- day1 with Clang currently doesn't work properly.
    According to interwebs <filesystem> is not part of libc++-6, it appears in libc++-7.
    At the time of writing (winter -19) Ubuntu defaults to libc++ 6.
    To get filesystem running see http://releases.llvm.org/7.0.0/projects/libcxx/docs/UsingLibcxx.html#using-filesystem-and-libc-fs
    Summary: Add \"-stdlib=libc++\" as a compiler flag and \"-lc++fs\" as a lib to the binary,
    i.e. set(FILESYSTEM_LIB -lc++fs)
    To see what lib is available:$ /sbin/ldconfig -p | grep stdc++")
endif()

new_cpp_executeable(
        NAME day1
        SOURCES main.cpp manager.cpp manager.hpp
        LINK_PRIVATE ${FILESYSTEM_LIB})