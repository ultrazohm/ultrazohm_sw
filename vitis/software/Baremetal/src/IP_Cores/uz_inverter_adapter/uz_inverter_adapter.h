#ifndef UZ_INVERTER_ADAPTER_H
#define UZ_INVERTER_ADAPTER_H
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Data type for object uz_inverter_adapter
 *
 */
typedef struct uz_inverter_adapter_t uz_inverter_adapter_t;

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
 * @brief Configuration struct for uz_inverter_adapter
 *
 */
struct uz_inverter_adapter_config_t{
    uint32_t base_address;                                      /**< Base address of the IP-Core instance to which the driver is coupled */
    uint32_t ip_clk_frequency_Hz;                               /**< Clock frequency of the IP-Core */
    linear_interpolation_params_t linear_interpolation_params;  /**< Parameters for linear interpolation of temperature measurement */
};

/**
 * @brief Struct to return and read the outputs of uz_inverter_adapter
 *
 */
struct uz_inverter_adapter_outputs_t{
    float PWMdutyCycNormalized_H1;
    float PWMdutyCycNormalized_L1;
    float PWMdutyCycNormalized_H2;
    float PWMdutyCycNormalized_L2;
    float PWMdutyCycNormalized_H3;
    float PWMdutyCycNormalized_L3;
    float ChipTempDegreesCelsius_H1; /**< Chip temperature of H1 in degrees celsius */
    float ChipTempDegreesCelsius_L1; /**< Chip temperature of L1 in degrees celsius */
    float ChipTempDegreesCelsius_H2; /**< Chip temperature of H2 in degrees celsius */
    float ChipTempDegreesCelsius_L2; /**< Chip temperature of L2 in degrees celsius */
    float ChipTempDegreesCelsius_H3; /**< Chip temperature of H3 in degrees celsius */
    float ChipTempDegreesCelsius_L3; /**< Chip temperature of L3 in degrees celsius */
    uint32_t OC;
    bool OC_H1; /**< Over current OC fault signal of H1 */
    bool OC_L1; /**< Over current OC fault signal of L1 */
    bool OC_H2; /**< Over current OC fault signal of H2 */
    bool OC_L2; /**< Over current OC fault signal of L2 */
    bool OC_H3; /**< Over current OC fault signal of H3 */
    bool OC_L3; /**< Over current OC fault signal of L3 */
    uint32_t FAULT;
    bool FAULT_H1; /**< FAULT signal of H1 */
    bool FAULT_L1; /**< FAULT signal of L1 */
    bool FAULT_H2; /**< FAULT signal of H2 */
    bool FAULT_L2; /**< FAULT signal of L2 */
    bool FAULT_H3; /**< FAULT signal of H3 */
    bool FAULT_L3; /**< FAULT signal of L3 */
    uint32_t I_DIAG;
    bool I_DC_DIAG; /**< Diagnostic signal of current amplifier for DC current */
    bool I1_DIAG; /**< Diagnostic signal of current amplifier for phase a current */
    bool I2_DIAG; /**< Diagnostic signal of current amplifier for phase b current */
    bool I3_DIAG; /**< Diagnostic signal of current amplifier for phase c current */
};

/**
 * @brief Initializes an instance of the uz_inverter_adapter driver
 *
 * @param config Configuration values for the IP-Core
 * @param outputs Output values of the IP-Core
 *
 * @return Pointer to initialized instance
 */
uz_inverter_adapter_t* uz_inverter_adapter_init(struct uz_inverter_adapter_config_t config, struct uz_inverter_adapter_outputs_t outputs);

/**
 * @brief Calculates chip temperature from duty cycle 
 *
 * @param dutyCycleNormalized is the measured duty cycle of the
 *        PWM temperature signal
 * @return float value of chip temperature in degrees celsius
 */
 float uz_inverter_adapter_PWMdutyCycNormalized_to_DegreesCelsius(uz_inverter_adapter_t *self, float dutyCycleNormalized);


/**
 * @brief updates the states and signals read from the ip-core
 *        called by uz_inverter_adapter_get_outputs function
 * 
 * @param self Pointer to the instance
 */
 void uz_inverter_adapter_update_states(uz_inverter_adapter_t *self);


/** 
 * @brief returns the state and signals of the output struct
 *        
 * @param self Pointer to the instance
 */ 
 struct uz_inverter_adapter_outputs_t uz_inverter_adapter_get_outputs(uz_inverter_adapter_t *self);

 /**
  * @brief sets the enable pin for the gate drivers
  *
  * @param self Pointer to the instance
  * @param pwm_en_onoff enables (true) or disables (false) the gates
  */
void uz_inverter_adapter_set_PWM_EN(uz_inverter_adapter_t *self, bool pwm_en_onoff);

#endif // UZ_INVERTER_ADAPTER_H
