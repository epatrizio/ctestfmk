#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <errno.h>
#include <stdbool.h>

#define ERROR_MESSAGE_MAX_SIZE 100

// ***** Framework *****

typedef void (* TestFunction)(const void*); // Test function pointer

typedef struct _TestFunctionAssertNode {
    char *file;
    int line;
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
void runTestSuite(TestSuite*, int, char*[]);

void displayTestSuite(TestSuite*);
void deleteTestSuite(TestSuite*);

void addTestFunctionAssert(TestFunctionNode*, char*, int, bool, char*);

// ***** Asserts *****

void assertEqualsInt(int, int, const void*, char*, int);
void assertEqualsDouble(double, double, const void*, char*, int);
void assertEqualsChar(char, char, const void*, char*, int);
void assertEqualsCharP(char*, char*, const void*, char*, int);
void assertTrue(bool, const void*, char*, int);
void assertFalse(bool, const void*, char*, int);
void assertNull(void*, const void*, char*, int);

#define assert_equals_int(expected, actual, function_node) assertEqualsInt(expected, actual, function_node, __FILE__, __LINE__)
#define assert_equals_double(expected, actual, function_node) assertEqualsDouble(expected, actual, function_node, __FILE__, __LINE__)
#define assert_equals_char(expected, actual, function_node) assertEqualsChar(expected, actual, function_node, __FILE__, __LINE__)
#define assert_equals_charp(expected, actual, function_node) assertEqualsCharP(expected, actual, function_node, __FILE__, __LINE__)
#define assert_true(actual, function_node) assertTrue(actual, function_node, __FILE__, __LINE__)
#define assert_false(actual, function_node) assertFalse(actual, function_node, __FILE__, __LINE__)
#define assert_null(actual, function_node) assertNull(actual, function_node, __FILE__, __LINE__)

#endif