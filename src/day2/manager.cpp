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
#include <tuple>
#include <utility>
#include <vector>

class task1
{
public:
    // Calc hash on entire file.
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

            // Creates a map from chars in a string, value in map is counted occurences.
            std::map<char, int> mp;
            for (auto& c : txt) {
                mp[c]++;
            }

            int foundTwo = 0;
            int foundThree = 0;
            std::tie(foundTwo, foundThree) = haveDuplicates(mp);
            accumulatedTwos += foundTwo;
            accumulatedThrees += foundThree;
        }

        return accumulatedTwos * accumulatedThrees;
    }

private:
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
};

class task2
{
public:
    // Find two Ids that only differs on one char.
    std::string findCommonIds(char const* path)
    {
        std::ifstream ifs(path, std::ios::in);

        if (!ifs) {
            throw std::runtime_error(std::string("Failed to open file: ") + std::strerror(errno));
        }

        std::vector<std::string> ids;
        while (!ifs.eof()) {
            std::string txt;
            std::getline(ifs, txt);
            if (txt.length() != 0) {
                ids.push_back(txt);
            }
        }

        if (!allSameLen(ids)) {
            throw std::runtime_error(std::string("Bad file contents."));
        }

        auto foundMatch = std::make_pair(static_cast<size_t>(0), static_cast<size_t>(0));
        const auto len = ids[0].length();
        for (size_t str1 = 0; str1 < ids.size() - 1; str1++) {
            // ... but not to itself.
            for (size_t str2 = str1 + 1; str2 < ids.size() - 1; str2++) {
                // Perform comparison!
                auto diffCount = 0;
                for (size_t i = 0; i < len && diffCount < 2; i++) {
                    if (ids.at(str1).at(i) != ids.at(str2).at(i)) {
                        diffCount++;
                        foundMatch = std::make_pair(str1, i);
                    }
                }

                if (diffCount == 1) {
                    ids.at(std::get<0>(foundMatch)).erase(std::get<1>(foundMatch), 1);
                }
            }
        }
        return ids.at(std::get<0>(foundMatch));
    }

private:
    // Simple error check.
    bool allSameLen(const std::vector<std::string>& ids)
    {
        auto expectLen = ids.front().length();
        for (const auto& id : ids) {
            if (expectLen != id.length()) {
                std::cout << "Inconsistent lenghths, first row has: " << expectLen << " current is: " << id << "(" << id.length() << ")\n";
                return false;
            }
        }
        return true;
    }
};

void manager::manager(char const* path)
{
    task1 tsk1;
    task2 tsk2;
    auto hash = tsk1.calcHash(path);
    auto id = tsk2.findCommonIds(path);

    std::cout << "Hash: " << hash << "\n";
    std::cout << "ID: " << id << "\n";
}
