#include "../include/deskbench.h"
#include "../include/pmsm_cil.h"
static void clear_references(DS_Data* data)
{
    data->rasv.speed_ref_rpm_prime_mover = 0.0f;
    data->rasv.ramped_speed_ref_rpm_prime_mover = 0.0f;
    data->rasv.dut_current_reference_A = (uz_3ph_dq_t){0};
    for (unsigned i = 1; i <= 3; i++) data->av.snd_fld[i] = 0.0f;
    uz_ramp_reset(data->objects.speed_ref_ramp_prime_mover);
}

static bool deskbench_read_measurements(DS_Data* data)
{
    /* D1 inverter A/B -> A1 ADC A/B; D2 inverter A/B -> A2 ADC A/B.
     * A1, A2 and D5 readout precede this call. PMSM control needs mechanical rad and rad/s;
     * it applies the machine pole-pair count internally.
     */
    data->av.prime_mover_measurements = (struct uz_pmsm_measurement_values){
        // A2 values are already in A/V; do not apply the inverter gains again.
        .i_abc_in_A = {
            .a = data->av.adc_ltc2311_a2_ch3,
            .b = data->av.adc_ltc2311_a2_ch2,
            .c = data->av.adc_ltc2311_a2_ch1
        },
        .v_abc_in_V = {
            .a = data->av.adc_ltc2311_a2_ch7,
            .b = data->av.adc_ltc2311_a2_ch6,
            .c = data->av.adc_ltc2311_a2_ch5
        },
        .v_dc_in_V = data->av.adc_ltc2311_a2_ch0,
        .i_dc_in_A = data->av.adc_ltc2311_a2_ch4,
        .theta_mech = data->av.resolver_pl_interface_d5_2_position_mech_2pi,
        .omega_mech_rad_per_sec = data->av.resolver_pl_interface_d5_2_omega_mech_rad_s
    };
    if (data->av.dut_backend == DUT_BACKEND_DESKBENCH)
    {
        data->av.dut_measurements = (struct uz_pmsm_measurement_values){
            // A1 values are already in A/V, using the same channel order as A2.
            .i_abc_in_A = {
                .a = data->av.adc_ltc2311_a1_ch3,
                .b = data->av.adc_ltc2311_a1_ch2,
                .c = data->av.adc_ltc2311_a1_ch1
            },
            .v_abc_in_V = {
                .a = data->av.adc_ltc2311_a1_ch7,
                .b = data->av.adc_ltc2311_a1_ch6,
                .c = data->av.adc_ltc2311_a1_ch5
            },
            .v_dc_in_V = data->av.adc_ltc2311_a1_ch0,
            .i_dc_in_A = data->av.adc_ltc2311_a1_ch4,
            .theta_mech = data->av.resolver_pl_interface_d5_1_position_mech_2pi,
            .omega_mech_rad_per_sec = data->av.resolver_pl_interface_d5_1_omega_mech_rad_s
        };
    }
    // Both machines have assigned feedback. Controller protection checks its limits.
    return true;
}

