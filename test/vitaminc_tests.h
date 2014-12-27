#ifndef _VITAMINC_TESTS_H_
#define _VITAMINC_TESTS_H_

#include <CUnit/Basic.h>
#include "vitamanc.h"

typedef struct {
    const char* name;
    CU_TestFunc func;
} TestDef;

int init_color_tests(void);
int clean_color_tests(void);
void test_complementary_color(void);
#endif
