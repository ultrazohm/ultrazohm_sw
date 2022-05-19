.. _cil_pmsm_foc:

=======================================
Controlling a PMSM IP-Core with the FOC
=======================================

Aim of the tutorial
*******************

In this tutorial the :ref:`PMSM IP-Core <uz_pmsmModel>` will be added to the Vivado project and controlled using the :ref:`uz_FOC`.

Requirements
************

The following tutorial requires:

- :ref:`The previous tutorial <gate_signals>`.
- :ref:`Check the documentation about the PMSM IP-Core <uz_pmsmModel>`.
- :ref:`Check the documentation about the FOC<uz_FOC>`.

Initial steps
*************

#. Open the project in ``File -> Project -> Open``
#. Choose the file ``~/ultrazohm/ultrazohm_sw/vivado/project/ultrazohm.xpr``
#. In *Vivado* project open up the *Block Design*.
#. Extend the ``uz_user`` block.

   ..  _Vivado_overview:
   ..  figure:: ./img/Vivado1.png
       :align: center

       Block design in Vivado.

#. Right click on the ``uz_user`` block and select ``Add IP ...`` and search for the ``uz_pmsm_model``.
#. Double click on the result. The IP-Core should now reside inside the ``uz_user`` block.
#. Double click on the ``AXI smartconnect`` and increase the number of *Master interfaces* by one.
#. Connect the IP-Core as shown below.

   ..  _Vivado_pmsm:
   ..  figure:: ./img/Vivado2.png
       :align: center

       Block design in Vivado.

#. Click on the *Adress Editor* tab and assign the new IP-Block an address by right clicking on the entry and selecting *Assign*.

   ..  _Vivado_ip_address:
   ..  figure:: ./img/Vivado3.png
       :align: center

       Assign IP-address in Vivado.

   .. note:: 

      If the new IP-Core shows up as *unconnected* instead of *unassigned*, delete the ``AXI smartconnect`` in the ``uz_user`` block and add it again with the same connections.

#. Save the project,generate and export the bitstream as done in :ref:`gen_bitstream`.
#. Generate the Vitis workspace as done in :ref:`genvitis`.
#. Open the ``uz_global_configuration.h`` file and increase ``#define UZ_PMSMMODEL_MAX_INSTANCES`` by one. This way, one instance of the PMSM IP-Core driver can be used.
#. At the same time check, that the ``UZ_PWM_FREQUENCY`` is set to ``20.0e3f`` .
#. In the ``main.h`` add the following includes.

   * ``#include "IP_Cores/uz_pmsmMmodel/uz_pmsmModel.h"``
   * ``#include "xparameters.h"``
   * ``#include "uz/uz_FOC/uz_FOC.h"``

#. In the ``main.c`` add another entry (e.g. ``init_pmsm`` ) to the ``init_chain`` enum and ``switch-case`` structure after the ``init_software`` case.
#. Add the declaration as a global variable of the PMSM IP-Core before the ``main``-function.
#. Add to the new ``init_foc_pmsm`` case the config struct and the init-function as show in the :ref:`PMSM IP-core docs <uz_pmsmModel>`. 

   .. note:: 

      The base-address needed is different to the one specified in the :ref:`PMSM IP-core docs <uz_pmsmModel>`. 
      We implemented the IP-Core in the ``uz_user`` subblock in Vivado, therefore the IP-Core base address has to be adjusted to the following: ``XPAR_UZ_USER_UZ_PMSM_MODEL_0_BASEADDR`` .
      If the IP-Core is not included into the block design in a subblock, the base address form the :ref:`PMSM IP-core docs <uz_pmsmModel>` is the correct one.

