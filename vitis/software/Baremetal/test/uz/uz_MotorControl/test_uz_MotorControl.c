#ifdef TEST

#include "test_assert_with_exception.h"
#include "unity.h"
#include "uz_MotorControl.h"
#include "uz_setpoint.h"
#include "uz_speedcontrol.h"
#include "uz_CurrentControl.h"
#include "uz_newton_raphson.h"
#include "uz_space_vector_modulation.h"
#include "uz_space_vector_limitation.h"
#include "uz_linear_decoupling.h"
#include "uz_Transformation.h"
#include "uz_piController.h"
#include "../uz_signals/uz_signals.h"

struct uz_SetPoint_config SP_config = {0};
struct uz_SpeedControl_config SC_config = {0};
struct uz_CurrentControl_config CC_config = {0};
struct uz_MotorControl_config MC_config = {0};
uz_PMSM_t PMSM_config = {0};
float omega_m_rad_per_sec = 0.0f;
float M_ref_Nm = 0.045f;
float V_DC_Volts = 24.0f;
uz_3ph_dq_t currents = {0};

void setUp(void)
{
    M_ref_Nm = 0.045f;
    V_DC_Volts = 24.0f;
    SP_config.id_ref_Ampere = 0.0f;
    PMSM_config.I_max_Ampere = 15.0f;
    PMSM_config.Ld_Henry = 0.0003f;
    PMSM_config.Lq_Henry = 0.0003f;
    PMSM_config.R_ph_Ohm = 0.1f;
    PMSM_config.polePairs = 4.0f;
    PMSM_config.Psi_PM_Vs = 0.0075f;
    SP_config.control_type = FOC;
    SP_config.motor_type = SMPMSM;
    SP_config.id_ref_Ampere = 0.0f;
    SP_config.is_field_weakening_enabled = false;
    SC_config.config_controller.Ki = 0.3456f;
    SC_config.config_controller.Kp = 0.03456f;
    SC_config.config_controller.samplingTime_sec = 0.00001f;
    SC_config.config_controller.upper_limit = 10.0f;
    SC_config.config_controller.lower_limit = -10.0f;
    CC_config.config_id.Kp = 6.75f;
    CC_config.config_id.Ki = 2000.0f;
    CC_config.config_id.samplingTime_sec = 0.00001f;
    CC_config.config_id.upper_limit = 10.0f;
    CC_config.config_id.lower_limit = -10.0f;
    CC_config.config_iq.Kp = 6.75f;
    CC_config.config_iq.Ki = 2000.0f;
    CC_config.config_iq.samplingTime_sec = 0.00001f;
    CC_config.config_iq.upper_limit = 10.0f;
    CC_config.config_iq.lower_limit = -10.0f;
    currents.d = 0.0f;
    currents.q = 0.0f;
}


void test_uz_MotorControl_init_assert_Rph_negative(void){
}


#endif // TEST
