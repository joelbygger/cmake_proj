//
// Created by joel on 2019-03-26.
//

#include "catch2.hpp"
#include "polymer.hpp"
#include <vector>

TEST_CASE("Some tests2", "[reducePolymer2]")
{
    std::vector<char> inputTest{ 'd', 'a', 'b', 'A', 'c', 'C', 'a', 'C', 'B', 'A', 'c', 'C', 'c', 'a', 'D', 'A' };
    REQUIRE(polymer::reduce(inputTest) == 10);
    REQUIRE(polymer::reduce(inputTest) == 11);
}
