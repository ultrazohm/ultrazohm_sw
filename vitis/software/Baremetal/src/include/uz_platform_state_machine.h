#pragma once
#include <stdbool.h>

/**
 * @brief Exectures the central state machine of the UltraZohm once
 * 
 */
void ultrazohm_state_machine_step(void);

/**
 * @brief Sets the input signal enable system of the state machine
 * 
 * @param enable_system 
 */
void ultrazohm_state_machine_set_enable_system(bool enable_system);

/**
 * @brief Sets the input signal enable control of the state machine
 * 
 * @param enable_control 
 */
void ultrazohm_state_machine_set_enable_control(bool enable_control);

/**
 * @brief Sets the input signal stop of the state machine
 * 
 * @param stop 
 */
void ultrazohm_state_machine_set_stop(bool stop);

/**
 * @brief Sets the input signal error of the state machine
 * 
 * @param error 
 */
void ultrazohm_state_machine_set_error(bool error);

/**
 * @brief Get state of the input signal enable system
 * 
 * @return true 
 * @return false 
 */
bool ultrazohm_state_machine_get_enable_system(void);

/**
 * @brief Get state of the input signal enable control
 * 
 * @return true 
 * @return false 
 */
bool ultrazohm_state_machine_get_enable_control(void);

/**
 * @brief Special function to check if the state machine is in the state "control" - should only be used in the ISR!
 * 
 * @return true 
 * @return false 
 */
bool ultrazohm_state_machine_is_control_state(void);