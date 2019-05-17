//
// Created by joel on 2019-03-24.
//

#include "polymer.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

namespace
{
    /**
     * Remove all adjacent duplicates: same letter but different capitilization.
     * @param polymer A lot of chars...
     * @return Resulting size.
     */
    size_t reduce(std::vector<char> polymer)
    {
        // Returns true if same char but different capitalization.
        auto compare = [](const char& x, const char& y) -> bool { return (toupper(x) == toupper(y) && x != y); };

        auto searchIt = polymer.begin();
        while (true) {
            auto findIt = adjacent_find(searchIt, polymer.end(), compare);
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
                advance(it2, 2);

                searchIt = polymer.erase(findIt, it2);

                if (searchIt == polymer.end()) {
                    // We erased last element, restart search from beginning.
                    searchIt = polymer.begin();
                }
            }
        }

        return polymer.size();
    }
} // namespace

std::tuple<int, int> polymer::manager(std::vector<char>& polymer)
{
    const auto task1Sz = reduce(polymer);

    std::cout << "Original polymer.size(): " << polymer.size() << "\n";
    std::cout << "Reduced polymer: " << task1Sz << "\n";

    // Now try to remove characters to find the char to remove to achieve minimum,
    size_t minSz = std::numeric_limits<size_t>::max();
    for (char x = 'a'; x <= 'z'; x++) {
        auto p{ polymer };
        p.erase(std::remove_if(p.begin(), p.end(), [=](const auto unit) { return std::tolower(unit) == x; }), p.end());
        minSz = std::min(minSz, reduce(p));
    }

    std::cout << "Min polymer sz: " << minSz << "\n";

    return std::make_pair(task1Sz, minSz);
}
