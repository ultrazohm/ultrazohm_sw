#ifdef TEST

#include "test_assert_with_exception.h"
#include "uz_resolverIP.h"
#include "mock_uz_resolverIP_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>


#define TEST_BASE_ADDRESS 0x43C00000
#define TEST_IP_CORE_FRQ 100000000U
#define TEST_IP_CORE_RES 16U
#define TEST_IP_CORE_CLKIN 8000000U



struct uz_resolverIP_config_t testconfig={
    .base_address=TEST_BASE_ADDRESS,
	.ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
	.resolution = TEST_IP_CORE_RES,
    .freq_clockin = TEST_IP_CORE_CLKIN
};
    
void setUp(void)
{
}

void tearDown(void)
{
}

uz_resolverIP_t* successful_init(void)
{
    //mocking init
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   //mocking setConfig
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
 
   
    uz_resolverIP_t* testinstance = uz_resolverIP_init(testconfig);
    return testinstance;
}

void test_uz_resolverIP_init(void)
{
    TEST_ASSERT_PASS_ASSERT(successful_init());
}

void test_uz_resolverIP_fail_assert_if_base_address_is_zero(void)
{
    struct uz_resolverIP_config_t config={
    	.ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
		.resolution = TEST_IP_CORE_RES,
		.freq_clockin = TEST_IP_CORE_CLKIN
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_init(config));
}

void test_uz_resolverIP_fail_assert_if_ip_clk_freq_is_zero(void)
{
    struct uz_resolverIP_config_t config={
        .base_address=TEST_BASE_ADDRESS,
		.resolution = TEST_IP_CORE_RES,
		.freq_clockin = TEST_IP_CORE_CLKIN
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_init(config));
}

void test_uz_resolverIP_fail_assert_if_ip_resolution_is_zero(void)
{
    struct uz_resolverIP_config_t config={
        .base_address=TEST_BASE_ADDRESS,
    	.ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
		.freq_clockin = TEST_IP_CORE_CLKIN
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_init(config) );
}

void test_uz_resolverIP_fail_assert_if_freq_clockin_is_zero(void)
{
    struct uz_resolverIP_config_t config={
        .base_address=TEST_BASE_ADDRESS,
    	.ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
		.resolution = TEST_IP_CORE_RES,
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_init(config) );
}

void test_uz_resolverIP_fail_assert_if_resolution_is_implausible(void)
{
    struct uz_resolverIP_config_t config={
        .base_address=TEST_BASE_ADDRESS,
    	.ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
		.resolution = 11,
        .freq_clockin = TEST_IP_CORE_CLKIN
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_init(config) );
}

void test_uz_resolverIP_fail_assert_if_freq_clockin_is_implausible(void)
{
    struct uz_resolverIP_config_t config={
        .base_address=TEST_BASE_ADDRESS,
    	.ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
		.resolution = TEST_IP_CORE_RES,
        .freq_clockin = 100U
    };
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_init(config) );
}


void test_uz_resolverIP_fail_assert_if_setConfigMode_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setConfigMode(NULL));
}

void test_uz_resolverIP_fail_assert_if_setZeroPosition_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setZeroPosition(NULL,0.F));
}

void test_uz_resolverIP_fail_assert_if_setPolePairs_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setPolePairs(NULL,0.F));
}

void test_uz_resolverIP_fail_assert_if_getPolePairs_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_getPolePairs(NULL));
}

void test_uz_resolverIP_fail_assert_if_setDataModeVelocity_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setDataModeVelocity(NULL));
}

void test_uz_resolverIP_fail_assert_if_setDataModePosition_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setDataModePosition(NULL));
}

void test_uz_resolverIP_fail_assert_if_setDataModePositionVelocity_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setDataModePositionVelocity(NULL));
}

void test_uz_resolverIP_fail_assert_if_readElectricalPosition_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_readElectricalPosition(NULL));
}

void test_uz_resolverIP_fail_assert_if_readMechanicalPosition_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_readMechanicalPosition(NULL));
}

void test_uz_resolverIP_fail_assert_if_readElectricalVelocity_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_readElectricalVelocity(NULL));
}

