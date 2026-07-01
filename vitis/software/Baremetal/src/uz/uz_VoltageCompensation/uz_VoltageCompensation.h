#ifndef UZ_VOLTAGECOMPENSATION_H
#define UZ_VOLTAGECOMPENSATION_H

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "../uz_HAL.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_Space_Vector_Modulation/uz_space_vector_modulation.h"

/**
 * @brief Configuration struct for VoltageCompensation. Accessible by the user
 */
enum uz_VoltageCompensation_dead_time_compensation_type {
    UZ_VOLTAGE_COMPENSATION_DEAD_TIME_USE_LOOKUP_TABLE = 0,
    UZ_VOLTAGE_COMPENSATION_DEAD_TIME_USE_EXPONENTIAL_FUNCTION = 1
};

struct uz_VoltageCompensation_config {
    float dead_time_us; /**< Dead time in microseconds */
    float switching_frequency_Hz; /**< Switching frequency in Hz */
    bool enable_dead_time_compensation; /**< Enable dead time compensation */
    bool enable_on_delay_time_compensation; /**< Enable compensation of on-delay-time of transistor and diode */
    bool enable_voltage_drop_compensation; /**< Enable diode and transistor voltage drop compensation */
    bool enable_R_on_compensation;
    float R_on_mOhm; // Resistance of R_ds,on and AC-Busbar
    float threshold_current; // Half-width of the smooth sign transition around 0 A
    enum uz_VoltageCompensation_dead_time_compensation_type dead_time_compensation_type; /**< Select LUT or exponential function inside threshold */
    float dead_time_exp_A; /**< Parameter A of exponential dead-time characteristic */
    float dead_time_exp_B; /**< Parameter B of exponential dead-time characteristic */
    float dead_time_exp_C; /**< Parameter C of exponential dead-time characteristic */
    float dead_time_exp_S; /**< Parameter S of exponential dead-time characteristic */
    float* dead_time_lut_currents_A; /**< Current support points of dead-time lookup table in A */
    float* dead_time_lut_values; /**< Corresponding normalized dead-time compensation values */
    int dead_time_lut_size; /**< Size of dead-time lookup table */
    float* diode_currents_A; /**< Array of current values for diode voltage drop lookup */
    float* diode_voltages_V; /**< Array of corresponding voltage drop values for diode */
    int diode_table_size; /**< Size of the diode lookup table */
    float* transistor_currents_A; /**< Array of current values for transistor voltage drop lookup */
    float* transistor_voltages_V; /**< Array of corresponding voltage drop values for transistor */
    int transistor_table_size; /**< Size of the transistor lookup table */
    float* transistor_delay_time_s; /**< Array of delay-time values for transistor */
    float* transistor_delay_time_current_A; /**< Array of current values to delay times */
    int transistor_delay_time_table_size; /**< Size of the transistor lookup table */
    float* diode_delay_time_s; /**< Array of delay-time values for transistor */
    float* diode_delay_time_current_A; /**< Array of current values to delay times */
    int diode_delay_time_table_size; /**< Size of the transistor lookup table */
};

/**
 * @brief Object definition for VoltageCompensation
 */
typedef struct uz_VoltageCompensation_t uz_VoltageCompensation_t;

/**
 * @brief Initialization of the uz_VoltageCompensation object
 *
 * @param config configuration struct for VoltageCompensation
 * @return uz_VoltageCompensation_t* Pointer to uz_VoltageCompensation_t instance
 */
uz_VoltageCompensation_t* uz_VoltageCompensation_init(struct uz_VoltageCompensation_config config);

/**
 * @brief Compensates the reference duty cycles for dead time and other voltage errors
 *
 * @param self uz_VoltageCompensation_t instance
 * @param duty_cycle_ref Reference duty cycles in abc frame (0 to 1)
 * @param i_actual_abc_A Actual currents in abc frame
 * @param dc_link_voltage_V DC link voltage in V
 * @return uz_3ph_abc_t Compensated duty cycles
 */
struct uz_DutyCycle_t uz_VoltageCompensation_sample(uz_VoltageCompensation_t* self, struct uz_DutyCycle_t duty_cycle_ref, uz_3ph_abc_t i_actual_abc_A, float dc_link_voltage_V);

#endif // UZ_VOLTAGECOMPENSATION_H
