
# Create a shared lib, add all files we'll include, for clarity.
new_cpp_library_shared (NAME utils
    SOURCES utils.cpp utils.hpp ${CMAKE_CURRENT_SOURCE_DIR}/priv/priv.hpp
    INCLUDE_PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}          # Make sure the compiler can find include files for our library when other libraries or executables link to it.
    INCLUDE_PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/priv)   # But some files we don't want to expose, so we keep them private.
                                                        # Could be a secret, or that we don't want to risk bad linkage or expose
                                                        # our inner workings.