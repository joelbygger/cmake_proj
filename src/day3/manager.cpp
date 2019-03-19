//
// Created by joel on 2019-03-17.
//

#include "manager.hpp"
#include "claim.hpp"
#include "fabric.hpp"
#include <algorithm>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

using claimsVec = std::vector<claim>;

class task1
{
public:
    auto findOverlaps(char const* path)
    {
        claimsVec claims;

        claims = fetchClaims(path);

        // Find max and min coordinates...
        size_t maxW = 0;
        size_t maxH = 0;
        std::tie(maxW, maxH) = getMaxCoordinates(claims);
        std::cout << " maxW: " << maxW << " maxH: " << maxH << "\n";
        // ... so that we can create a fabric of correct size.
        fabric santasFabric(maxH, maxW);

        santasFabric.markClaimsOnFabric(claims);
        // santasFabric.printFabric();

        return santasFabric.countOverlaps();
    }

private:
    /**
     * Calculate how big santas fabric needs to be to fit all the claims.
     * @param claims Vector of claims.
     * @return A tuple tuple with required width and height.
     */
    std::tuple<size_t, size_t> getMaxCoordinates(const claimsVec& claims) const
    {
        int maxW = 0;
        int maxH = 0;
        auto findMax = [&](const auto& c) {
            maxH = c.getHeightEndCoord() > maxH ? c.getHeightEndCoord() : maxH;
            maxW = c.getWidthEndCoord() > maxW ? c.getWidthEndCoord() : maxW;
        };

        std::for_each(claims.cbegin(), claims.cend(), findMax);
        return std::make_tuple(maxW, maxH);
    }

    /**
     * Creates a vector of claims.
     * @param path To a file with claims.
     * @return The created vector.
     */
    claimsVec fetchClaims(char const* path) const
    {
        claimsVec claims;
        std::ifstream ifs(path, std::ios::in);

        if (!ifs) {
            throw std::runtime_error(std::string("Failed to open file: ") + std::strerror(errno));
        }

        while (!ifs.eof()) {
            // Format in file: '#1 @ 1,3: 4x4'
            std::string id, dummy, coord, dimension;
            ifs >> id >> dummy >> coord >> dimension;
            claim c(std::stoi(id.substr(1)),
                    std::stoi(coord),
                    std::stoi(coord.substr(coord.find(',') + 1)),
                    std::stoi(dimension),
                    std::stoi(dimension.substr(dimension.find('x') + 1)));
            claims.emplace_back(c);
        }
        return claims;
    }
};

void manager::manager(char const* path)
{
    task1 tsk1;
    auto overlaps = tsk1.findOverlaps(path);
    std::cout << "Task 1, overlaps found: " << overlaps << "\n";
}
