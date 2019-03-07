

# Try to find Clang-format (for formatting code), and set variable that can be used by source code.

find_program(CLANG_FORMAT
        NAMES clang-format-5.0 clang-format
        DOC "Path to clang format executable.")

if(NOT CLANG_FORMAT)
    message("---- Cannot find clang-format (you cannot use clang format)!")
else()
    # Create a list of files to format.
    # GLOB is not very nice, but it's simple, and by specifying folder we make
    # sure to not format any 3rd party files.
    file(GLOB_RECURSE ALL_MY_CPP_FILES
            LIST_DIRECTORIES false
            ${CMAKE_SOURCE_DIR}/src/*.cpp)

    add_custom_target(
            clang_format
            COMMAND ${CLANG_FORMAT}
            -style=file             # Use format file in root.
            -i                      # Change the files.
            ${ALL_MY_CPP_FILES})
endif()
