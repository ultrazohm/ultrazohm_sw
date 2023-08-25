/******************************************************************************
 * Copyright 2021 Dennis Hufnagel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#ifndef UZ_PARAMETERID_DATA_H
#define UZ_PARAMETERID_DATA_H

#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_PMSM_config/uz_PMSM_config.h"
#include "../uz_CurrentControl/uz_CurrentControl.h"
#include "../uz_SpeedControl/uz_speedcontrol.h"
#include "../uz_setpoint/uz_setpoint.h"
#include "../uz_ResonantController/uz_resonant_controller.h"
#include "../uz_encoder_offset_estimation/uz_encoder_offset_estimation.h"
#include "../uz_controller_setpoint_filter/uz_controller_setpoint_filter.h"
#include "lib/rtwtypes.h"
#include <stdbool.h>


//----------------------------------------//
//----------------------------------------//
//------------GlobalStructs---------------//
//----------------------------------------//
//----------------------------------------//

/**
 * @brief struct for the measured values which are needed for the ParameterID
 *
 */
typedef struct {
  uz_3ph_abc_t V_abc; /**< measured three-phase voltages */
  uz_3ph_abc_t I_abc; /**< measured three-phase currents */
  uz_3ph_dq_t i_dq; /**< measured dq voltages */
  uz_3ph_dq_t v_dq; /**< measured dq currents */
  uz_6ph_abc_t v_abc_6ph; /**< measured six-phase voltages */
  uz_6ph_abc_t i_abc_6ph; /**< measured six-phase currents */
  uz_3ph_dq_t v_xy_rotating; /**< measured dq voltages */
  uz_3ph_dq_t i_xy_rotating; /**< measured dq currents */
  uz_3ph_dq_t v_zero_rotating; /**< measured dq voltages */
  uz_3ph_dq_t i_zero_rotating; /**< measured dq currents */
  uz_6ph_dq_t i_dq_6ph; /**< measured dq voltages */
  uz_6ph_dq_t v_dq_6ph; /**< measured dq currents */
  real32_T omega_m; /**< measured mechanical omega */
  real32_T omega_el; /**< measured electrical omega */
  real32_T theta_m; /**< measured mechanical theta */
  real32_T theta_el; /**< measured electrical theta */
  real32_T V_DC; /**< measured DC-link voltage */
  real32_T average_winding_temp; /**< Average winding temperature in deg C */
} uz_ParaID_ActualValues_t;

/**
 * @brief Global configuration struct for general settings of the ParameterID
 *
 */
typedef struct {
  uz_PMSM_t PMSM_config; /**< motor related parameters. Is needed, if ElectricalID should not be executed */
  uz_6ph_dq_t PMSM_6ph_inductances;
  boolean_T enableParameterID; /**< flag to enable the entire ParameterID */
  boolean_T Reset; /**< flag to Reset the entire ParameterID*/
  real32_T Kp_id; /**< value for Kp_id, which is needed, if ElectricalID should not be executed. Can be left at 0, if no FOC control algorithm is used */
  real32_T Kp_iq; /**< value for Kp_iq, which is needed, if ElectricalID should not be executed. Can be left at 0, if no FOC control algorithm is used */
  real32_T Kp_n; /**< value for Kp_n, which is needed, if ElectricalID should not be executed. Can be left at 0, if no FOC control algorithm is used */
  real32_T Ki_id; /**< value for Ki_id, which is needed, if ElectricalID should not be executed. Can be left at 0, if no FOC control algorithm is used */
  real32_T Ki_iq; /**< value for Ki_iq, which is needed, if ElectricalID should not be executed. Can be left at 0, if no FOC control algorithm is used */
  real32_T Ki_n; /**< value for Ki_n, which is needed, if ElectricalID should not be executed. Can be left at 0, if no FOC control algorithm is used */
  boolean_T ElectricalID; /**< flag to enable ElectricalID */
  boolean_T FrictionID; /**< flag to enable FrictionID */
  boolean_T TwoMassID; /**< flag to enable TwoMassID */
  boolean_T FluxMapID; /**< flag to enable FluxMapID */
  boolean_T OnlineID; /**< flag to enable OnlineID */
  boolean_T ACCEPT; /**< flag for the ACCEPT button  */
  real32_T sampleTimeISR; /**< sampleTime of the ISR. i.e. sampleTime of the function call uz_ParameterID_step. Very important parameter */
  real32_T ratCurrent; /**< rated current of the motor */
  real32_T ratTorque; /**< rated torque of the motor */
  real32_T ratSpeed; /**< rated speed of the motor */
  uz_3ph_dq_t i_dq_ref; /**< Not needed for ID-states. Can be used to transmit reference currents to a control algorithm. */
  real32_T n_ref; /**< Not needed for ID-states. Can be used to transmit reference speed to a control algorithm. */
  real32_T M_ref; /**< Not needed for ID-states. Can be used to transmit reference speed to a control algorithm. */
  uint16_T motor_type;
  real32_T voltage_measurement_C; /**< Voltage measurement: capacitor */
  real32_T voltage_measurement_Rp; /**< Voltage measurement: parallel resistor to capacitor*/
  real32_T voltage_measurement_Rs; /**< Voltage measurement: series resistor to capacitor*/
  uz_3ph_dq_t i_xy_ref; /**< Not needed for ID-states. Can be used to transmit reference currents to a control algorithm. */
  boolean_T PI_dq; /**< select PI-control in dq */
  boolean_T PI_xy; /**< select PI-control in xy */
  boolean_T PI_zero; /**< select PI-control in zero */
  boolean_T resonant_dq; /**< select resonant-control in dq */
  boolean_T resonant_xy; /**< select resonant-control in xy */
  boolean_T resonant_zero; /**< select resonant-control in zero */
  boolean_T controllers_updated; /**< controller configs updated */
  boolean_T setpoint_filter; /**< filter setpoints */
} uz_ParaID_GlobalConfig_t;


