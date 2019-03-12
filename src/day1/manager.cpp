//
// Created by joel on 2019-03-11.
//

#include "manager.hpp"
#include <cerrno>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

namespace file
{
    bool isValidFile(const char* path);
} // namespace file

bool file::isValidFile(const char* path)
{
    fs::path filepath{ path };
    /* First make sure supplied path exists and is of a type we want. */
    if (!fs::is_regular_file(filepath))
    {
        if (!fs::exists(filepath))
        {
            std::cout << "Supplied path/ file does not exist.\n";
        }
        else
        {
            std::cout << "Supplied path exists but is not a regular file (it's a special file).\n";
        }
    }
    else if (fs::is_directory(filepath))
    {
        std::cout << "Supplied path is a directory.\n";
    }
    else if (fs::is_character_file(filepath))
    {
        std::cout << "Supplied path is a character special file.\n";
    }
    else
    {
        std::cout << "This seems to a an ok file.\n";
        return true;
    }

    return false;
}

void manager::manager(char const* path)
{
    if (file::isValidFile(path))
    {
        std::ifstream ifs(path, std::ios::in);
        if (!ifs)
        {
            throw std::runtime_error(std::string("Failed to open file: ") + std::strerror(errno));
        }

        int sum = 0;
        while (!ifs.eof())
        {
            std::string txt;
            std::getline(ifs, txt);
            sum += std::stoi(txt);
        }
        std::cout << "Accumulated sum: " << sum << ".\n";
    }
}
