.. _first_changes:

=============================
First changes to the codebase
=============================

Aim of the tutorial
*******************

In this tutorial a multi-instances module from the :ref:`wave_generator` library of the UltraZohm project will be used and the output displayed in the GUI. 

Requirements
************

The following tutorial requires:

- Finished the tutorial :ref:`first_steps`.


Guideline
*********

#. For the purpose of this tutorial, multiple instances of the :ref:`uz_wavegen_chirp` will be used.
#. Open the ``uz_global_configuration.h`` file and look at the ``#define UZ_WAVEGEN_CHIRP_MAX_INSTANCES`` number. 

   * Currently *two* instances of this module are allowed. This means, that the ``uz_wavegen_chirp_init`` function can only be called twice, before an assertion stops the processor.
   * This is done to ensure a proper static memory allocation for this module. Since allocation memory for 50 instances, when only e.g. three are needed, is wasteful, the max amount of possible instances is limited by this define.
   * This procedure is the same for every multiple instance module (e.g. :ref:`IP-Core drivers<ip_cores>`, :ref:`uz_piController` etc.).
   * For further information see :ref:`static_memory_allocation`.

#. In this tutorial three instances of the :ref:`uz_wavegen_chirp` will be used. Therefore adjust the number after the define to ``3U`` .
#. Follow the guideline for an :ref:`uz_wavegen_chirp_example` implementation. Do this procedure three times.

   * Include the header file ``#include "uz/uz_wavegen/uz_wavegen.h"`` in the ``main.h`` header of the R5 processor (Baremetal).
   * Declare three different configuration structs with different values.
   * Initialize three different instances with three separate calls of the ``uz_wavegen_chirp_init`` function.
   * Create for the above steps a new case in the ``initialization_chain`` switch case and insert it after the ``init_software`` case.
  
#. After this, your ``main.c`` file should look something like this. ``//....`` signals that code has been left out of.

   * The declaration of the three instances outside of the main is necessary, so that they can be accessed by other c-files.
   * Since the config-structs are not needed after initialization, they can be declared local to the main function.

   .. code-block:: c
     :linenos:
     :emphasize-lines: 10,18-20,34,36-65
     :caption: main.c code after changes. ``//....`` marks left out code. 

      // Includes from own files
      #include "main.h"

      //....
      enum init_chain
      {
         init_assertions = 0,
         init_gpios,
         init_software,
         init_chirp,
         init_ip_cores,
         print_msg,
         init_interrupts,
         infinite_loop
      };
      enum init_chain initialization_chain = init_assertions;

      uz_wavegen_chirp* chirp_instance1 = NULL;
      uz_wavegen_chirp* chirp_instance2 = NULL;
      uz_wavegen_chirp* chirp_instance3 = NULL;

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
                  initialization_chain = init_chirp;
                  break;
               case init_chirp:;
                  struct uz_wavegen_chirp_config config_chirp1 = {
                     .amplitude = 2.0f,
                     .start_frequency_Hz = 1.0f,
                     .end_frequency_Hz = 10.0f,
                     .duration_sec = 5.0f,
                     .initial_delay_sec = 0.0f,
                     .offset = 0.0f
                  };
                  struct uz_wavegen_chirp_config config_chirp2 = {
                     .amplitude = 3.0f,
                     .start_frequency_Hz = 1.0f,
                     .end_frequency_Hz = 20.0f,
                     .duration_sec = 20.0f,
                     .initial_delay_sec = 5.0f,
                     .offset = 1.0f
                  };
                  struct uz_wavegen_chirp_config config_chirp3 = {
                     .amplitude = 4.0f,
                     .start_frequency_Hz = 1.0f,
                     .end_frequency_Hz = 50.0f,
                     .duration_sec = 30.0f,
                     .initial_delay_sec = 10.0f,
                     .offset = 2.0f
                  };
                  chirp_instance1 = uz_wavegen_chirp_init(config_chirp1);
                  chirp_instance2 = uz_wavegen_chirp_init(config_chirp2);
                  chirp_instance3 = uz_wavegen_chirp_init(config_chirp3);
                  initialization_chain = init_ip_cores;
                  break;
               case init_ip_cores:
                  //....;
               default:
                  break;
            }
         }
         return (status);
      }

#. Open up the ``isr.c`` file of the R5 processor (Baremetal).

   * This file is used to call the the sample functions (i.e. functions which calculate values for the current time step) of the wavegen module.
   * This is done in the ISR and not the main, since the ISR is called with a constant sample time (through an interrupt), which enables the use of discrete time models. 
   * The ``while(1)`` loop in ``main.c`` does not run with a constant sample time. 

#. Declare in the ``isr.c`` file the three instances again, but this time with the ``extern`` keyword in front.

   * This keyword specifies that the variable is defined in another file. The ``extern`` keyword must be applied in all files, in which the variable is used, except in which the variable is initially defined.
   * This only works, if the variable is global, i.e. declared outside the e.g. main-function.
   * It, in essence, allows the variable to be shared over multiple c-files.

#. Create three global float values, to which the output of the ``uz_wavegen_chirp_sample`` can be passed.
#. Add the three function calls ``uz_wavegen_chirp_sample`` for the three instances in the if-statement.

   * This if-statement prevents the code from being executed, unless the UltraZohm is in the ``Control`` state.  
   * The UZ has four different states (see :ref:`r5_statemachine`):
  
      #. Idle state: *Ready LED* will blink slowly, all IO and PWM pins are disabled.
      #. Running state: *Ready LED* will blink fast and the IP and PWM pins are enabled.
      #. Control state: *Ready LED* will blink fast, *Running LED* will turn on and the specific code inside the if-statement in the ISR will be executed.
      #. Error state: *Error LED* turns on, Running and Control state are disabled and the IO and PWM pins get disabled.

