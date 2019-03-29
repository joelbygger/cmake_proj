/**
 *
 * Program reads a file. A bit of error checking is applied.
 *
 */
#include "polymer.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 4) {
        std::cout << "This program can only be run with a file name as an input, and expected results.\n" << argc << "\n";
        return 1;
    }
    else {
        std::cout << "Received path: " << argv[1] << "\n";

        auto task1Sz = std::numeric_limits<size_t>::max();
        auto minSz = std::numeric_limits<size_t>::max();
        std::tie(task1Sz, minSz) = manager::manager(argv[1]);

        if (task1Sz != static_cast<size_t>(std::stoi(argv[2]))) {
            return 2;
        }
        else if (minSz != static_cast<size_t>(std::stoi(argv[3]))) {
            return 3;
        }
    }
    return 0;
}
