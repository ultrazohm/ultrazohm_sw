.. _uz_ParaID_GUI:

=============================
Custom uz_GUI for ParameterID
=============================

Since controlling the ParameterID only via the debugger windows is cumbersome and not very practical, a custom made uz_GUI is shipped as well. 
To use this however, additional setup steps have to be taken.
This page details these additional steps needed and how to use the uz_GUI.

.. _uz_ParaID_GUI_usage:

Usage
=====

This section gives an overview on how to use the ParameterID tab in the uz_GUI.

   .. image:: ../images/GUI_overview.png

#. The ParameterID is organized in its own panel, which can be selected via the ParameterID button. Each individual ``ID-state`` is further organized in its own subpanel and can be selected in the top left corner. 
#. Visible on the right side are the GlobalControls for the UltraZohm. The ``Enable System``, ``Enable Control`` and ``STOP`` buttons are mirrored to the ones in the UltraZohm-Gui ``Control`` tab. 
#. The button ``ParameterID`` enables or disables the ParameterID. The status indicator to the right signals the current state of the ParameterID (on/off).
#. Here all individual ``ID-states`` can be turned on or off. The current state of the ``ID-state`` is signaled via the status indicators next to the buttons. The possible states are:

   * ``Disabled``, for when the state is disabled and not requested for future use. As long as this status is active, the controls for this ``ID-state`` are locked.
   * ``Requested``, for when a ``ID-state`` is supposed to be executed, but hasn't started yet. In this state, the config values should be changed. 
   * ``Active``. for when this state is currently executing.
   * ``Finished``, for when the state is finished and another ``ID-state`` can be started.

#. The ``State Control`` buttons are used for general control of the ParameterID.

   * The ``ACCEPT`` button is used to transition the ParameterID into a different state. This is mostly used, to enable the ``ID-states`` after requesting them. Other uses can be, to continue one ``ID-state``, after some operations have to be done i.e. start up the load machine. 
   * The ``RESET`` button resets the entire ParameterID.
  
#. Each ``ID-state`` has an unique ``activeState`` variable for each substate. This is displayed here to give further information to the user, that the state is running and what it's doing.
#. Selection for control method, after every Offline-state is finished. The selection can only be changed, if the ``Control`` state of the UltraZohm is disabled.

   * If ``CurrentControl`` is selected, :math:`i_d` and :math:`i_q` reference values can be entered in the appropriate field in the JavaScope panel.
   * If ``SpeedControl`` is selected, a :math:`n_{ref}` reference value can be entered in the appropriate field in the JavaScope panel.
   * If ``Disable Control`` is selected, every previous control method selection is disabled and nothing happens.
  
#. Each ``ID-state`` has its own individual panel, where the individual config values can be configured and the identified values can be displayed. They have to be configured before entering the ``ID-state``. Standard values for the config values are displayed, which proved appropriate in the past. They can be used as an introductory baseline. 
  
.. _uz_ParaID_GUI_setup:

Setup
=====