/**
 * @brief struct which contains the enable state flags
 *
 */
typedef struct {
  boolean_T startFrictionID; /**< flag to start FrictionID */
  boolean_T startElectricalID; /**< flag to start ElectricalID */
  boolean_T startTwoMassID; /**< flag to start TwoMassID */
  boolean_T startFluxMapID; /**< flag to start FluxMapID */
  uint16_T transNr; /**< transistion number. 1 transistion number corresponds to one ID-state */
  boolean_T enableOnlineID; /**< flag to start OnlineID */
  boolean_T finished_all_Offline_states; /**< flag to signal, that all OfflineID-state are finished and OnlineID-state can be started*/
} uz_ParaID_ControlFlags_t;


/**
 * @brief struct with config values for a control algorithm
 *
 */
typedef struct {
  uz_3ph_dq_t i_dq_ref; /**< reference currents for current controller */
  real32_T M_ref_FOC;  /**< reference torque for the setpoint function */
  uint16_T activeState; /**< activeState of the ID-states */
  real32_T n_ref_FOC; /**< reference speed for the speed controller */
  boolean_T enableFOC_torque; /**<flag to enable torque controller */
  boolean_T enableFOC_speed; /**<flag to enable speed controller */
  boolean_T enableFOC_current; /**<flag to enable current controller */
  boolean_T resetIntegrator; /**<flag to reset the integrators used in the control algorithm */
  real32_T Kp_id_out; /**<Kp_id for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Kp_iq_out; /**<Kp_iq for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Kp_n_out; /**<Kp_n for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Ki_id_out; /**<Ki_id for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Ki_iq_out; /**<Ki_iq for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Ki_n_out; /**<Ki_n for FOC control. Can be ignored, if another control algorithm is used */
  uz_3ph_dq_t i_xy_ref; /**< reference currents for current controller */
  uz_3ph_dq_t i_zero_ref; /**< reference currents for current controller */
  boolean_T PI_dq; /**< select PI-control in dq */
  boolean_T PI_xy; /**< select PI-control in xy */
  boolean_T PI_zero; /**< select PI-control in zero */
  boolean_T resonant_dq; /**< select resonant-control in dq */
  boolean_T resonant_xy; /**< select resonant-control in xy */
  boolean_T resonant_zero; /**< select resonant-control in zero */
  boolean_T filter_dq; /**< select setpoint filtering in dq */
  boolean_T filter_xy; /**< select setpoint filtering in xy */
  boolean_T filter_zero; /**< select setpoint filtering in zero */
  } uz_ParaID_Controller_Parameters_output_t;

//----------------------------------------//
//----------------------------------------//
//------------ElectricalID----------------//
//----------------------------------------//
//----------------------------------------//

/**
 * @brief configuration struct for ElectricalID specific settings
 *
 */