#. Initialize in the same switch-case the FOC as shown :ref:`here <uz_FOC>`.
#. Your ``main.c`` should look similar to this now.

   .. code-block:: c  
        :linenos:
        :emphasize-lines: 7,13,14,28,30-66
        :caption: main.c code after changes. ``//....`` signals left out code.  

         //....
         enum init_chain
         {
           init_assertions = 0,
           init_gpios,
           init_software,
           init_foc_pmsm,
           init_ip_cores,
           print_msg,
           init_interrupts,
           infinite_loop
         };
         uz_pmsmModel_t *pmsm=NULL;
         uz_FOC* FOC_instance = NULL;
         //....
         int main(void)
         {
           int status = UZ_SUCCESS;
           while (1)
           {
               switch (initialization_chain)
               {
                   //....
                   case init_software:
                       Initialize_Timer();
                       uz_SystemTime_init();
                       JavaScope_initalize(&Global_Data);
                       initialization_chain = init_foc_pmsm;
                       break;
                   case init_foc_pmsm:;
                       struct uz_PMSM_t config_PMSM = {
                           .Ld_Henry = 3.00e-04f,
                           .Lq_Henry = 3.00e-04f,
                           .Psi_PM_Vs = 0.0075f};
                       struct uz_PI_Controller_config config_id = {
                           .Kp = 0.25f,
                           .Ki = 158.8f,
                           .samplingTime_sec = 0.00005f,
                           .upper_limit = 10.0f,
                           .lower_limit = -10.0f};
                       struct uz_PI_Controller_config config_iq = {
                           .Kp = 0.25f,
                           .Ki = 158.8f,
                           .samplingTime_sec = 0.00005f,
                           .upper_limit = 10.0f,
                           .lower_limit = -10.0f};
                       struct uz_FOC_config config_FOC = {
                           .decoupling_select = linear_decoupling,
                           .config_PMSM = config_PMSM,
                           .config_id = config_id,
                           .config_iq = config_iq};
                       FOC_instance = uz_FOC_init(config_FOC);
                       struct uz_pmsmModel_config_t pmsm_config={
                           .base_address=XPAR_UZ_USER_UZ_PMSM_MODEL_0_BASEADDR,
                           .ip_core_frequency_Hz=100000000,
                           .simulate_mechanical_system = true,
                           .r_1 = 0.085f,
                           .L_d = 3.00e-04f,
                           .L_q = 3.00e-04f,
                           .psi_pm = 0.0075f,
                           .polepairs = 4.0f,
                           .inertia = 3.24e-05f,
                           .coulomb_friction_constant = 0.01f,
                           .friction_coefficient = 0.001f};
                       pmsm=uz_pmsmModel_init(pmsm_config);
                       initialization_chain = init_ip_cores;
                   case init_ip_cores:
                    //....
               }
           }
           return (status);
         }

#. Add the code below to the ``isr.c`` . This will write the input and outputs of the IP-Core. The FOC ``uz_FOC_sample`` function will give out reference voltages for the PMSM IP-core.

   .. code-block:: c
        :linenos:
        :emphasize-lines: 1-19,25-34
        :caption: isr.c code after changes. ``//....`` signals left out code.  
   
         //....
         extern uz_pmsmModel_t *pmsm;
         extern uz_FOC* FOC_instance;
         uz_3ph_dq_t reference_currents_Amp = {0};
         uz_3ph_dq_t measured_currents_Amp = {0};
         uz_3ph_dq_t FOC_output_Volts = {0};
         float omega_el_rad_per_sec = 0.0f;
         struct uz_pmsmModel_inputs_t pmsm_inputs={
           .omega_mech_1_s=0.0f,
           .v_d_V=0.0f,
           .v_q_V=0.0f,
           .load_torque=0.0f
         };
         struct uz_pmsmModel_outputs_t pmsm_outputs={
           .i_d_A=0.0f,
           .i_q_A=0.0f,
           .torque_Nm=0.0f,
           .omega_mech_1_s=0.0f
         };
         void ISR_Control(void *data)
         {
           //....
           if (current_state==control_state)
           {
               uz_pmsmModel_trigger_input_strobe(pmsm);
               uz_pmsmModel_trigger_output_strobe(pmsm);
               pmsm_outputs=uz_pmsmModel_get_outputs(pmsm);
               measured_currents_Amp.d = pmsm_outputs.i_d_A;
               measured_currents_Amp.q = pmsm_outputs.i_q_A;
               omega_el_rad_per_sec = pmsm_outputs.omega_mech_1_s * 4.0f;
               FOC_output_Volts = uz_FOC_sample(FOC_instance, reference_currents_Amp, measured_currents_Amp, 24.0f, omega_el_rad_per_sec);
               pmsm_inputs.v_q_V=FOC_output_Volts.q;
               pmsm_inputs.v_d_V=FOC_output_Volts.d;
               uz_pmsmModel_set_inputs(pmsm, pmsm_inputs);
           }
           //....
         }

#. In the ``javascope.h`` replace the ``JS_OberservableData`` enum with the following.

   .. code-block:: c
     :caption: Adjust ``JS_OberservableData`` enum in ``javascope.h`` (R5) to measure pmsm_outputs

      // Do not change the first (zero) and last (end) entries.
      enum JS_OberservableData {
        JSO_ZEROVALUE=0,
        JSO_i_q,
        JSO_i_d,
        JSO_omega,
        JSO_v_d,
        JSO_v_q,
        JSO_ENDMARKER
      };

#. Change the description of ``send_field_1`` and ``send_field_2`` to ``i_q_ref`` and ``i_d_ref`` respectively. 
#. Adjust the labels of these *send_fields* to ``A`` .
#. Change the ``receive_field_X`` descriptions to:

   .. code-block:: c
     :caption: Adjust ``receive_field_X`` description

      RCV_FLD_ZEROVALUE=0,
      i_q,
      i_d,
      omega_m,
      v_q,
      v_d,
      receive_field_6,
      RCV_FLD_ENDMARKER

