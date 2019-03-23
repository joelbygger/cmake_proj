//
// Created by joel on 2019-03-23.
//

#ifndef ADVENTOFCODE2018_LOGS_HPP
#define ADVENTOFCODE2018_LOGS_HPP

#include <map>
#include <tuple>
#include <vector>

namespace logs
{
    /**
     * Where decoded logs are stored.
     * First: Id of the santa this log belongs to.
     * Second: Vector of minutes (60), each will contains the
     * number of times the elf has been asleep that minute.
     */
    using storage = std::map<int, std::vector<int>>;

    std::tuple<int, int, int> getMaxSleeperInfo(const storage& logs);
} // namespace logs

#endif // ADVENTOFCODE2018_LOGS_HPP
