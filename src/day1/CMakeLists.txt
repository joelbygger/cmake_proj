new_cpp_executeable(
        NAME day1
        SOURCES main.cpp manager.cpp manager.hpp
        LINK_PRIVATE -lstdc++fs) # To use <filesystem> we need to add special linkage.