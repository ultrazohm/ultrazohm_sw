.. _uz_ParaID_6ph_setup:

========================================
Information and Setup of ParameterID 6ph
========================================

This page shows the steps to setup the ParameterID in the UltraZohm software project. 
The setup process is split up in :ref:`ParaID_6ph_setup_general` and :ref:`ParaID_6ph_setup_GUI`.


.. _ParaID_6ph_general:

General Information
===================

INTRODUCE EVERYTHING


.. _ParaID_6ph_setup_general:

Setup General
=============

To initialize the ParameterID, the files ``init_ParameterID_6ph.h`` and ``init_ParameterID_6ph.c`` are created.
Make sure to include them in ``main.h`` in order to call the initialize functions from ``main.c``.
In the example code, the object pointers were added to the ``global_data`` struct.
For simplification reasons this is not shown here.
The ParameterID's cyclic calling is done in ``isr.c`` (see also the notes below).

.. code-block:: c
  :linenos:
  :caption: Initialize ParameterID_6ph in ``sw/init_ParaID_6ph/init_ParameterID_6ph.h``

  #include "../../uz/uz_global_configuration.h"
  #include "../../uz/uz_ParameterID/uz_ParameterID_6ph.h"

  #define RESONANT_LIMIT 10.0f
  #define RESONANT_ANTIWINDUP_GAIN 10.0f

  uz_ParameterID_6ph_t* init_ParaID_6ph_wrapper(void);
  struct uz_ParameterID_controller init_ParaID_6ph_controller(void);
  void init_ParaID_6ph_misc(void);


.. code-block:: c
  :linenos:
  :caption: Initialize ParameterID_6ph in ``sw/init_ParaID_6ph/init_ParameterID_6ph.c``

  #include "init_ParaID_6ph.h"

  // Para ID
  uz_ParameterID_Data_t ParaID_Data = { 0 };
  extern uz_6ph_dq_t controller_out;

  uz_ParameterID_6ph_t* init_ParaID_6ph_wrapper(void){
    return uz_ParameterID_6ph_init(&ParaID_Data);
  }

  // Para ID Controller
  const struct uz_PI_Controller_config PI_config_d = {
    .Ki = 40.0f,
	 .Kp = 0.1f,
	 .samplingTime_sec = INTERRUPT_ISR_SOURCE_USER_CHOICE/UZ_PWM_FREQUENCY};
  const struct uz_PI_Controller_config PI_config_q = {
	 .Ki = 45.0f,
	 .Kp = 0.1f,
	 .samplingTime_sec = INTERRUPT_ISR_SOURCE_USER_CHOICE/UZ_PWM_FREQUENCY};
  const struct uz_PI_Controller_config PI_config_x = {
	 .Ki = 40.0f,
	 .Kp = 0.05f,
	 .samplingTime_sec = INTERRUPT_ISR_SOURCE_USER_CHOICE/UZ_PWM_FREQUENCY};
  const struct uz_PI_Controller_config PI_config_y = {
	 .Ki = 45.0f,
	 .Kp = 0.05f,
	 .samplingTime_sec = INTERRUPT_ISR_SOURCE_USER_CHOICE/UZ_PWM_FREQUENCY};
  struct uz_CurrentControl_config cc_config_dq = {
	 .decoupling_select = linear_decoupling,
	 .config_id = PI_config_d,
	 .config_iq = PI_config_q,
	 .max_modulation_index = 0.5f};
  struct uz_CurrentControl_config cc_config_xy_z = {
	 .decoupling_select = no_decoupling,
	 .config_id = PI_config_x,
	 .config_iq = PI_config_y,
	 .max_modulation_index = 0.5f};
  struct uz_subspace_resonant_control_config resonant_dq = {
	 .antiwindup_gain = RESONANT_ANTIWINDUP_GAIN,
	 .gain_1 = 50.0f,
	 .gain_2 = 50.0f,
	 .harmonic_order = 2.0f,
	 .lower_limit = -RESONANT_LIMIT,
	 .upper_limit = RESONANT_LIMIT,
	 .sampling_time = INTERRUPT_ISR_SOURCE_USER_CHOICE/UZ_PWM_FREQUENCY};
  struct uz_subspace_resonant_control_config resonant_xy = {
	 .antiwindup_gain = RESONANT_ANTIWINDUP_GAIN,
	 .gain_1 = 200.0f,
	 .gain_2 = 200.0f,
	 .harmonic_order = 6.0f,
	 .lower_limit = -RESONANT_LIMIT,
	 .upper_limit = RESONANT_LIMIT,
	 .sampling_time = INTERRUPT_ISR_SOURCE_USER_CHOICE/UZ_PWM_FREQUENCY};
  struct uz_subspace_resonant_control_config resonant_zero = {
	 .antiwindup_gain = RESONANT_ANTIWINDUP_GAIN,
	 .gain_1 = 50.0f,
	 .gain_2 = 50.0f,
	 .harmonic_order = 6.0f,
	 .lower_limit = -RESONANT_LIMIT,
	 .upper_limit = RESONANT_LIMIT,
	 .sampling_time = INTERRUPT_ISR_SOURCE_USER_CHOICE/UZ_PWM_FREQUENCY};
  struct uz_SpeedControl_config speed_config = {
	 .config_controller.type = parallel,
	 .config_controller.Kp = 1.0f,
	 .config_controller.Ki = 1.0f,
	 .config_controller.samplingTime_sec =  INTERRUPT_ISR_SOURCE_USER_CHOICE/UZ_PWM_FREQUENCY,
	 .config_controller.upper_limit = 10.0f,
	 .config_controller.lower_limit = -10.0f };
  struct uz_SetPoint_config sp_config = {
	 .id_ref_Ampere = 0.0f,
	 .is_field_weakening_enabled = false,
	 .motor_type = SMPMSM,
	 .control_type = FOC
  };
  struct uz_ParameterID_controller init_ParaID_6ph_controller(void){
	 cc_config_dq.config_PMSM = ParaID_Data.GlobalConfig.PMSM_config;
	 sp_config.config_PMSM = ParaID_Data.GlobalConfig.PMSM_config;
    struct uz_ParameterID_controller out = {
      .CC_instance_dq = uz_CurrentControl_init(cc_config_dq),
	   .CC_instance_xy = uz_CurrentControl_init(cc_config_xy_z),
	   .CC_instance_zero = uz_CurrentControl_init(cc_config_xy_z),
	   .res_instance_dq = uz_subspace_resonant_control_init(resonant_dq),
	   .res_instance_xy = uz_subspace_resonant_control_init(resonant_xy),
	   .res_instance_zero = uz_subspace_resonant_control_init(resonant_zero),
	   .SP_instance = uz_SetPoint_init(sp_config),
	   .SC_instance = uz_SpeedControl_init(speed_config)}; 
    return out;
  }

  // other
  void init_ParaID_6ph_misc(void){
	 uz_ParameterID_6ph_initialize_filter(&ParaID_Data, UZ_PWM_FREQUENCY/INTERRUPT_ISR_SOURCE_USER_CHOICE);
	 uz_ParameterID_6ph_initialize_encoder_offset_estimation(&ParaID_Data, &controller_out.q);
  }


