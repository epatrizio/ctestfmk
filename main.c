#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tests.h"

/*
main arguments :
 - No : Run all test suites
 - First = Test suite name : To execute a specific test suite
 - Second = Function test name : To execute a specific test suite function
*/
int main(int argc, char *argv[])
{
    TestSuite *ts_fake_1 = createTestSuite("FAKE 1");
    addTestFunction(ts_fake_1, "fake no assert", test_fake);
    addTestFunction(ts_fake_1, "fake int", test_fake_int);
    addTestFunction(ts_fake_1, "fake double/float", test_fake_double);
    runTestSuite(ts_fake_1, argc, argv);
    displayTestSuite(ts_fake_1);

    TestSuite *ts_fake_2 = createTestSuite("FAKE 2");
    addTestFunction(ts_fake_2, "fake char", test_fake_char);
    addTestFunction(ts_fake_2, "fake char pointer", test_fake_charp);
    runTestSuite(ts_fake_2, argc, argv);

    TestSuite *ts_fake_3 = createTestSuite("FAKE 3");
    addTestFunction(ts_fake_3, "fake boolean", test_fake_bool);
    runTestSuite(ts_fake_3, argc, argv);

    deleteTestSuite(ts_fake_1);
    deleteTestSuite(ts_fake_2);
    deleteTestSuite(ts_fake_3);

    return EXIT_SUCCESS;
}