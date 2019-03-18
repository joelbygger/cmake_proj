//
// Created by joel on 2019-03-17.
//

#include "manager.hpp"
#include <algorithm>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

using matrixRow = std::vector<int>;
using matrix = std::vector<matrixRow>;

// A claim, an area. Grows from top left corner od area, to the right and down.
// i.e. top left corner is pos 0,0.
class claim
{
public:
    claim(int id, int leftCoord, int topCoord, int w, int h) : m_id(id), m_leftCoord(leftCoord), m_topCoord(topCoord), m_width(w), m_height(h) {}

    void print() const
    {
        std::cout << "#" << m_id << " @ " << m_leftCoord << "," << m_topCoord << ": " << m_width << "x" << m_height << "\n";
    }

    auto getLeftCoord() const
    {
        return m_leftCoord;
    }

    auto getTopCoord() const
    {
        return m_topCoord;
    }

    auto getWidthEndCoord() const
    {
        return m_leftCoord + m_width;
    }

    auto getHeightEndCoord() const
    {
        return m_topCoord + m_height;
    }

private:
    int m_id;        // ID of the claim.
    int m_leftCoord; // How many inches from left the box starts.
    int m_topCoord;  // How many inches from top the box starts.
    int m_width;
    int m_height;
};

class task1
{
public:
    auto findOverlaps(char const* path)
    {
        std::vector<claim> claims;

        claims = fetchClaims(path);

        // Find max and min coordinates...
        size_t maxW = 0;
        size_t maxH = 0;
        std::tie(maxW, maxH) = getMaxCoordinates(claims);
        std::cout << " maxW: " << maxW << " maxH: " << maxH << "\n";
        // ... so that we can create a fabric of correct size.
        matrix fabric(maxW, matrixRow(maxW, 0));

        markClaimsOnFabric(fabric, claims);

        // printFabric(fabric);

        return countOverlaps(fabric);
    }

private:
    int countOverlaps(const matrix& fabric) const
    {
        int overlaps = 0;
        for (const auto& row : fabric) {
            for (const auto spot : row) {
                if (spot > 1) {
                    overlaps++;
                }
            }
        }
        return overlaps;
    }

    // Prints a matrix, expexts the inner content to not be printable.
    void printFabric(const matrix& fabric) const
    {
        for (size_t i = 0; i < fabric.at(0).size(); i++) {
            for (size_t j = 0; j < fabric.size(); j++) {
                std::cout << fabric.at(i).at(j);
            }
            std::cout << "\n";
        }
    }

    // Marks all claims, laso noting where they overlap.
    void markClaimsOnFabric(matrix& fabric, const std::vector<claim>& claims) const
    {
        /* For each claim:
          - Places the row on hte fabric, starting on top row..
        For each row:
          - Mark where on row claim is. */
        for (auto c : claims) {
            for (auto i = static_cast<size_t>(c.getTopCoord()); i < static_cast<size_t>(c.getHeightEndCoord()); i++) {
                auto begin = fabric.at(i).begin();
                auto end = fabric.at(i).begin();
                std::advance(begin, c.getLeftCoord());
                std::advance(end, c.getWidthEndCoord());
                std::for_each(begin, end, [](auto& n) { ++n; });
            }
        }
    }

    // Calculate how big santas fabric needs to be to fit all the claims.
    std::tuple<size_t, size_t> getMaxCoordinates(const std::vector<claim>& claims) const
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

    // Read from file.
    std::vector<claim> fetchClaims(char const* path) const
    {
        std::vector<claim> claims;
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