#. Your ``isr.c`` should now look similar to this.

   .. code-block:: c
     :linenos:
     :emphasize-lines: 5-10,29-31
     :caption: isr.c code after changes. ``//....`` marks left out code.  

      //....
      // Global variable structure
      extern DS_Data Global_Data;

      extern uz_wavegen_chirp* chirp_instance1;
      extern uz_wavegen_chirp* chirp_instance2;
      extern uz_wavegen_chirp* chirp_instance3;
      float chirp_output1 = 0.0f;
      float chirp_output2 = 0.0f;
      float chirp_output3 = 0.0f;

      //==============================================================================================================================================================
      //----------------------------------------------------
      // INTERRUPT HANDLER FUNCTIONS
      // - triggered from PL
      // - start of the control period
      //----------------------------------------------------
      static void ReadAllADC();

      void ISR_Control(void *data)
      {
         uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
         ReadAllADC();
         update_speed_and_position_of_encoder_on_D5(&Global_Data);

         platform_state_t current_state=ultrazohm_state_machine_get_state();
         if (current_state==control_state)
         {
            chirp_output1 = uz_wavegen_chirp_sample(chirp_instance1);
            chirp_output2 = uz_wavegen_chirp_sample(chirp_instance2);
            chirp_output3 = uz_wavegen_chirp_sample(chirp_instance3);
         }
         uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
         // Set duty cycles for three-level modulator
         PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
                           Global_Data.rasv.halfBridge2DutyCycle,
                           Global_Data.rasv.halfBridge3DutyCycle);
         JavaScope_update(&Global_Data);
         // Read the timer value at the very end of the ISR to minimize measurement error
         // This has to be the last function executed in the ISR!
         uz_SystemTime_ISR_Toc();
      }
      //....

#. To display the different chirp waves on the JavaScope, the ``javascope.c`` and ``javascope.h`` file will be modified. 
#. Open the ``javascope.h`` file and add three new entrys to the ``JS_OberservableData`` enum. (e.g. JSO_Chirpwave1, etc.).

   * Here the names for all observable data are stored in an enum.
   * Observable data include all signals which can be displayed in the JavaScope.

   .. code-block:: c
     :linenos:
     :emphasize-lines: 6-8
     :caption: javascope.h code after changes

        #include "APU_RPU_shared.h"
        
        // Do not change the first (zero) and last (end) entries.
        enum JS_OberservableData {
           JSO_ZEROVALUE=0,
           JSO_Chirpwave1,
           JSO_Chirpwave2,
           JSO_Chirpwave3,
           JSO_ISR_ExecTime_us,
           JSO_ISR_Period_us,
           JSO_lifecheck,
           JSO_theta_mech,
           JSO_ua,
           JSO_ub,
           JSO_uc,
           JSO_ia,
           JSO_ib,
           JSO_ic,
           JSO_id,
           JSO_iq,
           JSO_ud,
           JSO_uq,
           JSO_Speed_rpm,
           JSO_LoadSpeed_rpm,
           JSO_volt_temp,
           JSO_SoC_init,
           JSO_Theta_el,
           JSO_Theta_mech,
           JSO_LoadTheta_mech,
           JSO_DeltaTheta_mech,
           JSO_Wtemp,
           JSO_Rs_mOhm,
           JSO_Ld_mH,
           JSO_Lq_mH,
           JSO_PsiPM_mVs,
           JSO_ENDMARKER
        };

  
#. Add to the ``javascope.c`` file with the ``extern`` keyword the three chirp_output float variables from the ``isr.c``.
#. In the ``JavaScope_initalize`` function add the three new entries to the ``js_ch_observable`` array.

   * Here the addresses of the variables are assigned to the specific elements in the ``js_ch_observable`` array corresponding to its enum.
   * The value of the variable itself will be automatically updated in the ``JavaScope_update`` function (no changes have to be made). 
  
#. The ``javascope.c`` file should look like this now.

   .. code-block:: c
     :linenos:
     :emphasize-lines: 2-4,12-14
     :caption: javascope.c code after changes. ``//....`` marks left out code.  

      //....
      extern float chirp_output1;
      extern float chirp_output2;
      extern float chirp_output3;

      int JavaScope_initalize(DS_Data* data)
      {
         //.... 
         js_ch_observable[JSO_ISR_ExecTime_us] = &ISR_execution_time_us;
         js_ch_observable[JSO_lifecheck]   	= &lifecheck;
         js_ch_observable[JSO_ISR_Period_us]	= &ISR_period_us;
         js_ch_observable[JSO_Chirpwave1]   = &chirp_output1;
         js_ch_observable[JSO_Chirpwave2]   = &chirp_output2;
         js_ch_observable[JSO_Chirpwave3]   = &chirp_output3;
         //.... 
      }
      //....

#. Build the changes and if no errors exist flash the UZ.
#. Open the JavaScope and connect it and select the three new signals in the *Setup Scope* page. Set every other channel to ``(0) ZeroValue`` . 

   * You can hide the visible channels by clicking on the corresponding entry in the legend of the scope.
   * Clicking on the entry of the legend in the scope again makes that specific channel visible again.
   * Do this for ``CH4`` and ``CH5`` (``CH6`` to ``CH20`` are hidden by default). This way, no unnecessary lines with ZeroValue are visible.
  
#. Press the *Enable System* and the *Enable Control* buttons. Now the chirp waves should be visible in the scope.

   ..  _GUI_chirp:
   ..  figure:: ./img/GUI_chirp.png
       :align: center

       Visible chirp signals

#. This concludes the second tutorial.