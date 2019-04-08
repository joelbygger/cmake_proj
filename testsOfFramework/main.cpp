
#include "test_base.hpp"
#include "ubsan.hpp"
//#include <stdlib.h>
#include <cstdlib>
//#include <sys/types.h>
#include <iostream>
#include <string_view>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

int main()
{
    // TestBase* array[2];
    std::vector<TestBase*> tests;
    // array[0] = new UBSAN();
    UBSAN tst;
    tests.push_back(&tst);

    while (!tests.empty()) {
        pid_t pid = fork();
        switch (pid) {
        case -1:
            std::cout << "Fork failed.\n";
            return 1;
        case 0: {
            std::cout << "We, the child, now calling our designated test.\n";
            // ubsan::app1();
            // UBSAN tst;
            // runTest(tst);
            // runTest(array[0]);
            // array[0]->operator()();
            // array[0]->doTest();
            std::cout << tests.back()->getName() << " - is about to run.\n" << std::flush;
            tests.back()->doTest();
            // runTest(tests.back());
            // Child - execute wrapped command
            // execvp(argv[1], argv + 1);
            exit(0); // If child has not crashed, it will return '0' here.
        }
        default: {
            // Parent - wait child and interpret its result
            int status = 666;
            wait(&status);
            // if(WIFEXITED(status)) {
            // if(WIFSIGNALED(status)) {
            if (status != 0) {
                std::cout << tests.back()->getName() << " - CRASHED, did you expect it to? It returned: " << status << "\n" << std::flush;
            }
            else {
                std::cout << tests.back()->getName() << " - did NOT crash (returned 0), did you expect it to? \n" << std::flush;
            }

            // If we want to use CTest, we might change this return value to e.g. 1 if we _know_ something has failed.
        }
        }
        tests.pop_back();
    }
    return 0;
}
