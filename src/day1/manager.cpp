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
#include <unordered_set>
#include <utility>
#include <vector>

namespace fs = std::filesystem;

namespace
{
    bool isValidFile(const char* path)
    {
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
    }

    int sumFreqs(char const* path) // ref?
    {
        std::ifstream ifs(path, std::ios::in);
        int totFreq = 0;

        if (!ifs) {
            throw std::runtime_error(std::string("Failed to open file: ") + std::strerror(errno));
        }

        while (!ifs.eof()) {
            std::string txt;
            std::getline(ifs, txt);
            totFreq += std::stoi(txt);
        }

        return totFreq;
    }

    int findFirstDuplicate(char const* path) // ref?
    {
        std::ifstream ifs(path, std::ios::in);
        std::vector<int> totFreqHist = { 0 };
        auto totFreq = 0;

        if (!ifs) {
            throw std::runtime_error(std::string("Failed to open file: ") + std::strerror(errno));
        }

        std::unordered_set<int> unique = { 0 };
        for (;;) {
            ifs.seekg(0); // Rewind.
            while (!ifs.eof()) {
                std::string txt;
                std::getline(ifs, txt);
                totFreq += std::stoi(txt);
                if (!unique.insert(totFreq).second) {
                    return totFreq;
                }
            }
        }
    }
}

void manager::manager(char const* path)
{
    if (isValidFile(path)) {
        auto totFreq = sumFreqs(path);

        int firstDuplicate = 0;
        firstDuplicate = findFirstDuplicate(path);

        std::cout << "Accumulated frequency: " << totFreq << "\n";
        std::cout << "First duplicate: " << firstDuplicate << "\n";
    }
}
