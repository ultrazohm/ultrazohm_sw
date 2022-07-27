#ifndef UZ_SETPOINT_H
#define UZ_SETPOINT_H

#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_PMSM_config/uz_PMSM_config.h"
#include <stdbool.h>

/*! enum for selection of machine type */
enum uz_Setpoint_motor_type {
	SMPMSM = 0, IPMSM
};

/**
 * @brief Object definition for uz_SetPoint_t
 *
 */
typedef struct uz_SetPoint_t uz_SetPoint_t;

/**
 * @brief Configuration struct for Setpoint module. Accessible by the user
 */
struct uz_SetPoint_config {
	uz_PMSM_t config_PMSM; /**< PMSM struct which carries necessary motor related parameters for field weakening */
	bool is_field_weakening_active; /**< flag to enable field_weaking */
	enum uz_Setpoint_motor_type motor_type;/**< Selection for which motor type is used \n
											0 = SMPMSM -> surface-mounted PMSM (Ld=Lq) \n
											1 = IPMSM -> interior PMSM (Ld=/=Lq) */
};

/**
 * @brief Initialization of the Setpoint object
 *
 * @param config uz_SetPoint_config configuration struct
 * @return Pointer to uz_SetPoint_t object
 */
uz_SetPoint_t* uz_SetPoint_init(struct uz_SetPoint_config config);

/**
 * @brief Calculates reference torque 
 * 
 * @param self pointer to uz_SetPoint_t object
 * @param omega_m_rad_per_sec mechanical rotational speed in 1/rad
 * @param M_ref_Nm reference torque in Nm
 * @param id_ref_Ampere if a manual d-current wants to be set, otherwise controlled by the field-weakening or MTPA
 * @param V_DC_Volts DC-link voltage 
 * @return uz_3ph_dq_t reference currents for current-control
 */
uz_3ph_dq_t uz_SetPoint_sample(uz_SetPoint_t* self, float omega_m_rad_per_sec, float M_ref_Nm, float id_ref_Ampere, float V_DC_Volts);

/**
 * @brief Enables or disables the field weakening
 * 
 * @param self pointer to uz_SetPoint_t object
 * @param is_field_weakening_active status flag if field_weakening should be enabled = true or disabled
 */
void uz_SetPoint_set_field_weakening(uz_SetPoint_t* self, bool is_field_weakening_active);

/**
 * @brief Updates the motor related parameters in the uz_PMSM_t struct
 * 
 * @param self pointer to uz_SetPoint_t object
 * @param input uz_PMSM_t struct with new values
 */
void uz_SetPoint_set_PMSM_config(uz_SetPoint_t* self, uz_PMSM_t input);

/**
 * @brief Returns the current value of the clamping signal
 * 
 * @param self pointer to uz_SetPoint_t instance
 * @return current value as bool 
 */
bool uz_SetPoint_get_clamping(uz_SetPoint_t* self);
#endif // UZ_SETPOINT_H
