#ifndef TESTS_H
#define TESTS_H

// Import ctestfmk framework
#include "../src/ctestfmk.h"

// Test functions declarations (specific signature defined by the framework)
void test_fake(const void*);
void test_fake_int(const void*);
void test_fake_double(const void*);
void test_fake_char(const void*);
void test_fake_charp(const void*);
void test_fake_bool(const void*);
void test_fake_null(const void*);

#endif