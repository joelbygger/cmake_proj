
#ifndef UBSAN_HPP
#define UBSAN_HPP

#include "test_base.hpp"
#include <string_view>

class UBSAN : public TestBase
{
public:
    // int operator()() final;
    int doTest() final;

    std::string_view getName() final
    {
        return "UBSAN";
    }
    // const std::string_view name = "UBSAN";

    // Define all special member functions.
    UBSAN() = default;
    ~UBSAN() final = default;
    UBSAN(const UBSAN&) = default;
    UBSAN& operator=(const UBSAN&) = delete;
    UBSAN(UBSAN&&) = delete;
    UBSAN& operator=(UBSAN&&) = delete;

private:
};

#endif // UBSAN_HPP
