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
#include "rtwtypes.h"

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
  real32_T omega_m; /**< measured mechanical omega */
  real32_T omega_el; /**< measured electrical omega */
  real32_T theta_m; /**< measured mechanical theta */
  real32_T theta_el; /**< measured electrical theta */
  real32_T V_DC; /**< measured DC-link voltage */
} uz_PID_ActualValues_t;

/**
 * @brief Global configuration struct for general settings of the ParameterID
 *
 */
typedef struct {
  uz_PMSM_t PMSM_config; /**< motor related parameters. Is needed, if ElectricalID should not be executed */
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
  real32_T ratSpeed; /**< rated speed of the motor */
  uz_3ph_dq_t i_dq_ref; /**< Not needed for ID-states. Can be used to transmit reference currents to a control algorithm. */
  real32_T n_ref; /**< Not needed for ID-states. Can be used to transmit reference speed to a control algorithm. */
} uz_PID_GlobalConfig_t;


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
} uz_PID_ControlFlags_t;


/**
 * @brief struct with config values for a control algorithm
 *
 */
typedef struct {
  uz_3ph_dq_t i_dq_ref; /**< reference currents for current controller */
  uint16_T activeState; /**< activeState of the ID-states */
  real32_T n_ref_FOC; /**< reference speed for the speed controller */
  boolean_T enableFOC_speed; /**<flag to enable speed controller */
  boolean_T enableFOC_current; /**<flag to enable current controller */
  boolean_T resetIntegrator; /**<flag to reset the integrators used in the control algorithm */
  real32_T Kp_id_out; /**<Kp_id for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Kp_iq_out; /**<Kp_iq for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Kp_n_out; /**<Kp_n for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Ki_id_out; /**<Ki_id for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Ki_iq_out; /**<Ki_iq for FOC control. Can be ignored, if another control algorithm is used */
  real32_T Ki_n_out; /**<Ki_n for FOC control. Can be ignored, if another control algorithm is used */
} uz_PID_Controller_Parameters_output_t;

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
  real32_T goertzlAmp; /**< amplitude of sine wave for vibration to identify J */
  real32_T min_n_ratio; /**< minimal ratio of rated speed for automatic DutyCycle identification. i.e. 0.025f @3000rpm rated speed -> 75rpm. If this value is reached, the algorithm assumes the DutyCycle is strong enough to properly turn the rotor. */
} uz_PID_ElectricalIDConfig_t;


/**
 * @brief output struct of ElectricalID
 *
 */
typedef struct {
  real32_T PWM_Switch_0; /**< DutyCycle for PWM Switch 0 (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  real32_T PWM_Switch_2; /**< DutyCycle for PWM Switch 2 (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  real32_T PWM_Switch_4; /**< DutyCycle for PWM Switch 4 (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  boolean_T enable_TriState[3]; /**< array to signal which halfbridge of the inverter should be in tristate mode. true signals, that the halfbridge should be in tristate mode. (only needed from the start of ElectricalID, until Ld and Lq have been identified) */
  real32_T thetaOffset; /**< determined offset of theta in rad */
  uz_PMSM_t PMSM_parameters; /**< identified motor parameters */
} uz_PID_ElectricalID_output_t;

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
} uz_PID_FluxMapIDConfig_t;

/**
 * @brief output struct of FluxMapID
 *
 */
typedef struct {
  boolean_T external_Measurement_Flag; /**< trigger to signal, when an external measurement equipment should measure */
  real32_T R_s; /**< identified online resistance in ohm */
  real32_T WindingTemp; /**< identified winding temperature of the stator */
} uz_PID_FluxMapID_output_t;

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
  real32_T BrkCount; /**< amount of unique breakaway attempts */
  real32_T N_Brk; /**< amount of breakaway identification values */
  real32_T N_Visco; /**< amount of viscous friction identification values */
  real32_T StepScale; /**< scales the steps for breakaway torque. Factor in % of rated current of the motor. Should be chosen as small as possible */
  real32_T n_eva_max; /**< maximum measuring speed in rpm*/
  real32_T eta; /**< steady state speed threshold in percent */
  real32_T maxCurrent; /**< max current for identification */
} uz_PID_FrictionIDConfig_t;

/**
 * @brief output struct of FrictionID
 *
 */
typedef struct {
  real32_T BrkTorque; /**< identified breakaway torque in Nm */
  real32_T CoulTorque; /**< identified coloumb torque in Nm */
  real32_T ViscoTorque; /**< identified viscous friction in Nms/rad */
} uz_PID_FrictionID_output_t;

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
  uint8_T UseLbMq; /**< flag to use Levenberg Marquardt Algorithm */
  real32_T d_TMS_start; /**< inital damping value for LM-algorithm */
} uz_PID_TwoMassIDConfig_t;

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
} uz_PID_TwoMassID_output_t;

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
} uz_PID_OnlineIDConfig_t;

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
} uz_PID_OnlineID_output_t;

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
} uz_PID_FluxMapsData_t;

#endif
