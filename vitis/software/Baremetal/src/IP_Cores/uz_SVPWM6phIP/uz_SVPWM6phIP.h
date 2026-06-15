#ifndef UZ_SVPWM6PHIP_H
#define UZ_SVPWM6PHIP_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Data type for object UZ_SVPWM6phIP
 *
 */
typedef struct uz_SVPWM6phIP_t uz_SVPWM6phIP_t;

/*! enum for readable configuring of the PWM mode in uz_SVPWM6phIP_hw_SetMode function */
enum uz_SVPWM6phIP_PWM_mode {
  normalized_input_via_AXI=0,
  normalized_input_via_FPGA,
  direct_control_via_FPGA
};

/*! enum for readable configuring of the PWM trigger source for the output of new DutyCycles and triangle shift in uz_PWM_SS_2L_hw_SetTriggerSource function */
enum uz_SVPWM6phIP_PWM_trigger_source {
    trigger_at_MIN=0,
    trigger_at_MAX,
    trigger_at_EITHER
};

/**
 * @brief Configuration struct for UZ_SVPWM6phIP
 *
 */
struct uz_SVPWM6phIP_config_t{
    uint32_t base_address;              /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz;       /**< Clock frequency of the IP-Core */
    bool Tristate_HB1;                  /**< Tristate flag for half-bridge 1, true=on, false=off */
    bool Tristate_HB2;                  /**< Tristate flag for half-bridge 2, true=on, false=off */
    bool Tristate_HB3;                  /**< Tristate flag for half-bridge 3, true=on, false=off */
    bool Tristate_HB4;                  /**< Tristate flag for half-bridge 1, true=on, false=off */
    bool Tristate_HB5;                  /**< Tristate flag for half-bridge 2, true=on, false=off */
    bool Tristate_HB6;                  /**< Tristate flag for half-bridge 3, true=on, false=off */
    float min_Ton_time;              /**< Minimum T on time in percent, e.g. 0.01 */
    float PWM_freq_Hz;                  /**< Switching frequency of PWM mode in Hz */
    enum uz_SVPWM6phIP_PWM_mode PWM_mode;/**< PWM mode selector\n  
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
    float init_T1;                      /**< Initial on-time of SV 1, 0...1 */
    float init_T2;                      /**< Initial on-time of SV 2, 0...1 */
    float init_T3;                      /**< Initial on-time of SV 3, 0...1 */
    float init_T4;                      /**< Initial on-time of SV 4, 0...1 */
    float init_T5;                      /**< Initial on-time of SV 5, 0...1 */
    uint32_t init_SV1;                     /**< Initial SV 1, 0...63 */
    uint32_t init_SV2;                     /**< Initial SV 2, 0...63 */
    uint32_t init_SV3;                     /**< Initial SV 3, 0...63 */
    uint32_t init_SV4;                     /**< Initial SV 4, 0...63 */
    uint32_t init_SV5;                     /**< Initial SV 5, 0...63 */
    enum uz_SVPWM6phIP_PWM_trigger_source trigger_source; /**< Trigger source for new DutyCycles and triangle shifts\n
                                                        0 = trigger at MIN of triangle\n
                                                        1 = trigger at MAX of triangle\n 
                                                        2 = trigger at EITHER MAX or MIN of triangle*/
};

/**
 * @brief Initializes an instance of the uz_SVPWM6phIP driver
 * 
 * @param config            Config struct of type uz_SVPWM6phIP_config_t for the IP-Core
 * @return uz_SVPWM6phIP_t*  Pointer to initialized instance
 */
uz_SVPWM6phIP_t* uz_SVPWM6phIP_init(struct uz_SVPWM6phIP_config_t config);

/**
 * @brief Uses a configuration struct of type uz_SVPWM6phIP_config_t from a
 *        uz_SVPWM6phIP_t instance and writes the configuration to the IP-core
 * 
 * @param self Instance of uz_SVPWM6phIP
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
void uz_SVPWM6phIP_set_T_and_SV(struct uz_SVPWM6phIP_t *self, float T1, float T2, float T3, float T4, float T5, uint32_t SV1, uint32_t SV2, uint32_t SV3, uint32_t SV4, uint32_t SV5);

/**
 * @brief Sets selected half-bridges in a non conducting high-Z tri state mode
 * 
 * @param self          Instance of uz_PWM_SS_2L
 * @param Tristate_HB1  Tristate flag for half-bridge 1, true=on, false=off
 * @param Tristate_HB2  Tristate flag for half-bridge 2, true=on, false=off
 * @param Tristate_HB3  Tristate flag for half-bridge 3, true=on, false=off
 * @param Tristate_HB4  Tristate flag for half-bridge 4, true=on, false=off
 * @param Tristate_HB5  Tristate flag for half-bridge 5, true=on, false=off
 * @param Tristate_HB6  Tristate flag for half-bridge 6, true=on, false=off
 */
void uz_SVPWM6phIP_set_tristate(struct uz_SVPWM6phIP_t *self, bool Tristate_HB1, bool Tristate_HB2, bool Tristate_HB3, bool Tristate_HB4, bool Tristate_HB5, bool Tristate_HB6);

/**
 * @brief Sets the input source of gate signals
 * 
 * @param self      Instance of uz_SVPWM6phIP
 * @param PWM_mode  There are three modes to chose\n
 *                  0 = normalized input of reference signal via AXI\n
 *                  e.g. a reference voltage value between 0 and 1\n
 *                  1 = normalized input of reference signal via FPGA\n
 *                  e.g. a reference voltage value between 0 and 1\n
 *                  2 = direct control of switching states via FPGA
 */
void uz_SVPWM6phIP_set_PWM_mode(struct uz_SVPWM6phIP_t *self, enum uz_SVPWM6phIP_PWM_mode PWM_mode);




#endif // UZ_SVPWM6PHIP_H
