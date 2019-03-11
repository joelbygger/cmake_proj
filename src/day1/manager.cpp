//
// Created by joel on 2019-03-11.
//

#include "manager.hpp"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

manager::manager(char const *path)
{
    fs::path filepath{path};
    /* First make sure supplied path exists and is of a type we want. */
    if(!filesystem::is_regular_file(filepath))
    {
        if(!filesystem::exists(filepath))
        {
            cout << "Supplied path/ file does not exist.\n";
        }
        else
        {
            cout << "Supplied path exists but is not a regular file (it's a special file).\n";
        }
    }
    else if(filesystem::is_directory(filepath))
    {
        cout << "Supplied path is a directory.\n";
    }

    cout << "exists() = " << filesystem::exists(filepath) << "\n"
         << "root_name() = " << filepath.root_name() << "\n"
         << "root_path() = " << filepath.root_path() << "\n"
         << "relative_path() = " << filepath.relative_path() << "\n"
         << "parent_path() = " << filepath.parent_path() << "\n"
         << "filename() = " << filepath.filename() << "\n"
         << "stem() = " << filepath.stem() << "\n"
         << "extension() = " << filepath.extension() << "\n";
}