static void apply_outputs(DS_Data* data, struct uz_DutyCycle_t dut,
    struct uz_DutyCycle_t prime_mover, bool enable_dut, bool enable_prime_mover)
{
    if (!enable_dut)
        dut = (struct uz_DutyCycle_t){.DutyCycle_A = 0.5f, .DutyCycle_B = 0.5f, .DutyCycle_C = 0.5f};
    if (!enable_prime_mover)
        prime_mover = (struct uz_DutyCycle_t){.DutyCycle_A = 0.5f, .DutyCycle_B = 0.5f, .DutyCycle_C = 0.5f};
    /* Deskbench half bridges 1..3 = DUT a..c (PWM object 0).
     * Deskbench half bridges 4..6 = prime mover a..c (PWM object 1).
     */
    data->rasv.pwm_2L_0_halfBridgeDutyCycle_1 = dut.DutyCycle_A;
    data->rasv.pwm_2L_0_halfBridgeDutyCycle_2 = dut.DutyCycle_B;
    data->rasv.pwm_2L_0_halfBridgeDutyCycle_3 = dut.DutyCycle_C;
    data->rasv.pwm_2L_1_halfBridgeDutyCycle_1 = prime_mover.DutyCycle_A;
    data->rasv.pwm_2L_1_halfBridgeDutyCycle_2 = prime_mover.DutyCycle_B;
    data->rasv.pwm_2L_1_halfBridgeDutyCycle_3 = prime_mover.DutyCycle_C;
    uz_PWM_SS_2L_set_tristate(data->objects.project_wizard_pwm_2l_0, !enable_dut, !enable_dut, !enable_dut);
    uz_PWM_SS_2L_set_tristate(data->objects.project_wizard_pwm_2l_1, !enable_prime_mover, !enable_prime_mover, !enable_prime_mover);
    // Unused PWM groups remain disabled in either backend.
    uz_PWM_SS_2L_set_tristate(data->objects.project_wizard_pwm_2l_2, true, true, true);
    uz_PWM_SS_2L_set_tristate(data->objects.project_wizard_pwm_2l_3, true, true, true);
    uz_inverter_adapter_set_PWM_EN(data->objects.inverter_adapter_d1, enable_dut);
    uz_inverter_adapter_set_PWM_EN(data->objects.inverter_adapter_d2, enable_prime_mover);
}

