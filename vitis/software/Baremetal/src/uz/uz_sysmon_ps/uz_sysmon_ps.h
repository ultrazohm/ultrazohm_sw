#ifndef UZ_SYSMON_PS_H
#define UZ_SYSMON_PS_H

#include <stdint.h>

/**
 * @brief Typedef for uz_sysmon_ps object definition
 *
 */
typedef struct uz_sysmon_ps_t uz_sysmon_ps_t;

/**
 * @brief Initializes an instance of the SYSMON_PS driver. Must not be called more than once!
 *
 * @param sysmon_device_id Device id of the SYSMON. Pass the define XPAR_XSYSMONPSU_0_DEVICE_ID from xparameters.h to uz_sysmon_ps_init.
 * @return uz_sysmon_ps_t*
 */
uz_sysmon_ps_t *uz_sysmon_ps_init(uint16_t sysmon_device_id);

/**
 * @brief Reads the on-chip temperature of the PS system.
 *
 * @param self Pointer to driver instance
 * @return float On-chip temperature in degree celsius
 */
float uz_sysmon_ps_read_temperature(uz_sysmon_ps_t *self);

/**
 * @brief Reads the supply voltage of the low power domain (LP)
 * 
 * @param self 
 * @return float Low power domain supply voltage PSINTLP in volt.
 */
float sysmon_ps_read_vcc_psint_lp_volt(uz_sysmon_ps_t *self);

/**
 * @brief Reads the supply voltage of the full power domain (LP)
 *
 * @param self
 * @return float full power domain supply voltage PSINTFP in volt.
 */
float sysmon_ps_read_vcc_psint_fp_volt(uz_sysmon_ps_t *self);

/**
 * @brief Reads the supply voltage of PSAUX.
 *
 * @param self
 * @return float Low power domain supply voltage PSAUX in volt.
 */
float sysmon_ps_read_vcc_psaux_volt(uz_sysmon_ps_t *self);

#endif // UZ_SYSMON_PS_H