typedef struct {
  real32_T goertzlFreq; /**< frequency of sine wave for vibration to identify J */
  real32_T dutyCyc; /**< manual input for DutyCycle during identification of thetaOffset, Ld and Lq. If the value is left at 0.0f, the DutyCycle will be identified automatically. */
  real32_T n_ref_measurement; /**< reference speed for identification of Psi_PM */
  boolean_T identLq; /**< flag to enable identification of Lq. If false, Lq=Ld */
  real32_T goertzlTorque; /**< max torque of sine wave for vibration to identify J */
  real32_T min_n_ratio; /**< minimal ratio of rated speed for automatic DutyCycle identification. i.e. 0.025f @3000rpm rated speed -> 75rpm. If this value is reached, the algorithm assumes the DutyCycle is strong enough to properly turn the rotor. */
  boolean_T extended_psi; /**< Input wether extended (high) or basic (low) psi pm determination is done */
  boolean_T extended_offset; /**< Input wether extended (high) or basic (low) theta determination is done */
  real32_T manual_offset; /**< give already predetermined offset angle in rad (optional) */
} uz_ParaID_ElectricalIDConfig_t;


/**
 * @brief output struct of ElectricalID
 *
 */
typedef struct {
  real32_T PWM_Switch_0; /**< DutyCycle for PWM Switch 0 (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  real32_T PWM_Switch_2; /**< DutyCycle for PWM Switch 2 (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  real32_T PWM_Switch_4; /**< DutyCycle for PWM Switch 4 (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  real32_T PWM_Switch_a2; /**< DutyCycle for PWM Switch 6 (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  real32_T PWM_Switch_b2; /**< DutyCycle for PWM Switch 8 (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  real32_T PWM_Switch_c2; /**< DutyCycle for PWM Switch 10 (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  boolean_T enable_TriState[3]; /**< System 1: array to signal which halfbridge of the inverter should be in tristate mode. true signals, that the halfbridge should be in tristate mode. (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  boolean_T enable_TriState_set_2[3]; /**< System 2: array to signal which halfbridge of the inverter should be in tristate mode. true signals, that the halfbridge should be in tristate mode. (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  real32_T thetaOffset; /**< determined offset of theta in rad */
  uz_PMSM_t PMSM_parameters; /**< identified motor parameters */
  uz_6ph_dq_t inductances_6ph; /**< identified stator inductances */
  uz_6ph_dq_t resistances_6ph; /**< identified stator resistances */
  real32_T psi_pm[5]; /**< identified psi pm magnitudes */
  real32_T psi_pm_angle[5]; /**< identified psi pm agnles */
  real32_T set_rpm_val; /**< setpoint speed in rpm for psi pm identification */
} uz_ParaID_ElectricalID_output_t;

typedef struct {
  boolean_T finished_flag; /**< finished calculation */
  real32_T psi_pm_frequency[5]; /**< frequencies of higher orders */
  real32_T psi_pm_amplitude[5]; /**< magnitudes for each frequency */
  real32_T psi_pm_angle[5]; /**< angle for each frequency */
} uz_ParaID_ElectricalID_fft_in_t;

typedef struct {
  boolean_T finished_flag; /**< finished offset estimation */
  uz_3ph_dq_t i_dq_ref; /**< ref currents from offset estimation */
  real32_T progress; /**< progress of offset estimation */
  real32_T offset_angle_rad; /**< offset angle in rad */
} uz_ParaID_ElectricalID_offset_estimation_t;

//----------------------------------------//
//----------------------------------------//
//------------FluxMapID-------------------//
//----------------------------------------//
//----------------------------------------//

/**
 * @brief configuration struct for FluxMapID specific settings
 *
 */
typedef struct {
  real32_T AMMsampleTime; /**<settling time needed to collect all data in seconds */
  real32_T IDstart; /**< start point of the id-steps */
  real32_T IDstepsize; /**< stepsize of the id-steps */
  real32_T IDstop; /**< end point of the id-steps */
  real32_T IQstart; /**< start point of the iq-steps */
  real32_T IQstepsize; /**< stepsize of the iq-steps */
  real32_T IQstop; /**< end point of the iq-stops */
  real32_T R_s_ref; /**< reference resistance for online identification in Ohm*/
  real32_T Temp_ref; /**< reference temperature, at which the reference resistance was measured */
  boolean_T start_FM_ID; /**< flag to enable the automatic current control */
  boolean_T identR; /**< flag to enable online identification */
  real32_T identRAmp; /**< amplitude of the d-current injection signal for online identification of Rs in Amps */
  boolean_T select_dq; /**< selected dq system for identification */
  boolean_T select_xy; /**< selected xy system for identification */
  boolean_T select_zero; /**< selected zero system for identification */
  real32_T lower_meas_temp; /**< lower threshold for measurement */
  real32_T upper_meas_temp; /**< upper threshold for measurement */
} uz_ParaID_FluxMapIDConfig_t; 

