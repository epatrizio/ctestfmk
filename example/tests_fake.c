#include <stdlib.h>

#include "tests.h"

// Test fonctions, remember use assert macro

void test_fake(const void *function_node)
{
    // No assert, warning reporting.
}

void test_fake_int(const void *function_node)
{
    assert_equals_int(2, 2, function_node);
    assert_equals_int(2, 3, function_node);
}

void test_fake_double(const void *function_node)
{
    assert_equals_double(1.1, 1.23, function_node);
    assert_equals_double(222.20, 222.20, function_node);
    double d1 = 2.45;
    double d2 = 12.45;
    assert_equals_double(d1, d2, function_node);
    float f1 = 123.78;
    float f2 = 123.78;
    assert_equals_double(f1, f2, function_node);
}

void test_fake_char(const void *function_node)
{
    assert_equals_char('a', 'a', function_node);
    assert_equals_char('a', 'b', function_node);
}

void test_fake_charp(const void *function_node)
{
    assert_equals_charp("fake", "fake", function_node);
    assert_equals_charp("fake1", "fake2", function_node);
    assert_equals_charp("fake_fake", "fake", function_node);
    assert_equals_charp("fake", "fake_fake", function_node);

    char *s1 = "fake1";
    char *s2 = "fake2";
    char *s3 = "fake3";
    assert_equals_charp(s1, s2, function_node);
    assert_equals_charp(s1, s3, function_node);

    char s4[] = "fake4";
    char s5[] = "fake5";
    char s6[] = "fake6";
    char s11[] = "fake1";
    assert_equals_charp(s4, s5, function_node);
    assert_equals_charp(s4, s6, function_node);
    assert_equals_charp(s1, s11, function_node);
}

void test_fake_bool(const void *function_node)
{
    assert_true(true, function_node);
    assert_true(false, function_node);
    assert_true(1 == 1, function_node);
    assert_true(1 == 2, function_node);
    assert_true(12.0 == 12, function_node);
    assert_true('a' == 'a', function_node);

    assert_false(false, function_node);
    assert_false(true, function_node);
    assert_false(12 == 23, function_node);
    assert_false(12 == 12, function_node);
    assert_false('a' == 'a', function_node);
    assert_false(12.0 == 12, function_node);
}

void test_fake_null(const void *function_node)
{
    assert_null(NULL, function_node);

    char *s = NULL;
    assert_null(s, function_node);
    s = "not null";
    assert_null(s, function_node);

    int *ip = NULL;
    assert_null(ip, function_node);
    int i = 0;
    ip = &i;
    assert_null(ip, function_node);
}