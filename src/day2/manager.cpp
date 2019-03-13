//
// Created by joel on 2019-03-13.
//

#include "manager.hpp"
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <tuple>

namespace
{
    // Creates a map from chars in a string, value in map is counted occurences.
    std::map<char, int> createMap(const std::string& txt)
    {
        std::map<char, int> mp;

        for (auto& c : txt) {
            auto it = mp.find(c);
            if (it != mp.end()) {
                it->second++;
            }
            else {
                mp.insert({ c, 1 });
            }
        }
        return mp;
    }

    // Loop over a map, check if value has reached a limit and if so note it and return it.
    std::tuple<int, int> haveDuplicates(const std::map<char, int>& mp)
    {
        int foundTwo = 0;
        int foundThree = 0;
        for (auto const& [key, val] : mp) {
            if (val == 2) {
                foundTwo = 1;
            }
            else if (val == 3) {
                foundThree = 1;
            }
        }

        return std::make_tuple(foundTwo, foundThree);
    }

    int calcHash(char const* path)
    {
        std::ifstream ifs(path, std::ios::in);

        if (!ifs) {
            throw std::runtime_error(std::string("Failed to open file: ") + std::strerror(errno));
        }

        // Go through file.
        int accumulatedTwos = 0;
        int accumulatedThrees = 0;
        while (!ifs.eof()) {
            std::string txt;
            std::getline(ifs, txt);

            std::map<char, int> mp = createMap(txt);

            int foundTwo = 0;
            int foundThree = 0;
            std::tie(foundTwo, foundThree) = haveDuplicates(mp);
            accumulatedTwos += foundTwo;
            accumulatedThrees += foundThree;
        }

        return accumulatedTwos * accumulatedThrees;
    }
} // namespace

void manager::manager(char const* path)
{
    auto hash = calcHash(path);

    std::cout << "Hash: " << hash << "\n";
}
