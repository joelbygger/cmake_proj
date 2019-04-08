/**
 * This program intends to test that additional compiler definitions will make stdlibc++ crash when run.
 * Without this additional compiler definition this program won't crash.
 *
 * Program taken from: https://kristerw.blogspot.com/2018/03/detecting-incorrect-c-stl-usage.html
 */


#include "libcxx_debug.hpp"
#include <list>

int LibCXXdebug::doTest()
{
    std::list<int> list1 = { 1, 2, 3, 4 };
    list1.insert(list1.begin(), list1.begin(), list1.end());
    auto j = 0;
    for (auto x : list1) {
        j += x; // Dummy stuff.
    }

    if(j == 666) { // Dummy stuff.
        return 1;
    }
    return 0;
}
