/**
 * This program intends to test that an UBSAN check will crash this application when run.
 *
 * Program taken from: https://developer.apple.com/documentation/code_diagnostics/undefined_behavior_sanitizer/division_by_zero
 * Adapted original program:
 * - to use floats (GCC flag -fsanitize=float-divide-by-zero) and
 * - to fool Clangs compilation checks / Clang tidy
 */

#include "ubsan.hpp"

int UBSAN::doTest()
{
    float sum = 10;
    for (int i = 64; i >= 0; --i) {
        sum /= static_cast<float>(i); // Error: division by zero on the last iteration.
    }
    return 0;
}
