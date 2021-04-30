#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/resource.h>

#include "ctestfmk.h"

void insertList(TestFunctionList *list, const char *name, TestFunction function);
long getMemoryUsage();

TestSuite *createTestSuite(const char *name)
{
    TestFunctionList empty_list;
    empty_list.first_node = NULL;

    TestSuite *empty_test_suite = (TestSuite *) malloc(sizeof(TestSuite));
    empty_test_suite->name = name;
    empty_test_suite->nb_tests = 0;
    empty_test_suite->nb_asserts = 0;
    empty_test_suite->execution_time = 0;
    empty_test_suite->memory_usage = getMemoryUsage();
    empty_test_suite->functions = empty_list;

    return empty_test_suite;
}

void addTestFunction(TestSuite *suite, const char *name, TestFunction function)
{
    insertList(&suite->functions, name, function);
    suite->nb_tests++;
}

void runTestFunction(TestFunctionNode *function_node)
{
    clock_t begin = clock();
    function_node->function(function_node);
    clock_t end = clock();

    function_node->execute = true;
    function_node->execution_time = (double)(end - begin) / CLOCKS_PER_SEC;
}

void runTestSuite(TestSuite *suite)
{
    printf("Test Suite %s (%i tests) -------------------------------\n", suite->name, suite->nb_tests);

    unsigned short int tests_in_success = 0;
    unsigned short int tests_in_failure = 0;

    TestFunctionNode *current_node = suite->functions.first_node;
    while (current_node != NULL) {
        runTestFunction(current_node);
        (current_node->execute && current_node->in_success) ? tests_in_success++ : tests_in_failure++;
        suite->nb_asserts += current_node->nb_asserts;
        suite->execution_time += current_node->execution_time;
        printf(
            "Run %s (%i asserts) in %f seconds => %s\n",
            current_node->name,
            current_node->nb_asserts,
            current_node->execution_time,
            (current_node->execute && current_node->in_success) ?
                ((current_node->nb_asserts == 0) ? "\033[0;33mOK\033[0m" : "\033[0;32mOK\033[0m") :
                "\033[1;31mKO\033[0m"
        );
        TestFunctionAssertNode *current_assert_node = current_node->assert_functions.first_node;
        while (current_assert_node != NULL) {
            if (!current_assert_node->in_success)
                printf(" - \033[1;31m%s\033[0m\n", current_assert_node->error_message);
            current_assert_node = current_assert_node->next;
        }
        current_node = current_node->next;
    }

    printf("> Test suite statistics:\n");
    printf(
        "\tRun %hu tests (%i asserts) in %f seconds - Memory usage: %ld kilobytes\n",
        tests_in_success+tests_in_failure,
        suite->nb_asserts,
        suite->execution_time,
        suite->memory_usage
    );
    printf("\t - %hu test(s) in success\n", tests_in_success);
    printf("\t - %hu test(s) in failure\n\n", tests_in_failure);
}

void insertList(TestFunctionList *list, const char *name, TestFunction function)
{
    TestFunctionAssertList empty_list;
    empty_list.first_node = NULL;

    TestFunctionNode *node = (TestFunctionNode *) malloc(sizeof(TestFunctionNode));
    node->name = name;
    node->function = function;
    node->execute = false;
    node->in_success = true;
    node->nb_asserts = 0;
    node->execution_time = 0;
    node->assert_functions = empty_list;
    node->next = NULL;

    if (list->first_node == NULL) {        
        list->first_node = node;
        return;
    }

    TestFunctionNode *current_node = list->first_node;
    while (current_node != NULL) {
        if (current_node->next == NULL) {
            current_node->next = node;
            return;
        }
        current_node = current_node->next;
    }
}

void addTestFunctionAssert(TestFunctionNode* function_node, char *file, int line, bool in_success, char *error_message)
{
    char *message;
    message = (char *) malloc(strlen(error_message)+1);
    strcpy(message, error_message);

    char *filename;
    filename = (char *) malloc(strlen(file)+1);
    strcpy(filename, file);

    TestFunctionAssertNode *node = (TestFunctionAssertNode *) malloc(sizeof(TestFunctionAssertNode));
    node->file = filename;
    node->line = line;
    node->in_success = in_success;
    node->error_message = message;
    node->next = NULL;

    if (function_node->assert_functions.first_node == NULL) {        
        function_node->assert_functions.first_node = node;
        return;
    }

    TestFunctionAssertNode *current_node = function_node->assert_functions.first_node;
    while (current_node != NULL) {
        if (current_node->next == NULL) {
            current_node->next = node;
            return;
        }
        current_node = current_node->next;
    }
}

void deleteTestSuite(TestSuite *suite)
{
    TestFunctionNode *current_node = suite->functions.first_node;
    while (current_node != NULL) {
        TestFunctionAssertNode *current_assert_node = current_node->assert_functions.first_node;
        while (current_assert_node != NULL) {
            TestFunctionAssertNode *next_assert_node = current_assert_node->next;
            free(current_assert_node);
            current_assert_node = next_assert_node;
        }
        TestFunctionNode *next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }

    free(suite);
}

void displayTestSuite(TestSuite *suite)
{
    printf(
        "Test suite %s (%i tests) - Execution time: %f seconds - Memory usage: %ld kilobytes\n",
        suite->name,
        suite->nb_tests,
        suite->execution_time,
        suite->memory_usage
    );
    TestFunctionNode *current_node = suite->functions.first_node;
    while (current_node != NULL) {
        printf(" - Function test name: %s\n", current_node->name);
        printf("  - Execute: %s\n", current_node->execute ? "YES" : "NO");
        printf("  - In success: %s\n", current_node->in_success ? "YES" : "NO");
        printf("  - Execution time: %f seconds\n", current_node->execution_time);
        printf("  - Number of asserts: %i\n", current_node->nb_asserts);
        TestFunctionAssertNode *current_assert_node = current_node->assert_functions.first_node;
        while (current_assert_node != NULL) {
            printf("   * File call name: %s\n", current_assert_node->file);
            printf("   * File call line: %i\n", current_assert_node->line);
            printf("   * In success: %s\n", current_assert_node->in_success ? "YES" : "NO");
            printf("   * Error message: %s\n", current_assert_node->error_message);
            current_assert_node = current_assert_node->next;
        }
        current_node = current_node->next;
    }
}

long getMemoryUsage()
{
    struct rusage r_usage;
    int ret = getrusage(RUSAGE_SELF,&r_usage);
    if (ret == 0)
        return r_usage.ru_maxrss;
    else
        return errno;
}