#. In the ``properties.ini`` file change the value of the ``ParameterID`` variable to **1**.
#. Replace the appropriate code in the ``javascope.h`` file with the following:

   .. code-block:: C
        :linenos:
        :caption: Changes to the ``javascope.h`` file
    
        // Determination of Button IDs via enum. When a button in the GUI is pressed,
        // the GUI sends an ID and a value. IDs of the buttons are the respective enum
        // numbers in the following enum.
        // Do not change the first (zero) and last (end) entries.
        // Do not change names! They are hard coupled within the GUI!
        enum gui_button_mapping {
            GUI_BTN_ZEROVALUE=0,
            Enable_System,
            Enable_Control,
            Stop,
            Set_Send_Field_1,
            Set_Send_Field_2,
            Set_Send_Field_3,
            Set_Send_Field_4,
            Set_Send_Field_5,
            Set_Send_Field_6,
            My_Button_1,
            My_Button_2,
            My_Button_3,
            My_Button_4,
            My_Button_5,
            My_Button_6,
            My_Button_7,
            My_Button_8,
            Error_Reset,
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
            GUI_BTN_ENDMARKER
        };


        /* Visualization Config for GUI*/
        // LEAVE IT COMMENTED OUT AS IT IS, the plain text below is parsed by the GUI!
        // Change entries according to your needs.
        /*
        // Description (printed text) for the send_fields top to bottom
        // Do not change the first (zero) and last (end) entries.

        SND_FLD_ZEROVALUE=0,
        n_ref,
        i_d_ref,
        i_q_ref,
        send_field_4,
        send_field_5,
        send_field_6,
        SND_FLD_ENDMARKER


        // Physical unit label (printed text) for the send_fields top to bottom
        // Do not change the first (zero) and last (end) entries.

        SND_LABELS_ZEROVALUE=0,
        RPM,
        A,
        A,
        A,
        A,
        A,
        SND_LABELS_ENDMARKER


        // Description (printed text) for the receive_fields top to bottom
        // Do not change the first (zero) and last (end) entries.

        RCV_FLD_ZEROVALUE=0,
        speed,
        torque,
        i_d,
        i_q,
        u_d,
        u_q,
        RCV_FLD_ENDMARKER


        // Physical unit label (printed text) for the receive_fields top to bottom
        // Do not change the first (zero) and last (end) entries.

        RCV_LABELS_ZEROVALUE=0,
        RPM,
        Nm,
        A,
        A,
        V,
        V,
        RCV_LABELS_ENDMARKER


        // Slow Data values that are displayed in the receive_fields top to bottom
        // Do not change the first (zero) and last (end) entries.
        // Make sure that the signal names below are also present in the JS_SlowData enum!

        SLOWDAT_DISPLAY_ZEROVALUE=0,
        JSSD_FLOAT_speed,
        JSSD_FLOAT_torque,
        JSSD_FLOAT_i_d,
        JSSD_FLOAT_i_q,
        JSSD_FLOAT_u_d,
        JSSD_FLOAT_u_q,
        JSSD_FLOAT_Error_Code,
        SLOWDAT_DISPLAY_ENDMARKER
        */

#. Add the following code to the ``ipc_ARM.c`` file.

   .. code-block:: C
        :linenos:
        :emphasize-lines: 16,29,324,380
        :caption: Changes to the ``ipc_ARM.c`` file. (Breaks in the code are marked with ``....``).
    
        // slowData Naming Convention: Use JSSD_FLOAT_ as prefix
        // Do not change the first (zero) and last (end) entries.
        extern uz_ParameterID_Data_t ParaID_Data;
        //If FOC is used
        extern uz_FOC* FOC_instance;
        extern uz_SpeedControl_t* SpeedControl_instance;

        void ipc_Control_func(uint32_t msgId, float value, DS_Data *data)
        {       
            // HANDLE RECEIVED MESSAGE
            if (msgId != 0)
            {
                // GENERAL VARIABLES
                switch (msgId)
                {
                .... 
                //Change Send_Filed 1-3
                case (Set_Send_Field_1):
                    ParaID_Data.GlobalConfig.n_ref = value;
                    break;

                case (Set_Send_Field_2):
                    ParaID_Data.GlobalConfig.i_dq_ref.d = value;
                    break;

                case (Set_Send_Field_3):
                    ParaID_Data.GlobalConfig.i_dq_ref.q = value;
                    break; 
                ....
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
                    break;

                case (ParaID_EID_sampleTimeISR):
                    ParaID_Data.GlobalConfig.sampleTimeISR = value * 0.000001f;
                    break;

                case (ParaID_EID_n_ref_meas):
                    ParaID_Data.ElectricalID_Config.n_ref_measurement = value;
                    break;

                case (ParaID_EID_goertzl_Amp):
                    ParaID_Data.ElectricalID_Config.goertzlAmp = value;
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

                case (ParaID_EID_Admit_Params):
                    //If FOC is used
                    uz_FOC_set_PMSM_parameters(FOC_instance, ParaID_Data.ElectricalID_Output->PMSM_parameters);
                    uz_SpeedControl_set_PMSM_config(SpeedControl_instance, ParaID_Data.ElectricalID_Output->PMSM_parameters);
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
                ....
                }
            }

            ....
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
            ....
        }