void test_uz_resolverIP_fail_assert_if_readMechanicalVelocity_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_readMechanicalVelocity(NULL));
}

void test_uz_resolverIP_fail_assert_if_readElectricalPositionAndVelocity_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_readElectricalPositionAndVelocity(NULL,NULL,NULL));
}

void test_uz_resolverIP_fail_assert_if_readMechanicalPositionAndVelocity_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_readMechanicalPositionAndVelocity(NULL,NULL,NULL));
}

void test_uz_resolverIP_fail_assert_if_readRegister_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_readRegister(NULL,0x80));
}

void test_uz_resolverIP_fail_assert_if_writeRegister_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_writeRegister(NULL,0x80,0U));
}


void test_uz_resolverIP_fail_assert_if_readRegister_is_called_with_invalid_addr(void)
{
    uz_resolverIP_t* myIP = successful_init();

    int32_t address = 0x7F;
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_readRegister(myIP,address));
}

void test_uz_resolverIP_fail_assert_if_writeRegister_is_called_with_invalid_addr(void)
{
    uz_resolverIP_t* myIP = successful_init();

    int32_t address = 0x7F;
    int32_t value = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_writeRegister(myIP,address,value));
}

void test_uz_resolverIP_fail_assert_if_writeRegister_is_called_with_invalid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    int32_t address = 0x8F;
    int32_t value = 300;
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_writeRegister(myIP,address,value));
}

void test_uz_resolverIP_fail_assert_if_setLOSThresh_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setLOSThresh(NULL,4.0f));
}

void test_uz_resolverIP_fail_assert_if_getLOSThresh_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_getLOSThresh(NULL));
}

void test_uz_resolverIP_fail_assert_if_setDOSOverrangeThresh_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setDOSOverrangeThresh(NULL,4.0f));
}

void test_uz_resolverIP_fail_assert_if_getDOSOverrangeThresh_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_getDOSOverrangeThresh(NULL));
}

void test_uz_resolverIP_fail_assert_if_setDOSMismatchThresh_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setDOSMismatchThresh(NULL,4.0f));
}

void test_uz_resolverIP_fail_assert_if_getDOSMismatchThresh_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_getDOSMismatchThresh(NULL));
}

void test_uz_resolverIP_fail_assert_if_setDOSResetMin_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setDOSResetMin(NULL,4.0f));
}

void test_uz_resolverIP_fail_assert_if_getDOSResetMin_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_getDOSResetMin(NULL));
}

void test_uz_resolverIP_fail_assert_if_setDOSResetMax_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setDOSResetMax(NULL,4.0f));
}

void test_uz_resolverIP_fail_assert_if_getDOSResetMax_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_getDOSResetMax(NULL));
}

void test_uz_resolverIP_fail_assert_if_setLOTHighThresh_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setLOTHighThresh(NULL,4.0f));
}

void test_uz_resolverIP_fail_assert_if_getLOTHighThresh_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_getLOTHighThresh(NULL));
}

void test_uz_resolverIP_fail_assert_if_setLOTLowThresh_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setLOTLowThresh(NULL,4.0f));
}

void test_uz_resolverIP_fail_assert_if_getLOTLowThresh_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_getLOTLowThresh(NULL));
}

void test_uz_resolverIP_fail_assert_if_setExcitationFrequency_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setExcitationFrequency(NULL,10000.0f));
}

void test_uz_resolverIP_fail_assert_if_getExcitationFrequency_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_getExcitationFrequency(NULL));
}

void test_uz_resolverIP_fail_assert_if_setCTRLReg_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setCTRLReg(NULL,0x00));
}

void test_uz_resolverIP_fail_assert_if_getCTRLReg_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_getCTRLReg(NULL));
}

void test_uz_resolverIP_fail_assert_if_resetSoftware_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_resetSoftware(NULL));
}

void test_uz_resolverIP_fail_assert_if_getFLTRegister_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_getFLTRegister(NULL));
}

void test_uz_resolverIP_fail_assert_if_setLOSThresh_is_called_with_invalid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 5.f;
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setLOSThresh(myIP,value));
}

