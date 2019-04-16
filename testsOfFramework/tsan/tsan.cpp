/**
 * This program intends to test that an TSAN check will crash this application when run.
 *
 * Program taken from: https://github.com/google/sanitizers/wiki/ThreadSanitizerCppManual
 * Adapted original program so that there are no compiler wanrings and put stuff in namespace.
 */

#include "tsan.hpp"
#include <pthread.h>

namespace
{
    int Global;

    void* Thread1(void* x)
    {
        (void)x;  // Tell compiler var. is unused.
        Global++; // Data race.
        return nullptr;
    }

    void* Thread2(void* x)
    {
        (void)x;  // Tell compiler var. is unused.
        Global--; // Data race.
        return nullptr;
    }
} // namespace

int TSAN::doTest()
{
    pthread_t t[2];
    pthread_create(&t[0], nullptr, Thread1, nullptr);
    pthread_create(&t[1], nullptr, Thread2, nullptr);
    pthread_join(t[0], nullptr);
    pthread_join(t[1], nullptr);
    return 0;
}
