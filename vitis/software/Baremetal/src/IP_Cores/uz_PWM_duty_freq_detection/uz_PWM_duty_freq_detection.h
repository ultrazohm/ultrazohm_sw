#ifndef UZ_PWM_DUTY_FREQ_DETECTION_H
#define UZ_PWM_DUTY_FREQ_DETECTION_H
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Data type for object uz_PWM_duty_freq_detection
 *
 */
typedef struct uz_PWM_duty_freq_detection_t uz_PWM_duty_freq_detection_t;

/**
 * @brief Struct for linear interpolation parameters
 * using a function of the form y=ax+b
 *
 * @param a Gradient
 * @param b Offset
 */
typedef struct linear_interpolation_parameters_t{
    float a;
    float b;
} linear_interpolation_parameters_t;

/**
 * @brief Configuration struct for uz_PWM_duty_freq_detection
 *
 */
struct uz_PWM_duty_freq_detection_config_t{
    uint32_t base_address;                                      /**< Base address of the IP-Core instance to which the driver is coupled */
    uint32_t ip_clk_frequency_Hz;                               /**< Clock frequency of the IP-Core */
};

/**
 * @brief Initializes an instance of the uz_PWM_duty_freq_detection driver
 *
 * @param config Configuration values for the IP-Core
 *
 * @return Pointer to initialized instance
 */
uz_PWM_duty_freq_detection_t* uz_PWM_duty_freq_detection_init(struct uz_PWM_duty_freq_detection_config_t config);

/**
 * @brief Returns the detected frequency of the PWM signal.
 * 
 * @param self pointer to initialized instance
 * @return Frequency in Hz
 */
float uz_PWM_duty_freq_detection_get_frequency_in_Hz(uz_PWM_duty_freq_detection_t *self);

/**
 * @brief Returns the normalized duty cycle of the PWM signal.
 * 
 * @param self pointer to initialized instance
 * @return Duty cycle normalized to the range 0.0 to 1.0
 */
float uz_PWM_duty_freq_detection_get_duty_cycle_normalized(uz_PWM_duty_freq_detection_t *self);

/**
 * @brief Returns the duty cycle of the PWM signal in percent.
 *
 * @param self pointer to initialized instance
 * @return Duty cycle in the range 0.0 to 100.0 percent
 */
float uz_PWM_duty_freq_detection_get_duty_cycle_in_percent(uz_PWM_duty_freq_detection_t *self);


/**
 * @brief Returns the temperature 
 * 
 * @param duty_cycle_normalized Normalized duty cycle in the range 0.0 to 1.0
 * @param lin_interp_param Parameters of the linear interpolation
 * @return float temperature in degree Celsius
 */
float uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(float duty_cycle_normalized, struct linear_interpolation_parameters_t lin_interp_param);


#endif // UZ_PWM_DUTY_FREQ_DETECTION_H
