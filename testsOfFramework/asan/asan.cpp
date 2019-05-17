
#include "asan.hpp"
#include <memory>

int ASAN::doTest()
{
    int* x;
    {
        std::shared_ptr<int[]> array(new int[100]); // NOLINT : This code is intended to be bad
        array[0] = 0;
        x = &array[0];
    }

    // Crash here.
    // cppcheck-suppress invalidLifetime
    return x[5]; // NOLINT(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers) : This code is intended to be bad.
}
