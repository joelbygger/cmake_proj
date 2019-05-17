
#ifndef UBSAN_HPP
#define UBSAN_HPP

#include "test_base.hpp"
#include <string_view>

class UBSAN : public TestBase
{
public:
    int doTest() final;

    std::string_view getName() final
    {
        return "UBSAN";
    }

    // Define all special member functions.
    UBSAN() = default;
    ~UBSAN() final = default;
    UBSAN(const UBSAN&) = delete;
    UBSAN& operator=(const UBSAN&) = delete;
    UBSAN(UBSAN&&) = delete;
    UBSAN& operator=(UBSAN&&) = delete;
};

#endif // UBSAN_HPP
