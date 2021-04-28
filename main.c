#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tests.h"

int main() {
    TestSuite *ts_fake = createTestSuite("FAKE");
    addTestFunction(ts_fake, "fake no assert", test_fake);
    addTestFunction(ts_fake, "fake int", test_fake_int);
    addTestFunction(ts_fake, "fake double/float", test_fake_double);
    addTestFunction(ts_fake, "fake char", test_fake_char);
    addTestFunction(ts_fake, "fake char pointer", test_fake_charp);
    addTestFunction(ts_fake, "fake boolean", test_fake_bool);
    runTestSuite(ts_fake);

    displayTestSuite(ts_fake);

    deleteTestSuite(ts_fake);

    return EXIT_SUCCESS;
}