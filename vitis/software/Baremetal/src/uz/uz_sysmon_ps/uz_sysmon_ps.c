#include "uz_sysmon_ps.h"
#include "../../uz/uz_global_configuration.h"
#if UZ_SYSMON_PS_MAX_INSTANCES > 0U

#ifndef TEST
#if UZ_SYSMON_PS_MAX_INSTANCES>1
    #error Maximum number of ZU_SYSMON_PS instances is 1 as there is only one SYSMON in the PS system!
#endif
#endif

#include <stdbool.h>

#include "xsysmonpsu.h"
#include "xstatus.h"
// Hard-codes that the system monitor is the PS SYSMON. XSYSMON_PS is defined in xsysmonpsu.h
#define XSYSMON_TYPE XSYSMON_PS

#include "../../uz/uz_HAL.h"

struct uz_sysmon_ps_t
{
    bool is_ready;
    XSysMonPsu_Config *ConfigPtr;
    XSysMonPsu SysMonInst; /* System Monitor driver instance */
    float chip_temperature_degree_celsius;
    float vcc_psaux_volt;
    float vcc_psint_lp_volt;
    float vcc_psint_fp_volt;
};

static uint32_t instance_counter = 0U;
static uz_sysmon_ps_t instances[UZ_SYSMON_PS_MAX_INSTANCES] = {0};

static uz_sysmon_ps_t *uz_sysmon_ps_allocation(void);

static uz_sysmon_ps_t *uz_sysmon_ps_allocation(void)
{
    uz_assert(instance_counter < UZ_SYSMON_PS_MAX_INSTANCES);
    uz_sysmon_ps_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_sysmon_ps_t *uz_sysmon_ps_init(uint16_t sysmon_device_id)
{
    uz_assert(sysmon_device_id==0U); // Since the PS Sysmon is hard-ip inside the UltraScale, the device ID should not change and always be zero. We pass the sysmon_device_id to the init function nonetheless to catch errors if this assumption is wrong.
    uz_sysmon_ps_t *self = uz_sysmon_ps_allocation();

    /* Initialize the SysMon driver. */
    self->ConfigPtr = XSysMonPsu_LookupConfig(sysmon_device_id);
    int32_t Status = XSysMonPsu_CfgInitialize(&self->SysMonInst, self->ConfigPtr, (uint32_t)self->ConfigPtr->BaseAddress); // This typecast is due to Xilinx defining BaseAddress inside the Config struct with type UINTPTR, which has to be passed to XSysMonPsu_CfgInitialize. However, XSysMonPsu_CfgInitialize defines the argument as uint32_t...
    uz_assert(Status == UZ_SUCCESS);
    Status = XSysMonPsu_SelfTest(&self->SysMonInst);
    uz_assert(Status == UZ_SUCCESS);

    XSysMonPsu_SetSequencerMode(&self->SysMonInst, XSM_SEQ_MODE_SAFE, XSYSMON_TYPE);
    XSysMonPsu_SetAlarmEnables(&self->SysMonInst, 0x0U, XSYSMON_TYPE);
    XSysMonPsu_SetAvg(&self->SysMonInst, XSM_AVG_16_SAMPLES, XSYSMON_TYPE);
    Status = XSysMonPsu_SetSeqAvgEnables(&self->SysMonInst, XSYSMONPSU_SEQ_CH0_TEMP_MASK | XSYSMONPSU_SEQ_CH0_SUP1_MASK | XSYSMONPSU_SEQ_CH0_SUP2_MASK | XSYSMONPSU_SEQ_CH0_SUP3_MASK | XSYSMONPSU_SEQ_CH0_CALIBRTN_MASK, XSYSMON_TYPE);
    uz_assert(Status == UZ_SUCCESS);

    Status = XSysMonPsu_SetSeqChEnables(&self->SysMonInst, XSYSMONPSU_SEQ_CH0_TEMP_MASK | XSYSMONPSU_SEQ_CH0_SUP1_MASK | XSYSMONPSU_SEQ_CH0_SUP2_MASK | XSYSMONPSU_SEQ_CH0_SUP3_MASK | XSYSMONPSU_SEQ_CH0_CALIBRTN_MASK, XSYSMON_TYPE);
    uz_assert(Status == UZ_SUCCESS);

    /* Clear any bits set in the Interrupt Status Register. */
    uint64_t IntrStatus = XSysMonPsu_IntrGetStatus(&self->SysMonInst);
    XSysMonPsu_IntrClear(&self->SysMonInst, IntrStatus);

    /* Enable the Channel Sequencer in continuous sequencer cycling mode. */
    XSysMonPsu_SetSequencerMode(&self->SysMonInst, XSM_SEQ_MODE_CONTINPASS, XSYSMON_TYPE);


    return (self);
}

float uz_sysmon_ps_read_temperature(uz_sysmon_ps_t *self)
{
    uint32_t TempRawData = XSysMonPsu_GetAdcData(&self->SysMonInst, XSM_CH_TEMP, XSYSMON_TYPE);
    self->chip_temperature_degree_celsius = XSysMonPsu_RawToTemperature_OnChip(TempRawData);
    return self->chip_temperature_degree_celsius;
}

float sysmon_ps_read_vcc_psint_lp_volt(uz_sysmon_ps_t *self)
{
    uint32_t Supply1RawData = XSysMonPsu_GetAdcData(&self->SysMonInst, XSM_CH_SUPPLY1, XSYSMON_TYPE);
    // XSysMonPsu_RawToVoltage is a define 
    self->vcc_psint_lp_volt = XSysMonPsu_RawToVoltage(Supply1RawData);
    return self->vcc_psint_lp_volt;
}

float sysmon_ps_read_vcc_psint_fp_volt(uz_sysmon_ps_t *self)
{
    uint32_t Supply1RawData = XSysMonPsu_GetAdcData(&self->SysMonInst, XSM_CH_SUPPLY2, XSYSMON_TYPE);
    self->vcc_psint_fp_volt = XSysMonPsu_RawToVoltage(Supply1RawData);
    return self->vcc_psint_fp_volt;
}

float sysmon_ps_read_vcc_psaux_volt(uz_sysmon_ps_t *self)
{
    uint32_t Supply3RawData = XSysMonPsu_GetAdcData(&self->SysMonInst, XSM_CH_SUPPLY3, XSYSMON_TYPE);
    self->vcc_psaux_volt = XSysMonPsu_RawToVoltage(Supply3RawData);
    return self->vcc_psaux_volt;
}

#endif
