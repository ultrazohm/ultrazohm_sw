#include "../include/deskbench.h"
#include "../include/dut.h"
#include "../include/experiment_manager.h"
#include "../include/pmsm_cil.h"
#include <math.h>

static bool valid_duty_cycle(float duty)
{
    return isfinite(duty) && duty >= 0.0f && duty <= 1.0f;
}

bool deskbench_set_prime_mover_duty_cycle(DS_Data* data, float duty)
{
    if (!valid_duty_cycle(duty)) return false;
    data->rasv.prime_mover_duty_cycle_ref = duty;
    data->av.snd_fld[4] = duty;
    return true;
}

void deskbench_cancel_prime_mover_duty_cycle(DS_Data* data)
{
    data->rasv.prime_mover_duty_cycle_applied = 0.5f;
    data->rasv.prime_mover_duty_phase = PRIME_MOVER_DUTY_NONE;
    data->av.prime_mover_duty_active = false;
}

bool deskbench_apply_prime_mover_duty_cycle(DS_Data* data, platform_state_t state,
    enum prime_mover_duty_phase phase)
{
    if (data->av.dut_backend != DUT_BACKEND_DUTY_CYCLE || state != control_state ||
        !data->av.deskbench_inputs_ready ||
        phase < PRIME_MOVER_DUTY_A || phase > PRIME_MOVER_DUTY_C ||
        !valid_duty_cycle(data->rasv.prime_mover_duty_cycle_ref) ||
        uz_pmsm_control_get_safe_operating_area_violation(data->objects.prime_mover) != uz_pmsm_control_no_violation)
        return false;
    data->rasv.prime_mover_duty_cycle_applied = data->rasv.prime_mover_duty_cycle_ref;
    data->rasv.prime_mover_duty_phase = phase;
    return true;
}

static void clear_references(DS_Data* data)
{
    data->rasv.speed_ref_rpm_prime_mover = 0.0f;
    data->rasv.ramped_speed_ref_rpm_prime_mover = 0.0f;
    data->rasv.dut_current_reference_A = (uz_3ph_dq_t){0};
    for (unsigned i = 1; i <= 3; i++) data->av.snd_fld[i] = 0.0f;
    uz_ramp_reset(data->objects.speed_ref_ramp_prime_mover);
    // Keep the pending field-4 value; a fresh phase-button press is required to apply it.
    deskbench_cancel_prime_mover_duty_cycle(data);
}

