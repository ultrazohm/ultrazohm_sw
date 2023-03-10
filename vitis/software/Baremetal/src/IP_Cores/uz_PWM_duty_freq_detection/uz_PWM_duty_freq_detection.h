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
typedef struct linear_interpolation_params_t{
    float a;
    float b;
} linear_interpolation_params_t;

/**
 * @brief Configuration struct for uz_PWM_duty_freq_detection
 *
 */
struct uz_PWM_duty_freq_detection_config_t{
    uint32_t base_address;                                      /**< Base address of the IP-Core instance to which the driver is coupled */
    uint32_t ip_clk_frequency_Hz;                               /**< Clock frequency of the IP-Core */
    linear_interpolation_params_t linear_interpolation_params;  /**< Parameters for linear interpolation of temperature measurement */
};

/**
 * @brief Struct to return and read the outputs of uz_PWM_duty_freq_detection
 *
 */
struct uz_PWM_duty_freq_detection_outputs_t{
    float PWMdutyCycNormalized;
    float TempDegreesCelsius; /**< temperature from PWM to degrees celsius */
    uint32_t PWMFreq;
    uint32_t PWMhightime;
    uint32_t PWMlowtime;
};

/**
 * @brief Initializes an instance of the uz_PWM_duty_freq_detection driver
 *
 * @param config Configuration values for the IP-Core
 * @param outputs Output values of the IP-Core
 *
 * @return Pointer to initialized instance
 */
uz_PWM_duty_freq_detection_t* uz_PWM_duty_freq_detection_init(struct uz_PWM_duty_freq_detection_config_t config, struct uz_PWM_duty_freq_detection_outputs_t outputs);

/**
 * @brief Calculates chip temperature from duty cycle,  
 *        called by uz_PWM_duty_freq_detection_get_outputs function
 *
 * @param dutyCycleNormalized is the measured duty cycle of the
 *        PWM temperature signal
 * @return float value of chip temperature in degrees celsius
 */
 float uz_PWM_duty_freq_detection_PWMdutyCycNormalized_to_DegreesCelsius(uz_PWM_duty_freq_detection_t *self, float dutyCycleNormalized);


/**
 * @brief updates the states and signals read from the ip-core, 
 *        called by uz_PWM_duty_freq_detection_get_outputs function
 * 
 * @param self Pointer to the instance
 */
 void uz_PWM_duty_freq_detection_update_states(uz_PWM_duty_freq_detection_t *self);


/** 
 * @brief returns the state and signals of the output struct
 *        
 * @param self Pointer to the instance
 */ 
 struct uz_PWM_duty_freq_detection_outputs_t uz_PWM_duty_freq_detection_get_outputs(uz_PWM_duty_freq_detection_t *self);


#endif // UZ_PWM_DUTY_FREQ_DETECTION_H
