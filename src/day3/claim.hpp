//
// Created by joel on 2019-03-19.
//

#ifndef ADVENTOFCODE2018_CLAIM_HPP
#define ADVENTOFCODE2018_CLAIM_HPP

#include <iostream>

/** A claim, an area. Grows from top left corner of area.
 * Grows to the right and down.
 * I.e. top left corner is pos 0,0.
 */
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
    int m_id; // ID of the claim.
    int m_leftCoord; // How many inches from left the box starts.
    int m_topCoord; // How many inches from top the box starts.
    int m_width; // Width from left coord.
    int m_height; // Height from top coord.
};

#endif // ADVENTOFCODE2018_CLAIM_HPP
