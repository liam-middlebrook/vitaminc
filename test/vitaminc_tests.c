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
    vc_color red_comp = vc_create_color(0.0, 1.0, 0.5, VC_HSL, 1.0);
   
    vc_print(red);

    //vc_print(red_comp);

    red_comp = (vc_color_equals(vc_complementary_color(red, VC_WHEEL_RGB), red_comp));

    vc_print(red_comp);
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