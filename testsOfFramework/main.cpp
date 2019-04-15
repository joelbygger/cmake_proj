
#include "asan.hpp"
#include "libcxx_debug.hpp"
#include "test_base.hpp"
#include "tsan.hpp"
#include "ubsan.hpp"
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

class Tests
{
public:
    void addTest(TestBase* tst)
    {
        tests.push_back(tst);
    }

    int run()
    {
        while (!tests.empty()) {
            pid_t pid = fork();

            switch (pid) {
            case -1:
                std::cout << "Fork failed.\n";
                return 1;

            case 0: {
                std::cout << "\n===============================================================\n"
                          << tests.back()->getName() << " - is about to run.\n"
                          << std::flush;
                tests.back()->doTest();
                exit(0); // If child has not crashed, it will return '0' here.
            }

            default: {
                // Parent - wait child and interpret its result
                int status = 666;
                wait(&status);
                if (status != 0) {
                    std::cout << "\n-----> " << tests.back()->getName() << "\n - CRASHED, did you expect it to? It returned: " << status << "\n" << std::flush;
                }
                else {
                    std::cout << "\n-----> " << tests.back()->getName() << "\n - did NOT crash (returned 0), did you expect it to? \n" << std::flush;
                }
                break;
            }
            }

            tests.pop_back();
        }

        std::cout << "\n===============================================================\n" << std::flush;

        // If we want to use CTest, we might change this return value to e.g. 1 if we _know_ something has failed.
        return 0;
    }

private:
    std::vector<TestBase*> tests;
};

int main()
{
    Tests tests;

    ASAN asan;
    LibCXXdebug libcxx;
    TSAN tsan;
    UBSAN ubsan;

    tests.addTest(&asan);
    tests.addTest(&libcxx);
    tests.addTest(&tsan);
    tests.addTest(&ubsan);
    return tests.run();
}
