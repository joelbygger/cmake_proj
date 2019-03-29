//
// Created by joel on 2019-03-24.
//

#ifndef ADVENTOFCODE2018_MANAGER_HPP
#define ADVENTOFCODE2018_MANAGER_HPP

#include <cstddef>
#include <tuple>
#include <vector>

namespace polymer
{
    /**
     * Performs a recuction, removing adjacent identical chars if one is capital and the other is not.
     * @param polymer A whole lot of chars.
     * @return The size of a reducuction.
     */
    size_t reduce(std::vector<char> polymer);

    /**
     * Entry point, accepts a file, reads it and works the data.
     * @param path to a file.
     * @return First the reduced poölymer in the file, second the smallest reduced polymer if all occurences of a char is removed. Which char to remove is evaluated.
     */
    std::tuple<int, int> manager(char const* path);
} // namespace manager

#endif // ADVENTOFCODE2018_MANAGER_HPP
