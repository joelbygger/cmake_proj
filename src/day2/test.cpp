//
// Created by joel on 2019-03-31.
//

#include "catch2.hpp"
#include "input.hpp"
#include "manager.hpp"
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

SCENARIO("Day 2: Box IDs, calculating hash for all and then fining two that matches")
{
    GIVEN("We want to calc hash on a file")
    {
        WHEN("Test input is used")
        {
            std::vector<std::string> ids;

            std::istringstream stream(inputTestStr.data());
            for (std::string id; std::getline(stream, id, '\n');) {
                ids.emplace_back(id);
            }

            int hash = 0;
            std::string id;
            std::tie(hash, id) = manager::manager(ids);
            THEN("We get correct results")
            {
                REQUIRE(hash == 12);
                REQUIRE(id == "aabcdd");
            }
        }

        WHEN("Real input is used")
        {
            std::vector<std::string> ids;

            std::istringstream stream(inputStr.data());
            for (std::string id; std::getline(stream, id, '\n');) {
                ids.emplace_back(id);
            }

            int hash = 0;
            std::string id;
            std::tie(hash, id) = manager::manager(ids);
            THEN("We get correct results")
            {
                REQUIRE(hash == 5456);
                REQUIRE(id == "megsdwkukhrinkatftoyzxcbvq");
            }
        }
    }
}