void deskbench_step(DS_Data* data, platform_state_t state)
{
    static bool was_active = true; // Also initialize the stopped plant on first ISR.
    static platform_state_t previous_state = idle_state;
    bool mode_changed = false;
    if (state == idle_state &&
        (data->rasv.requested_dut_backend == DUT_BACKEND_CIL ||
         data->rasv.requested_dut_backend == DUT_BACKEND_DESKBENCH))
    {
        mode_changed = data->av.dut_backend != data->rasv.requested_dut_backend;
        data->av.dut_backend = data->rasv.requested_dut_backend;
    }
    // Reject requests made outside idle rather than deferring a surprise switch.
    data->rasv.requested_dut_backend = data->av.dut_backend;
    data->av.snd_fld[4] = (float)data->av.dut_backend;
    bool cil = data->av.dut_backend == DUT_BACKEND_CIL;
    data->av.deskbench_inputs_ready = deskbench_read_measurements(data);
    bool healthy = uz_pmsm_control_get_safe_operating_area_violation(data->objects.dut) == uz_pmsm_control_no_violation;
    if (!cil)
        healthy = healthy && uz_pmsm_control_get_safe_operating_area_violation(data->objects.prime_mover) == uz_pmsm_control_no_violation;
    // DUT feedback: A1 + D5_1; prime-mover feedback: A2 + D5_2.
    bool active = state == control_state && healthy;
    bool dut_active = active && (cil || data->av.deskbench_inputs_ready);
    bool stopped = state != previous_state && (state == idle_state || state == error_state);
    if (mode_changed || (!active && was_active) || stopped)
    {
        clear_references(data);
        uz_pmsm_control_reset(data->objects.dut);
        uz_pmsm_control_reset(data->objects.prime_mover);
        // CIL reset only: physical machines are disabled through apply_outputs.
        data->av.pmsm_cil_inputs = (struct uz_pmsmModel_inputs_t){0};
        reset_uz_pmsm_cil(data->objects.pmsm_cil);
    }
    was_active = active;
    previous_state = state;

    if (cil)
    {
        uz_pmsmModel_trigger_input_strobe(data->objects.pmsm_cil);
        uz_pmsmModel_trigger_output_strobe(data->objects.pmsm_cil);
        data->av.pmsm_cil_outputs = uz_pmsmModel_get_outputs(data->objects.pmsm_cil);
        data->av.dut_measurements = pmsm_cil_get_control_measurements(
            data->av.pmsm_cil_outputs, data->av.pmsm_cil_inputs,
            data->rasv.pmsm_cil_dc_link_voltage_V, data->av.isr_samplerate_s);
    }
    if (data->rasv.dut_acknowledge_error)
    {
        if (state != control_state)
        {
            uz_pmsm_control_acknowledge_and_reset_error(data->objects.dut, data->av.dut_measurements);
            uz_pmsm_control_acknowledge_and_reset_error(data->objects.prime_mover, data->av.prime_mover_measurements);
        }
        data->rasv.dut_acknowledge_error = false;
    }

    if (active)
        data->rasv.ramped_speed_ref_rpm_prime_mover = uz_ramp_step(
            data->objects.speed_ref_ramp_prime_mover, data->rasv.speed_ref_rpm_prime_mover);
    else
    {
        uz_ramp_reset(data->objects.speed_ref_ramp_prime_mover);
        data->rasv.ramped_speed_ref_rpm_prime_mover = 0.0f;
    }
    uz_pmsm_control_enable(data->objects.dut, dut_active);
    uz_pmsm_control_enable(data->objects.prime_mover, active && !cil);
    struct uz_DutyCycle_t dut_duty = {0};
    uz_3ph_dq_t voltage = {0};
    if (cil)
        voltage = uz_pmsm_control_sample_dq(data->objects.dut, data->av.dut_measurements,
            0.0f, data->rasv.dut_current_reference_A, 0.0f);
    else
        dut_duty = uz_pmsm_control_sample_duty(data->objects.dut, data->av.dut_measurements,
            0.0f, data->rasv.dut_current_reference_A, 0.0f);
    struct uz_DutyCycle_t prime_mover_duty = uz_pmsm_control_sample_duty(
        data->objects.prime_mover, data->av.prime_mover_measurements,
        data->rasv.ramped_speed_ref_rpm_prime_mover, (uz_3ph_dq_t){0}, 0.0f);
    data->av.dut_measured_currents_dq_A = uz_pmsm_control_get_actual_data(data->objects.dut)->i_dq_in_A;
    data->av.prime_mover_measured_currents_dq_A = uz_pmsm_control_get_actual_data(data->objects.prime_mover)->i_dq_in_A;
    data->av.dut_speed_rpm = uz_pmsm_control_get_actual_data(data->objects.dut)->speed_in_rpm;
    data->av.prime_mover_speed_rpm = uz_pmsm_control_get_actual_data(data->objects.prime_mover)->speed_in_rpm;
    data->av.dut_violation = uz_pmsm_control_get_safe_operating_area_violation(data->objects.dut);
    data->av.prime_mover_violation = uz_pmsm_control_get_safe_operating_area_violation(data->objects.prime_mover);
    bool tripped = data->av.dut_violation != uz_pmsm_control_no_violation ||
        (!cil && data->av.prime_mover_violation != uz_pmsm_control_no_violation);
    if (tripped)
    {
        clear_references(data);
        uz_pmsm_control_enable(data->objects.dut, false);
        uz_pmsm_control_enable(data->objects.prime_mover, false);
        uz_pmsm_control_reset(data->objects.dut);
        uz_pmsm_control_reset(data->objects.prime_mover);
    }
    // Reset retains the last internal current setpoints; display zero when inactive.
    data->av.prime_mover_reference_currents_dq_A = active && !cil && !tripped
        ? uz_pmsm_control_get_reference_values(data->objects.prime_mover)->i_dq_in_A
        : (uz_3ph_dq_t){0};
    if (cil)
    {
        data->av.pmsm_cil_inputs.v_d_V = voltage.d;
        data->av.pmsm_cil_inputs.v_q_V = voltage.q;
        data->av.pmsm_cil_inputs.omega_mech_1_s =
            -(UZ_PIf / 30.0f) * data->rasv.ramped_speed_ref_rpm_prime_mover;
        uz_pmsmModel_set_inputs(data->objects.pmsm_cil, data->av.pmsm_cil_inputs);
    }
    // STOP and either controller's trip disable BOTH physical inverters.
    // This is output shutdown, not a controlled mechanical deceleration.
    bool closed_loop_enable = !cil && active && !tripped;
    apply_outputs(data, dut_duty, prime_mover_duty,
        closed_loop_enable && data->av.deskbench_inputs_ready, closed_loop_enable);
}
