#ifndef UZ_PWM_SS_2L_H
#define UZ_PWM_SS_2L_H

#include <stdint.h>

/**
 * @brief Data type for object UZ_PWM_SS_2L
 *
 */
typedef struct uz_PWM_SS_2L_t uz_PWM_SS_2L_t;

/**
 * @brief Configuration struct for UZ_PWM_SS_2L
 *
 */
struct uz_PWM_SS_2L_config_t{
    uint32_t base_address;          /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz;   /**< Clock frequency of the IP-Core */
    uint32_t Tristate_HB1;          /**< Tristate flag for half-bridge 1, 1=on, 0=off */
    uint32_t Tristate_HB2;          /**< Tristate flag for half-bridge 2, 1=on, 0=off */
    uint32_t Tristate_HB3;          /**< Tristate flag for half-bridge 3, 1=on, 0=off */
    float min_pulse_width;          /**< Minimum pulse width in percent, e.g. 0.01 */
    float PWM_freq_Hz;              /**< Switching frequency of PWM mode in Hz */
    uint32_t PWM_mode;              /**< PWM mode selector\n  
                                         0 = normalized input of reference signal via AXI\n
                                             e.g. a reference voltage value between 0 and 1\n
                                         1 = normalized input of reference signal via FPGA\n
                                             e.g. a reference voltage value between 0 and 1\n
                                         2 = direct control of switching states via FPGA */
    uint32_t PWM_en;                /**< IP core enable flag\n 
                                         0=disable module, 1=enable module */
    float init_dutyCyc_A;           /**< Initial PWM duty cycle of half-bridge 1, 0...1 */
    float init_dutyCyc_B;           /**< Initial PWM duty cycle of half-bridge 2, 0...1 */
    float init_dutyCyc_C;           /**< Initial PWM duty cycle of half-bridge 3, 0...1 */
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
 * @param instance Instance of uz_PWM_SS_2L
 */
void uz_PWM_SS_2L_set_config(struct uz_PWM_SS_2L_t *instance);

/**
 * @brief Sets the three duty cycle values of one uz_PWM_SS_2L instance via AXI
 * 
 * @param instance      Instance of uz_PWM_SS_2L
 * @param dutyCyc_A     //duty cycle of channel A, 0...1
 * @param dutyCyc_B     //duty cycle of channel B, 0...1
 * @param dutyCyc_C     //duty cycle of channel C, 0...1
 */
void uz_PWM_SS_2L_set_duty_cycle(struct uz_PWM_SS_2L_t *instance, float dutyCyc_A, float dutyCyc_B, float dutyCyc_C);

#endif // UZ_PWM_SS_2L_H