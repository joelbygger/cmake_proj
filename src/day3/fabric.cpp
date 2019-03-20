//
// Created by joel on 2019-03-19.
//

#include "fabric.hpp"
#include "claim.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>

/*************************************************
 *
 * Public functions
 *
 ************************************************/

/**
 * Constructor, creates a fabric large enough to fit all claims.
 */
fabric::fabric(const size_t maxW, const size_t maxH) : m_fabric(maxH, matrixRow(maxW, 0)) {}

/**
 * Marks all claims, implicitly also notes where any claims overlap.
 * @param claims Vector with all claims.
 */
void fabric::markClaimsOnFabric(const std::vector<claim>& claims)
{
    /* For each claim:
      - Places the row on hte fabric, starting on top row..
    For each row:
      - Mark where on row claim is. */
    for (auto c : claims) {
        for (auto i = static_cast<size_t>(c.topCoord()); i <= static_cast<size_t>(c.heightEndCoord()); i++) {
            auto begin = m_fabric.at(i).begin();
            auto end = m_fabric.at(i).begin();
            std::advance(begin, c.leftCoord());
            std::advance(end, c.widthEndCoord() + 1); // Add 1, we want the iterator after the element to make for_each work.
            std::for_each(begin, end, [](auto& n) { ++n; });
        }
    }
}

/**
 * Calculate how many coordinates claims overlap.
 * @return Number of coordinates where claims overlap.
 */
int fabric::countOverlaps() const
{
    int overlaps = 0;

    for (const auto& row : m_fabric) {
        for (const auto spot : row) {
            if (spot > 1) {
                overlaps++;
            }
        }
    }
    return overlaps;
}

// Prints a matrix, expects the inner content to not be printable.
void fabric::printFabric() const
{
    for (size_t i = 0; i < m_fabric.size(); i++) {           // Rows
        for (size_t j = 0; j < m_fabric.at(0).size(); j++) { // Columns
            std::cout << m_fabric.at(i).at(j) << std::flush;
        }
        std::cout << "\n";
    }
}

/*************************************************
 *
 * Private functions
 *
 ************************************************/
