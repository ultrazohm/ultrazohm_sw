#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_inverter_3ph.h"
#include "mock_uz_inverter_3ph_hw.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_inverter_3ph_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_core_frequency_Hz = IP_FRQ,
    .switch_pspl_abc = true,
    .switch_pspl_gate = true, 
    .udc = 560.0f};

void setUp(void)
{
}

void tearDown(void)
{
}

uz_inverter_3ph_t *successful_init(struct uz_inverter_3ph_config_t configuration);
uz_inverter_3ph_t *successful_init(struct uz_inverter_3ph_config_t configuration)
{
    uz_inverter_3ph_hw_write_switch_pspl_abc_Expect(BASE_ADDRESS, configuration.switch_pspl_abc);
    uz_inverter_3ph_hw_write_switch_pspl_gate_Expect(BASE_ADDRESS, configuration.switch_pspl_gate);
    uz_inverter_3ph_hw_write_udc_Expect(BASE_ADDRESS, configuration.udc);
    uz_inverter_3ph_t *instance = uz_inverter_3ph_init(configuration);
    return (instance);
}

void test_uz_inverter_3ph_successful_init(void)
{
    uz_inverter_3ph_t *test_instance = successful_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}


void test_uz_inverter_3ph_normal_usage(void)
{
    uz_inverter_3ph_t *test_instance = successful_init(config);

    uz_inverter_3ph_hw_trigger_u_abc_ps_strobe_Expect(BASE_ADDRESS);
    uz_inverter_3ph_trigger_u_abc_ps_strobe(test_instance);
    uz_inverter_3ph_hw_trigger_u_abc_ps_strobe_Expect(BASE_ADDRESS);
    uz_inverter_3ph_trigger_u_abc_ps_strobe(test_instance);
    
    uz_3ph_abc_t u_abc_expect = {
        .a = 1.1f,
        .b = 2.1f,
        .c = 3.1f};

    uz_inverter_3ph_hw_read_u_ab_ps_ExpectAndReturn(BASE_ADDRESS, u_abc_expect.a);
    uz_inverter_3ph_hw_read_u_bc_ps_ExpectAndReturn(BASE_ADDRESS, u_abc_expect.b);
    uz_inverter_3ph_hw_read_u_ca_ps_ExpectAndReturn(BASE_ADDRESS, u_abc_expect.c);

    uz_3ph_abc_t u_out = uz_inverter_3ph_get_u_abc_ps(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(u_abc_expect.a, u_out.a);
    TEST_ASSERT_EQUAL_FLOAT(u_abc_expect.b, u_out.b);
    TEST_ASSERT_EQUAL_FLOAT(u_abc_expect.c, u_out.c);

    uz_3ph_abc_t i_abc_in = {
        .a = 4.3f,
        .b = 5.3f,
        .c = 6.3f};
    
    struct uz_inverter_3ph_gate_ps_t gate_sig = {
        .gate1 = true,
        .gate2 = false,
        .gate3 = false,
        .gate4 = true,
        .gate5 = false,
        .gate6 = true};

    uz_inverter_3ph_hw_write_i_a_ps_Expect(BASE_ADDRESS, i_abc_in.a);
    uz_inverter_3ph_hw_write_i_b_ps_Expect(BASE_ADDRESS, i_abc_in.b);
    uz_inverter_3ph_hw_write_i_c_ps_Expect(BASE_ADDRESS, i_abc_in.c);
    uz_inverter_3ph_set_i_abc_ps(test_instance, i_abc_in);

    uz_inverter_3ph_hw_trigger_i_abc_ps_strobe_Expect(BASE_ADDRESS);
    uz_inverter_3ph_trigger_i_abc_ps_strobe(test_instance);
    uz_inverter_3ph_hw_trigger_i_abc_ps_strobe_Expect(BASE_ADDRESS);
    uz_inverter_3ph_trigger_i_abc_ps_strobe(test_instance);

    uz_inverter_3ph_hw_write_gate1_Expect(BASE_ADDRESS, gate_sig.gate1);
    uz_inverter_3ph_hw_write_gate2_Expect(BASE_ADDRESS, gate_sig.gate2);
    uz_inverter_3ph_hw_write_gate3_Expect(BASE_ADDRESS, gate_sig.gate3);
    uz_inverter_3ph_hw_write_gate4_Expect(BASE_ADDRESS, gate_sig.gate4);
    uz_inverter_3ph_hw_write_gate5_Expect(BASE_ADDRESS, gate_sig.gate5);
    uz_inverter_3ph_hw_write_gate6_Expect(BASE_ADDRESS, gate_sig.gate6);
    uz_inverter_3ph_set_gate_ps(test_instance, gate_sig);

    uz_inverter_3ph_hw_trigger_gate_ps_strobe_Expect(BASE_ADDRESS);
    uz_inverter_3ph_trigger_gate_ps_strobe(test_instance);
    uz_inverter_3ph_hw_trigger_gate_ps_strobe_Expect(BASE_ADDRESS);
    uz_inverter_3ph_trigger_gate_ps_strobe(test_instance);
}

#endif // TEST
