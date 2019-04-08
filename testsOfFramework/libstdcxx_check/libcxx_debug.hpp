
#ifndef LIBCXX_DEBUG_HPP
#define LIBCXX_DEBUG_HPP

#include "test_base.hpp"
#include <string_view>

class LibCXXdebug : public TestBase
{
public:
    int doTest() final;

    std::string_view getName() final
    {
        return "LIBSTDCXX_DEBUG";
    }

    // Define all special member functions.
    LibCXXdebug() = default;
    ~LibCXXdebug() final = default;
    LibCXXdebug(const LibCXXdebug&) = delete;
    LibCXXdebug& operator=(const LibCXXdebug&) = delete;
    LibCXXdebug(LibCXXdebug&&) = delete;
    LibCXXdebug& operator=(LibCXXdebug&&) = delete;
};

#endif // LIBCXX_DEBUG_HPP
