.. _uz_PID_GUI:

=============================
Custom uz_GUI for ParameterID
=============================

Since controlling the ParameterID only via the debugger windows is cumbersome and not very practical, a custom made uz_GUI is shipped as well. 
To use this however, additional setup steps have to be taken.
This page details these additional steps needed and how to use the uz_GUI.

.. _uz_PID_GUI_usage:

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
  
.. _uz_PID_GUI_setup:

Setup
=====

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
            PID_Enable_System,
            PID_Enable_Control,
            PID_Enable_ParameterID,
            PID_Disable_ParameterID,
            PID_Enable_ElectricalID,
            PID_Disable_ElectricalID,
            PID_Enable_FrictionID,
            PID_Disable_FrictionID,
            PID_Enable_TwoMassID,
            PID_Disable_TwoMassID,
            PID_Enable_FluxMapID,
            PID_Disable_FluxMapID,
            PID_Enable_OnlineID,
            PID_Disable_OnlineID,
            PID_Enable_Current_Control,
            PID_Enable_Speed_Control,
            PID_Disable_FOC_Control,
            PID_ACCEPT,
            PID_RESET,
            PID_EID_sampleTimeISR,
            PID_EID_n_ref_meas,
            PID_EID_goertzl_Amp,
            PID_EID_goertzl_Freq,
            PID_EID_DutyCyc,
            PID_EID_MaxContinousCurrent,
            PID_EID_Enable_IdentLQ,
            PID_EID_Disable_IdentLQ,
            PID_EID_Admit_Params,
            PID_FID_max_speed,
            PID_FID_N_Brk,
            PID_FID_N_Visco,
            PID_FID_s_step,
            PID_FID_Brk_Count,
            PID_FID_eta_speed,
            PID_FID_Array_Control_counter,
            PID_TMID_Scale_PRBS,
            PID_TMID_d_TMS_start,
            PID_TMID_n_ref,
            PID_TMID_f_min,
            PID_TMID_f_max,
            PID_TMID_Admit_Params,
            PID_FMID_i_d_start,
            PID_FMID_i_d_stop,
            PID_FMID_i_d_step,
            PID_FMID_i_q_start,
            PID_FMID_i_q_stop,
            PID_FMID_i_q_step,
            PID_FMID_Rs_ref,
            PID_FMID_Temp_ref,
            PID_FMID_identRAmp,
            PID_FMID_enable_ident_R,
            PID_FMID_disable_ident_R,
            PID_FMID_enable_AMM,
            PID_FMID_disable_AMM,
            PID_OID_Refresh_Flux_Maps,
            PID_OID_Reset_OnlineID,
            PID_OID_Enable_AutoCurrentControl,
            PID_OID_Disable_AutoCurrentControl,
            PID_OID_d_current_steps,
            PID_OID_q_current_steps,
            PID_OID_max_current,
            PID_OID_ref_temp,
            PID_OID_ref_Rs,
            PID_OID_max_speed,
            PID_OID_min_speed,
            PID_OID_Ident_range_factor,
            PID_OID_max_ident_pause,
            PID_OID_identR_Amp,
            PID_OID_Fluxmap_Control_counter,
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
        :emphasize-lines: 15,28,322,378
        :caption: Changes to the ``ipc_ARM.c`` file. (Breaks in the code are marked with ``....``).
    
        // slowData Naming Convention: Use JSSD_FLOAT_ as prefix
        // Do not change the first (zero) and last (end) entries.
        extern uz_ParameterID_Data_t PID_Data;
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
                    PID_Data.GlobalConfig.n_ref = value;
                    break;

                case (Set_Send_Field_2):
                    PID_Data.GlobalConfig.i_dq_ref.d = value;
                    break;

                case (Set_Send_Field_3):
                    PID_Data.GlobalConfig.i_dq_ref.q = value;
                    break; 
                ....
                //After all My_Button cases add the following
                //ParameterID

                case (PID_Enable_System):
                    ultrazohm_state_machine_set_enable_system(true);
                    break;

                case (PID_Enable_Control):
                    ultrazohm_state_machine_set_enable_control(true);
                    break;

                case (PID_Enable_ParameterID):
                    PID_Data.GlobalConfig.enableParameterID = true;
                    break;

                case (PID_Disable_ParameterID):
                    PID_Data.GlobalConfig.enableParameterID = false;
                    PID_Data.GlobalConfig.ElectricalID = false;
                    PID_Data.GlobalConfig.TwoMassID = false;
                    PID_Data.GlobalConfig.FrictionID = false;
                    PID_Data.GlobalConfig.FluxMapID = false;
                    PID_Data.GlobalConfig.OnlineID = false;
                break;

                case (PID_Enable_Current_Control):
                    if (ultrazohm_state_machine_get_state() != control_state) {
                        PID_Data.PID_Control_Selection = Current_Control;
                    }
                    break;

                case (PID_Enable_Speed_Control):
                    if (ultrazohm_state_machine_get_state() != control_state) {
                        PID_Data.PID_Control_Selection = Speed_Control;
                    }
                    break;

                case (PID_Disable_FOC_Control):
                    PID_Data.PID_Control_Selection = No_Control;
                    break;

                case (PID_Enable_ElectricalID):
                    PID_Data.GlobalConfig.ElectricalID = true;
                    break;

                case (PID_Disable_ElectricalID):
                    PID_Data.GlobalConfig.ElectricalID = false;
                    break;

                case (PID_Enable_FrictionID):
                    PID_Data.GlobalConfig.FrictionID = true;
                    break;

                case (PID_Disable_FrictionID):
                    PID_Data.GlobalConfig.FrictionID = false;
                    break;

                case (PID_Enable_TwoMassID):
                    PID_Data.GlobalConfig.TwoMassID = true;
                    break;

                case (PID_Disable_TwoMassID):
                    PID_Data.GlobalConfig.TwoMassID = false;
                    break;

                case (PID_Enable_FluxMapID):
                    PID_Data.GlobalConfig.FluxMapID = true;
                    break;

                case (PID_Disable_FluxMapID):
                    PID_Data.GlobalConfig.FluxMapID = false;
                    break;

                case (PID_Enable_OnlineID):
                    PID_Data.GlobalConfig.OnlineID = true;
                    break;

                case (PID_Disable_OnlineID):
                    PID_Data.GlobalConfig.OnlineID = false;
                    PID_Data.AutoRefCurrents_Config.enableCRS = false;
                    break;

                case (PID_ACCEPT):
                    PID_Data.GlobalConfig.ACCEPT = true;
                    break;

                case (PID_RESET):
                    PID_Data.GlobalConfig.Reset = true;
                    PID_Data.GlobalConfig.ElectricalID = false;
                    PID_Data.GlobalConfig.TwoMassID = false;
                    PID_Data.GlobalConfig.FrictionID = false;
                    PID_Data.GlobalConfig.FluxMapID = false;
                    PID_Data.GlobalConfig.OnlineID = false;
                    PID_Data.AutoRefCurrents_Config.enableCRS = false;
                    PID_Data.PID_Control_Selection = No_Control;
                    break;

                case (PID_EID_sampleTimeISR):
                    PID_Data.GlobalConfig.sampleTimeISR = value * 0.000001f;
                    break;

                case (PID_EID_n_ref_meas):
                    PID_Data.ElectricalID_Config.n_ref_measurement = value;
                    break;

                case (PID_EID_goertzl_Amp):
                    PID_Data.ElectricalID_Config.goertzlAmp = value;
                    break;

                case (PID_EID_goertzl_Freq):
                    PID_Data.ElectricalID_Config.goertzlFreq = value;
                    break;

                case (PID_EID_DutyCyc):
                    PID_Data.ElectricalID_Config.dutyCyc = value;
                    break;

                case (PID_EID_MaxContinousCurrent):
                    PID_Data.GlobalConfig.PMSM_config.I_max_Ampere = value;
                    break;

                case (PID_EID_Enable_IdentLQ):
                    PID_Data.ElectricalID_Config.identLq = true;
                    break;

                case (PID_EID_Disable_IdentLQ):
                    PID_Data.ElectricalID_Config.identLq = false;
                    break;

                case (PID_EID_Admit_Params):
                    //If FOC is used
                    uz_FOC_set_PMSM_parameters(FOC_instance, PID_Data.ElectricalID_Output->PMSM_parameters);
                    uz_SpeedControl_set_PMSM_config(SpeedControl_instance, PID_Data.ElectricalID_Output->PMSM_parameters);
                    break;

                case (PID_FID_max_speed):
                    PID_Data.FrictionID_Config.n_eva_max = value;
                    break;

                case (PID_FID_N_Brk):
                    PID_Data.FrictionID_Config.N_Brk = value;
                    break;

                case (PID_FID_N_Visco):
                    PID_Data.FrictionID_Config.N_Visco = value;
                    break;

                case (PID_FID_s_step):
                    PID_Data.FrictionID_Config.StepScale = value;
                    break;

                case (PID_FID_Brk_Count):
                    PID_Data.FrictionID_Config.BrkCount = value;
                    break;

                case (PID_FID_eta_speed):
                    PID_Data.FrictionID_Config.eta = value;
                    break;

                case (PID_TMID_Scale_PRBS):
                    PID_Data.TwoMassID_Config.ScaleTorquePRBS = value;
                    break;

                case (PID_TMID_d_TMS_start):
                    PID_Data.TwoMassID_Config.d_TMS_start = value;
                    break;

                case (PID_TMID_n_ref):
                    PID_Data.TwoMassID_Config.n_ref_measurement = value;
                    break;

                case (PID_TMID_f_min):
                    PID_Data.TwoMassID_Config.f_min = value;
                    break;

                case (PID_TMID_f_max):
                    PID_Data.TwoMassID_Config.f_max = value;
                    break;

                case (PID_FMID_i_d_start):
                    PID_Data.FluxMapID_Config.IDstart = value;
                    break;

                case (PID_FMID_i_d_stop):
                    PID_Data.FluxMapID_Config.IDstop = value;
                    break;

                case (PID_FMID_i_d_step):
                    PID_Data.FluxMapID_Config.IDstepsize = value;
                    break;

                case (PID_FMID_i_q_start):
                    PID_Data.FluxMapID_Config.IQstart = value;
                    break;

                case (PID_FMID_i_q_stop):
                    PID_Data.FluxMapID_Config.IQstop = value;
                    break;

                case (PID_FMID_i_q_step):
                    PID_Data.FluxMapID_Config.IQstepsize = value;
                    break;

                case (PID_FMID_Rs_ref):
                    PID_Data.FluxMapID_Config.R_s_ref = value;
                    break;

                case (PID_FMID_Temp_ref):
                    PID_Data.FluxMapID_Config.Temp_ref = value;
                    break;

                case (PID_FMID_identRAmp):
                    PID_Data.FluxMapID_Config.identRAmp = value;
                    break;

                case (PID_FMID_enable_ident_R):
                    PID_Data.FluxMapID_Config.identR = true;
                    break;

                case (PID_FMID_disable_ident_R):
                    PID_Data.FluxMapID_Config.identR = false;
                    break;

                case (PID_FMID_enable_AMM):
                    PID_Data.FluxMapID_Config.start_FM_ID = true;
                    break;

                case (PID_FMID_disable_AMM):
                    PID_Data.FluxMapID_Config.start_FM_ID = false;
                    break;

                case (PID_OID_Refresh_Flux_Maps):
                    PID_Data.calculate_flux_maps = true;
                    break;

                case (PID_OID_Reset_OnlineID):
                    PID_Data.OnlineID_Config.OnlineID_Reset = true;
                    PID_Data.AutoRefCurrents_Config.Reset = true;
                    PID_Data.AutoRefCurrents_Config.enableCRS = false;
                    break;

                case (PID_OID_Enable_AutoCurrentControl):
                    PID_Data.AutoRefCurrents_Config.enableCRS = true;
                    break;

                case (PID_OID_Disable_AutoCurrentControl):
                    PID_Data.AutoRefCurrents_Config.enableCRS = false;
                    break;

                case (PID_OID_d_current_steps):
                    PID_Data.AutoRefCurrents_Config.id_points = value;
                    break;

                case (PID_OID_q_current_steps):
                    PID_Data.AutoRefCurrents_Config.iq_points = value;
                    break;

                case (PID_OID_max_current):
                    PID_Data.AutoRefCurrents_Config.max_current = value;
                    break;

                case (PID_OID_ref_temp):
                    PID_Data.OnlineID_Config.Temp_ref = value;
                    break;

                case (PID_OID_ref_Rs):
                    PID_Data.GlobalConfig.PMSM_config.R_ph_Ohm = value;
                    break;

                case (PID_OID_max_speed):
                    PID_Data.OnlineID_Config.max_n_ratio = value;
                    break;

                case (PID_OID_min_speed):
                    PID_Data.OnlineID_Config.min_n_ratio = value;
                    break;

                case (PID_OID_Ident_range_factor):
                    PID_Data.OnlineID_Config.nom_factor = value;
                    break;

                case (PID_OID_max_ident_pause):
                    PID_Data.OnlineID_Config.Rs_time = value;
                    break;
                case (PID_OID_identR_Amp):
                    PID_Data.OnlineID_Config.identRAmp = value;
                    break;
                    
                case (PID_OID_Fluxmap_Control_counter):
                    PID_Data.FluxMap_Control_counter = value;
                    break;

                case (PID_FID_Array_Control_counter):
                    PID_Data.Array_Control_counter = value;
                    break;
                ....
                }
            }

            ....
            //Replace Bit 4-10 with the following
            /* Bit 4 - Ident_Lq */
            if (PID_Data.ElectricalID_Config.identLq == true) {
                js_status_BareToRTOS |= (1 << 13);
            } else {
                js_status_BareToRTOS &= ~(1 << 13);
            }

            /* Bit 5 - FluxMapID R-Online */
            if (PID_Data.FluxMapID_Config.identR == true) {
                js_status_BareToRTOS |= (1 << 14);
            } else {
                js_status_BareToRTOS &= ~(1 << 14);
            }

            /* Bit 6 - FluxMapID start */
            if (PID_Data.FluxMapID_Config.start_FM_ID == true) {
                js_status_BareToRTOS |= (1 << 15);
            } else {
                js_status_BareToRTOS &= ~(1 << 15);
            }

            /* Bit 7 - PID_FOC_CC */
            if (PID_Data.PID_Control_Selection == Current_Control) {
                js_status_BareToRTOS |= (1 << 16);
            } else {
                js_status_BareToRTOS &= ~(1 << 16);
            }

            /* Bit 8 - PID_FOC_SC */
            if (PID_Data.PID_Control_Selection == Speed_Control) {
                js_status_BareToRTOS |= (1 << 17);
            } else {
                js_status_BareToRTOS &= ~(1 << 17);
            }

            /* Bit 9 -PID_FOC_no_control */
            if (PID_Data.PID_Control_Selection == No_Control) {
                js_status_BareToRTOS |= (1 << 18);
            } else {
                js_status_BareToRTOS &= ~(1 << 18);
            }

            /* Bit 10 -ParameterID active */
            if (PID_Data.GlobalConfig.enableParameterID == true) {
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
        extern uz_ParameterID_Data_t PID_Data;
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
            js_slowDataArray[JSSD_FLOAT_u_d]                    = &(PID_Data.ActualValues.v_dq.d);
            js_slowDataArray[JSSD_FLOAT_u_q]                    = &(PID_Data.ActualValues.v_dq.q);
            js_slowDataArray[JSSD_FLOAT_i_d]                    = &(PID_Data.ActualValues.i_dq.d);
            js_slowDataArray[JSSD_FLOAT_i_q]                    = &(PID_Data.ActualValues.i_dq.q);
            js_slowDataArray[JSSD_FLOAT_speed]                  = &(data->av.mechanicalRotorSpeed);
            js_slowDataArray[JSSD_FLOAT_torque]                 = &(data->av.mechanicalTorqueObserved);
            js_slowDataArray[JSSD_FLOAT_PsiPM_Offline]          = &(PID_Data.ElectricalID_Output->PMSM_parameters.Psi_PM_Vs);
            js_slowDataArray[JSSD_FLOAT_Lq_Offline]             = &(PID_Data.ElectricalID_Output->PMSM_parameters.Lq_Henry);
            js_slowDataArray[JSSD_FLOAT_Ld_Offline]             = &(PID_Data.ElectricalID_Output->PMSM_parameters.Ld_Henry);
            js_slowDataArray[JSSD_FLOAT_Rs_Offline]             = &(PID_Data.ElectricalID_Output->PMSM_parameters.R_ph_Ohm);
            js_slowDataArray[JSSD_FLOAT_polePairs]              = &(PID_Data.ElectricalID_Output->PMSM_parameters.polePairs);
            js_slowDataArray[JSSD_FLOAT_J]                      = &(PID_Data.ElectricalID_Output->PMSM_parameters.J_kg_m_squared);
            js_slowDataArray[JSSD_FLOAT_activeState]            = &(activeState);
            js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &System_UpTime_seconds;
            js_slowDataArray[JSSD_FLOAT_ISR_ExecTime_us]        = &ISR_execution_time_us;
            js_slowDataArray[JSSD_FLOAT_ISR_Period_us]          = &ISR_period_us;
            js_slowDataArray[JSSD_FLOAT_Milliseconds]           = &System_UpTime_ms;
            js_slowDataArray[JSSD_FLOAT_encoderOffset] 			= &(PID_Data.ElectricalID_Output->thetaOffset);
            js_slowDataArray[JSSD_FLOAT_ArrayCounter] 			= &(ArrayCounter);
            js_slowDataArray[JSSD_FLOAT_measArraySpeed] 		= &(PID_Data.MeasArraySpeed_pointer);
            js_slowDataArray[JSSD_FLOAT_measArrayTorque]		= &(PID_Data.MeasArrayTorque_pointer);
            js_slowDataArray[JSSD_FLOAT_ArrayControlCounter]	= &(ArrayCounter);
            js_slowDataArray[JSSD_FLOAT_Stribtorque]            = &(PID_Data.FrictionID_Output->BrkTorque);
            js_slowDataArray[JSSD_FLOAT_Coulombtorque]          = &(PID_Data.FrictionID_Output->CoulTorque);
            js_slowDataArray[JSSD_FLOAT_Viscotorque]            = &(PID_Data.FrictionID_Output->ViscoTorque);
            js_slowDataArray[JSSD_FLOAT_TrainInertia]           = &(PID_Data.TwoMassID_Output->TrainInertia);
            js_slowDataArray[JSSD_FLOAT_LoadInertia]            = &(PID_Data.TwoMassID_Output->LoadInertia);
            js_slowDataArray[JSSD_FLOAT_c_est]                  = &(PID_Data.TwoMassID_Output->c_est_out);
            js_slowDataArray[JSSD_FLOAT_d_est]                  = &(PID_Data.TwoMassID_Output->d_est_out);
            js_slowDataArray[JSSD_FLOAT_I_rated]                = &(PID_Data.GlobalConfig.ratCurrent);
            js_slowDataArray[JSSD_FLOAT_totalRotorInertia]      = &(PID_Data.TwoMassID_Output->rotorInertia);
            js_slowDataArray[JSSD_FLOAT_Wtemp]                  = &(PID_Data.OnlineID_Output->Wtemp);
            js_slowDataArray[JSSD_FLOAT_FluxTempConst]          = &(PID_Data.FluxMap_Data->psi_temp_const);
            js_slowDataArray[JSSD_FLOAT_FluxTempError]          = &(PID_Data.FluxMap_Data->psi_temp_error);
            js_slowDataArray[JSSD_FLOAT_Ld_Online]              = &(PID_Data.OnlineID_Output->Ld_out);
            js_slowDataArray[JSSD_FLOAT_Lq_Online]              = &(PID_Data.OnlineID_Output->Lq_out);
            js_slowDataArray[JSSD_FLOAT_PsiPM_Online]           = &(PID_Data.OnlineID_Output->psi_pm_out);
            js_slowDataArray[JSSD_FLOAT_Rs_Online]              = &(PID_Data.OnlineID_Output->Rph_out);
            js_slowDataArray[JSSD_FLOAT_n_FluxPoints]           = &(PID_Data.FluxMap_MeasuringPoints);
            js_slowDataArray[JSSD_FLOAT_Rs_online_FMID]         = &(PID_Data.FluxMapID_Output->R_s);
            js_slowDataArray[JSSD_FLOAT_Wtemp_FMID]             = &(PID_Data.FluxMapID_Output->WindingTemp);
            js_slowDataArray[JSSD_FLOAT_MapCounter]             = &(FluxMapCounter);
            js_slowDataArray[JSSD_FLOAT_psidMap]                = &(PID_Data.Psi_D_pointer);
            js_slowDataArray[JSSD_FLOAT_psiqMap]                = &(PID_Data.Psi_Q_pointer);
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
            uz_ParameterID_update_transmit_values(&PID_Data, &activeState, &FluxMapCounter, &ArrayCounter);
            .... 
        }