.. code-block:: c
  :linenos:
  :caption: Call ParameterID_6ph in ``main.c``

  ...
  extern uz_ParameterID_Data_t ParaID_Data;
  int main(void){
  ...
  case init_software:
    ... // init ParaID BEFORE JavaScope_initialize
    Global_Data.objects.ParaID_6ph = init_ParaID_6ph_wrapper();
    Global_Data.objects.controller = init_ParaID_6ph_controller();
    init_ParaID_6ph_misc();
    JavaScope_initialize(&Global_Data);
    initialization_chain = init_ip_cores;
    break;
  ...
  case infinite_loop:
    ultrazohm_state_machine_step();
    uz_ParameterID_6ph_calculate_PsiPMs(Global_Data.objects.ParaID_6ph, &ParaID_Data);
    break;   

The ParameterID's step and controller function are called while the control state is active.
The custom DutyCycle generation and the setting of the TriStates is necessary for the :ref:`uz_ElectricalID_6ph`.

In order for the ParameterID to get all actual values, the user has to assign those to the ``ActualValues`` struct.
The processing function simplifies tasks like transforming phase quantities and rotating the individual subsystems.
If other states than the :ref:`uz_ElectricalID_6ph` should be used, make sure to set the correct offset angle as in the commented out line below.

.. code-block:: c
  :linenos:
  :caption: Call ParameterID_6ph in ``isr.c``

  // ParaID 6ph
  #include "../uz/uz_ParameterID/uz_ParameterID_6ph.h"
  extern uz_ParameterID_Data_t ParaID_Data;
  struct uz_DutyCycle_2x3ph_t ParaID_DutyCycle = { 0 };
  uz_6ph_dq_t controller_out = {0};
  float u_a1c1 = 0.0f;
  float u_a2c2 = 0.0f;
  void ISR_Control(void *data){
    ...
    // ParaID Actual values
    u_a1c1 = Global_Data.av.v_a1 - Global_Data.av.v_c1;
    u_a2c2 = Global_Data.av.v_a2 - Global_Data.av.v_c2;
    ParaID_Data.ActualValues.i_abc_6ph = Global_Data.av.currents;
    ParaID_Data.ActualValues.v_abc_6ph = REAL_v_abc_meas;
    ParaID_Data.ActualValues.V_DC = Global_Data.av.v_dc1;
    ParaID_Data.ActualValues.omega_m = Global_Data.av.omega_mech;
    ParaID_Data.ActualValues.omega_el = Global_Data.av.omega_el;
    ParaID_Data.ActualValues.average_winding_temp = ParaID_Data.FluxMapID_Output->WindingTemp; // if no temperature sensors are available, use FMID output
    ParaID_Data.ActualValues.theta_el_raw = Global_Data.av.theta_el;
    // processing
    uz_ParameterID_6ph_process_actual_values(&ParaID_Data, u_a1c1, u_a2c2);
    // if offset is already known and not determined by ElID, set it AFTER process function
    //ParaID_Data.ActualValues.theta_el =  Global_Data.av.theta_el - theta_offset; 
    // ParaID Actual values end

    if (current_state==control_state)
    {
      // step ParaID and controllers
   	uz_ParameterID_6ph_step(Global_Data.objects.ParaID_6ph, &ParaID_Data);
   	controller_out = uz_ParameterID_6ph_Controller(&ParaID_Data, Global_Data.objects.controller);
   	ParaID_DutyCycle = uz_ParameterID_6ph_generate_DutyCycle(&ParaID_Data, controller_out);
   	// write duty-cycles
   	Global_Data.rasv.halfBridge1DutyCycle = ParaID_DutyCycle.system1.DutyCycle_A;
   	Global_Data.rasv.halfBridge2DutyCycle = ParaID_DutyCycle.system1.DutyCycle_B;
   	Global_Data.rasv.halfBridge3DutyCycle = ParaID_DutyCycle.system1.DutyCycle_C;
   	Global_Data.rasv.halfBridge4DutyCycle = ParaID_DutyCycle.system2.DutyCycle_A;
   	Global_Data.rasv.halfBridge5DutyCycle = ParaID_DutyCycle.system2.DutyCycle_B;
   	Global_Data.rasv.halfBridge6DutyCycle = ParaID_DutyCycle.system2.DutyCycle_C;
   	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, ParaID_Data.ElectricalID_Output->enable_TriState[0], ParaID_Data.ElectricalID_Output->enable_TriState[1], ParaID_Data.ElectricalID_Output->enable_TriState[2]);
   	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, ParaID_Data.ElectricalID_Output->enable_TriState_set_2[0], ParaID_Data.ElectricalID_Output->enable_TriState_set_2[1], ParaID_Data.ElectricalID_Output->enable_TriState_set_2[2]);
   }else{
   	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
   	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
   	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
   	Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
   	Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
   	Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
   	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
   	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, false, false, false);
   }
   ...


