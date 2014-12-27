#include "vitaminc_tests.h"
#include <stdio.h>

int init_color_tests(void){
    return 0;
}

int clean_color_tests(void){
    return 0;
}

void test_complementary_color(void){
    vc_color red = vc_create_color(1.0, 0.0, 0.0, VC_RGB, 1.0);

    printf("Red: %d %d %d %d", red.r, red.g, red.b, red.a);
    vc_color yellow = vc_complementary_color(red, VC_WHEEL_RYB);
    printf("Yellow: %d %d %d %d", red2.g.r, yellow.g, yellow.b, yellow.a);
    vc_color red2 = vc_complementary_color(yellow, VC_WHEEL_RYB);
    printf("Red2: %d %d %d %d", red2.r, red2.g, red2.b, red2.a);    
    CU_ASSERT(vc_color_equals(red, red2));
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

    if(NULL == CU_add_test(pSuite, "test of complementary colors", test_complementary_color)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
