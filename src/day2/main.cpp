/**
 * Objective:
 * Count occurrences of the same letter on each line and then sum it for all lines if occurred twice or thrice.
 *
 * Program reads a file. A bit of error checking is applied.
 *
 */
#include "manager.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "This program can only be run with a file name as an input. File is expected to contains ASCII chars only, only letters.\n"
                  << argc << "\n";
    }
    else {
        std::cout << "Received path: " << argv[1] << "\n";

        std::ifstream ifs(argv[1], std::ios::in);
        if (!ifs) {
            std::cout << "Failed to open file.\n";
        }
        else {
            std::vector<std::string> ids;
            while (!ifs.eof()) {
                std::string txt;
                std::getline(ifs, txt);
                if (txt.length() != 0) {
                    ids.push_back(txt);
                }
            }

            if (!ids.empty()) {
                manager::manager(ids);
            }
        }
    }
    return 0;
}
