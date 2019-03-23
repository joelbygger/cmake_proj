//
// Created by joel on 2019-03-23.
//

#include "logs.hpp"
#include <cstddef>
#include <utility>

std::tuple<int, int, int> logs::getMaxSleeperInfo(const storage& logs)
{
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

    return std::make_tuple(maxSleeperId, maxSleepMinute, maxSleepTime);
}
