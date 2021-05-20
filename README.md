# ctestfmk - Minimalist and naive unit testing framework for C programs

I'm learning the C language! (Mieux vaut tard que jamais :)

I read the reference book (Kernighan / Ritchie). And i decided to experiment with some concepts through a concrete projet.
So, ctestfmk was born! inspired by this online [tutorial](https://koor.fr/C/Tutorial/FunctionPointers.wp).

This framework provides an environment to perform functions and get quick feedbacks on results.
This project is experimental, only to learn. I hope it can help, even evolve with real use cases.

# Installation

Here is how to integrate ctestfmk into your C program :
* In your program tree structure, create a "tests" directory
    * tests/ will contain all your test source code
    * create a "lib" subdirectory
        * "lib" will contain the ctestfmk static library and the .h file for #import

After that, your environment is ready!
In the following sections, you will see how to write your tests and then compile them.

# Use (writing tests)

* In tests/ directory
    * create a tests.h file (ctestfmk #import and test functions declarations)
    * create *.c files for implement all your test functions respecting some framework rules
        * A test function have to respect a specific signature -> void test_fct_name(const void *function_node)
        * A test function have to integrate assert specific macros (to automatically have the file and the call line)
    * create main.c file for create tests suites (Remember, manual creation)

*In the project, you can see a full commented example offering fake test suites.*

# Compilation

Last step : compile to execute the tests!

Your program already has a compilation process. With tests, your program will have another independent compilation process.
In practice, this is another full program with:
* Your files containing the functions to test
* Your specific test files
* A link on the ctestfmk library

Here is the gcc command with ctestfmk static library :
gcc -g -o myPrg_test -Wall -Wextra myFile1.c myFile2.c ... tests/myTestFile1.c tests/myTestFile2.c ... -lm -L./tests/lib -lctestfmk

*In the project, the Makefile contains static and dynamic library compilation process.*

# Run tests

main.c arguments :
* No argument : Run all test suites
* First argument (= Test suite name) : To execute a specific test suite
* Second argument (= Function test name) : To execute a specific test suite function
