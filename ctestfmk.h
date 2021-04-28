#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <errno.h>
#include <stdbool.h>

#define ERROR_MESSAGE_MAX_SIZE 100

// ***** Framework *****

typedef void (* TestFunction)(const void*); // Test function pointer

typedef struct _TestFunctionAssertNode {
    bool in_success;
    char *error_message;
    struct _TestFunctionAssertNode *next;
} TestFunctionAssertNode;

typedef struct {
    TestFunctionAssertNode *first_node;
} TestFunctionAssertList;

typedef struct _TestFunctionNode {
    const char *name;
    TestFunction function;
    bool execute;
    bool in_success;
    int nb_asserts;
    double execution_time;
    TestFunctionAssertList assert_functions;
    struct _TestFunctionNode *next;
} TestFunctionNode;

typedef struct {
    TestFunctionNode *first_node;
} TestFunctionList;

typedef struct {
    const char *name;
    int nb_tests;
    int nb_asserts;
    double execution_time;
    long memory_usage;
    TestFunctionList functions;
} TestSuite;

TestSuite *createTestSuite(const char*);

void addTestFunction(TestSuite*, const char*, TestFunction);
void runTestSuite(TestSuite*);

void displayTestSuite(TestSuite*);
void deleteTestSuite(TestSuite*);

void addTestFunctionAssert(TestFunctionNode*, bool, char*);

// ***** Asserts *****

void assertEqualsInt(int, int, const void*);
void assertEqualsDouble(double, double, const void*);
void assertEqualsChar(char, char, const void*);
void assertEqualsCharP(char*, char*, const void*);
void assertTrue(bool, const void*);
void assertFalse(bool, const void*);

#endif