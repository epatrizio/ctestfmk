#include <stdio.h>
#include <string.h>

#include "ctestfmk.h"

void updateTestFunctionNode(const void *function_node, bool success, char *error_message)
{
    TestFunctionNode* current_function_node = (TestFunctionNode*) function_node;
    current_function_node->nb_asserts++;
    current_function_node->in_success = current_function_node->in_success && success;
    addTestFunctionAssert(current_function_node, success, error_message);
}

void assertEqualsInt(int expected, int actual, const void *function_node)
{
    bool success = (expected == actual);
    char error_message[ERROR_MESSAGE_MAX_SIZE] = {'\0'};
    if (!success)
        sprintf(error_message, "[error] assertEqualsInt: expected %i - actual %i", expected, actual);

    updateTestFunctionNode(function_node, success, error_message);
}

void assertEqualsDouble(double expected, double actual, const void *function_node)
{
    bool success = (expected == actual);
    char error_message[ERROR_MESSAGE_MAX_SIZE] = {'\0'};
    if (!success)
        sprintf(error_message, "[error] assertEqualsDouble: expected %f - actual %f", expected, actual);

    updateTestFunctionNode(function_node, success, error_message);
}

void assertEqualsChar(char expected, char actual, const void *function_node)
{
    bool success = (expected == actual);
    char error_message[ERROR_MESSAGE_MAX_SIZE] = {'\0'};
    if (!success)
        sprintf(
            error_message,
            "[error] assertEqualsChar: expected %c (%i) - actual %c (%i)",
            expected, expected,
            actual, actual
        );

    updateTestFunctionNode(function_node, success, error_message);
}

void assertEqualsCharP(char* expected, char* actual, const void *function_node)
{
    bool success = (strcmp(expected, actual) == 0);
    char error_message[ERROR_MESSAGE_MAX_SIZE] = {'\0'};
    if (!success)
        sprintf( error_message, "[error] assertEqualsCharP: expected %s - actual %s", expected, actual);

    updateTestFunctionNode(function_node, success, error_message);
}

void assertTrue(bool actual, const void *function_node)
{
    updateTestFunctionNode(function_node, actual, actual ? "" : "[error] assertEqualsTrue: False return");
}

void assertFalse(bool actual, const void *function_node)
{
    updateTestFunctionNode(function_node, !actual, !actual ? "" : "[error] assertEqualsFalse: True return");
}
