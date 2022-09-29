#ifndef UZ_SETPOINT_H
#define UZ_SETPOINT_H

#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_PMSM_config/uz_PMSM_config.h"
#include <stdbool.h>

/*! enum for selection of machine type */
enum uz_Setpoint_motor_type {
	SMPMSM = 0, IPMSM
};

/*! enum for selection of control type */
enum uz_Setpoint_control_type {
	FOC = 0,
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
	uz_PMSM_t config_PMSM; /**< PMSM struct which carries necessary motor related parameters for field weakening and MTPA */
	float id_ref_Ampere; 	/**< manual i_d reference current. Will be added on top of the MTPA d-current. Unused, if FW is active. */
	bool is_field_weakening_enabled; /**< flag to enable field_weaking. True = enabled */
	enum uz_Setpoint_motor_type motor_type;/**< Selection for which motor type is used \n
											0 = SMPMSM -> surface-mounted PMSM (Ld=Lq) \n
											1 = IPMSM -> interior PMSM (Ld=/=Lq) */
	enum uz_Setpoint_control_type control_type; /**< Selection for which control type is used \n
											0 = FOC -> field oriented control \n */							
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
 * @param V_DC_Volts DC-link voltage in Volts
 * @param actual_currents_Ampere uz_3ph_dq_t struct with measured currents in Ampere
 * @return uz_3ph_dq_t reference currents for current-control module in Ampere
 */
uz_3ph_dq_t uz_SetPoint_sample(uz_SetPoint_t* self, float omega_m_rad_per_sec, float M_ref_Nm, float V_DC_Volts, uz_3ph_dq_t actual_currents_Ampere);

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
void uz_SetPoint_set_PMSM_parameters(uz_SetPoint_t* self, uz_PMSM_t input);

/**
 * @brief Updates the manual reference id-current
 * 
 * @param self pointer to uz_SetPoint_t instance
 * @param id_ref_Ampere new value for manual id-reference current
 */
void uz_SetPoint_set_id_ref(uz_SetPoint_t* self, float id_ref_Ampere);
#endif // UZ_SETPOINT_H
