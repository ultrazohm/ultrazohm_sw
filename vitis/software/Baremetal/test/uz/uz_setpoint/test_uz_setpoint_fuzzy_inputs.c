#ifdef TEST

#include "unity.h"
#include "uz_setpoint.h"
#include "uz_newton_raphson.h"
#include "../uz_signals/uz_signals.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

TEST_SOURCE_FILE("src/uz/uz_PMSM_config/uz_PMSM_config.c")

#define FUZZ_TEST_ITERATIONS 1000000U

static const uz_PMSM_t Beckhoff_AM8071_0R01 = {
    .machine_id = 0U,
    .R_ph_Ohm = 0.08f,
    .Ld_Henry = 0.0011f,
    .Lq_Henry = 0.002f,
    .Psi_PM_Vs = 0.1092f,
    .polePairs = 5.0f,
    .J_kg_m_squared = 0.00683f,
    .I_max_Ampere = 81.8f,
    .I_rated_Ampere = 17.6f,
    .Torque_rated_Nm = 18.0f,
    .Torque_max_Nm = 78.0f,
    .Torque_min_Nm = 0.0f,
    .speed_rated_rpm = 4000.0f,
    .speed_max_rpm = 5000.0f,
    .speed_min_rpm = 0.0f,
    .V_dc_nominal_V = 565.0f,
    .I_d_max_A = 81.8f,
    .I_d_min_A = -81.8f,
    .I_q_max_A = 81.8f,
    .I_q_min_A = -81.8f
};

static float random_float_minus_one_to_one(void)
{
    return (((float)rand() / (float)RAND_MAX) * 2.0f) - 1.0f;
}

static void fuzz_setpoint_inputs(uz_SetPoint_t *instance, float i_max_Ampere)
{
    for (uint32_t i = 0U; i < FUZZ_TEST_ITERATIONS; i++) {
        const float random_omega_m_rad_per_sec = random_float_minus_one_to_one();
        const float random_M_ref_Nm = random_float_minus_one_to_one();
        // V_DC must be greater than zero according to the public API contract.
        const float random_V_DC_Volts = fmaxf(fabsf(random_float_minus_one_to_one()), FLT_MIN);
        const uz_3ph_dq_t random_currents_Ampere = {
            .d = random_float_minus_one_to_one(),
            .q = random_float_minus_one_to_one()
        };

        const uz_3ph_dq_t output = uz_SetPoint_sample(instance,
                                                       random_omega_m_rad_per_sec,
                                                       random_M_ref_Nm,
                                                       random_V_DC_Volts,
                                                       random_currents_Ampere);

        TEST_ASSERT_TRUE(isfinite(output.d));
        TEST_ASSERT_TRUE(isfinite(output.q));
        TEST_ASSERT_LESS_OR_EQUAL_FLOAT(i_max_Ampere * i_max_Ampere,
                                        (output.d * output.d) + (output.q * output.q));
    }
}

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_SetPoint_sample_fuzz_existing_motor_parameters(void)
{
    const struct uz_SetPoint_config config = {
        .config_PMSM = {
            .I_max_Ampere = 15.0f,
            .Ld_Henry = 0.0003f,
            .Lq_Henry = 0.0002f,
            .R_ph_Ohm = 0.1f,
            .polePairs = 4.0f,
            .Psi_PM_Vs = 0.0075f,
            .J_kg_m_squared = 0.0001f
        },
        .id_ref_Ampere = 0.0f,
        .relative_torque_tolerance = 1.0f,
        .is_field_weakening_enabled = false,
        .motor_type = IPMSM,
        .control_type = FOC
    };
    srand(0x5E7F01U);
    uz_SetPoint_t *instance = uz_SetPoint_init(config);

    fuzz_setpoint_inputs(instance, config.config_PMSM.I_max_Ampere);
}

void test_uz_SetPoint_sample_fuzz_Beckhoff_AM8071_0R01(void)
{
    const struct uz_SetPoint_config config = {
        .config_PMSM = Beckhoff_AM8071_0R01,
        .id_ref_Ampere = 0.0f,
        .relative_torque_tolerance = 1.0f,
        .is_field_weakening_enabled = false,
        .motor_type = IPMSM,
        .control_type = FOC};
    srand(0x5E7F02U);
    uz_SetPoint_t *instance = uz_SetPoint_init(config);

    fuzz_setpoint_inputs(instance, config.config_PMSM.I_max_Ampere);
}

#endif // TEST
