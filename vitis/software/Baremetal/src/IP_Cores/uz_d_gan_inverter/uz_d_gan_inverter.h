#ifndef UZ_D_GAN_INVERTER_H
#define UZ_D_GAN_INVERTER_H
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Data type for object uz_d_gan_inverter
 *
 */
typedef struct uz_d_gan_inverter_t uz_d_gan_inverter_t;

/**
 * @brief Configuration struct for uz_d_gan_inverter
 *
 */
struct uz_d_gan_inverter_config_t{
    uint32_t base_address; /**< Base address of the IP-Core instance to which the driver is coupled */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
};

/**
 * @brief Struct to return and read the outputs of uz_d_gan_inverter
 *
 */
struct uz_d_gan_inverter_outputs_t{
    uint32_t PWMdutyCycPerCent_H1;
    uint32_t PWMdutyCycPerCent_L1;
    uint32_t PWMdutyCycPerCent_H2;
    uint32_t PWMdutyCycPerCent_L2;
    uint32_t PWMdutyCycPerCent_H3;
    uint32_t PWMdutyCycPerCent_L3;
    float GaN_ChipTempDegreesCelsius_H1; /**< Chip temperature of GaN H1 in degrees celsius */
    float GaN_ChipTempDegreesCelsius_L1; /**< Chip temperature of GaN L1 in degrees celsius */
    float GaN_ChipTempDegreesCelsius_H2; /**< Chip temperature of GaN H2 in degrees celsius */
    float GaN_ChipTempDegreesCelsius_L2; /**< Chip temperature of GaN L2 in degrees celsius */
    float GaN_ChipTempDegreesCelsius_H3; /**< Chip temperature of GaN H3 in degrees celsius */
    float GaN_ChipTempDegreesCelsius_L3; /**< Chip temperature of GaN L3 in degrees celsius */
    bool OC_H1; /**< Over current OC fault signal of GaN H1 */
    bool OC_L1; /**< Over current OC fault signal of GaN L1 */
    bool OC_H2; /**< Over current OC fault signal of GaN H2 */
    bool OC_L2; /**< Over current OC fault signal of GaN L2 */
    bool OC_H3; /**< Over current OC fault signal of GaN H3 */
    bool OC_L3; /**< Over current OC fault signal of GaN L3 */
    bool FAULT_H1; /**< FAULT signal of GaN H1 */
    bool FAULT_L1; /**< FAULT signal of GaN L1 */
    bool FAULT_H2; /**< FAULT signal of GaN H2 */
    bool FAULT_L2; /**< FAULT signal of GaN L2 */
    bool FAULT_H3; /**< FAULT signal of GaN H3 */
    bool FAULT_L3; /**< FAULT signal of GaN L3 */
    bool I_DC_DIAG; /**< Diagnostic signal of current amplifier for DC current */
    bool I1_DIAG; /**< Diagnostic signal of current amplifier for phase a current */
    bool I2_DIAG; /**< Diagnostic signal of current amplifier for phase b current */
    bool I3_DIAG; /**< Diagnostic signal of current amplifier for phase c current */
};

/**
 * @brief Initializes an instance of the uz_d_gan_inverter driver
 *
 * @param config Configuration values for the IP-Core
 * @return Pointer to initialized instance
 */
uz_d_gan_inverter_t* uz_d_gan_inverter_init(struct uz_d_gan_inverter_config_t config);

/**
 * @brief Calculates chip temperature from duty cycle 
 *
 * @param dutyCyclePerCent is the measured duty cycle of the 
 *        PWM temperature signal
 * @return float value of chip temperature in degrees celsius
 */
 float uz_d_gan_inverter_PWMdutyCycPerCent_to_DegreesCelsius(float dutyCyclePerCent);

 void uz_d_gan_inverter_update_states(uz_d_gan_inverter_t *self);

#endif // UZ_D_GAN_INVERTER_H
