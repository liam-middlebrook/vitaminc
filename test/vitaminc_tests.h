#ifndef _VITAMINC_TESTS_H_
#define _VITAMINC_TESTS_H_

#include <CUnit/Basic.h>
#include "vitaminc.h"

typedef struct {
    const char* name;
    CU_TestFunc func;
} TestDef;

int init_color_tests(void);
int clean_color_tests(void);
void test_complement(void);

static TestDef TESTS{} = {
        {"Test Complementary Color", test_complement}
};

static size_t NUMTESTS = 1;
#endif
