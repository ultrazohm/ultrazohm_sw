#ifdef TEST

#include "unity.h"
#include "uz_HAL.h"
#include <stdint.h>
#include "uz_sysmon_ps.h"
#include "mock_xsysmonpsu.h"

uint16_t sysmon_device_id = 0U;
XSysMonPsu SysMonInst; // System Monitor driver instance for tests
XSysMonPsu_Config XSysMon_config = {
    .BaseAddress = 0xFFFFFFFFU,
    .DeviceId = 0U,
    .InputClockMHz = 50U};

XSysMonPsu_Config *ConfigPtr = &XSysMon_config;
static void correct_init_expect_and_returns(void);

void setUp(void)
{
    // Reset global config struct before each test
    XSysMon_config.BaseAddress = 0xFFFFFFFFU;
    XSysMon_config.DeviceId = 0U;
    XSysMon_config.InputClockMHz = 50U;
    ConfigPtr = &XSysMon_config;
}

void tearDown(void)
{
}

void test_uz_sysmon_ps_init(void)
{
    correct_init_expect_and_returns();
    uz_sysmon_ps_init(sysmon_device_id);
}

void test_uz_sysmon_ps_read_temperature(void)
{
    correct_init_expect_and_returns();
    uz_sysmon_ps_t *test_instance = uz_sysmon_ps_init(sysmon_device_id);

    XSysMonPsu_GetAdcData_ExpectAndReturn(&SysMonInst, XSM_CH_TEMP, XSYSMON_PS, 0x0U);
    uz_sysmon_ps_read_temperature(test_instance);
    // No test with the returned value as all logic is inside Xilinx driver
}

static void correct_init_expect_and_returns(void)
{

    XSysMonPsu_LookupConfig_ExpectAndReturn(sysmon_device_id, &XSysMon_config);
    XSysMonPsu_CfgInitialize_ExpectAndReturn(&SysMonInst, ConfigPtr, 0xFFFFFFFFU, UZ_SUCCESS);
    XSysMonPsu_CfgInitialize_IgnoreArg_ConfigPtr();
    XSysMonPsu_CfgInitialize_ReturnThruPtr_InstancePtr(&SysMonInst);

    XSysMonPsu_SelfTest_ExpectAndReturn(&SysMonInst, UZ_SUCCESS);
    XSysMonPsu_SetSequencerMode_Expect(&SysMonInst, XSM_SEQ_MODE_SAFE, XSYSMON_PS);
    XSysMonPsu_SetAlarmEnables_Expect(&SysMonInst, 0x0U, XSYSMON_PS);
    XSysMonPsu_SetAvg_Expect(&SysMonInst, XSM_AVG_16_SAMPLES, XSYSMON_PS);
    XSysMonPsu_SetSeqAvgEnables_ExpectAndReturn(&SysMonInst, XSYSMONPSU_SEQ_CH0_TEMP_MASK | XSYSMONPSU_SEQ_CH0_SUP1_MASK | XSYSMONPSU_SEQ_CH0_SUP2_MASK | XSYSMONPSU_SEQ_CH0_SUP3_MASK | XSYSMONPSU_SEQ_CH0_CALIBRTN_MASK, XSYSMON_PS, UZ_SUCCESS);

    XSysMonPsu_SetSeqChEnables_ExpectAndReturn(&SysMonInst, XSYSMONPSU_SEQ_CH0_TEMP_MASK | XSYSMONPSU_SEQ_CH0_SUP1_MASK | XSYSMONPSU_SEQ_CH0_SUP2_MASK | XSYSMONPSU_SEQ_CH0_SUP3_MASK | XSYSMONPSU_SEQ_CH0_CALIBRTN_MASK, XSYSMON_PS, UZ_SUCCESS);

    uint64_t interrupt_status = 0x0FU; // some random bitmask that is returned from interrupt status and passed agin to clear it
    XSysMonPsu_IntrGetStatus_ExpectAndReturn(&SysMonInst, interrupt_status);
    XSysMonPsu_IntrClear_Expect(&SysMonInst, interrupt_status);

    XSysMonPsu_SetSequencerMode_Expect(&SysMonInst, XSM_SEQ_MODE_CONTINPASS, XSYSMON_PS);
}

#endif // TEST
