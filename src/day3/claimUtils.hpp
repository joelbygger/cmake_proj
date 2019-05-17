//
// Created by joel on 2019-03-19.
//

#ifndef ADVENTOFCODE2018_CLAIMUTILS_HPP
#define ADVENTOFCODE2018_CLAIMUTILS_HPP

#include "claim.hpp"
#include <cstddef>
#include <tuple>
#include <vector>

using claimsVec = std::vector<claim>;

namespace claimUtils
{
    /**
     * Creates a vector of claims.
     * @param path To a file with claims.
     * @return The created vector.
     */
    claimsVec fetchClaims(char const* path);

    /**
     * Calculate how big santas fabric needs to be to fit all the claims.
     * @param claims Vector of claims.
     * @return A tuple tuple with required width and height.
     */
    std::tuple<size_t, size_t> getMaxCoordinates(const claimsVec& claims);

    /**
     * Compares all claims in received vector to all other claims, marks them if they overlap or not.
     * @param claims vector of claims
     */
    void markOverlappingClaims(claimsVec& claims);

    /**
     * Loops over all claims, returns the first found non-overlapping claim.
     * @param claims vector of claims
     * @return ID of the first found non-overlapping claim, otherwise returns 0.
     */
    int findNonOverlapping(const claimsVec& claims);
} // namespace claimUtils

#endif // ADVENTOFCODE2018_CLAIMUTILS_HPP
