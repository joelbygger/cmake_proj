
#ifndef TSAN_HPP
#define TSAN_HPP

#include "test_base.hpp"
#include <string_view>

class TSAN : public TestBase
{
public:
    int doTest() final;

    std::string_view getName() final
    {
        return "TSAN";
    }

    // Define all special member functions.
    TSAN() = default;
    ~TSAN() final = default;
    TSAN(const TSAN&) = delete;
    TSAN& operator=(const TSAN&) = delete;
    TSAN(TSAN&&) = delete;
    TSAN& operator=(TSAN&&) = delete;
};

#endif // TSAN_HPP
