//
// Created by joel on 2019-03-13.
//

#include "manager.hpp"
#include <fstream>
#include <iostream>

namespace
{
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