static bool deskbench_read_measurements(DS_Data* data)
{
    // Run continuously in every state/backend so STOP does not discard PLL lock.
    // Physical controllers use PLL velocity; CIL retains simulated feedback.
    uz_pos_to_speed_pll_step(data->objects.dut_speed_pll,
        data->av.resolver_pl_interface_d5_1_position_mech_2pi);
    uz_pos_to_speed_pll_step(data->objects.prime_mover_speed_pll,
        data->av.ssi_encoder_d4_1_position_mech_si_single_turn);
    /* D1 inverter A/B -> A1 ADC A/B; D2 inverter A/B -> A2 ADC A/B.
     * A1, A2, D4 SSI and D5 resolver readout precede this call.
     * PMSM control needs mechanical rad and rad/s and applies the machine pole-pair count internally.
     * D4 SSI alignment is applied by the encoder driver; retain the prime-mover speed PLL.
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
        .theta_mech = data->av.ssi_encoder_d4_1_position_mech_si_single_turn,
        .omega_mech_rad_per_sec = uz_pos_to_speed_pll_get_omega_mech_si(data->objects.prime_mover_speed_pll)
    };
    if (data->av.dut_backend == DUT_BACKEND_DESKBENCH || data->av.dut_backend == DUT_BACKEND_DUTY_CYCLE)
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
            .omega_mech_rad_per_sec = uz_pos_to_speed_pll_get_omega_mech_si(data->objects.dut_speed_pll)
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
         data->rasv.requested_dut_backend == DUT_BACKEND_DESKBENCH ||
         data->rasv.requested_dut_backend == DUT_BACKEND_DUTY_CYCLE))
    {
        mode_changed = data->av.dut_backend != data->rasv.requested_dut_backend;
        data->av.dut_backend = data->rasv.requested_dut_backend;
    }
    // Reject requests made outside idle rather than deferring a surprise switch.
    data->rasv.requested_dut_backend = data->av.dut_backend;
    bool cil = data->av.dut_backend == DUT_BACKEND_CIL;
    bool manual_duty = data->av.dut_backend == DUT_BACKEND_DUTY_CYCLE;
    data->av.deskbench_inputs_ready = deskbench_read_measurements(data);
    // The DUT remains disabled in manual mode; only prime-mover protection gates that output.
    bool healthy = manual_duty || uz_pmsm_control_get_safe_operating_area_violation(data->objects.dut) == uz_pmsm_control_no_violation;
    if (!cil)
        healthy = healthy && uz_pmsm_control_get_safe_operating_area_violation(data->objects.prime_mover) == uz_pmsm_control_no_violation;
    // DUT feedback: A1 + D5_1 resolver; prime-mover feedback: A2 + D4_1 SSI.
    bool active = state == control_state && healthy;
    bool dut_active = !manual_duty && active && (cil || data->av.deskbench_inputs_ready);
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
        uz_pmsmModel_trigger_output_strobe(data->objects.pmsm_cil);
        uz_pmsmModel_trigger_input_strobe(data->objects.pmsm_cil);
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

    if (active && !manual_duty)
        data->rasv.ramped_speed_ref_rpm_prime_mover = uz_ramp_step(
            data->objects.speed_ref_ramp_prime_mover, data->rasv.speed_ref_rpm_prime_mover);
    else
    {
        uz_ramp_reset(data->objects.speed_ref_ramp_prime_mover);
        data->rasv.ramped_speed_ref_rpm_prime_mover = 0.0f;
    }
    // One experiment update per control ISR, before either DUT backend consumes iq.
    bool experiment_owned_iq = experiment_manager_owns_iq();
    experiment_manager_update(dut_active, (unsigned)data->av.dut_backend,
        &data->rasv.dut_current_reference_A.q);
    if (experiment_owned_iq || experiment_manager_owns_iq())
        data->av.snd_fld[3] = data->rasv.dut_current_reference_A.q;

    uz_pmsm_control_enable(data->objects.dut, dut_active);
    uz_pmsm_control_enable(data->objects.prime_mover, active && !cil && !manual_duty);
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
    data->av.dut_torque_Nm = dut_estimate_torque_Nm(data->av.dut_measured_currents_dq_A);
    data->av.dut_speed_rpm = uz_pmsm_control_get_actual_data(data->objects.dut)->speed_in_rpm;
    data->av.dut_violation = uz_pmsm_control_get_safe_operating_area_violation(data->objects.dut);
    data->av.prime_mover_violation = uz_pmsm_control_get_safe_operating_area_violation(data->objects.prime_mover);
    bool tripped = (!manual_duty && data->av.dut_violation != uz_pmsm_control_no_violation) ||
        (!cil && data->av.prime_mover_violation != uz_pmsm_control_no_violation);
    if (tripped)
    {
        experiment_manager_abort(&data->rasv.dut_current_reference_A.q);
        clear_references(data);
        uz_pmsm_control_enable(data->objects.dut, false);
        uz_pmsm_control_enable(data->objects.prime_mover, false);
        uz_pmsm_control_reset(data->objects.dut);
        uz_pmsm_control_reset(data->objects.prime_mover);
    }
    // Scope references are the controller's limited commands; clear when disabled.
    const struct uz_pmsm_reference_values *dut_ref = uz_pmsm_control_get_reference_values(data->objects.dut);
    data->av.dut_reference_currents_dq_A = dut_active && !tripped ? dut_ref->i_dq_in_A : (uz_3ph_dq_t){0};
    data->av.dut_reference_voltages_dq_V = dut_active && !tripped ? dut_ref->v_dq_in_V : (uz_3ph_dq_t){0};
    data->av.dut_theta_el_rad = uz_pmsm_control_get_actual_data(data->objects.dut)->theta_el;
    if (cil)
    {
        data->av.pmsm_cil_inputs.v_d_V = voltage.d;
        data->av.pmsm_cil_inputs.v_q_V = voltage.q;
        data->av.pmsm_cil_inputs.omega_mech_1_s =
            -(UZ_PIf / 30.0f) * data->rasv.ramped_speed_ref_rpm_prime_mover;
        uz_pmsmModel_set_inputs(data->objects.pmsm_cil, data->av.pmsm_cil_inputs);
    }
    // Physical outputs require control_state and healthy feedback for the selected mode.
    // This is output shutdown, not a controlled mechanical deceleration.
    bool closed_loop_enable = !cil && !manual_duty && active && !tripped;
    if (!manual_duty || !active || tripped)
        deskbench_cancel_prime_mover_duty_cycle(data);
    bool manual_enable = manual_duty && active && !tripped && data->av.deskbench_inputs_ready &&
        valid_duty_cycle(data->rasv.prime_mover_duty_cycle_applied) &&
        data->rasv.prime_mover_duty_phase >= PRIME_MOVER_DUTY_A &&
        data->rasv.prime_mover_duty_phase <= PRIME_MOVER_DUTY_C;
    if (manual_duty)
    {
        // Disabled controller sampling above still updates protection before any PWM is enabled.
        prime_mover_duty = (struct uz_DutyCycle_t){.DutyCycle_A = 0.5f, .DutyCycle_B = 0.5f, .DutyCycle_C = 0.5f};
        if (manual_enable)
        {
            switch (data->rasv.prime_mover_duty_phase)
            {
            case PRIME_MOVER_DUTY_A: prime_mover_duty.DutyCycle_A = data->rasv.prime_mover_duty_cycle_applied; break;
            case PRIME_MOVER_DUTY_B: prime_mover_duty.DutyCycle_B = data->rasv.prime_mover_duty_cycle_applied; break;
            case PRIME_MOVER_DUTY_C: prime_mover_duty.DutyCycle_C = data->rasv.prime_mover_duty_cycle_applied; break;
            default: break;
            }
        }
    }
    data->av.prime_mover_duty_active = manual_enable;
    apply_outputs(data, dut_duty, prime_mover_duty,
        closed_loop_enable && data->av.deskbench_inputs_ready, closed_loop_enable || manual_enable);
}
