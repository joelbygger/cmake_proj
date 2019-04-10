//
// Created by joel on 2019-03-19.
//

#include "claimUtils.hpp"
#include "claim.hpp"
#include <algorithm>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace
{
    /**
     * Returns true if the ranges overlap.
     * A range is [x1, x2] and [y1, y2] where they may overlap as;
     * x1 y1 x2 y2 || y1 x1 y1 x2
     * x1 y1 y2 x2 || y1 x1 x2 y2
     * @param x1 a start pos
     * @param x2 an end pos
     * @param y1 a start pos
     * @param y2 an end pos
     * @return True of they overlap
     */
    auto rangesOverlap(const int& x1, const int& x2, const int& y1, const int& y2)
    {
        bool result = x1 <= y2 && y1 <= x2;
        return result;
    }
} // namespace

claimsVec claimUtils::fetchClaims(char const* path)
{
    claimsVec claims;
    std::ifstream ifs(path, std::ios_base::in);

    if (!ifs) {
        throw std::runtime_error(std::__cxx11::string("Failed to open file: ") + ::std::strerror(errno));
    }

    while (!ifs.eof()) {
        // Format in file: '#1 @ 1,3: 4x4'
        std::__cxx11::string id, dummy, coord, dimension;
        ifs >> id >> dummy >> coord >> dimension;
        claim c(stoi(id.substr(1)), stoi(coord), stoi(coord.substr(coord.find(',') + 1)), stoi(dimension), stoi(dimension.substr(dimension.find('x') + 1)));
        claims.emplace_back(c);
    }
    return claims;
}

std::tuple<size_t, size_t> claimUtils::getMaxCoordinates(const claimsVec& claims)
{
    int maxW = 0;
    int maxH = 0;
    auto findMax = [&](const auto& c) {
        maxH = c.heightEndCoord() > maxH ? c.heightEndCoord() : maxH;
        maxW = c.widthEndCoord() > maxW ? c.widthEndCoord() : maxW;
    };

    std::for_each(claims.cbegin(), claims.cend(), findMax);
    return std::make_tuple(maxW, maxH);
}

void claimUtils::markOverlappingClaims(claimsVec& claims)
{
    for (size_t c1 = 0; c1 < claims.size() - 1; c1++) {
        for (size_t c2 = c1 + 1; c2 < claims.size(); c2++) {
            if (rangesOverlap(claims.at(c1).leftCoord(), claims.at(c1).widthEndCoord(), claims.at(c2).leftCoord(), claims.at(c2).widthEndCoord())
                && rangesOverlap(claims.at(c1).topCoord(), claims.at(c1).heightEndCoord(), claims.at(c2).topCoord(), claims.at(c2).heightEndCoord())) {
                claims.at(c1).setOverlapIfUnset(true);
                claims.at(c2).setOverlapIfUnset(true);
            }
            else {
                claims.at(c1).setOverlapIfUnset(false);
                claims.at(c2).setOverlapIfUnset(false);
            }
        }
    }
}

int claimUtils::findNonOverlapping(const claimsVec& claims)
{
    for (const auto& c : claims) {
        if (c.hasOverlap()) {
            return c.id();
        }
    }
    return 0;
}