/**
 * @brief output struct of FluxMapID
 *
 */
typedef struct {
  boolean_T external_Measurement_Flag; /**< trigger to signal, when an external measurement equipment should measure */
  real32_T R_s; /**< identified online resistance in ohm */
  real32_T WindingTemp; /**< identified winding temperature of the stator */
  real32_T psi_array[4]; /**< measurement values */
  uint32_T array_index; /**< index of measurement point */
} uz_ParaID_FluxMapID_output_t;

//----------------------------------------//
//----------------------------------------//
//------------FrictionID------------------//
//----------------------------------------//
//----------------------------------------//

/**
 * @brief configuration struct for FrictionID specific settings
 *
 */
typedef struct {
  uint16_T BrkCount; /**< amount of unique breakaway attempts */
  uint16_T N_Brk; /**< amount of breakaway identification values */
  uint16_T N_Visco; /**< amount of viscous friction identification values */
  real32_T StepScale; /**< scales the steps for breakaway torque. Factor in % of rated current of the motor. Should be chosen as small as possible */
  real32_T n_eva_max; /**< maximum measuring speed in rpm*/
  real32_T eta; /**< steady state speed threshold in percent */
  real32_T maxCurrent; /**< max current for identification */
} uz_ParaID_FrictionIDConfig_t;

/**
 * @brief output struct of FrictionID
 *
 */
typedef struct {
  real32_T measArrayTorque[256]; /**< measured torque values for friction curve */
  real32_T measArraySpeed[256]; //*< measured speed values for friction curve */
  real32_T BrkTorque; /**< identified breakaway torque in Nm */
  real32_T CoulTorque; /**< identified coloumb torque in Nm */
  real32_T ViscoTorque; /**< identified viscous friction in Nms/rad */
} uz_ParaID_FrictionID_output_t;

//----------------------------------------//
//----------------------------------------//
//------------TwoMassID-------------------//
//----------------------------------------//
//----------------------------------------//

/**
 * @brief configuration struct for TwoMassID specific settings
 *
 */
typedef struct {
  real32_T ScaleTorquePRBS; /**< current amplitude of PRBS excitation */
  real32_T n_ref_measurement; /** reference speed for identification */
  uint16_T f_max; /**< maximum evaluation frequency */
  uint16_T f_min; /**< minimum evaluation frequency */
  boolean_T UseLbMq; /**< flag to use Levenberg Marquardt Algorithm */
  real32_T d_TMS_start; /**< inital damping value for LM-algorithm */
} uz_ParaID_TwoMassIDConfig_t;

/**
 * @brief output struct of TwoMassID
 *
 */
typedef struct {
  real32_T PRBS_out; /**< output of excitation signal. Has to added on top of the speedcontrol q_reference_current */
  real32_T c_est_out; /**< identified TMS stiffness in Nm/rad */
  real32_T d_est_out; /**< identified TMS damping in Nms/rad */
  real32_T LoadInertia; /**< identified inertia of the load in kgm² */
  real32_T TrainInertia; /**< identified inertia of the total system in kgm² */
  real32_T rotorInertia; /**< identified inertia of the motor in kgm² */
} uz_ParaID_TwoMassID_output_t;

//----------------------------------------//
//----------------------------------------//
//------------OnlineID--------------------//
//----------------------------------------//
//----------------------------------------//

/**
 * @brief configuration struct for TwoMassID specific settings
 *
 */
typedef struct {
  boolean_T OnlineID_Reset; /**< flag to reset the OnlineID state*/
  real32_T Temp_ref; /**< reference temperature for identification of the winding temperature of the motor */
  real32_T dev_omega; /**< scale factor to determine the tolerance band for the speed during steady-state detection. Default value is 0.05.*/
  real32_T dev_curr; /**< scale factor to determine the tolerance band for the dq-currents during steady-state detection. Default value is 0.05.*/
  real32_T identRAmp; /**< amplitude for d-current injection signal for identification of linear parameters */
  boolean_T AverageTransParams; /**< flag to enable the averaging of identified linear parameters */
  real32_T nom_factor; /**< eactor for rated current,to determine in which interval the linear Parameters will be identified. i.e. 0.5*I_n */
  real32_T Rs_time; /**< enter value in seconds. Determines, after which time the linear Parameters have to be identified again, even if the currents are outside the interval determined by nom_factor. */
  boolean_T allowPsiCalcOutside; /**< false: Flux maps will only be calculated, if linear parameters have been identified inside the valid range. Flux maps will only be calculated again, if the machine is in the valid range. \n
               true:Flux maps will always be calculated, even if the linear parameters were identified outside of range. */
  real32_T min_n_ratio; /**< factor for rated speed to determine the lower end in which interval the linear Parameters will be identified. i.e. 0.1*n_n. */
  real32_T max_n_ratio; /**< factor for rated speed to determine the upper end in which interval the linear Parameters will be identified. i.e. 0.9*n_n. */
	boolean_T array_cleaned; /**< flag to signal, that the flux map array has been cleaned */
} uz_ParaID_OnlineIDConfig_t;