#. Change the code of ``js_slowDataArray`` in the ``javascope.c`` file. 

   .. code-block:: C
        :linenos:
        :emphasize-lines: 9
        :caption: Changes to the ``javascope.c`` file. (Breaks in the code are marked with ``....``).

        //ParameterID
        extern uz_ParameterID_Data_t ParaID_Data;
        float activeState = 0.0f;
        float FluxMapCounter = 0.0f;
        float ArrayCounter = 0.0f;

        int JavaScope_initalize(DS_Data* data)
        {   
            ....
            // Store slow / not-time-critical signals into the SlowData-Array.
            // Will be transferred one after another
            // The array may grow arbitrarily long, the refresh rate of the individual values decreases.
            // Only float is allowed!
            js_slowDataArray[JSSD_FLOAT_u_d]                    = &(ParaID_Data.ActualValues.v_dq.d);
            js_slowDataArray[JSSD_FLOAT_u_q]                    = &(ParaID_Data.ActualValues.v_dq.q);
            js_slowDataArray[JSSD_FLOAT_i_d]                    = &(ParaID_Data.ActualValues.i_dq.d);
            js_slowDataArray[JSSD_FLOAT_i_q]                    = &(ParaID_Data.ActualValues.i_dq.q);
            js_slowDataArray[JSSD_FLOAT_speed]                  = &(data->av.mechanicalRotorSpeed);
            js_slowDataArray[JSSD_FLOAT_torque]                 = &(data->av.mechanicalTorqueObserved);
            js_slowDataArray[JSSD_FLOAT_PsiPM_Offline]          = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.Psi_PM_Vs);
            js_slowDataArray[JSSD_FLOAT_Lq_Offline]             = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.Lq_Henry);
            js_slowDataArray[JSSD_FLOAT_Ld_Offline]             = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.Ld_Henry);
            js_slowDataArray[JSSD_FLOAT_Rs_Offline]             = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.R_ph_Ohm);
            js_slowDataArray[JSSD_FLOAT_polePairs]              = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.polePairs);
            js_slowDataArray[JSSD_FLOAT_J]                      = &(ParaID_Data.ElectricalID_Output->PMSM_parameters.J_kg_m_squared);
            js_slowDataArray[JSSD_FLOAT_activeState]            = &(activeState);
            js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
            js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us]        = &ISR_execution_time_us;
            js_slowDataArray[JSSD_FLOAT_ISR_Period_us]          = &ISR_period_us;
            js_slowDataArray[JSSD_FLOAT_Milliseconds]           = &System_UpTime_ms;
            js_slowDataArray[JSSD_FLOAT_encoderOffset] 			= &(ParaID_Data.ElectricalID_Output->thetaOffset);
            js_slowDataArray[JSSD_FLOAT_ArrayCounter] 			= &(ArrayCounter);
            js_slowDataArray[JSSD_FLOAT_measArraySpeed] 		= &(ParaID_Data.MeasArraySpeed_pointer);
            js_slowDataArray[JSSD_FLOAT_measArrayTorque]		= &(ParaID_Data.MeasArrayTorque_pointer);
            js_slowDataArray[JSSD_FLOAT_ArrayControlCounter]	= &(ArrayCounter);
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
            js_slowDataArray[JSSD_FLOAT_MapCounter]             = &(FluxMapCounter);
            js_slowDataArray[JSSD_FLOAT_psidMap]                = &(ParaID_Data.Psi_D_pointer);
            js_slowDataArray[JSSD_FLOAT_psiqMap]                = &(ParaID_Data.Psi_Q_pointer);
            js_slowDataArray[JSSD_FLOAT_MapControlCounter]      = &(FluxMapCounter);
            return Status;
        }

#. In the ``JavaScope_update`` function in the ``javascope.c`` file add.

   .. code-block:: C
        :linenos:
        :emphasize-lines: 3,5
        :caption: Changes to the ``javascope.c`` file. (Breaks in the code are marked with ``....``).

        void JavaScope_update(DS_Data* data)
        {
            ....
            uz_ParameterID_update_transmit_values(&ParaID_Data, &activeState, &FluxMapCounter, &ArrayCounter);
            .... 
        }
