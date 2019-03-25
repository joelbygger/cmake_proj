//
// Created by joel on 2019-03-24.
//

#include "manager.hpp"
#include <algorithm>
#include <cctype>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

void manager::manager(char const* path)
{
    std::ifstream ifs(path, std::ios_base::in);
    if (!ifs) {
        throw std::runtime_error(std::string("Failed to open file: ") + std::strerror(errno));
    }

    std::vector<char> polymer;

    // Read the file.
    char c;
    while (ifs.get(c)) {
        polymer.emplace_back(c);
    }
    std::cout << "polymer.size(): " << polymer.size() << "\n";

    // Returns true if same char but different capitalization.
    auto compare = [](const char& x, const char& y) -> bool { return (std::toupper(x) == std::toupper(y) && x != y); };
    auto searchIt = polymer.begin();
    while (true) {
        auto findIt = std::adjacent_find(searchIt, polymer.end(), compare);
        if (findIt == polymer.end()) {
            if (searchIt != polymer.begin()) {
                // Found nothing, restart search, we might not have searched form begining.
                searchIt = polymer.begin();
            }
            else {
                break; // Didn't find anything, we're done.
            }
        }
        else {
            auto it2 = findIt;
            std::advance(it2, 2);

            searchIt = polymer.erase(findIt, it2);

            if (searchIt == polymer.end()) {
                // We erased last element, restart search from beginning.
                searchIt = polymer.begin();
            }
        }
    }

    std::cout << "polymer.size(): " << polymer.size() << "\n";
}
