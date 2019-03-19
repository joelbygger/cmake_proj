//
// Created by joel on 2019-03-17.
//

#include "manager.hpp"
#include "claimUtils.hpp"
#include "fabric.hpp"
#include <cstring>
#include <iostream>
#include <tuple>

namespace task1
{
    /**
     * Find all coordinates for overlapping claims in Santas fabric.
     * @param claims a vector of claims
     * @return number of overlapping coordinates.
     */
    auto findOverlaps(const claimsVec& claims);

    auto findOverlaps(const claimsVec& claims)
    {
        // Find max and min coordinates...
        size_t maxW = 0;
        size_t maxH = 0;
        std::tie(maxW, maxH) = ::claimUtils::getMaxCoordinates(claims);
        std::cout << " maxW: " << maxW << " maxH: " << maxH << "\n";
        // ... so that we can create a fabric of correct size.
        fabric santasFabric(maxH, maxW);

        santasFabric.markClaimsOnFabric(claims);
        // santasFabric.printFabric();

        return santasFabric.countOverlaps();
    }
} // namespace task1

namespace task2
{
    auto findNonOverlappingClaim(claimsVec& claims);

    auto findNonOverlappingClaim(claimsVec& claims)
    {
        claimUtils::markOverlappingClaims(claims);
        return claimUtils::findNonOverlapping(claims);
    }
} // namespace task2

void manager::manager(char const* path)
{
    claimsVec claims = claimUtils::fetchClaims(path);

    auto overlaps = task1::findOverlaps(claims);
    auto claimId = task2::findNonOverlappingClaim(claims);

    std::cout << "Task 1, overlaps found: " << overlaps << "\n";
    std::cout << "Task 2, non-overlapping claim ID: " << claimId << "\n";
}
