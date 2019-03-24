//
// Created by joel on 2019-03-24.
//

#include "manager.hpp"
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void manager::manager(char const* path)
{
    std::ifstream ifs(path, std::ios_base::in);   
    if(!ifs) {
        throw std::runtime_error(std::string("Failed to open file: ") + std::strerror(errno));
    }

    std::vector<char> input;
    //ifs.get(input, ifs.gcount());
    char c;
    while(ifs.get(c)) {
        input.emplace_back(c);
    }
}