/**
 *
 * Program reads a file. A bit of error checking is applied.
 *
 */
#include "polymer.hpp"
#include <fstream>
#include <iostream>
#include <vector>

namespace
{
    /**
     * Reads from file.
     * @param path Path to file.
     * @return File data to be used.
     */
    std::vector<char> getInput(const char* path)
    {
        std::ifstream ifs(path, std::ios_base::in);
        if (!ifs) {
            std::cout << "Failed to open file.\n";
        }

        std::vector<char> polymer;

        // Read the file.
        char c;
        while (ifs.get(c)) {
            polymer.emplace_back(c);
        }

        return polymer;
    }

} // namespace

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "This program can only be run with a file name as an input. File is expected to contains ASCII chars only.\n" << argc << "\n";
    }
    else {
        std::cout << "Received path: " << argv[1] << "\n";

        // Read the file.
        std::vector<char> polymer = getInput(argv[1]);
        if (!polymer.empty()) {
            polymer::manager(polymer);
        }
    }
    return 0;
}