void test_uz_resolverIP_fail_assert_if_setDOSOverrangeThresh_is_called_with_invalid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 5.f;
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setDOSOverrangeThresh(myIP,value));
}

void test_uz_resolverIP_fail_assert_if_setDOSMismatchThresh_is_called_with_invalid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 5.f;
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setDOSMismatchThresh(myIP,value));
}

void test_uz_resolverIP_fail_assert_if_setDOSResetMin_is_called_with_invalid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 5.f;
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setDOSResetMin(myIP,value));
}

void test_uz_resolverIP_fail_assert_if_setDOSResetMax_is_called_with_invalid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 5.f;
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setDOSResetMax(myIP,value));
}

void test_uz_resolverIP_fail_assert_if_setLOTHighThresh_is_called_with_invalid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 10.f;
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setLOTHighThresh(myIP,value));
}

void test_uz_resolverIP_fail_assert_if_setLOTLowThresh_is_called_with_invalid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 10.f;
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setLOTLowThresh(myIP,value));
}

void test_uz_resolverIP_fail_assert_if_setExcitationFrequency_is_called_with_invalid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 1000.f;
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setExcitationFrequency(myIP,value));
}

void test_uz_resolverIP_fail_assert_if_setCTRLReg_is_called_with_invalid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    int32_t value = 0x1FF;
    TEST_ASSERT_FAIL_ASSERT(uz_resolverIP_setCTRLReg(myIP,value));
}


void test_uz_resolverIP_pass_assert_if_setLOSThresh_is_called_with_valid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();
    float value = 4.f;
    int32_t val = (int) (value/0.038f) ;
    //mocking writeRegister
        //mocking setConfig
        uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
        uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
  
    uz_resolverIP_hw_write_RESADR_Expect(TEST_BASE_ADDRESS,LOS_THRESHOLD_REG_ADR);
    uz_resolverIP_hw_write_RESDAT_Expect(TEST_BASE_ADDRESS,val);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit | RESCON_Data_uz_axi_GO_bit);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   

    
    TEST_ASSERT_PASS_ASSERT(uz_resolverIP_setLOSThresh(myIP,value));
}

void test_uz_resolverIP_pass_assert_if_setDOSOverrangeThresh_is_called_with_valid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

       float value = 4.f;
    int32_t val = (int) (value/0.038f) ;
    //mocking writeRegister
        //mocking setConfig
        uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
        uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
  
    uz_resolverIP_hw_write_RESADR_Expect(TEST_BASE_ADDRESS,DOS_OVERRANGE_REG_ADR);
    uz_resolverIP_hw_write_RESDAT_Expect(TEST_BASE_ADDRESS,val);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit | RESCON_Data_uz_axi_GO_bit);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   

    TEST_ASSERT_PASS_ASSERT(uz_resolverIP_setDOSOverrangeThresh(myIP,value));
}

void test_uz_resolverIP_pass_assert_if_setDOSMismatchThresh_is_called_with_valid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 4.f;
    int32_t val = (int) (value/0.038f) ;
    //mocking writeRegister
        //mocking setConfig
        uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
        uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
  
    uz_resolverIP_hw_write_RESADR_Expect(TEST_BASE_ADDRESS,DOS_MISMATCH_REG_ADR);
    uz_resolverIP_hw_write_RESDAT_Expect(TEST_BASE_ADDRESS,val);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit | RESCON_Data_uz_axi_GO_bit);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   
    TEST_ASSERT_PASS_ASSERT(uz_resolverIP_setDOSMismatchThresh(myIP,value));
}

void test_uz_resolverIP_pass_assert_if_setDOSResetMin_is_called_with_valid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 4.f;
    int32_t val = (int) (value/0.038f) ;
    //mocking writeRegister
        //mocking setConfig
        uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
        uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
  
    uz_resolverIP_hw_write_RESADR_Expect(TEST_BASE_ADDRESS,DOS_RESET_MIN_REG_ADR);
    uz_resolverIP_hw_write_RESDAT_Expect(TEST_BASE_ADDRESS,val);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit | RESCON_Data_uz_axi_GO_bit);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   
    TEST_ASSERT_PASS_ASSERT(uz_resolverIP_setDOSResetMin(myIP,value));
}

