//
// Created by joel on 2019-03-19.
//

#ifndef ADVENTOFCODE2018_FABRIC_HPP
#define ADVENTOFCODE2018_FABRIC_HPP

#include <cstddef>
#include <vector>
class claim;

using matrixRow = std::vector<int>;
using matrix = std::vector<matrixRow>;

class fabric
{
public:
    fabric(const size_t maxH, const size_t maxW);
    void markClaimsOnFabric(const std::vector<claim>& claims);
    int countOverlaps() const;
    void printFabric() const;

private:
    matrix m_fabric;
};

#endif // ADVENTOFCODE2018_FABRIC_HPP
