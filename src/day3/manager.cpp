//
// Created by joel on 2019-03-17.
//

#include "manager.hpp"
#include <algorithm>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

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
        std::ifstream ifs(path, std::ios::in);
        std::vector<claim> claims;

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

        // Calculate how big santas fabric needs to be to fit all the claims.
        int maxW = 0;
        int maxH = 0;
        auto findMax = [&](const auto& c) {
            maxH = c.getHeightEndCoord() > maxH ? c.getHeightEndCoord() : maxH;
            maxW = c.getWidthEndCoord() > maxW ? c.getWidthEndCoord() : maxW;
        };
        std::for_each(claims.cbegin(), claims.cend(), findMax);
        /*for (auto c : claims) {
            maxH = c.getHeightEndCoord() > maxH ? c.getHeightEndCoord() : maxH;
            maxW = c.getWidthEndCoord() > maxW ? c.getWidthEndCoord() : maxW;
        }*/

        std::cout << "maxH: " << maxH << " maxW" << maxW << "\n";

        for (auto c : claims) {
            c.print();
        }

        return 0;
    }

private:
};

void manager::manager(char const* path)
{
    task1 tsk1;
    auto overlaps = tsk1.findOverlaps(path);
    std::cout << "Task 1, overlaps found: " << overlaps << "\n";
}
