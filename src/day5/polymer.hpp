//
// Created by joel on 2019-03-24.
//

#ifndef ADVENTOFCODE2018_POLYMER_HPP
#define ADVENTOFCODE2018_POLYMER_HPP

#include <tuple>
#include <vector>

namespace polymer
{
    /**
     * Entry point, accepts a file, reads it and works the data.
     * @param polymer A whoe lot of chars.
     * @return First the reduced poölymer in the file, second the smallest reduced polymer if all occurences of a char is removed. Which char to remove is
     * evaluated.
     */
    std::tuple<int, int> manager(std::vector<char>& polymer);
} // namespace polymer

#endif // ADVENTOFCODE2018_POLYMER_HPP
