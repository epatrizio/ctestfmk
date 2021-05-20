#include <stdio.h>
#include <string.h>

#include "ctestfmk.h"

void updateTestFunctionNode(const void *function_node, char* file, int line, bool success, char *error_message)
{
    TestFunctionNode* current_function_node = (TestFunctionNode*) function_node;
    current_function_node->nb_asserts++;
    current_function_node->in_success = current_function_node->in_success && success;
    addTestFunctionAssert(current_function_node, file, line, success, error_message);
}

void assertEqualsInt(int expected, int actual, const void *function_node, char* file, int line)
{
    bool success = (expected == actual);
    char error_message[ERROR_MESSAGE_MAX_SIZE] = {'\0'};
    if (!success)
        sprintf(error_message, "[error %s:%i] assertEqualsInt: %i expected %i", file, line, actual, expected);

    updateTestFunctionNode(function_node, file, line, success, error_message);
}

void assertEqualsDouble(double expected, double actual, const void *function_node, char* file, int line)
{
    bool success = (expected == actual);
    char error_message[ERROR_MESSAGE_MAX_SIZE] = {'\0'};
    if (!success)
        sprintf(error_message, "[error %s:%i] assertEqualsDouble: %f expected %f", file, line, actual, expected);

    updateTestFunctionNode(function_node, file, line, success, error_message);
}

void assertEqualsChar(char expected, char actual, const void *function_node, char* file, int line)
{
    bool success = (expected == actual);
    char error_message[ERROR_MESSAGE_MAX_SIZE] = {'\0'};
    if (!success)
        sprintf(
            error_message,
            "[error %s:%i] assertEqualsChar: %c (%i) expected %c (%i)",
            file, line,
            actual, actual,
            expected, expected
        );

    updateTestFunctionNode(function_node, file, line, success, error_message);
}

void assertEqualsCharP(char* expected, char* actual, const void *function_node, char* file, int line)
{
    bool success = (strcmp(expected, actual) == 0);
    char error_message[ERROR_MESSAGE_MAX_SIZE] = {'\0'};
    if (!success)
        sprintf( error_message, "[error %s:%i] assertEqualsCharP: %s expected %s", file, line, actual, expected);

    updateTestFunctionNode(function_node, file, line, success, error_message);
}

void assertTrue(bool actual, const void *function_node, char* file, int line)
{
    char error_message[ERROR_MESSAGE_MAX_SIZE] = {'\0'};
    if (!actual)
        sprintf(error_message, "[error %s:%i] assertEqualsTrue: False return", file, line);

    updateTestFunctionNode(function_node, file, line, actual, error_message);
}

void assertFalse(bool actual, const void *function_node, char* file, int line)
{
    char error_message[ERROR_MESSAGE_MAX_SIZE] = {'\0'};
    if (actual)
        sprintf(error_message, "[error %s:%i] assertEqualsFalse: True return", file, line);

    updateTestFunctionNode(function_node, file, line, !actual, error_message);
}