/**
 * @brief output struct for OnlineID
 *
 */
typedef struct {
  real32_T id_out; /**< output for the d-current injection signal */
  real32_T Rph_out; /**< identified online resistance */
  real32_T Wtemp; /**< identified online winding temperature */
  real32_T psi_array[600]; /**< array storing all the measured flux map for each unique operating point of the motor */
  boolean_T IdControlFlag; /**< flag to signal, if the injection d-current is active */
  real32_T delta_psi[200]; /**< array storing the temperature dependent psi_pm values for all the operating points */
  uint16_T activeState; /**< activeState output of the OnlineID state */
  real32_T psi_pm_out; /**< identified Psi_PM */
  real32_T Ld_out; /**< identified Lq */
  real32_T Lq_out; /**< identified Ld */
	boolean_T clean_array; /**< flag to signal, that a new flux measurement point got saved in the array and it needs to be cleaned */
} uz_ParaID_OnlineID_output_t;

/**
 * @brief configuration struct for AutoRefCurrents config specific settings
 * 
 */
typedef struct {
  boolean_T enableCRS; /**< flag to enable the state */ 
  boolean_T Reset; /**< flag to reset the state */
  real32_T iq_points; /**< amount of iq-points that will be cycled through */
  real32_T id_points; /**< amount of id-points that will be cycled through */
  real32_T max_current; /**< max combined current for the generator */
} uz_ParaID_AutoRefCurrentsConfig_t;

/**
 * @brief output struct for AutoRefCurrents
 *
 */
typedef struct {
  uz_3ph_dq_t i_dq_ref; /**<reference dq-currents */
} uz_ParaID_AutoRefCurrents_output_t;

/**
 * @brief struct which contains the calculated fluxmaps of the OnlineID state
 *
 */
typedef struct {
	real32_T psid_grid[400]; /**< array of calculated values for Psi_D fluxmap*/
	real32_T psiq_grid[400]; /**< array of calculated values for Psi_Q fluxmap */
	real32_T id_grid[400]; /**< array of calculated values for i_d inverse fluxmap*/
	real32_T iq_grid[400]; /**< array of calculated values for i_q inverse fluxmap*/
	real32_T range_id_Y[20]; /**< y-values for i_d inverse fluxmap*/
	real32_T range_psid_Y[20]; /**< y-values for Psi_D fluxmap*/
	real32_T range_psiq_Y[20]; /**< y-values for Psi_Q fluxmap*/
	real32_T range_psid_X[20]; /**< x-values for Psi_D fluxmap*/
	real32_T range_psiq_X[20]; /**< x-values for Psi_Q fluxmap*/
	real32_T range_iq_Y[20]; /**< y-values for i_q inverse fluxmap*/
	real32_T range_iq_X[20]; /**< x-values for i_q inverse fluxmap*/
	real32_T range_id_X[20]; /**< x-values for i_d inverse fluxmap*/
	real32_T psi_temp_const; /**< estimated temperature constant of psi_pm*/
	real32_T psi_temp_error; /**< estimated error of psi_pm because of heat losses of the magnets */
} uz_ParaID_FluxMapsData_t;

//----------------------------------------//
//----------------------------------------//
//--------ParameterID_Data struct---------//
//----------------------------------------//
//----------------------------------------//

/*! enum for selection of control algorithm if all OfflineID states are finished */
enum uz_ParaID_Control_selection {
	No_Control = 0, Current_Control, Speed_Control, Torque_Control
};

/**
 * @brief Data struct to share inputs and outputs to the encapsuled uz_ParameterID_t object
 *
 */
