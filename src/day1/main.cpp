/**
 * Objective:
 * Sum integers.
 *
 * Program reads a file. A bit of error checking is applied.
 * Contains some use of std::filesystem.
 *
 */
#include <iostream>
#include "manager.hpp"

using namespace std;

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        cout << "This program can only be run with a file name as an input. File is expected to contains ASCII chars only, representing positive and negative integers, one number on each line.\n";
        cout << argc <<"\n";
    }
    else {
        cout << "Received path: " << argv[1] << "\n";

        manager::manager(argv[1]);

    }
    return 0;
}