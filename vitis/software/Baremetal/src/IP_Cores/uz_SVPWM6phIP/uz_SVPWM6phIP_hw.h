#ifndef UZ_SVPWM6PHIP_HW_H
#define UZ_SVPWM6PHIP_HW_H
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief selects whether the PWM counter is taken from within the instance or 
 *        from an external source
 * 
 * @param base_address          base address of the instance
 * @param use_external_counter  flag for choosing the PWM counter source
 *                              false=internal counter source, true=external counter source
 */
void uz_SVPWM6phIP_hw_SetExternalCounterSource(uint32_t base_address, bool use_external_counter);

/**
 * @brief sets the input reference (dutyCycle) of the module
 *        when PWM_mode is set to 0 (references set via AXI).
 * 
 * @param base_address  //base address of the instance
 * @param T1 on time for SV 1
 * @param T2 on time for SV 2
 * @param T3 on time for SV 3
 * @param T4 on time for SV 4
 * @param T5 on time for SV 5
 * @param SV1 Space vector SV 1
 * @param SV2 Space vector SV 2
 * @param SV3 Space vector SV 3
 * @param SV4 Space vector SV 4
 * @param SV5 Space vector SV 5
 */
void uz_SVPWM6phIP_hw_Set_T_and_SV(uint32_t base_address, float T1, float T2, float T3, float T4, float T5, uint32_t SV1, uint32_t SV2, uint32_t SV3, uint32_t SV4, uint32_t SV5);

/**
 * @brief turns the whole PWM_SS_2L module on or off
 * 
 * @param base_address  //base address of the instance
 * @param PWM_en        //false=disable module, true=enable module
 */
void uz_SVPWM6phIP_hw_SetStatus(uint32_t base_address, bool PWM_en);

/**
 * @brief sets the input source for the PWM_SS_2L module.
 *        There are three modes to chose.
 *        0 = normalized input of reference signal via AXI,
 *            e.g. a reference voltage value between 0 and 1
 *        1 = normalized input of reference signal via FPGA
 *            e.g. a reference voltage value between 0 and 1
 *        2 = direct control of switching states via FPGA
 * @param base_address  //base address of the instance
 * @param PWM_mode      //number of the above mentioned mode, 0,1 or 2
 */
void uz_SVPWM6phIP_hw_SetMode(uint32_t base_address, uint32_t PWM_mode);

/**
 * @brief sets the carrier frequency (PWM frequency) of the PWM module.
 * 
 * @param base_address          //base address of the instance
 * @param ip_clk_frequency_Hz   //frequency of ip core clock, e.g. 100000000 for 100 MHz
 * @param PWM_freq_Hz           //desired PWM frequency, e.g. 10000 for 10 kHz
 */
void uz_SVPWM6phIP_hw_SetCarrierFrequency(uint32_t base_address, uint32_t ip_clk_frequency_Hz, float PWM_freq_Hz);

/**
 * @brief sets a half-bridge in a non conducting high-Z tri state mode.
 * 
 * @param base_address          //base address of the instance
 * @param halfBridgeNumber      //number of the half bridge to set. 1,2 or 3.
 * @param TriState_true_false   //turns tri state mode on or off. true=on, false=off
 */
void uz_SVPWM6phIP_hw_SetTristate(uint32_t base_address, uint32_t halfBridgeNumber, bool TriState_true_false);

/**
 * @brief sets the minimum amount of pulse width that is generated 
 *        by the PWM module.
 * 
 * @param base_address              //base address of the instance
 * @param min_on_time_percent   //minimum on time in percent, e.g. 0.01
 */
void uz_SVPWM6phIP_hw_SetMinimumTon(uint32_t base_address, float min_on_time_percent);

/**
 * @brief sets the trigger source to output new DutyCycles and apply the 
 * 
 * @param base_address      //base address of the instance
 * @param trigger_source    //Trigger source for new DutyCycles and triangle shifts
                            0 = trigger at MIN of triangle\n
                            e.g. the PWM module will apply new values for triangle shift and DutyCycles respectively switch positions
                            1 = trigger at MAX of triangle\n 
                            2 = trigger at EITHER MAX or MIN of triangle
 */
void uz_SVPWM6phIP_hw_SetTriggerSource(uint32_t base_address, uint32_t trigger_source);
     



#endif // UZ_SVPWM6PHIP_HW_H