.. _ParaID_6ph_setup_GUI:

Setup GUI
=========

To use the custom GUI, changes have to be made to ``javascope.h``, ``javascope.c`` and ``ipc_ARM.c``.
The changes are in line with :ref:`uz_ParaID_GUI_setup` and the user only has to add a few signals on top of that.

Make sure to change the value of the ParameterID and ParameterID_6ph variables to 1 in ``properties.ini``.

.. code-block:: c
  :linenos:
  :caption: Changes in ``javascope.h``

  ...
  // add the following Slowdata enums after the existing ones
  enum JS_SlowData {
    ...
    JSSD_FLOAT_Rs_Offline,
    JSSD_FLOAT_Ld_Offline,
    JSSD_FLOAT_Lq_Offline,
    JSSD_FLOAT_PsiPM_Offline,
    JSSD_FLOAT_J,
    JSSD_FLOAT_activeState,
    JSSD_FLOAT_ArrayCounter,
    JSSD_FLOAT_measArraySpeed,
    JSSD_FLOAT_measArrayTorque,
    JSSD_FLOAT_ArrayControlCounter,
    JSSD_FLOAT_Stribtorque,
    JSSD_FLOAT_Coulombtorque,
    JSSD_FLOAT_Viscotorque,
    JSSD_FLOAT_Rs_online_FMID,
    JSSD_FLOAT_Wtemp_FMID,
    JSSD_FLOAT_TrainInertia,
    JSSD_FLOAT_LoadInertia,
    JSSD_FLOAT_c_est,
    JSSD_FLOAT_d_est,
    JSSD_FLOAT_MapCounter,
    JSSD_FLOAT_psidMap,
    JSSD_FLOAT_psiqMap,
    JSSD_FLOAT_FluxTemp,
    JSSD_FLOAT_MapControl,
    JSSD_FLOAT_I_rated,
    JSSD_FLOAT_Ld_Online,
    JSSD_FLOAT_Lq_Online,
    JSSD_FLOAT_PsiPM_Online,
    JSSD_FLOAT_Rs_Online,
    JSSD_FLOAT_n_FluxPoints,
    JSSD_FLOAT_totalRotorInertia,
    JSSD_FLOAT_MapControlCounter,
    JSSD_FLOAT_polePairs,
    JSSD_FLOAT_Psi_0,
    JSSD_FLOAT_Psi_1,
    JSSD_FLOAT_Psi_2,
    JSSD_FLOAT_Psi_3,
    JSSD_FLOAT_Psi_4,
    JSSD_FLOAT_Rs_d,
    JSSD_FLOAT_Rs_q,
    JSSD_FLOAT_Rs_X,
    JSSD_FLOAT_Rs_Y,
    JSSD_FLOAT_Rs_Z1,
    JSSD_FLOAT_Rs_Z2,
    JSSD_FLOAT_L_d,
    JSSD_FLOAT_L_q,
    JSSD_FLOAT_L_X,
    JSSD_FLOAT_L_Y,
    JSSD_FLOAT_L_Z1,
    JSSD_FLOAT_L_Z2,
    JSSD_FLOAT_set_rpm_val,
    JSSD_FLOAT_extended_offset_progress,
    JSSD_FLOAT_out_point_number,
    JSSD_FLOAT_out_i_d,
    JSSD_FLOAT_out_i_q,
    JSSD_FLOAT_out_psi_d,
    JSSD_FLOAT_out_psi_q,
    JSSD_FLOAT_average_winding_temp,
    JSSD_FLOAT_fluxmap_index,
    JSSD_ENDMARKER
  };

  // add the follwoing button enums after the existing ones
  enum gui_button_mapping {
    ...
    ParaID_Enable_System,
    ParaID_Enable_Control,
    ParaID_Enable_ParameterID,
    ParaID_Disable_ParameterID,
    ParaID_Enable_ElectricalID,
    ParaID_Disable_ElectricalID,
    ParaID_Enable_FrictionID,
    ParaID_Disable_FrictionID,
    ParaID_Enable_TwoMassID,
    ParaID_Disable_TwoMassID,
    ParaID_Enable_FluxMapID,
    ParaID_Disable_FluxMapID,
    ParaID_Enable_OnlineID,
    ParaID_Disable_OnlineID,
    ParaID_Enable_Current_Control,
    ParaID_Enable_Speed_Control,
    ParaID_Disable_FOC_Control,
    ParaID_ACCEPT,
    ParaID_RESET,
    ParaID_EID_sampleTimeISR,
    ParaID_EID_n_ref_meas,
    ParaID_EID_goertzl_Amp,
    ParaID_EID_goertzl_Freq,
    ParaID_EID_DutyCyc,
    ParaID_EID_MaxContinousCurrent,
    ParaID_EID_Enable_IdentLQ,
    ParaID_EID_Disable_IdentLQ,
    ParaID_EID_Admit_Params,
    ParaID_FID_max_speed,
    ParaID_FID_N_Brk,
    ParaID_FID_N_Visco,
    ParaID_FID_s_step,
    ParaID_FID_Brk_Count,
    ParaID_FID_eta_speed,
    ParaID_FID_Array_Control_counter,
    ParaID_TMID_Scale_PRBS,
    ParaID_TMID_d_TMS_start,
    ParaID_TMID_n_ref,
    ParaID_TMID_f_min,
    ParaID_TMID_f_max,
    ParaID_TMID_Admit_Params,
    ParaID_FMID_i_d_start,
    ParaID_FMID_i_d_stop,
    ParaID_FMID_i_d_step,
    ParaID_FMID_i_q_start,
    ParaID_FMID_i_q_stop,
    ParaID_FMID_i_q_step,
    ParaID_FMID_Rs_ref,
    ParaID_FMID_Temp_ref,
    ParaID_FMID_identRAmp,
    ParaID_FMID_enable_ident_R,
    ParaID_FMID_disable_ident_R,
    ParaID_FMID_enable_AMM,
    ParaID_FMID_disable_AMM,
    ParaID_OID_Refresh_Flux_Maps,
    ParaID_OID_Reset_OnlineID,
    ParaID_OID_Enable_AutoCurrentControl,
    ParaID_OID_Disable_AutoCurrentControl,
    ParaID_OID_d_current_steps,
    ParaID_OID_q_current_steps,
    ParaID_OID_max_current,
    ParaID_OID_ref_temp,
    ParaID_OID_ref_Rs,
    ParaID_OID_max_speed,
    ParaID_OID_min_speed,
    ParaID_OID_Ident_range_factor,
    ParaID_OID_max_ident_pause,
    ParaID_OID_identR_Amp,
    ParaID_OID_Fluxmap_Control_counter,
    ParaID_EID_Enable_EXT_PSI,
    ParaID_EID_Disable_EXT_PSI,
    ParaID_EID_Enable_EXT_THETA,
    ParaID_EID_Disable_EXT_THETA,
    ParaID_EID_ManualOffset,
    ParaID_FMID_temperature_lower,
    ParaID_FMID_temperature_upper,
    ParaID_FMID_selected_subsystem,
    ParaID_Control_PI,
    ParaID_Control_res,
    ParaID_Enable_setpoint_filter,
    ParaID_Disable_setpoint_filter,
    GUI_BTN_ENDMARKER
  };

  // receive fields
  // Description (printed text) for the receive_fields top to bottom
  // Do not change the first (zero) and last (end) entries.

    RCV_FLD_ZEROVALUE=0,
    AvgWindingTemp,
    index,
    i_d,
    i_q,
    psi_d,
    psi_q,
    receive_field_7,
    receive_field_8,
    receive_field_9,
    receive_field_10,
    receive_field_11,
    receive_field_12,
    receive_field_13,
    receive_field_14,
    receive_field_15,
    receive_field_16,
    receive_field_17,
    receive_field_18,
    receive_field_19,
    receive_field_20,
    RCV_FLD_ENDMARKER

    // Slowdata display values
    // Slow Data values that are displayed in the receive_fields top to bottom
    // Do not change the first (zero) and last (end) entries.
    // Make sure that the signal names below are also present in the JS_SlowData enum!
    //Set the line to JSSD_FLOAT_ZEROVALUE if no value should be transmitted

    SLOWDAT_DISPLAY_ZEROVALUE=0,
    JSSD_FLOAT_average_winding_temp,
    JSSD_FLOAT_fluxmap_index,
    JSSD_FLOAT_out_i_d,
    JSSD_FLOAT_out_i_q,
    JSSD_FLOAT_out_psi_d,
    JSSD_FLOAT_out_psi_q,
    JSSD_FLOAT_ZEROVALUE,
    JSSD_FLOAT_ZEROVALUE,
    JSSD_FLOAT_ZEROVALUE,
    JSSD_FLOAT_ZEROVALUE,
    JSSD_FLOAT_ZEROVALUE,
    JSSD_FLOAT_ZEROVALUE,
    JSSD_FLOAT_ZEROVALUE,
    JSSD_FLOAT_ZEROVALUE,
    JSSD_FLOAT_ZEROVALUE,
    JSSD_FLOAT_ZEROVALUE,
    JSSD_FLOAT_ZEROVALUE,
    JSSD_FLOAT_ZEROVALUE,
    JSSD_FLOAT_ZEROVALUE,
    JSSD_FLOAT_Error_Code,
    SLOWDAT_DISPLAY_ENDMARKER


