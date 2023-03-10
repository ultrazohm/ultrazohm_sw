#ifndef UZ_PWM_SS_2L_HW_H
#define UZ_PWM_SS_2L_HW_H
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
void uz_PWM_SS_2L_hw_SetExternalCounterSource(uint32_t base_address, bool use_external_counter);

/**
 * @brief sets the input reference (dutyCycle) of the module
 *        when PWM_mode is set to 0 (references set via AXI).
 * 
 * @param base_address  //base address of the instance
 * @param dutyCyc_HB1   //duty cycle of half-bridge 1
 * @param dutyCyc_HB2   //duty cycle of half-bridge 2
 * @param dutyCyc_HB3   //duty cycle of half-bridge 3
 */
void uz_PWM_SS_2L_hw_SetDutyCycle(uint32_t base_address, float dutyCyc_HB1, float dutyCyc_HB2, float dutyCyc_HB3);

/**
 * @brief turns the whole PWM_SS_2L module on or off
 * 
 * @param base_address  //base address of the instance
 * @param PWM_en        //false=disable module, true=enable module
 */
void uz_PWM_SS_2L_hw_SetStatus(uint32_t base_address, bool PWM_en);

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
void uz_PWM_SS_2L_hw_SetMode(uint32_t base_address, uint32_t PWM_mode);

/**
 * @brief sets the carrier frequency (PWM frequency) of the PWM module.
 * 
 * @param base_address          //base address of the instance
 * @param ip_clk_frequency_Hz   //frequency of ip core clock, e.g. 100000000 for 100 MHz
 * @param PWM_freq_Hz           //desired PWM frequency, e.g. 10000 for 10 kHz
 */
void uz_PWM_SS_2L_hw_SetCarrierFrequency(uint32_t base_address, uint32_t ip_clk_frequency_Hz, float PWM_freq_Hz);

/**
 * @brief sets a half-bridge in a non conducting high-Z tri state mode.
 * 
 * @param base_address          //base address of the instance
 * @param halfBridgeNumber      //number of the half bridge to set. 1,2 or 3.
 * @param TriState_true_false   //turns tri state mode on or off. true=on, false=off
 */
void uz_PWM_SS_2L_hw_SetTristate(uint32_t base_address, uint32_t halfBridgeNumber, bool TriState_true_false);

/**
 * @brief sets the minimum amount of pulse width that is generated 
 *        by the PWM module.
 * 
 * @param base_address              //base address of the instance
 * @param min_pulse_width_percent   //minimum pulse width in percent, e.g. 0.01
 */
void uz_PWM_SS_2L_hw_SetMinimumPulseWidth(uint32_t base_address, float min_pulse_width_percent);

/**
 * @brief sets the shift of the carrier triangle signal to enable interleaved operation.
 * 
 * @param base_address              //base address of the instance
 * @param triangle_shift_HB1        //shift of HB1 fixed to 0-1, e.g. 0.25.  0 represents no shift and 1 represents a shift by an entire period.
 * @param triangle_shift_HB2        //shift of HB2 fixed to 0-1, e.g. 0.25.  0 represents no shift and 1 represents a shift by an entire period.
 * @param triangle_shift_HB3        //shift of HB3 fixed to 0-1, e.g. 0.25.  0 represents no shift and 1 represents a shift by an entire period.
 */
void uz_PWM_SS_2L_hw_SetTriangleShift(uint32_t base_address, float triangle_shift_HB1, float triangle_shift_HB2, float triangle_shift_HB3);

#endif // UZ_PWM_SS_2L_HW_H
