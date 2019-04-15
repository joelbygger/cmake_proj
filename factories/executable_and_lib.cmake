
# This file contains factories to generate build targets. Intended to make sure
# all build targets gets the correct global compilation options, tooling etc.

###
# Factory for generating executable targets.
# Usage (from some CMakeLists.txt file):
#    new_cpp_executable(
#        NAME yourTargetName
#        SOURCES a.cpp priv.cpp priv.hpp
#        INCLUDE_PUBLIC pathToPublicIncludeFolder
#        INCLUDE_PRIVATE pathToPrivateIncludeFolder
#        LINK_PUBLIC different target withPublicLinkage
#        LINK_PRIVATE different target withPrivateLinkage
#        NO_CPPCHECK trueIfYouDontWantIt)
###
function(new_cpp_executable)
    # Extract function params.
    set(options)
    set(oneValueArgs NAME NO_CPPCHECK)
    set(multiValueArgs SOURCES INCLUDE_PUBLIC INCLUDE_PRIVATE LINK_PUBLIC LINK_PRIVATE)
    cmake_parse_arguments(EXEC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Not sure how we can get an unparsed argument(s), but I think we want to inform user about it.
    if(EXEC_UNPARSED_ARGUMENTS)
        message(WARNING "---- Unparsed arguments: " ${EXEC_UNPARSED_ARGUMENTS} " when trying to make target:" ${EXEC_NAME})
    endif()

    add_executable(${EXEC_NAME} ${EXEC_SOURCES})

    set_target_properties(${EXEC_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON)
    # We must also actually define which C++ standard to use.
    set_target_properties(${EXEC_NAME} PROPERTIES CXX_STANDARD 17)

    target_compile_options(${EXEC_NAME} PRIVATE ${MY_CXX_COMPILE_FLAGS})
    target_link_libraries(${EXEC_NAME} PRIVATE ${EXTRA_LINKER_LIBS})

    if(EXEC_INCLUDE_PUBLIC)
        target_include_directories(${EXEC_NAME} PUBLIC ${EXEC_INCLUDE_PUBLIC})
    endif()
    if(EXEC_INCLUDE_PRIVATE)
        target_include_directories(${EXEC_NAME} PRIVATE ${EXEC_INCLUDE_PRIVATE})
    endif()
    if(EXEC_LINK_PUBLIC)
        target_link_libraries(${EXEC_NAME} PUBLIC ${EXEC_LINK_PUBLIC})
    endif()
    if(EXEC_LINK_PRIVATE)
        target_link_libraries(${EXEC_NAME} PRIVATE ${EXEC_LINK_PRIVATE})
    endif()

    if (CMAKE_BUILD_TYPE STREQUAL Release)
        strip_symbols(
                NAME ${EXEC_NAME}
                INPUT ${EXEC_NAME})
    endif ()

    # Create a command to execute built binary.
    add_custom_target(${EXEC_NAME}_run
            COMMAND ${EXEC_NAME}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Run generated binary in ${CMAKE_CURRENT_SOURCE_DIR}"
            )

    # Add clang-tidy.
    add_clang_tidy_to_target(
            NAME ${EXEC_NAME}
            SOURCES ${EXEC_SOURCES}
            INCLUDE_PUBLIC ${EXEC_INCLUDE_PUBLIC}
            INCLUDE_PRIVATE ${EXEC_INCLUDE_PRIVATE})
    # Add IWYU.
    add_iwyu_to_target(NAME ${EXEC_NAME})
    # Add Cppcheck.
    if(NOT EXEC_NO_CPPCHECK)
        add_cppcheck_to_target(NAME ${EXEC_NAME})
    endif()

endfunction()



###
# Factory for generating library targets.
# Usage (from some CMakeLists.txt file):
#    new_cpp_library_shared(
#        NAME yourTargetName
#        SOURCES a.cpp priv.cpp priv.hpp
#        INCLUDE_PUBLIC pathToPublicIncludeFolder
#        INCLUDE_PRIVATE pathToPrivateIncludeFolder
#        LINK_PUBLIC different target withPublicLinkage
#        LINK_PRIVATE different target withPrivateLinkage
#        NO_CPPCHECK trueIfYouDontWantIt)
###
function(new_cpp_library_shared)
    # Extract function params.
    set(options)
    set(oneValueArgs NAME NO_CPPCHECK)
    set(multiValueArgs SOURCES INCLUDE_PUBLIC INCLUDE_PRIVATE LINK_PUBLIC LINK_PRIVATE)
    cmake_parse_arguments(LIB "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Not sure how we can get an unparsed argument(s), but I think we want to inform user about it.
    if(LIB_UNPARSED_ARGUMENTS)
        message(WARNING "---- Unparsed arguments: " ${LIB_UNPARSED_ARGUMENTS} " when trying to make target:" ${LIB_NAME})
    endif()

    add_library(${LIB_NAME} SHARED ${LIB_SOURCES})

    set_target_properties(${LIB_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON)
    # We must also actually define which C++ standard to use.
    set_target_properties(${LIB_NAME} PROPERTIES CXX_STANDARD 17)

    target_compile_options(${LIB_NAME} PRIVATE ${MY_CXX_COMPILE_FLAGS})
    target_link_libraries(${LIB_NAME} PRIVATE ${EXTRA_LINKER_LIBS})

    if(LIB_INCLUDE_PUBLIC)
        target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE_PUBLIC})
    endif()
    if(LIB_INCLUDE_PRIVATE)
        target_include_directories(${LIB_NAME} PRIVATE ${LIB_INCLUDE_PRIVATE})
    endif()
    if(LIB_LINK_PUBLIC)
        target_link_libraries(${LIB_NAME} PUBLIC ${LIB_LINK_PUBLIC})
    endif()
    if(LIB_LINK_PRIVATE)
        target_link_libraries(${LIB_NAME} PRIVATE ${LIB_LINK_PRIVATE})
    endif()


    if (CMAKE_BUILD_TYPE STREQUAL Release)
        strip_symbols(
                NAME ${LIB_NAME}
                INPUT ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${LIB_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}${CMAKE_EXTRA_SHARED_LIBRARY_SUFFIXES})
    endif ()

    # Add clang-tidy.
    add_clang_tidy_to_target(
            NAME ${LIB_NAME}
            SOURCES ${LIB_SOURCES}
            INCLUDE_PUBLIC ${LIB_INCLUDE_PUBLIC}
            INCLUDE_PRIVATE ${LIB_INCLUDE_PRIVATE})
    # Add Include What You Use (IWYU).
    add_iwyu_to_target(NAME ${LIB_NAME})
    # Add Cppcheck.
    if(NOT LIB_NO_CPPCHECK)
        add_cppcheck_to_target(NAME ${LIB_NAME})
    endif()

endfunction()