void test_uz_resolverIP_pass_assert_if_setDOSResetMax_is_called_with_valid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 4.f;
    int32_t val = (int) (value/0.038f) ;
    //mocking writeRegister
        //mocking setConfig
        uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
        uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
  
    uz_resolverIP_hw_write_RESADR_Expect(TEST_BASE_ADDRESS,DOS_RESET_MAX_REG_ADR);
    uz_resolverIP_hw_write_RESDAT_Expect(TEST_BASE_ADDRESS,val);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit | RESCON_Data_uz_axi_GO_bit);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   
    TEST_ASSERT_PASS_ASSERT(uz_resolverIP_setDOSResetMax(myIP,value));
}

void test_uz_resolverIP_pass_assert_if_setLOTHighThresh_is_called_with_valid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 5.f;
    int32_t val = (int) (value/0.09f) ;
    //mocking writeRegister
        //mocking setConfig
        uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
        uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
  
    uz_resolverIP_hw_write_RESADR_Expect(TEST_BASE_ADDRESS,LOT_HIGH_THRESH_REG_ADR);
    uz_resolverIP_hw_write_RESDAT_Expect(TEST_BASE_ADDRESS,val);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit | RESCON_Data_uz_axi_GO_bit);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   
    TEST_ASSERT_PASS_ASSERT(uz_resolverIP_setLOTHighThresh(myIP,value));
}

void test_uz_resolverIP_pass_assert_if_setLOTLowThresh_is_called_with_valid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 5.f;
    int32_t val = (int) (value/0.09f) ;
    //mocking writeRegister
        //mocking setConfig
        uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
        uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
  
    uz_resolverIP_hw_write_RESADR_Expect(TEST_BASE_ADDRESS,LOT_LOW_THRESH_REG_ADR);
    uz_resolverIP_hw_write_RESDAT_Expect(TEST_BASE_ADDRESS,val);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit | RESCON_Data_uz_axi_GO_bit);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
  
    TEST_ASSERT_PASS_ASSERT(uz_resolverIP_setLOTLowThresh(myIP,value));
}

void test_uz_resolverIP_pass_assert_if_setExcitationFrequency_is_called_with_valid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    float value = 10000.f;
    int32_t val = (int32_t) (value*(1<<15)/TEST_IP_CORE_CLKIN);
	
    //mocking writeRegister
        //mocking setConfig
        uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
        uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
  
    uz_resolverIP_hw_write_RESADR_Expect(TEST_BASE_ADDRESS,EXIT_FREQ_REG_ADR);
    uz_resolverIP_hw_write_RESDAT_Expect(TEST_BASE_ADDRESS,val);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit | RESCON_Data_uz_axi_GO_bit);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
  
    TEST_ASSERT_PASS_ASSERT(uz_resolverIP_setExcitationFrequency(myIP,value));
}

void test_uz_resolverIP_pass_assert_if_setCTRLReg_is_called_with_valid_value(void)
{
    uz_resolverIP_t* myIP = successful_init();

    int32_t value = 0xFF;

    //mocking writeRegister
        //mocking setConfig
        uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
        uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
   
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
  
    uz_resolverIP_hw_write_RESADR_Expect(TEST_BASE_ADDRESS,CONTROL_REG_ADR);
    uz_resolverIP_hw_write_RESDAT_Expect(TEST_BASE_ADDRESS,value);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit | RESCON_Data_uz_axi_GO_bit);
  
    uz_resolverIP_hw_write_RESCON_Expect(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit | RESCON_Data_uz_axi_RW_bit);
    uz_resolverIP_hw_read_RESCON_ExpectAndReturn(TEST_BASE_ADDRESS,RESCON_Data_uz_axi_EN_bit | RESCON_Data_uz_axi_nRESET_bit);
  
    TEST_ASSERT_PASS_ASSERT(uz_resolverIP_setCTRLReg(myIP,value));
}

#endif // TEST
