#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_FOC.h"
TEST_FILE("uz_PI_controller.c")


uz_PI_Controller_config config_id = {
    .Kp = 6.75f,
    .Ki = 2000.0f,
    .samplingTime_sec = 0.001f,
    .d_y_max = 10.0f,
    .d_y_min = -10.0f 
};

uz_PI_Controller_config config_iq = {
    .Kp = 6.75f,
    .Ki = 2000.0f,
    .samplingTime_sec = 0.001f,
    .d_y_max = 10.0f,
    .d_y_min = -10.0f 
};

uz_PI_Controller_config config_n = {
    .Kp = 0.00864f,
    .Ki = 0.0864f,
    .samplingTime_sec = 0.001f,
    .d_y_max = 10.0f,
    .d_y_min = -10.0f 
};

void test_uz_FOC_init_L_d_negative(void){

}

#endif // TEST