#. Change their label to:

   .. code-block:: c
     :caption: Adjust ``receive_field_X`` labels

      RCV_LABELS_ZEROVALUE=0,
      A,
      A,
      rad/s,
      V,
      V,
      sec,
      RCV_LABELS_ENDMARKER

#. Change the displayed values of the ``receive_field_X`` to the following. This is done to display the values 

   .. code-block:: c
     :caption: Adjust ``receive_field_X`` displayed values

      SLOWDAT_DISPLAY_ZEROVALUE=0,
	  JSSD_FLOAT_i_q,
	  JSSD_FLOAT_i_d,
	  JSSD_FLOAT_speed,
	  JSSD_FLOAT_u_q,
	  JSSD_FLOAT_u_d,
	  JSSD_FLOAT_SecondsSinceSystemStart,
	  JSSD_FLOAT_Error_Code,
	  SLOWDAT_DISPLAY_ENDMARKER

#. In the javascope.c file add the pmsm input/outputs and replace the content of the ``JavaScope_initalize`` function.

   .. code-block:: c
     :linenos:
     :emphasize-lines: 12-16,22-27
     :caption: javascope.c code after changes. ``//....`` marks left out code.  

      //....
      extern struct uz_pmsmModel_outputs_t pmsm_outputs;
      extern struct uz_pmsmModel_inputs_t pmsm_inputs;

      int JavaScope_initalize(DS_Data* data)
      {
        //....
        // Store every observable signal into the Pointer-Array.
        // With the JavaScope, signals can be displayed simultaneously
        // Changing between the observable signals is possible at runtime in the JavaScope.
        // the addresses in Global_Data do not change during runtime, this can be done in the init
        js_ch_observable[JSO_i_q] = &pmsm_outputs.i_q_A;
        js_ch_observable[JSO_i_d] = &pmsm_outputs.i_d_A;
        js_ch_observable[JSO_omega] = &pmsm_outputs.omega_mech_1_s;
        js_ch_observable[JSO_v_d] = &pmsm_inputs.v_d_V;
        js_ch_observable[JSO_v_q] = &pmsm_inputs.v_q_V;

        // Store slow / not-time-critical signals into the SlowData-Array.
        // Will be transferred one after another
        // The array may grow arbitrarily long, the refresh rate of the individual values decreases.
        // Only float is allowed!
        js_slowDataArray[JSSD_FLOAT_u_d] 			        = &(pmsm_inputs.v_d_V);
        js_slowDataArray[JSSD_FLOAT_u_q] 			        = &(pmsm_inputs.v_q_V);
        js_slowDataArray[JSSD_FLOAT_i_d] 			        = &(pmsm_outputs.i_d_A);
        js_slowDataArray[JSSD_FLOAT_i_q] 			        = &(pmsm_outputs.i_q_A);
        js_slowDataArray[JSSD_FLOAT_speed] 		         	= &(pmsm_outputs.omega_mech_1_s);
        js_slowDataArray[JSSD_FLOAT_SecondsSinceSystemStart]= &(System_UpTime_seconds);
      }
      //....

#. In the ``ipc_ARM.c`` file add the ``extern uz_3ph_dq_t reference_currents_Amp`` struct.
#. Adjust the ``Set_Send_Field_1`` and ``Set_Send_Field_2`` cases with the following code. This way we can transmit reference currents from the GUI to the R5.

   .. code-block:: c
     :linenos:
     :emphasize-lines: 2,8,12
     :caption: ipc_ARM.c code after changes. ``//....`` marks left out code.  

      //....
      extern uz_3ph_dq_t reference_currents_Amp;

      int ipc_Control_func(uint32_t msgId, float value, DS_Data *data)
      {
         //.... 
         case (Set_Send_Field_1):
            reference_currents_Amp.q = value;
            break;

         case (Set_Send_Field_2):
            reference_currents_Amp.d = value;
            break;
         //....
      }

#. Build the changes. If errors exist, fix them. 
#. Flash the UltraZohm and connect the GUI.
#. Choose the appropriate channels in the *Setup Scope* and set a reference current for the q-axis, e.g. 3A. 
#. Press *Enable System* and *Enable Control* and you should see, that the PMSM is running.

   * Notice, that the speed changes, if the current increases. This is the case, because the PMSM IP-Core is configured, to simulate the mechanical system.
   * Increasing the current over ~9.32A is not possible at first. This is the case, because the FOC has a :ref:`uz_spacevectorlimiation` to limit the voltage from exceeding the DC-link voltage.
   * Setting a negative d-current (e.g. -5A) lets you increase the q-current further. The machine operates now in the field weakening territory.

#. Try out different combinations of d- and q-currents and observe how the PMSM model reacts.
#. This concludes the fifth tutorial.