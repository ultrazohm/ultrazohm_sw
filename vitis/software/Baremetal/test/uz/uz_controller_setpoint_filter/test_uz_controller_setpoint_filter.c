#ifdef TEST

#include "unity.h"

#include "uz_signals.h"
TEST_FILE("uz_signals_iir_filter.c")
#include "uz_controller_setpoint_filter.h"
#include "test_assert_with_exception.h"

#define ISR_SAMPLE_FREQ_HZ 10000.0f

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_signals_IIR_Filter_dq_setpoint_assert(void){
    uz_3ph_dq_t setpoint = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_dq_setpoint(NULL, setpoint));
}

void test_uz_signals_IIR_Filter_dq_setpoint(void){
    const struct uz_IIR_Filter_config config_filter = {
        .cutoff_frequency_Hz = 1.0f,
        .sample_frequency_Hz = ISR_SAMPLE_FREQ_HZ,
        .selection = LowPass_first_order};
    struct uz_dq_setpoint_filter_config config = {
        .config_filter_d = config_filter,
        .config_filter_q = config_filter};
    uz_dq_setpoint_filter* obj = uz_uz_dq_setpoint_filter_init(config);
    // fist value of IIR should be 0, as it uses it directly as output
    uz_3ph_dq_t setpoint = {0};
    uz_3ph_dq_t filtered = uz_signals_IIR_Filter_dq_setpoint(obj, setpoint);
    // setting value != 0 and testing two cycles
    setpoint.d = 1.0f;
    setpoint.q = 2.0f;
    filtered = uz_signals_IIR_Filter_dq_setpoint(obj, setpoint);
    TEST_ASSERT_FLOAT_WITHIN(0.000628f, filtered.d, 1e-3f);
    TEST_ASSERT_FLOAT_WITHIN(0.001256f, filtered.q, 1e-3f);
    filtered = uz_signals_IIR_Filter_dq_setpoint(obj, setpoint);
    TEST_ASSERT_FLOAT_WITHIN(0.001255f, filtered.d, 1e-3f);
    TEST_ASSERT_FLOAT_WITHIN(0.002511f, filtered.q, 1e-3f);
}

#endif // TEST
