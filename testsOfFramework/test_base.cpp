/**
 * This file only implements anchor, contains no business logic.
 */

#include "test_base.hpp"

/**
 * Required to remove vtable from all translation units including this file.
 * Removes compiler warning:
 * "warning: 'nnn' has no out-of-line virtual method definitions; its vtable will be emitted in every translation unit [-Wweak-vtables]"
 */
void TestBase::anchor() {}
