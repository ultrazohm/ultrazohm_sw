=================
Modifying the GUI
=================

Aim of the tutorial
*******************

In this tutorial the chirp-waves from the :ref:`previous tutorial <first_changes>` will be reused. But this time the chirp waves will only start, if three separate button in the GUI are pressed.

Requirements
************

The following tutorial requires:

- :ref:`Finishing the previous tutorial <first_changes>`.
- Read the :ref:`section about modifying the GUI <javascope_customizing>`.


Guideline
*********

#. The GUI has 8 general purpose buttons in the Control panel, which can be mapped to our needs.

   ..  _GUI_buttons:
   ..  figure:: ./img/buttons.png
       :align: center

       General purpose buttons in the Control panel of the GUI

#. Add three new global ``bool`` variables to the ``isr.c`` file which will be used to enable the chirp waves.
#. Add if-statements with the new variables for every chirp-wave sample function. It should look similar to this. 

   .. code-block:: c
     :linenos:
     :emphasize-lines: 1,47
     :caption: isr.c code after changes. ``//....`` signals left out code.  

      //....
      // Global variable structure
      extern DS_Data Global_Data;

      extern uz_wavegen_chirp* chirp_instance1;
      extern uz_wavegen_chirp* chirp_instance2;
      extern uz_wavegen_chirp* chirp_instance3;
      float chirp_output1 = 0.0f;
      float chirp_output2 = 0.0f;
      float chirp_output3 = 0.0f;
      bool is_chirp1_active = false;
      bool is_chirp2_active = false;
      bool is_chirp3_active = false;


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
            if (is_chirp1_active) { chirp_output1 = uz_wavegen_chirp_sample(chirp_instance1); }
            if (is_chirp2_active) { chirp_output2 = uz_wavegen_chirp_sample(chirp_instance2); }
            if (is_chirp3_active) { chirp_output3 = uz_wavegen_chirp_sample(chirp_instance3); }
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

#. Open the ``ipc_ARM.c`` file and add the three bool variables with the ``extern`` keyword.