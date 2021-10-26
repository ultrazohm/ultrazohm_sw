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
    bool use_external_counter;          /**< Flag for choosing the PWM counter source\n
                                         0 = internal counter source of the instance\n
                                         1 = counter at port count_in */
    float init_dutyCyc_A;               /**< Initial PWM duty cycle of half-bridge 1, 0...1 */
    float init_dutyCyc_B;               /**< Initial PWM duty cycle of half-bridge 2, 0...1 */
    float init_dutyCyc_C;               /**< Initial PWM duty cycle of half-bridge 3, 0...1 */
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
 */

void uz_PWM_SS_2L_set_duty_cycle(struct uz_PWM_SS_2L_t *self, float dutyCyc_A, float dutyCyc_B, float dutyCyc_C);

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

#endif // UZ_PWM_SS_2L_H