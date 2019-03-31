//
// Created by joel on 2019-03-26.
//

#include "catch2.hpp"
#include "input.hpp"
#include "polymer.hpp"
#include <cstddef>
#include <string_view>
#include <tuple>
#include <vector>

SCENARIO("Day 5: testing inputs")
{
    GIVEN("We want to reduce different polymers")
    {
        WHEN("Test input is used")
        {
            std::vector<char> inputTest{ 'd', 'a', 'b', 'A', 'c', 'C', 'a', 'C', 'B', 'A', 'c', 'C', 'c', 'a', 'D', 'A' };

            size_t task1Sz = 0;
            size_t minSz = 0;
            std::tie(task1Sz, minSz) = polymer::manager(inputTest);
            THEN("We get correct results")
            {
                REQUIRE(task1Sz == 10);
                REQUIRE(minSz == 4);
            }
        }

        WHEN("Real input is used")
        {
            std::vector<char> input;
            for (const char c : inputStr) {
                input.emplace_back(c);
            }

            size_t task1Sz = 0;
            size_t minSz = 0;
            std::tie(task1Sz, minSz) = polymer::manager(input);

            THEN("We get nice numbers")
            {
                REQUIRE(task1Sz == 11636);
                REQUIRE(minSz == 5302);
            }
        }
    }
}
