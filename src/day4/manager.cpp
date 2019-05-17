//
// Created by joel on 2019-03-21.
//

#include "manager.hpp"
#include "decoder.hpp"
#include "logs.hpp"
#include <algorithm>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
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
    // Gather all data, common for all tasks today.
    std::vector<std::string> input = readAndSortFile(path);

    logs::storage logs;
    decoder decoder(logs);

    // Pars ethe logs to find how much time each elf slept.
    for (const auto& log : input) {
        decoder.run(log);
    }

    // Task 1.
    auto [maxSleeperId, maxSleeperMinute] = logs::getMaxSleeperInfo(logs);

    // Task 2.
    auto [maxFrequentSleeperId, maxFrequentsleeperMinute] = logs::getMaxFrequentSleeperInfo(logs);

    std::cout << "Task1: maxSleeperId: " << maxSleeperId << " maxSleeperMinute: " << maxSleeperMinute
              << " maxSleeperId * maxSleeperMinute: " << (maxSleeperId * maxSleeperMinute) << "\n";

    std::cout << "Task2: maxFrequentSleeperId: " << maxFrequentSleeperId << " maxFrequentsleeperMinute: " << maxFrequentsleeperMinute
              << " sum: " << maxFrequentSleeperId * maxFrequentsleeperMinute << "\n";
}
