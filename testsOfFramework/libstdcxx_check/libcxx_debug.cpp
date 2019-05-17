/**
 * This program intends to test that additional compiler definitions will make stdlibc++ crash when run.
 * Without this additional compiler definition this program won't crash.
 *
 * Program taken from: https://kristerw.blogspot.com/2018/03/detecting-incorrect-c-stl-usage.html
 */

#include "libcxx_debug.hpp"
#include <list>
#include <numeric>

int LibCXXdebug::doTest()
{
    std::list<int> list1 = { 1, 2, 3, 4 };
    list1.insert(list1.begin(), list1.begin(), list1.end()); // Crash.

    auto j = std::accumulate(list1.begin(), list1.end(), 0); // Dummy stuff to get a ret. val.
    const auto impossibleVal = 666;
    if (j == impossibleVal) { // Dummy stuff.
        return 1;
    }
    return 0;
}
