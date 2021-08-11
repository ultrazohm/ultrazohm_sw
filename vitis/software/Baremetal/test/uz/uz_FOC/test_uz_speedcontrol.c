#ifdef TEST

#include "unity.h"
#include "uz_speedcontrol.h"
TEST_FILE("uz_piController.c")
TEST_FILE("uz_signals.c")

struct uz_PI_Controller_config config = {0};
void setUp(void)
{
    config.Kp = 10.0f;
    config.Ki = 10.0f;
    config.samplingTime_sec = 0.001f;
    config.upper_limit = 10.0f;
    config.lower_limit = -10.0f;
}



void test_uz_speedcontrol_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_speedcontrol");
}

#endif // TEST
