#ifndef UZ_PWM_SS_2L_H
#define UZ_PWM_SS_2L_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Data type for object UZ_PWM_SS_2L
 *
 */
typedef struct uz_PWM_SS_2L_t uz_PWM_SS_2L_t;

/*! enum for readable configuring of the PWM mode in uz_PWM_SS_2L_hw_SetMode function */
enum uz_PWM_SS_2L_PWM_mode {
  normalized_input_via_AXI=0,
  normalized_input_via_FPGA,
  direct_control_via_FPGA
};

/*! enum for readable configuring of the PWM trigger source for the output of new DutyCycles and triangle shift in uz_PWM_SS_2L_hw_SetTriggerSource function */
enum uz_PWM_SS_2L_PWM_trigger_source {
    trigger_at_MIN=0,
    trigger_at_MAX,
    trigger_at_EITHER
};

/**
 * @brief Configuration struct for UZ_PWM_SS_2L
 *
 */
struct uz_PWM_SS_2L_config_t{
    uint32_t base_address;              /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz;       /**< Clock frequency of the IP-Core */
    bool Tristate_HB1;                  /**< Tristate flag for half-bridge 1, true=on, false=off */
    bool Tristate_HB2;                  /**< Tristate flag for half-bridge 2, true=on, false=off */
    bool Tristate_HB3;                  /**< Tristate flag for half-bridge 3, true=on, false=off */
    float min_pulse_width;              /**< Minimum pulse width in percent, e.g. 0.01 */
    float PWM_freq_Hz;                  /**< Switching frequency of PWM mode in Hz */
    enum uz_PWM_SS_2L_PWM_mode PWM_mode;/**< PWM mode selector\n  
                                        0 = normalized input of reference signal via AXI\n
                                            e.g. a reference voltage value between 0 and 1\n
                                        1 = normalized input of reference signal via FPGA\n
                                            e.g. a reference voltage value between 0 and 1\n
                                        2 = direct control of switching states via FPGA */
    bool PWM_en;                        /**< IP core enable flag\n 
                                         0=disable module, 1=enable module */
    bool use_external_counter;          /**< Flag for choosing the PWM triangle source\n
                                         0 = internal counter source of the instance\n
                                         1 = triangle signal at port triangle_in */
    float init_dutyCyc_HB1;             /**< Initial PWM duty cycle of half-bridge 1, 0...1 */
    float init_dutyCyc_HB2;             /**< Initial PWM duty cycle of half-bridge 2, 0...1 */
    float init_dutyCyc_HB3;             /**< Initial PWM duty cycle of half-bridge 3, 0...1 */
    float triangle_shift_HB1;           /**< Shift the triangle signal of HB1 to enable interleaved PWM operation. Input is fixed to 0-1. \n
                                         0=no shift \n
                                         0.5=shift by a half period \n
                                        1=shift by an entire period */
    float triangle_shift_HB2;           /**< Shift the triangle signal of HB2 to enable interleaved PWM operation. Input is fixed to 0-1. */
    float triangle_shift_HB3;           /**< Shift the triangle signal of HB3 to enable interleaved PWM operation. Input is fixed to 0-1. */
    enum uz_PWM_SS_2L_PWM_trigger_source trigger_source; /** Trigger source for new DutyCycles and triangle shifts
                                                        0 = trigger at MIN of triangle\n
                                                        1 = trigger at MAX of triangle\n 
                                                        2 = trigger at EITHER MAX or MIN of triangle*/
};

/**
 * @brief Initializes an instance of the uz_PWM_SS_2L driver
 * 
 * @param config            Config struct of type uz_PWM_SS_2L_config_t for the IP-Core
 * @return uz_PWM_SS_2L_t*  Pointer to initialized instance
 */
uz_PWM_SS_2L_t* uz_PWM_SS_2L_init(struct uz_PWM_SS_2L_config_t config);

/**
 * @brief Uses a configuration struct of type uz_PWM_SS_2L_config_t from a
 *        uz_PWM_SS_2L_t instance and writes the configuration to the IP-core
 * 
 * @param self Instance of uz_PWM_SS_2L
 * @param dutyCyc_HB1 DutyCycle for half-bridge 1
 * @param dutyCyc_HB2 DutyCycle for half-bridge 2
 * @param dutyCyc_HB3 DutyCycle for half-bridge 3
 */
void uz_PWM_SS_2L_set_duty_cycle(struct uz_PWM_SS_2L_t *self, float dutyCyc_HB1, float dutyCyc_HB2, float dutyCyc_HB3);

/**
 * @brief Sets selected half-bridges in a non conducting high-Z tri state mode
 * 
 * @param self          Instance of uz_PWM_SS_2L
 * @param Tristate_HB1  Tristate flag for half-bridge 1, true=on, false=off
 * @param Tristate_HB2  Tristate flag for half-bridge 2, true=on, false=off
 * @param Tristate_HB3  Tristate flag for half-bridge 3, true=on, false=off
 */
void uz_PWM_SS_2L_set_tristate(struct uz_PWM_SS_2L_t *self, bool Tristate_HB1, bool Tristate_HB2, bool Tristate_HB3);

/**
 * @brief Sets the input source of gate signals
 * 
 * @param self      Instance of uz_PWM_SS_2L
 * @param PWM_mode  There are three modes to chose\n
 *                  0 = normalized input of reference signal via AXI\n
 *                  e.g. a reference voltage value between 0 and 1\n
 *                  1 = normalized input of reference signal via FPGA\n
 *                  e.g. a reference voltage value between 0 and 1\n
 *                  2 = direct control of switching states via FPGA
 */
void uz_PWM_SS_2L_set_PWM_mode(struct uz_PWM_SS_2L_t *self, enum uz_PWM_SS_2L_PWM_mode PWM_mode);

/**
 * @brief sets the shift of the carrier triangle signal for each half-bridge to enable interleaved operation.
 * 
 * @param self                  Instance of uz_PWM_SS_2L
 * @param triangle_shift_HB1    Shift of HB1 fixed to 0-1, e.g. 0.25f.  0 represents no shift and 1 represents a shift by an entire period.
 * @param triangle_shift_HB2    Shift of HB2 fixed to 0-1, e.g. 0.25f.  0 represents no shift and 1 represents a shift by an entire period.
 * @param triangle_shift_HB3    Shift of HB3 fixed to 0-1, e.g. 0.25f.  0 represents no shift and 1 represents a shift by an entire period.
 */
void uz_PWM_SS_2L_set_triangle_shift(struct uz_PWM_SS_2L_t *self, float triangle_shift_HB1, float triangle_shift_HB2, float triangle_shift_HB3);

#endif // UZ_PWM_SS_2L_H