#ifdef TEST

#include "unity.h"
#include "uz_inverter_3ph_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_inverter_3ph_hwAddresses.h"
#define BASE_ADDRESS 0x00000000FU // random hex value that represents a fictional base address


void setUp(void)
{
}

void tearDown(void)
{
}


//general Inputs
void test_uz_inverter_3ph_hw_write_switch_pspl_abc(void){
    bool test_val=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+switch_pspl_abc_Data_uz_inverter_3ph,test_val);
    uz_inverter_3ph_hw_write_switch_pspl_abc(BASE_ADDRESS,test_val);
}

void test_uz_inverter_3ph_hw_write_switch_pspl_gate(void){
    bool test_val=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+switch_pspl_gate_Data_uz_inverter_3ph,test_val);
    uz_inverter_3ph_hw_write_switch_pspl_gate(BASE_ADDRESS,test_val);
}

void test_uz_inverter_3ph_hw_write_udc(void){
    float test_val=789.4f;
    float expect_val=test_val/2;
    uz_axi_write_float_Expect(BASE_ADDRESS+u_dc_Data_uz_inverter_3ph,expect_val);
    uz_inverter_3ph_hw_write_udc(BASE_ADDRESS,test_val);
}


// Model Outputs
void test_uz_inverter_3ph_hw_read_u_ab_ps(void)
{
    float expect_val=4.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+u_ab_ps_Data_uz_inverter_3ph,expect_val);
    float val_read=uz_inverter_3ph_hw_read_u_ab_ps(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expect_val,val_read);
}

void test_uz_inverter_3ph_hw_read_u_bc_ps(void)
{
    float expect_val=5.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+u_bc_ps_Data_uz_inverter_3ph,expect_val);
    float val_read=uz_inverter_3ph_hw_read_u_bc_ps(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expect_val,val_read);
}

void test_uz_inverter_3ph_hw_read_u_ca_ps(void)
{
    float expect_val=6.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+u_ca_ps_Data_uz_inverter_3ph,expect_val);
    float val_read=uz_inverter_3ph_hw_read_u_ca_ps(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expect_val,val_read);
}

void test_uz_inverter_3ph_hw_trigger_u_abc_ps_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+u_abc_ps_Strobe_uz_inverter_3ph,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+u_abc_ps_Strobe_uz_inverter_3ph,false);
    uz_inverter_3ph_hw_trigger_u_abc_ps_strobe(BASE_ADDRESS);
}

// Model Inputs Iabc
void test_uz_inverter_3ph_hw_write_i_a_ps(void){
    float test_val=12.4f;
    uz_axi_write_float_Expect(BASE_ADDRESS+i_a_ps_Data_uz_inverter_3ph,test_val);
    uz_inverter_3ph_hw_write_i_a_ps(BASE_ADDRESS,test_val);
}

void test_uz_inverter_3ph_hw_write_i_b_ps(void){
    float test_val=23.4f;
    uz_axi_write_float_Expect(BASE_ADDRESS+i_b_ps_Data_uz_inverter_3ph,test_val);
    uz_inverter_3ph_hw_write_i_b_ps(BASE_ADDRESS,test_val);
}

void test_uz_inverter_3ph_hw_write_i_c_ps(void){
    float test_val=34.4f;
    uz_axi_write_float_Expect(BASE_ADDRESS+i_c_ps_Data_uz_inverter_3ph,test_val);
    uz_inverter_3ph_hw_write_i_c_ps(BASE_ADDRESS,test_val);
}

void test_uz_inverter_3ph_hw_trigger_i_abc_ps_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+i_abc_ps_Strobe_uz_inverter_3ph,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+i_abc_ps_Strobe_uz_inverter_3ph,false);
    uz_inverter_3ph_hw_trigger_i_abc_ps_strobe(BASE_ADDRESS);
}

// Model Inputs Gate Signals
void test_uz_inverter_3ph_hw_write_gate1(void){
    bool test_val=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+gate1_ps_Data_uz_inverter_3ph,test_val);
    uz_inverter_3ph_hw_write_gate1(BASE_ADDRESS,test_val);
}

void test_uz_inverter_3ph_hw_write_gate2(void){
    bool test_val=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+gate2_ps_Data_uz_inverter_3ph,test_val);
    uz_inverter_3ph_hw_write_gate2(BASE_ADDRESS,test_val);
}

void test_uz_inverter_3ph_hw_write_gate3(void){
    bool test_val=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+gate3_ps_Data_uz_inverter_3ph,test_val);
    uz_inverter_3ph_hw_write_gate3(BASE_ADDRESS,test_val);
}

void test_uz_inverter_3ph_hw_write_gate4(void){
    bool test_val=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+gate4_ps_Data_uz_inverter_3ph,test_val);
    uz_inverter_3ph_hw_write_gate4(BASE_ADDRESS,test_val);
}

void test_uz_inverter_3ph_hw_write_gate5(void){
    bool test_val=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+gate5_ps_Data_uz_inverter_3ph,test_val);
    uz_inverter_3ph_hw_write_gate5(BASE_ADDRESS,test_val);
}

void test_uz_inverter_3ph_hw_write_gate6(void){
    bool test_val=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+gate6_ps_Data_uz_inverter_3ph,test_val);
    uz_inverter_3ph_hw_write_gate6(BASE_ADDRESS,test_val);
}

void test_uz_inverter_3ph_hw_trigger_gate_ps_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+gate_ps_Strobe_uz_inverter_3ph,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+gate_ps_Strobe_uz_inverter_3ph,false);
    uz_inverter_3ph_hw_trigger_gate_ps_strobe(BASE_ADDRESS);
}

#endif // TEST
