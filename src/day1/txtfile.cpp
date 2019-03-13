//
// Created by joel on 2019-03-13.
//

#include "txtfile.hpp"
#include <iostream>

#if not defined(__clang__) // We are GCC, Clang also defines __GNUC__ so we must look at __clang__.
#include <filesystem>
namespace fs = std::filesystem;
#endif

namespace txtFile
{
    bool isValid(const char* path)
    {
        /* Since I don't have libc++7 (only 6) i can't use Clang with <filesystem>,
         * we just ignore it. When libc++7 is available, remove this and change CMakeLists.txt. */
#if defined(__clang__)
        (void)path;
        return true; // Don't bother, this code was just to explore filesystem.
#elif defined(__GNUC__)
        fs::path filepath{ path };

        /* First make sure supplied path exists and is of a type we want. */
        if (!fs::is_regular_file(filepath)) {
            if (!fs::exists(filepath)) {
                std::cout << "Supplied path/ file does not exist.\n";
            }
            else {
                std::cout << "Supplied path exists but is not a regular file (it's a special file).\n";
            }
        }
        else if (fs::is_directory(filepath)) {
            std::cout << "Supplied path is a directory.\n";
        }
        else if (fs::is_character_file(filepath)) {
            std::cout << "Supplied path is a character special file.\n";
        }
        else {
            std::cout << "This seems to a an ok file.\n";
            return true;
        }

        return false;
#endif
    }
} // namespace txtFile