typedef struct uz_ParameterID_Data_t {
	uz_ParaID_ActualValues_t ActualValues; /**<Input: measured values needed for the ParameterID */
	uz_ParaID_ControlFlags_t* ControlFlags; /**<Output: current values of the ControlFlags struct */
	uz_ParaID_GlobalConfig_t GlobalConfig; /**<Input: Global configuration struct for general settings of the ParameterID */
	uz_ParaID_ElectricalIDConfig_t ElectricalID_Config; /**<Input: Configuration struct for ElectricalID */
	uz_ParaID_TwoMassIDConfig_t TwoMassID_Config; /**<Input: Configuration struct for TwoMassID */
	uz_ParaID_FrictionIDConfig_t FrictionID_Config; /**<Input: Configuration struct for FrictionID */
	uz_ParaID_FluxMapIDConfig_t FluxMapID_Config; /**< Input:Configuration struct for FluxMapID */
	uz_ParaID_OnlineIDConfig_t OnlineID_Config; /**<Input: Configuration struct for  OnlineID */
	uz_ParaID_AutoRefCurrentsConfig_t AutoRefCurrents_Config; /**<Input: Configuration struct for AutoReference current generator */
	uz_ParaID_ElectricalID_output_t *ElectricalID_Output; /**<Output: Pointer to output struct of ElectricalID */
	uz_ParaID_TwoMassID_output_t *TwoMassID_Output; /**<Output: Pointer to output struct of TwoMassID */
	uz_ParaID_FrictionID_output_t *FrictionID_Output; /**<Output: Pointer to output struct of FrictionID */
	uz_ParaID_FluxMapID_output_t *FluxMapID_Output; /**<Output: Pointer to output struct of FluxMapID */
	uz_ParaID_OnlineID_output_t* OnlineID_Output; /**<Output: Pointer to output struct of OnlineID */
	uz_ParaID_Controller_Parameters_output_t Controller_Parameters;/**<Output: output struct for control algorithm (i_dq_ref / n_ref etc.) */
	uz_ParaID_AutoRefCurrents_output_t AutoRefCurrents_Output; /**<Output: output struct for reference currents of the AutoReference current generator*/
	uz_ParaID_FluxMapsData_t* FluxMap_Data; /**<Storage for calculated OnlineID FluxMaps*/
  uz_ParaID_ElectricalID_fft_in_t ElectricalID_FFT; /**< Storage for FFT which is done in main */
  uz_ParaID_ElectricalID_offset_estimation_t ElectricalID_Offset_Estimation; /**< Output: Encoder offset estimation */
 // uz_ParaID_FluxMapID_extended_controller_output_t *FluxmapID_extended_controller_Output;
	bool calculate_flux_maps; /**<status bool to signal, that the OnlineID FluxMaps should be calculated */
  bool finished_voltage_measurement; /**<status bool to signal, that voltage measurement for psi pm is finished */
  bool finished_extended_offset_estimation; /**<status bool to signal, extended encoder offset estimation is finished */
	int FluxMap_counter; /**<counter to transmit FluxMaps 1by1 to the uz_GUI */
	int FluxMap_Control_counter; /**<control counter from the GUI to sync the FluxMaps counter */
	float Psi_D_pointer; /**<current value of the FluxMap array corresponding to the value of the FluxMap_counter*/
	float Psi_Q_pointer; /**<current value of the FluxMap array corresponding to the value of the FluxMap_counter*/
	int Array_counter; /**<counter to transmit meas arrays of FrictionID 1by1 to the uz_GUI */
	int Array_Control_counter; /**<control counter from the GUI to sync the array_counter */
	float MeasArraySpeed_pointer; /**< current value of the MeasSpeedArray corresponding to the value of the array_counter*/
	float MeasArrayTorque_pointer; /**< current value of the MeasTorqueArray corresponding to the value of the array_counter*/
	float FluxMap_MeasuringPoints; /**<amount of unique measuring points for the FluxMaps */
	enum uz_ParaID_Control_selection ParaID_Control_Selection;/**< ParaID_Control_Selection \n
													0 = No_Control \n
													1 = Current_Control \n
													2 = Speed_Control\n
                          3 = Torque_Control*/
  bool OnlineID_reset_was_pressed; /**<Signals the functions in the main.c, that the reset was pressed */
} uz_ParameterID_Data_t;

/**
 * @brief Data struct to collect all controller pointers
 *
 */
struct uz_ParameterID_controller{
  uz_CurrentControl_t* CC_instance_dq; /**< current control instance for dq system */
  uz_SpeedControl_t* SC_instance; /**< speed control instance */
  uz_SetPoint_t* SP_instance; /**< setpoint instance */
}

#endif
