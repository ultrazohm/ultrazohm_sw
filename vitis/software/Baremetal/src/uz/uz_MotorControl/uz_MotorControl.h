#ifndef UZ_MOTORCONTROL_H
#define UZ_MOTORCONTROL_H

#include "../uz_HAL.h"
#include "../uz_CurrentControl/uz_CurrentControl.h"
#include "../uz_SpeedControl/uz_speedcontrol.h"
#include "../uz_setpoint/uz_setpoint.h"
#include "../uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include <stdlib.h>
#include <stdbool.h>

struct uz_MotorControl_config {
	uz_PMSM_t config_PMSM; /**< Configuration struct for PMSM parameters */
	struct uz_SpeedControl_config SC_config; /**< Configuration struct for the SpeedControl module */
	struct uz_CurrentControl_config CC_config; /**< Configuration struct for the CurrentControl module */
	struct uz_SetPoint_config SP_config; /**< Configuration struct for the SetPoint module */
	bool is_SpeedControl_selected; /**< Flag which indicates, if the SpeedControl is enabled, or a manual reference Torque is used as the input for the SetPoint module. 
										If set to *true*, the SetPoint module must be enabled as well.*/
	bool is_SetPoint_selected; /**< Flag which indicates, if the SetPoint module is enabled, or manual reference dq-currents are used for the CurrentControl module.
										If set to *false*, the SpeedControl module is automatically disabled. */
	float M_ref_Nm; /**< Manual reference torque for the SetPoint module, if SpeedControl is disabled */
	float n_ref_rpm; /**< Manual reference speed for the SpeedControl module */
	uz_3ph_dq_t i_ref_Ampere; /**< Manual reference dq-currents for the CurrentControl module */
};

/**
 * @brief Object definition for MotorControl
 *
 */
typedef struct uz_MotorControl_t uz_MotorControl_t;

/**
 * @brief Initialization of the uz_MotorControl_t object
 *
 * @param config configuration struct for MotorControl
 * @return uz_MotorControl_t* Pointer to uz_MotorControl_t instance
 */
uz_MotorControl_t* uz_MotorControl_init(struct uz_MotorControl_config config, uz_PWM_SS_2L_t* pwm_d1_pin_0_to_5) ;

void uz_MotorControl_sample(uz_MotorControl_t* self, uz_3ph_dq_t i_meas_Ampere, float V_DC_Volts, float omega_m_rad_per_sec, float theta_el_rad);


void uz_MotorControl_set_reference_torque(uz_MotorControl_t* self, float M_ref_Nm);

void uz_MotorControl_set_reference_speed(uz_MotorControl_t* self, float n_ref_rpm);

void uz_MotorControl_set_reference_currents(uz_MotorControl_t* self, uz_3ph_dq_t i_ref_Ampere);

void uz_MotorControl_set_CurrentControl_Kp_Ki(uz_MotorControl_t* self, float Kp_id, float Ki_id, float Kp_iq, float Ki_iq);

void uz_MotorControl_set_SpeedControl_Kp_Ki(uz_MotorControl_t* self, float Kp_n, float Ki_n);

void uz_MotorControl_set_PMSM_parameters(uz_MotorControl_t* self, uz_PMSM_t input);

void uz_MotorControl_set_field_weakening(uz_MotorControl_t* self, bool is_field_weakening_enabled);

void uz_MotorControl_set_id_ref(uz_MotorControl_t* self, float id_ref_Ampere);

void uz_MotorControl_set_decoupling_method(uz_MotorControl_t* self, enum uz_CurrentControl_decoupling_select decoupling_select);

void uz_MotorControl_set_SpeedControl(uz_MotorControl_t* self, bool is_SpeedControl_enabled);

void uz_MotorControl_set_SetPoint(uz_MotorControl_t* self, bool is_SetPoint_enabled);
#endif // UZ_MOTORCONTROL_H
