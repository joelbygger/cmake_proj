/**
 * This base class shall be used for all tests, to make calling the tests easier vi a common interface.
 * */

#ifndef TEST_BASE_HPP
#define TEST_BASE_HPP

#include <string_view>

class TestBase
{
public:
    // All tests will be called via this interface.
    // virtual int operator()() = 0;
    virtual int doTest() = 0;
    virtual std::string_view getName() = 0;

    // Required to remove vtable from all translation units including this header.
    virtual void anchor();

    // Define all special member functions.
    TestBase() = default;
    virtual ~TestBase() = default;
    TestBase(const TestBase&) = default;
    TestBase& operator=(const TestBase&) = delete;
    TestBase(TestBase&&) = delete;
    TestBase& operator=(TestBase&&) = delete;
};

#endif // TEST_BASE_HPP
