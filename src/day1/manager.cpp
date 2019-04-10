//
// Created by joel on 2019-03-11.
//

#include "manager.hpp"
#include "txtfile.hpp"
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>

namespace
{
    int sumFreqs(char const* path)
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

    int findFirstDuplicate(char const* path)
    {
        std::ifstream ifs(path, std::ios::in);
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
} // namespace

void manager::manager(char const* path)
{
    if (txtFile::isValid(path)) {
        auto totFreq = sumFreqs(path);

        int firstDuplicate = 0;
        firstDuplicate = findFirstDuplicate(path);

        std::cout << "Accumulated frequency: " << totFreq << "\n";
        std::cout << "First duplicate: " << firstDuplicate << "\n";
    }
}