.. code-block:: c
  :linenos:
  :caption: Changes in ``ipc_ARM.c``

  #include "../uz/uz_ParameterID/uz_ParameterID_data.h"
  extern uz_ParameterID_Data_t ParaID_Data;
  void ipc_Control_func(uint32_t msgId, float value, DS_Data *data){
  ...

  // set the following send fields
  case (Set_Send_Field_1):
    ParaID_Data.GlobalConfig.i_dq_ref.d = value;
  break;
  case (Set_Send_Field_2):
    ParaID_Data.GlobalConfig.i_dq_ref.q = value;
  break;
  case (Set_Send_Field_3):
    ParaID_Data.GlobalConfig.i_xy_ref.d = value;
  break;
  case (Set_Send_Field_4):
    ParaID_Data.GlobalConfig.i_xy_ref.q = value;
  break;

  ...

  //After all My_Button cases add the following
  //ParameterID
  case (ParaID_Enable_System):
    ultrazohm_state_machine_set_enable_system(true);
  break;

  case (ParaID_Enable_Control):
    ultrazohm_state_machine_set_enable_control(true);
  break;

  case (ParaID_Enable_ParameterID):
    ParaID_Data.GlobalConfig.enableParameterID = true;
  break;
  case (ParaID_Disable_ParameterID):
    ParaID_Data.GlobalConfig.enableParameterID = false;
    ParaID_Data.GlobalConfig.ElectricalID = false;
    ParaID_Data.GlobalConfig.TwoMassID = false;
    ParaID_Data.GlobalConfig.FrictionID = false;
    ParaID_Data.GlobalConfig.FluxMapID = false;
    ParaID_Data.GlobalConfig.OnlineID = false;
    ParaID_Data.FluxMapID_Config.start_FM_ID = false;
  break;
  case (ParaID_Enable_Current_Control):
    if (ultrazohm_state_machine_get_state() != control_state) {
      ParaID_Data.ParaID_Control_Selection = Current_Control;
    }
  break;
  case (ParaID_Enable_Speed_Control):
    if (ultrazohm_state_machine_get_state() != control_state) {
      ParaID_Data.ParaID_Control_Selection = Speed_Control;
    }
  break;
  case (ParaID_Disable_FOC_Control):
    ParaID_Data.ParaID_Control_Selection = No_Control;
  break;
  case (ParaID_Control_PI):
    if(((uint16_t) value) & 0x01){
      ParaID_Data.GlobalConfig.PI_dq = true;
    }else{
      ParaID_Data.GlobalConfig.PI_dq  = false;
    }
    if(((uint16_t) value) & 0x02){
      ParaID_Data.GlobalConfig.PI_xy = true;
    }else{
      ParaID_Data.GlobalConfig.PI_xy = false;
    }
    if(((uint16_t) value) & 0x04){
      ParaID_Data.GlobalConfig.PI_zero = true;
    }else{
      ParaID_Data.GlobalConfig.PI_zero = false;
    }
    ParaID_Data.GlobalConfig.controllers_updated = true;
  break;
  case (ParaID_Control_res):
    if(((uint16_t) value) & 0x01){
      ParaID_Data.GlobalConfig.resonant_dq = true;
    }else{
      ParaID_Data.GlobalConfig.resonant_dq  = false;
    }
    if(((uint16_t) value) & 0x02){
      ParaID_Data.GlobalConfig.resonant_xy = true;
    }else{
      ParaID_Data.GlobalConfig.resonant_xy = false;
    }
    if(((uint16_t) value) & 0x04){
      ParaID_Data.GlobalConfig.resonant_zero = true;
    }else{
      ParaID_Data.GlobalConfig.resonant_zero = false;
    }
  break;
  case (ParaID_Enable_setpoint_filter):
    ParaID_Data.GlobalConfig.setpoint_filter = true;
  break;
  case (ParaID_Disable_setpoint_filter):
    ParaID_Data.GlobalConfig.setpoint_filter = false;
  break;
  case (ParaID_Enable_ElectricalID):
    ParaID_Data.GlobalConfig.ElectricalID = true;
  break;
  case (ParaID_Disable_ElectricalID):
    ParaID_Data.GlobalConfig.ElectricalID = false;
  break;
  case (ParaID_Enable_FrictionID):
    ParaID_Data.GlobalConfig.FrictionID = true;
  break;
  case (ParaID_Disable_FrictionID):
    ParaID_Data.GlobalConfig.FrictionID = false;
  break;
  case (ParaID_Enable_TwoMassID):
    ParaID_Data.GlobalConfig.TwoMassID = true;
  break;
  case (ParaID_Disable_TwoMassID):
    ParaID_Data.GlobalConfig.TwoMassID = false;
  break;
  case (ParaID_Enable_FluxMapID):
    ParaID_Data.GlobalConfig.FluxMapID = true;
  break;
  case (ParaID_Disable_FluxMapID):
    ParaID_Data.GlobalConfig.FluxMapID = false;
    ParaID_Data.FluxMapID_Config.start_FM_ID = false;
  break;
  case (ParaID_Enable_OnlineID):
    ParaID_Data.GlobalConfig.OnlineID = true;
  break;
  case (ParaID_Disable_OnlineID):
    ParaID_Data.GlobalConfig.OnlineID = false;
    ParaID_Data.AutoRefCurrents_Config.enableCRS = false;
  break;
  case (ParaID_ACCEPT):
    ParaID_Data.GlobalConfig.ACCEPT = true;
  break;
  case (ParaID_RESET):
    ParaID_Data.GlobalConfig.Reset = true;
    ParaID_Data.GlobalConfig.ElectricalID = false;
    ParaID_Data.GlobalConfig.TwoMassID = false;
    ParaID_Data.GlobalConfig.FrictionID = false;
    ParaID_Data.GlobalConfig.FluxMapID = false;
    ParaID_Data.GlobalConfig.OnlineID = false;
    ParaID_Data.AutoRefCurrents_Config.enableCRS = false;
    ParaID_Data.ParaID_Control_Selection = No_Control;
    ParaID_Data.ElectricalID_Config.identLq = false;
    ParaID_Data.FluxMapID_Config.start_FM_ID = false;
  break;
  case (ParaID_EID_sampleTimeISR):
    ParaID_Data.GlobalConfig.sampleTimeISR = value * 0.000001f;
  break;
  case (ParaID_EID_n_ref_meas):
    ParaID_Data.ElectricalID_Config.n_ref_measurement = value;
  break;
  case (ParaID_EID_goertzl_Amp):
    ParaID_Data.ElectricalID_Config.goertzlTorque = value;
  break;
  case (ParaID_EID_goertzl_Freq):
    ParaID_Data.ElectricalID_Config.goertzlFreq = value;
  break;
  case (ParaID_EID_DutyCyc):
    ParaID_Data.ElectricalID_Config.dutyCyc = value;
  break;
  case (ParaID_EID_MaxContinousCurrent):
    ParaID_Data.GlobalConfig.PMSM_config.I_max_Ampere = value;
  break;
  case (ParaID_EID_Enable_IdentLQ):
    ParaID_Data.ElectricalID_Config.identLq = true;
  break;
  case (ParaID_EID_Disable_IdentLQ):
    ParaID_Data.ElectricalID_Config.identLq = false;
  break;
  case (ParaID_EID_Enable_EXT_PSI):
    ParaID_Data.ElectricalID_Config.extended_psi = true;
  break;

  case (ParaID_EID_Disable_EXT_PSI):
    ParaID_Data.ElectricalID_Config.extended_psi = false;
  break;
  case (ParaID_EID_Enable_EXT_THETA):
    ParaID_Data.ElectricalID_Config.extended_offset = true;
  break;
  case (ParaID_EID_Disable_EXT_THETA):
    ParaID_Data.ElectricalID_Config.extended_offset = false;
  break;
  case (ParaID_EID_ManualOffset):
    ParaID_Data.ElectricalID_Config.manual_offset = value;
  break;
  case (ParaID_EID_Admit_Params):
    //If FOC is used
    //uz_FOC_set_PMSM_parameters(FOC_instance, ParaID_Data.ElectricalID_Output.PMSM_parameters);
    //uz_SpeedControl_set_PMSM_config(SpeedControl_instance, ParaID_Data.ElectricalID_Output.PMSM_parameters);
  break;
  case (ParaID_FID_max_speed):
    ParaID_Data.FrictionID_Config.n_eva_max = value;
  break;

  case (ParaID_FID_N_Brk):
    ParaID_Data.FrictionID_Config.N_Brk = value;
  break;
  case (ParaID_FID_N_Visco):
    ParaID_Data.FrictionID_Config.N_Visco = value;
  break;
  case (ParaID_FID_s_step):
    ParaID_Data.FrictionID_Config.StepScale = value;
  break;
  case (ParaID_FID_Brk_Count):
    ParaID_Data.FrictionID_Config.BrkCount = value;
  break;
  case (ParaID_FID_eta_speed):
    ParaID_Data.FrictionID_Config.eta = value;
  break;
  case (ParaID_TMID_Scale_PRBS):
    ParaID_Data.TwoMassID_Config.ScaleTorquePRBS = value;
  break;
  case (ParaID_TMID_d_TMS_start):
    ParaID_Data.TwoMassID_Config.d_TMS_start = value;
  break;
  case (ParaID_TMID_n_ref):
    ParaID_Data.TwoMassID_Config.n_ref_measurement = value;
  break;
  case (ParaID_TMID_f_min):
    ParaID_Data.TwoMassID_Config.f_min = value;
  break;
  case (ParaID_TMID_f_max):
    ParaID_Data.TwoMassID_Config.f_max = value;
  break;
  case (ParaID_FMID_i_d_start):
    ParaID_Data.FluxMapID_Config.IDstart = value;
  break;
  case (ParaID_FMID_i_d_stop):
    ParaID_Data.FluxMapID_Config.IDstop = value;
  break;
  case (ParaID_FMID_i_d_step):
    ParaID_Data.FluxMapID_Config.IDstepsize = value;
  break;
  case (ParaID_FMID_i_q_start):
    ParaID_Data.FluxMapID_Config.IQstart = value;
  break;
  case (ParaID_FMID_i_q_stop):
    ParaID_Data.FluxMapID_Config.IQstop = value;
  break;
  case (ParaID_FMID_i_q_step):
    ParaID_Data.FluxMapID_Config.IQstepsize = value;
  break;
  case (ParaID_FMID_Rs_ref):
    ParaID_Data.FluxMapID_Config.R_s_ref = value;
  break;
  case (ParaID_FMID_Temp_ref):
    ParaID_Data.FluxMapID_Config.Temp_ref = value;
  break;
  case (ParaID_FMID_identRAmp):
    ParaID_Data.FluxMapID_Config.identRAmp = value;
  break;
  case (ParaID_FMID_enable_ident_R):
    ParaID_Data.FluxMapID_Config.identR = true;
  break;
  case (ParaID_FMID_disable_ident_R):
    ParaID_Data.FluxMapID_Config.identR = false;
  break;
  case (ParaID_FMID_enable_AMM):
    ParaID_Data.FluxMapID_Config.start_FM_ID = true;
  break;
  case (ParaID_FMID_disable_AMM):
    ParaID_Data.FluxMapID_Config.start_FM_ID = false;
  break;
  case (ParaID_OID_Refresh_Flux_Maps):
    ParaID_Data.calculate_flux_maps = true;
  break;
  case (ParaID_OID_Reset_OnlineID):
    ParaID_Data.OnlineID_Config.OnlineID_Reset = true;
    ParaID_Data.AutoRefCurrents_Config.Reset = true;
    ParaID_Data.AutoRefCurrents_Config.enableCRS = false;
  break;
  case (ParaID_OID_Enable_AutoCurrentControl):
    ParaID_Data.AutoRefCurrents_Config.enableCRS = true;
  break;
  case (ParaID_OID_Disable_AutoCurrentControl):
    ParaID_Data.AutoRefCurrents_Config.enableCRS = false;
  break;
  case (ParaID_OID_d_current_steps):
    ParaID_Data.AutoRefCurrents_Config.id_points = value;
  break;
  case (ParaID_OID_q_current_steps):
    ParaID_Data.AutoRefCurrents_Config.iq_points = value;
  break;
  case (ParaID_OID_max_current):
    ParaID_Data.AutoRefCurrents_Config.max_current = value;
  break;
  case (ParaID_OID_ref_temp):
    ParaID_Data.OnlineID_Config.Temp_ref = value;
  break;
  case (ParaID_OID_ref_Rs):
    ParaID_Data.GlobalConfig.PMSM_config.R_ph_Ohm = value;
  break;
  case (ParaID_OID_max_speed):
    ParaID_Data.OnlineID_Config.max_n_ratio = value;
  break;
  case (ParaID_OID_min_speed):
    ParaID_Data.OnlineID_Config.min_n_ratio = value;
  break;
  case (ParaID_OID_Ident_range_factor):
    ParaID_Data.OnlineID_Config.nom_factor = value;
  break;
  case (ParaID_OID_max_ident_pause):
    ParaID_Data.OnlineID_Config.Rs_time = value;
  break;
  case (ParaID_OID_identR_Amp):
    ParaID_Data.OnlineID_Config.identRAmp = value;
  break;
  case (ParaID_OID_Fluxmap_Control_counter):
    ParaID_Data.FluxMap_Control_counter = value;
  break;
  case (ParaID_FID_Array_Control_counter):
    ParaID_Data.Array_Control_counter = value;
  break;
  case (ParaID_FMID_temperature_lower):
    ParaID_Data.FluxMapID_Config.lower_meas_temp = value;
  break;
  case (ParaID_FMID_temperature_upper):
    ParaID_Data.FluxMapID_Config.upper_meas_temp = value;
  break;
  case (ParaID_FMID_selected_subsystem):
    if(((uint16_t) value) & 0x01){
      ParaID_Data.FluxMapID_Config.select_dq = true;
    }else{
      ParaID_Data.FluxMapID_Config.select_dq = false;
    }
    if(((uint16_t) value) & 0x02){
      ParaID_Data.FluxMapID_Config.select_xy = true;
    }else{
      ParaID_Data.FluxMapID_Config.select_xy = false;
    }
    if(((uint16_t) value) & 0x04){
      ParaID_Data.FluxMapID_Config.select_zero = true;
    }else{
      ParaID_Data.FluxMapID_Config.select_zero = false;
    }
  break;

  ...
  //Replace Bit 12-21 with the following
	/* Bit 12 - trigger ext. logging */
	if (ParaID_Data.Controller_Parameters.activeState == 404U && ParaID_Data.Controller_Parameters.activeState == 405U) {
		js_status_BareToRTOS |= (1 << 12);
	} else {
		js_status_BareToRTOS &= ~(1 << 12);
	}

	//Replace Bit 13-19 with the following
	/* Bit 13 - Ident_Lq */
	if (ParaID_Data.ElectricalID_Config.identLq == true) {
		js_status_BareToRTOS |= (1 << 13);
	} else {
		js_status_BareToRTOS &= ~(1 << 13);
	}

	/* Bit 14 - FluxMapID R-Online */
	if (ParaID_Data.FluxMapID_Config.identR == true) {
		js_status_BareToRTOS |= (1 << 14);
	} else {
		js_status_BareToRTOS &= ~(1 << 14);
	}

	/* Bit 15 - FluxMapID start */
	if (ParaID_Data.FluxMapID_Config.start_FM_ID == true) {
		js_status_BareToRTOS |= (1 << 15);
	} else {
		js_status_BareToRTOS &= ~(1 << 15);
	}

	/* Bit 16 - ParaID_FOC_CC */
	if (ParaID_Data.ParaID_Control_Selection == Current_Control) {
		js_status_BareToRTOS |= (1 << 16);
	} else {
		js_status_BareToRTOS &= ~(1 << 16);
	}

	/* Bit 17 - ParaID_FOC_SC */
	if (ParaID_Data.ParaID_Control_Selection == Speed_Control) {
		js_status_BareToRTOS |= (1 << 17);
	} else {
		js_status_BareToRTOS &= ~(1 << 17);
	}

	/* Bit 18 -ParaID_FOC_no_control */
	if (ParaID_Data.ParaID_Control_Selection == No_Control) {
		js_status_BareToRTOS |= (1 << 18);
	} else {
		js_status_BareToRTOS &= ~(1 << 18);
	}

	/* Bit 19 -ParameterID active */
	if (ParaID_Data.GlobalConfig.enableParameterID == true) {
		ultrazohm_state_machine_set_userLED(true);
		js_status_BareToRTOS |= (1 << 19);
	} else {
		js_status_BareToRTOS &= ~(1 << 19);
		ultrazohm_state_machine_set_userLED(false);
	}

	/* Bit 20 - ext offset */
	if (ParaID_Data.ElectricalID_Config.extended_offset == true) {
		js_status_BareToRTOS |= (1 << 20);
	} else {
		js_status_BareToRTOS &= ~(1 << 20);
	}

	//* Bit 21 - ext psi */
	if (ParaID_Data.ElectricalID_Config.extended_psi == true) {
		js_status_BareToRTOS |= (1 << 21);
	} else {
		js_status_BareToRTOS &= ~(1 << 21);
	}

.. code-block:: c
  :linenos:
  :caption: Changes in ``javascope.c``

  //ParameterID
  #include "../uz/uz_ParameterID/uz_ParameterID_data.h"
  extern uz_ParameterID_Data_t ParaID_Data;
  float activeState = 0.0f;
  float FMID_array_index = 0.0f;

  int JavaScope_initialize(DS_Data* data)
  {
  ...	
    // add the following after your Slowdata assignments
    // ParaID
    js_slowDataArray[JSSD_FLOAT_PsiPM_Offline]          = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.Psi_PM_Vs);
    js_slowDataArray[JSSD_FLOAT_Lq_Offline]             = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.Lq_Henry);
    js_slowDataArray[JSSD_FLOAT_Ld_Offline]             = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.Ld_Henry);
    js_slowDataArray[JSSD_FLOAT_Rs_Offline]             = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.R_ph_Ohm);
    js_slowDataArray[JSSD_FLOAT_polePairs]              = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.polePairs);
    js_slowDataArray[JSSD_FLOAT_J]                      = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.J_kg_m_squared);
    js_slowDataArray[JSSD_FLOAT_activeState]            = &(activeState);
    js_slowDataArray[JSSD_FLOAT_encoderOffset]          = &(ParaID_Data.ElectricalID_Output->thetaOffset);
    js_slowDataArray[JSSD_FLOAT_measArraySpeed]         = &(ParaID_Data.MeasArraySpeed_pointer);
    js_slowDataArray[JSSD_FLOAT_measArrayTorque]        = &(ParaID_Data.MeasArrayTorque_pointer);
    js_slowDataArray[JSSD_FLOAT_Stribtorque]            = &(ParaID_Data.FrictionID_Output->BrkTorque);
    js_slowDataArray[JSSD_FLOAT_Coulombtorque]          = &(ParaID_Data.FrictionID_Output->CoulTorque);
    js_slowDataArray[JSSD_FLOAT_Viscotorque]            = &(ParaID_Data.FrictionID_Output->ViscoTorque);
    js_slowDataArray[JSSD_FLOAT_TrainInertia]           = &(ParaID_Data.TwoMassID_Output->TrainInertia);
    js_slowDataArray[JSSD_FLOAT_LoadInertia]            = &(ParaID_Data.TwoMassID_Output->LoadInertia);
    js_slowDataArray[JSSD_FLOAT_c_est]                  = &(ParaID_Data.TwoMassID_Output->c_est_out);
    js_slowDataArray[JSSD_FLOAT_d_est]                  = &(ParaID_Data.TwoMassID_Output->d_est_out);
    js_slowDataArray[JSSD_FLOAT_I_rated]                = &(ParaID_Data.GlobalConfig.ratCurrent);
    js_slowDataArray[JSSD_FLOAT_totalRotorInertia]      = &(ParaID_Data.TwoMassID_Output->rotorInertia);
    js_slowDataArray[JSSD_FLOAT_Ld_Online]              = &(ParaID_Data.OnlineID_Output->Ld_out);
    js_slowDataArray[JSSD_FLOAT_Lq_Online]              = &(ParaID_Data.OnlineID_Output->Lq_out);
    js_slowDataArray[JSSD_FLOAT_PsiPM_Online]           = &(ParaID_Data.OnlineID_Output->psi_pm_out);
    js_slowDataArray[JSSD_FLOAT_Rs_Online]              = &(ParaID_Data.OnlineID_Output->Rph_out);
    js_slowDataArray[JSSD_FLOAT_n_FluxPoints]           = &(ParaID_Data.FluxMap_MeasuringPoints);
    js_slowDataArray[JSSD_FLOAT_Rs_online_FMID]         = &(ParaID_Data.FluxMapID_Output->R_s);
    js_slowDataArray[JSSD_FLOAT_Wtemp_FMID]             = &(ParaID_Data.FluxMapID_Output->WindingTemp);
    js_slowDataArray[JSSD_FLOAT_psidMap]                = &(ParaID_Data.Psi_D_pointer);
    js_slowDataArray[JSSD_FLOAT_psiqMap]                = &(ParaID_Data.Psi_Q_pointer);
    // ParaID 6ph
    js_slowDataArray[JSSD_FLOAT_Psi_0]           			  = &(ParaID_Data.ElectricalID_Output->psi_pm[0]);
    js_slowDataArray[JSSD_FLOAT_Psi_1]           			  = &(ParaID_Data.ElectricalID_Output->psi_pm[1]);
    js_slowDataArray[JSSD_FLOAT_Psi_2]       		    	  = &(ParaID_Data.ElectricalID_Output->psi_pm[2]);
    js_slowDataArray[JSSD_FLOAT_Psi_3]      			      = &(ParaID_Data.ElectricalID_Output->psi_pm[3]);
    js_slowDataArray[JSSD_FLOAT_Psi_4]      			      = &(ParaID_Data.ElectricalID_Output->psi_pm[4]);
    js_slowDataArray[JSSD_FLOAT_Rs_d]      				      = &(ParaID_Data.ElectricalID_Output->resistances_6ph.d);
    js_slowDataArray[JSSD_FLOAT_Rs_q]      				      = &(ParaID_Data.ElectricalID_Output->resistances_6ph.q);
    js_slowDataArray[JSSD_FLOAT_Rs_X]      				      = &(ParaID_Data.ElectricalID_Output->resistances_6ph.x);
    js_slowDataArray[JSSD_FLOAT_Rs_Y]      				      = &(ParaID_Data.ElectricalID_Output->resistances_6ph.y);
    js_slowDataArray[JSSD_FLOAT_Rs_Z1]      			      = &(ParaID_Data.ElectricalID_Output->resistances_6ph.z1);
    js_slowDataArray[JSSD_FLOAT_Rs_Z2]      			      = &(ParaID_Data.ElectricalID_Output->resistances_6ph.z2);
    js_slowDataArray[JSSD_FLOAT_L_d]      				      = &(ParaID_Data.ElectricalID_Output->inductances_6ph.d);
    js_slowDataArray[JSSD_FLOAT_L_q]      				      = &(ParaID_Data.ElectricalID_Output->inductances_6ph.q);
    js_slowDataArray[JSSD_FLOAT_L_X]      				      = &(ParaID_Data.ElectricalID_Output->inductances_6ph.x);
    js_slowDataArray[JSSD_FLOAT_L_Y]      				      = &(ParaID_Data.ElectricalID_Output->inductances_6ph.y);
    js_slowDataArray[JSSD_FLOAT_L_Z1]      				      = &(ParaID_Data.ElectricalID_Output->inductances_6ph.z1);
    js_slowDataArray[JSSD_FLOAT_L_Z2]      				      = &(ParaID_Data.ElectricalID_Output->inductances_6ph.z2);
    js_slowDataArray[JSSD_FLOAT_set_rpm_val]      		  = &(ParaID_Data.ElectricalID_Output->set_rpm_val);
    js_slowDataArray[JSSD_FLOAT_extended_offset_progress] = &(ParaID_Data.ElectricalID_Offset_Estimation.progress);
    js_slowDataArray[JSSD_FLOAT_out_point_number]		    = &(FMID_array_index);
    js_slowDataArray[JSSD_FLOAT_out_i_d]				        = &(ParaID_Data.FluxMapID_Output->psi_array[0]);
    js_slowDataArray[JSSD_FLOAT_out_i_q]				        = &(ParaID_Data.FluxMapID_Output->psi_array[1]);
    js_slowDataArray[JSSD_FLOAT_out_psi_d]				      = &(ParaID_Data.FluxMapID_Output->psi_array[2]);
    js_slowDataArray[JSSD_FLOAT_out_psi_q]				      = &(ParaID_Data.FluxMapID_Output->psi_array[3]);
    js_slowDataArray[JSSD_FLOAT_average_winding_temp]	  = &(ParaID_Data.ActualValues.average_winding_temp);
    js_slowDataArray[JSSD_FLOAT_fluxmap_index]			    = &(FMID_array_index);

    return Status;
  }
  // add to the update function
  void JavaScope_update(DS_Data* data){
    	uz_ParameterID_6ph_update_transmit_values(&ParaID_Data, &activeState, &FMID_array_index);
  ...
