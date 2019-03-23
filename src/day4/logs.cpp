//
// Created by joel on 2019-03-23.
//

#include "logs.hpp"
#include <cstddef>
#include <utility>

std::tuple<int, int> logs::getMaxSleeperInfo(const storage& logs)
{
    auto maxSleeperId = 666;
    auto maxSleeperTimeSum = 0;

    // First find out which elf slep the most.
    for (const auto& log : logs) {
        auto sleepSum = 0;
        for (const auto& minCnt : log.second) {
            sleepSum += minCnt;
        }

        if (sleepSum > maxSleeperTimeSum) {
            maxSleeperTimeSum = sleepSum;
            maxSleeperId = log.first;
        }
    }

    // The find which minute said elf slept most.
    auto maxSleeperMinute = 0;
    auto maxSleeperTime = 0;
    for (size_t min = 0; min < logs.at(maxSleeperId).size(); min++) {
        if (logs.at(maxSleeperId).at(min) > maxSleeperTime) {
            maxSleeperTime = logs.at(maxSleeperId).at(min);
            maxSleeperMinute = static_cast<int>(min);
        }
    }

    return std::make_tuple(maxSleeperId, maxSleeperMinute);
}
