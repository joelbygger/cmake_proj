

# Try to find Clang-format (for formatting code), and set variable that can be used by source code.

find_program(CLANG_FORMAT
        NAMES clang-format
        DOC "Path to clang format executable.")

if(NOT CLANG_FORMAT)
    message("---- Cannot find \"clang-format\" (you won't get a build target to run clang format on your sources).")
else()
    # Create a list of files to format.
    # GLOB is not very nice, but it's simple, and by specifying folder we make
    # sure to not format any 3rd party files.
    file(GLOB_RECURSE ALL_MY_CPP_FILES
            LIST_DIRECTORIES false
            ${CMAKE_SOURCE_DIR}/src/*.*pp
            ${CMAKE_SOURCE_DIR}/testsOfFramework/*.*pp)

    add_custom_target(
            clang_format
            COMMAND ${CLANG_FORMAT}
            -style=file             # Use format file in root.
            -i                      # Change the files.
            ${ALL_MY_CPP_FILES})
endif()
