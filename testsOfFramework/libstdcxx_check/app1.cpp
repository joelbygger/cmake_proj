/**
 * This program intends to test that additional compiler definitions will make stdlibc++ crash.
 * Normally this program wonät crash.
 *
 * Program taken from: https://kristerw.blogspot.com/2018/03/detecting-incorrect-c-stl-usage.html
 */

#include <iostream>
#include <list>

int main()
{
    std::list<int> list1 = { 1, 2, 3, 4 };
    std::list<int> list2 = { 5, 3, 4, 2 };
    list1.merge(list2);
    for (auto x : list1)
        std::cout << x << '\n';
}