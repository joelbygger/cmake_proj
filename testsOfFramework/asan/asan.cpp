
#include "asan.hpp"
#include <memory>

int ASAN::doTest()
{
    int* x;
    {
        std::shared_ptr<int[]> array(new int[100]);
        array[0] = 0;
        /* We shouldn't extracxt a raw pointer at all, but to prove a concept...
        Also we don't want any compiler warnings, this is what I could figure out... */
        x = &array[0];
    }
    return x[5]; // Crash here.
}
