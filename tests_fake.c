#include "tests.h"

void test_fake(const void *function_node)
{
    // No assert
}

void test_fake_int(const void *function_node)
{
    assertEqualsInt(2, 2, function_node);
    assertEqualsInt(3, 3, function_node);
}

void test_fake_double(const void *function_node)
{
    assertEqualsDouble(1.1, 1.23, function_node);
    assertEqualsDouble(222.20, 222.20, function_node);
    double d1 = 2.45;
    double d2 = 12.45;
    assertEqualsDouble(d1, d2, function_node);
    float f1 = 123.78;
    float f2 = 123.78;
    assertEqualsDouble(f1, f2, function_node);
}

void test_fake_char(const void *function_node)
{
    assertEqualsChar('a', 'a', function_node);
    assertEqualsChar('a', 'b', function_node);
}

void test_fake_charp(const void *function_node)
{
    assertEqualsCharP("fake", "fake", function_node);
    assertEqualsCharP("fake1", "fake2", function_node);
    assertEqualsCharP("fake_fake", "fake", function_node);
    assertEqualsCharP("fake", "fake_fake", function_node);

    char *s1 = "fake1";
    char *s2 = "fake2";
    char *s3 = "fake3";
    assertEqualsCharP(s1, s2, function_node);
    assertEqualsCharP(s1, s3, function_node);

    char s4[] = "fake4";
    char s5[] = "fake5";
    char s6[] = "fake6";
    char s11[] = "fake1";
    assertEqualsCharP(s4, s5, function_node);
    assertEqualsCharP(s4, s6, function_node);
    assertEqualsCharP(s1, s11, function_node);
}

void test_fake_bool(const void *function_node)
{
    assertTrue(true, function_node);
    assertTrue(false, function_node);
    assertTrue(1 == 1, function_node);
    assertTrue(1 == 2, function_node);

    assertFalse(false, function_node);
    assertFalse(true, function_node);
    assertFalse(12 == 23, function_node);
    assertFalse(12 == 12, function_node);
}