//
// Created by joel on 2019-03-21.
//

#include "manager.hpp"
#include "decoder.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace
{
    auto readAndSortFile(char const* path);
    auto readAndSortFile(char const* path)
    {
        std::ifstream ifs(path, std::ios_base::in);
        if (!ifs) {
            throw std::runtime_error(std::string("Failed to open file: ") + std::strerror(errno));
        }

        std::vector<std::string> input;
        while (!ifs.eof()) {
            std::string str;
            std::getline(ifs, str);
            input.emplace_back(str);
        }

        std::sort(input.begin(), input.end());
        return input;
    }

} // namespace

void manager::manager(char const* path)
{
    std::vector<std::string> input = readAndSortFile(path);

    log::storage logs;

    decoder decoder(logs);

    for(const auto& log : input) {
        //decoder.run(input.at(i++));
        decoder.run(log);
    }

    // size_t i = 0;
    // while (i < input.size()) {
    // }

    /*auto str = input.at(i++);
    while (i < input.size()) {
        auto itPos = str.find_first_of('#');

        int id = stoi(str.substr(itPos + 1));

        // If ID is missing add vector of size 60 initialized to 0, if ID exists leave it be.
        logs.try_emplace(id, 60, 0);

        // Can't get Clang to accept my asserts... So I've decided to have no checks and assume file is nice.

        str = input.at(i++);
        itPos = str.find_first_of('#');
        if (itPos == std::string::npos) // If this was not an ID-line we continue to check for sleep.
        {
            while (true) {
                // itPos = str.find_first_of("falls asleep");
                itPos = str.find_first_of(':');
                auto asleepMin = stoi(str.substr(itPos + 1));

                str = input.at(i++);
                // itPos = str.find_first_of("wakes up");
                itPos = str.find_first_of(':');
                auto awakeMin = stoi(str.substr(itPos + 1));

                for (int jj = asleepMin; jj < awakeMin; ++jj) {
                    logs.at(id).at(static_cast<size_t>(jj))++;
                }

                if (i >= input.size()) {
                    break;
                }

                str = input.at(i++);
                itPos = str.find_first_of('#');
                if (itPos != std::string::npos) {
                    break;
                }
            }
        }
    }*/

    // Find minute with most sleep.
    auto maxSleeperId = 666;
    auto maxSleepMinute = 666;
    auto maxSleepTime = 0;

    for (const auto& log : logs) {
        for (size_t min = 0; min < log.second.size(); min++) {
            if (maxSleepTime < log.second.at(min)) {
                maxSleepTime = log.second.at(min);
                maxSleepMinute = static_cast<int>(min);
                maxSleeperId = log.first;
            }
        }
    }

    std::cout << "maxSleeperId: " << maxSleeperId << " maxSleepMinute: " << maxSleepMinute << " maxSleepTime: " << maxSleepTime << "\n";
}
