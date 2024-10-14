#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"

#include "uz_pmsm_control.h"
#include "uz_Transformation/uz_Transformation.h"
#include "uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "uz_signals.h"
#include "uz_speedcontrol.h"
#include "../uz_piController/uz_piController.h"
#include "uz_CurrentControl.h"
#include "uz_linear_decoupling.h"
#include "uz_space_vector_limitation.h"
#include "uz_setpoint.h"
#include "uz_newton_raphson.h"

#include <math.h>

TEST_FILE("uz_signals_iir_filter.c")

struct uz_pmsm_control_configuration_t config = {
    .current_conversion_factors = {
        .a = 1,
        .b = 2,
        .c = 3},
    .current_offsets = {.a = 1, .b = 2, .c = -1},
    .v_dc_in_V_conversion_factor = 10,
    .v_dc_in_V_offset = -1,
    .theta_el_offset = 0.1f,
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = true,
    .speed_controller_max_torque = 10.0f,
    .speed_controller_kp = 1,
    .speed_controller_ki = 2,
    .current_controller_d_kp = 1,
    .current_controller_d_ki = 2,
    .current_controller_q_kp = 3,
    .current_controller_q_ki = 4,
    .decoupling_method = linear_decoupling,
    .motor_type = IPMSM,
    .enable_field_weakening = false,
    .relative_torque_tolerance = 0.1f,
    .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f}};

struct uz_PMSM_t config_PMSM_brose = {
    .R_ph_Ohm = 0.023f,
    .Ld_Henry = 3e-5f,
    .Lq_Henry = 6e-5f,
    .Psi_PM_Vs = 0.007f,
    .polePairs = 5.0f,
    .J_kg_m_squared = 0.000084f,
    .I_max_Ampere = 35.0f,
    .I_rated_Ampere = 28.3f};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_pmsm_control_NeedToImplement(void)
{
    uz_pmsm_control_t *test = uz_pmsm_control_init(config, config_PMSM_brose);
    struct uz_pmsm_actual_data const *const observed_data = uz_pmsm_control_get_actual_data(test);
}

#endif // TEST
