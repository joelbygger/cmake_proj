//
// Created by joel on 2019-03-11.
//

#include "manager.hpp"
#include <cstring>
#include <errno.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;
namespace fs = std::filesystem;

namespace file
{
    bool isValidFile(const char* path);
}

bool file::isValidFile(const char* path)
{
    fs::path filepath{ path };
    /* First make sure supplied path exists and is of a type we want. */
    if (!filesystem::is_regular_file(filepath))
    {
        if (!filesystem::exists(filepath))
        {
            cout << "Supplied path/ file does not exist.\n";
        }
        else
        {
            cout << "Supplied path exists but is not a regular file (it's a special file).\n";
        }
    }
    else if (filesystem::is_directory(filepath))
    {
        cout << "Supplied path is a directory.\n";
    }
    else if (filesystem::is_character_file(filepath))
    {
        cout << "Supplied path is a character special file.\n";
    }
    else
    {
        cout << "This seems to a an ok file.\n";
        return true;
    }

    cout << "exists() = " << filesystem::exists(filepath) << "\n"
         << "root_name() = " << filepath.root_name() << "\n"
         << "root_path() = " << filepath.root_path() << "\n"
         << "relative_path() = " << filepath.relative_path() << "\n"
         << "parent_path() = " << filepath.parent_path() << "\n"
         << "filename() = " << filepath.filename() << "\n"
         << "stem() = " << filepath.stem() << "\n"
         << "extension() = " << filepath.extension() << "\n";

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
        cout << "Accumulated sum: " << sum << ".\n";
    }

    return;
}