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
    claim(int id, int leftCoord, int topCoord, int w, int h)
        : m_id(id), m_leftCoord(leftCoord), m_topCoord(topCoord), m_width(w), m_height(h), m_hasOverlap(HasOverlap::unknown)
    {
    }

    void print() const
    {
        std::cout << "#" << m_id << " @ " << m_leftCoord << "," << m_topCoord << ": " << m_width << "x" << m_height << "\n";
    }

    auto leftCoord() const
    {
        return m_leftCoord;
    }

    auto topCoord() const
    {
        return m_topCoord;
    }

    auto widthEndCoord() const
    {
        return m_leftCoord + m_width;
    }

    auto heightEndCoord() const
    {
        return m_topCoord + m_height;
    }

    void setOverlapIfUnset(const bool doesOverlap)
    {
        // Don't overwrite a previously set overlap, that overlap still exists...
        if (m_hasOverlap == HasOverlap::unknown) {
            if (doesOverlap) {
                m_hasOverlap = HasOverlap::yes;
            }
            else {
                m_hasOverlap = HasOverlap::no;
            }
        }
    }

    auto hasOverlap() const
    {
        // An unset overlap status is interpreted as it is set.
        return m_hasOverlap == HasOverlap::no;
    }

    auto id() const
    {
        return m_id;
    }

    enum class HasOverlap
    {
        unknown,
        yes,
        no
    };

private:
    int m_id;                // ID of the claim.
    int m_leftCoord;         // How many inches from left the box starts.
    int m_topCoord;          // How many inches from top the box starts.
    int m_width;             // Width from left coord.
    int m_height;            // Height from top coord.
    HasOverlap m_hasOverlap; // Info on if this claim overlaps another claim.
};

#endif // ADVENTOFCODE2018_CLAIM_HPP
