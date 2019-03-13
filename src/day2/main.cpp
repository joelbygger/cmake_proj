/**
 * Objective:
 * Count occurrences of the same letter on each line and then sum it for all lines if occurred twice or thrice.
 *
 * Program reads a file. A bit of error checking is applied.
 *
 */
#include "manager.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "This program can only be run with a file name as an input. File is expected to contains ASCII chars only, only letters.\n"
                  << argc << "\n";
    }
    else {
        std::cout << "Received path: " << argv[1] << "\n";

        manager::manager(argv[1]);
    }
    return 0;
}
