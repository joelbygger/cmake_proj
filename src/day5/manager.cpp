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
    while (true) {
        auto it = std::adjacent_find(polymer.begin(), polymer.end(), compare);
        if (it != polymer.end()) {
            auto it2 = it;
            std::advance(it2, 2);
            polymer.erase(it, it2);
        }
        else {
            break;
        }
    }

    std::cout << "polymer.size(): " << polymer.size() << "\n";
}
