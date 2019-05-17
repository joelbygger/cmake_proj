/**
 * This program intends to test that an ASAN check will crash this application when run.
 */

#ifndef ASAN_HPP
#define ASAN_HPP

#include "test_base.hpp"
#include <string_view>

class ASAN : public TestBase
{
public:
    int doTest() final;

    std::string_view getName() final
    {
        return "ASAN";
    }

    // Define all special member functions.
    ASAN() = default;
    ~ASAN() final = default;
    ASAN(const ASAN&) = delete;
    ASAN& operator=(const ASAN&) = delete;
    ASAN(ASAN&&) = delete;
    ASAN& operator=(ASAN&&) = delete;
};

#endif // ASAN_HPP
