#include "vitaminc_tests.h"
#include <stdio.h>

int init_color_tests(void){
    return 0;
}

int clean_color_tests(void){
    return 0;
}

void test_complement(void){
    vc_color red = vc_create_color(1.0, 0.0, 0.0, VC_RGB, 1.0);
    vc_color red_comp = vc_create_color(180.0, 1.0, 0.5, VC_HSL, 1.0);
    
    CU_ASSERT(vc_color_equals(vc_complementary_color(red, VC_WHEEL_RGB), red_comp));
}

void test_rgb_hsl(void){

    // Red (1, 0, 0)rgb - hsl(180, 1, 0.5)
    vc_color red = vc_create_color(1.0, 0.0, 0.0, VC_RGB, 1.0);

    CU_ASSERT(1);
}

int main(){
    CU_pSuite pSuite = NULL;

    if(CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    pSuite = CU_add_suite("Suite_1", init_color_tests, clean_color_tests);
    if(NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    for(size_t i = 0; i < NUMTESTS; ++i) {
            if(NULL == CU_add_test(pSuite, TESTS[i].name, TESTS[i].func)) {
                CU_cleanup_registry();
                return CU_get_error();
            }
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    int errCode = CU_get_number_of_tests_failed();
    CU_cleanup_registry();
    return errCode;
}
