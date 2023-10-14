.. _uz_ParaID_6ph_setup:

======================================
Setup and functions of the ParameterID
======================================

This page details the steps to setup the ParameterID in the UltraZohm software project. 

Setup
=====

.. code-block:: c
  :linenos:
  :caption: init ParaID 6ph in init_ParameterID_6ph.c 

  #define ADDITIONAL_SYSTEM_LIMIT 10.0f
  #define SAMPLETIME (UZ_PWM_FREQUENCY/INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE)
  #define RESONANT_ANTIWINDUP_GAIN 10.0f

  extern DS_Data Global_Data;
  extern uz_ParameterID_Data_t ParaID_Data = { 0 };

  // Controller inits
  struct uz_PI_Controller_config PI_config_dq = {
     .Ki = 1000.0f,
     .Kp = 5.0f,
     .samplingTime_sec = };
  struct uz_CurrentControl_config cc_config_dq = {
     .decoupling_select = linear_decoupling,
     .config_id = PI_config_dq,
     .config_iq = PI_config_dq,
     .config_PMSM = ParaID_Data.GlobalConfig.PMSM_config,
     .max_modulation_index = 0.5f};
  struct uz_PI_Controller_config PI_config_xy = {
     .Ki = 500.0f,
     .Kp = 15.0f,
     .samplingTime_sec = SAMPLETIME};
  struct uz_CurrentControl_config cc_config_2 = {
     .decoupling_select = no_decoupling,
     .config_id = PI_config_xy,
     .config_iq = PI_config_xy,
     .max_modulation_index = 0.5f};
  struct uz_PI_Controller_config PI_config_zero = {
     .Ki = 100.0f,
     .Kp = 15.0f,
     .samplingTime_sec = SAMPLETIME};
  struct uz_CurrentControl_config cc_config_zero = {
     .decoupling_select = no_decoupling,
     .config_id = PI_config_zero,
     .config_iq = PI_config_zero,
     .max_modulation_index = 0.5f};
  struct uz_subspace_resonant_control_config resonant_config_dq = {
    .sampling_time = SAMPLETIME,
    .gain_1 = 1000.0f,
    .gain_2 = 1000.0f,
    .harmonic_order = 2.0f,
    .lower_limit = -ADDITIONAL_SYSTEM_LIMIT,
    .upper_limit = ADDITIONAL_SYSTEM_LIMIT,
    .antiwindup_gain = RESONANT_ANTIWINDUP_GAIN};
  struct uz_subspace_resonant_control_config resonant_config_xy = {
    .sampling_time = SAMPLETIME,
    .gain_1 = 1000.0f,
    .gain_2 = 1000.0f,
    .harmonic_order = 6.0f,
    .lower_limit = -ADDITIONAL_SYSTEM_LIMIT,
    .upper_limit = ADDITIONAL_SYSTEM_LIMIT,
    .antiwindup_gain = RESONANT_ANTIWINDUP_GAIN};
  struct uz_subspace_resonant_control_config resonant_config_zero = {
    .sampling_time = SAMPLETIME,
    .gain_1 = 1000.0f,
    .gain_2 = 1000.0f,
    .harmonic_order = 6.0f,
    .lower_limit = -ADDITIONAL_SYSTEM_LIMIT,
    .upper_limit = ADDITIONAL_SYSTEM_LIMIT,
    .antiwindup_gain = RESONANT_ANTIWINDUP_GAIN};
  struct uz_SetPoint_config setpoint_config = {
     .id_ref_Ampere = 0.0f,
     .is_field_weakening_enabled = false,
     .motor_type = SMPMSM,
     .control_type = FOC,
     .config_PMSM = ParaID_Data.GlobalConfig.PMSM_config};
  struct uz_SpeedControl_config speed_config = { 
     .config_controller.type = parallel, 
     .config_controller.Kp = 1.0f, 
     .config_controller.Ki = 1.0f,
     .config_controller.samplingTime_sec = SAMPLETIME,
     .config_controller.upper_limit = 10.0f, 
     .config_controller.lower_limit = -10.0f};
  
  struct uz_ParameterID_controller init_uz_ParameterID_6ph_controllers(void){
     struct uz_ParameterID_controller out = {
          .SC_instance = uz_SpeedControl_init(speed_config),
          .SP_instance = uz_SetPoint_init(setpoint_config),
          .CC_instance_dq = uz_CurrentControl_init(cc_config_dq),
          .CC_instance_xy = uz_CurrentControl_init(cc_config_xy),
          .CC_instance_zero = uz_CurrentControl_init(cc_config_zero),
          .res_instance_dq = uz_subspace_resonant_control_init(resonant_config_dq),
          .res_instance_xy = uz_subspace_resonant_control_init(resonant_config_xy),
          .res_instance_zero = uz_subspace_resonant_control_init(resonant_config_zero)};
     return out;
  }

  struct uz_IIR_Filter_config config_filter = {.selection = LowPass_first_order, .cutoff_frequency_Hz = 1.0f, .sample_frequency_Hz = 10000.0f};

  uz_ParameterID_6ph_t init_uz_ParameterID_6ph(void){
     uz_ParameterID_6ph_init_filter(&ParaID_Data, config_filter);
     uz_ParameterID_6ph_initialize_encoder_offset_estimation(&ParaID_Data, &Global_Data.av.theta_elec_rad, &Global_Data.rasv.controller_out.q);
     uz_ParameterID_6ph_t out = uz_ParameterID_6ph_init(&ParaID_Data);
     return out;
  }
