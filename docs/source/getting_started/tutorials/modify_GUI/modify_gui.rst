.. _modify_gui:

=================
Modifying the GUI
=================

Aim of the tutorial
*******************

In this tutorial the :ref:`three-phase-wave <uz_wavegen_three_phase>` from the wavegen library will be used. 
Configuration values of the three-phase wave will be modified during runtime via the GUI.

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

#. **Discard** any changes you made to the code basis in the :ref:`previous tutorial <first_changes>`.
#. Add the include statement ``#include "uz/uz_Transformation/uz_Transformation.h"`` and ``#include "uz/uz_wavegen/uz_wavegen.h"`` to the ``main.h`` file.

   * This ``uz_Transformation.h`` header file includes structs for common coordinate systems used in the motor control world (e.g. abc-, dq0-system, etc.).
   * For further information see :ref:`uz_transformation`.
  
#. Add a new global ``bool`` variable to the ``isr.c`` file which will be used to enable the three-phase wave.
#. Add a new global ``uz_3ph_abc_t`` struct to the same file. This will store the calculated values of the ``uz_wavegen_three_phase_sample`` function.
#. Add three new global ``float`` variables titled, *amplitude, frequency* and *offset* and initialize them with values. 
#. Add an if-statement with the new bool variable inside the ``if (current_state==control_state)`` statement.
#. Add the ``uz_wavegen_three_phase_sample`` function inside your new if-statement.

   .. code-block:: c
     :linenos:
     :emphasize-lines: 5-9,29
     :caption: isr.c code after changes. ``//....`` signals left out code.  

      //....
      // Global variable structure
      extern DS_Data Global_Data;

      uz_3ph_abc_t three_phase_output = {0};
      bool is_three_phase_active = false;
      float amplitude = 2.0f;
      float frequency = 5.0f;
      float offset = 0.0f;


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
            if (is_three_phase_active) { three_phase_output = uz_wavegen_three_phase_sample(amplitude, frequency, offset); }
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

#. In the ``javascope.c`` file add the ``three_phase_output`` struct with the ``extern`` keyword.
#. Replace the assignment of the addresses for the ``JSO_ua`` , ``JSO_ub`` and ``JSO_uc`` members of the ``js_ch_observable`` array with the three elements of the ``three_phase_output`` struct.

   .. code-block:: c
     :linenos:
     :emphasize-lines: 2,7-9
     :caption: javascope.c code after changes. ``//....`` marks left out code.  

      //....
      extern uz_3ph_abc_t three_phase_output;

      int JavaScope_initalize(DS_Data* data)
      {
         //.... 
         js_ch_observable[JSO_ua] 			= &three_phase_output.a;
         js_ch_observable[JSO_ub] 			= &three_phase_output.b;
         js_ch_observable[JSO_uc] 			= &three_phase_output.c;
         //.... 
      }
      //....

#. Open the ``ipc_ARM.c`` file and add the ``is_three_phase_active`` variable with the ``extern`` keyword.

   * This file processes the commands send from the GUI.
   * This includes e.g. the commands for the *Enable System* and *Enable Control* buttons, the *8 My_Buttons* and the *send_fields*.

#. Scroll down to the cases of the ``My_Buttons`` in the switch-case structure and assign the variable ``is_three_phase_active`` the value *true* in the ``case (My_Button_4):`` .

   * This sets the value of the bool variable to true, if the ``My_Button_4`` is pressed.
   * Keep in mind, that the corresponding button in the GUI is not a toggle button. Pressing this button will always set variable to true. It will not change the value depending on if the button is selected (pressed) or unselected.

#. To be able to disable the three-phase-wave again, assign in the case ``case (My_Button_5):`` the variable ``is_three_phase_active`` the value *false*.
#. Set the ``ultrazohm_state_machine_set_userLED()`` to true, if ``My_Button_4`` is pressed and to false, if ``My_Button_5`` is pressed. This will turn the *userLED* on, when the three-phase wave is active.
#. Comment in the code of ``Bit_7`` and ``Bit_8`` for ``My_Button_4`` and ``My_Button_5`` and change it to the following.

   * These status-bit relay information from the R5 back to the GUI.
   * They are e.g. used to sync the *Ready LED*, *Running LED* etc.
   * For this specific tutorial these two bits are used to relay the information to the GUI, that the button press was acknowledged by the R5.

   .. code-block:: c
     :linenos:
     :emphasize-lines: 2,8,9,13,14,17-29
     :caption: ipc_ARM.c code after changes. ``//....`` marks left out code.  

      //....
      extern bool is_three_phase_active;

      int ipc_Control_func(uint32_t msgId, float value, DS_Data *data)
      {
         //.... 
         case (My_Button_4):
            is_three_phase_active = true;
            ultrazohm_state_machine_set_userLED(true);
            break;

         case (My_Button_5):
            is_three_phase_active = false;
            ultrazohm_state_machine_set_userLED(false);
            break;
         //.... 
         /* Bit 7 - My_Button_4 */
         if (is_three_phase_active) {
            js_status_BareToRTOS |= ~(1 << 7);
         } else {
            js_status_BareToRTOS &= ~(1 << 7);
         }

         /* Bit 8 - My_Button_5 */
         if (!is_three_phase_active) {
            js_status_BareToRTOS |= ~(1 << 8);
         } else {
            js_status_BareToRTOS &= ~(1 << 8);
	      }
         //....
      }

#. Open the uz_GUI and select the *ua, ub* and *uc* members in the channel selection. Set every other channel to ``(0) ZeroValue``.
#. Change the UltraZohm to the *Control state* by pressing the respective buttons.
#. Because of the additional if-statement in the ``isr.c`` file no three-phase wave should be visible in the Scope.
#. Press the ``My_Button_4``. The *userLED* should turn on and the three-phase wave should be visible in the Scope and the field below the ``My_Button_4`` should turn green.

   ..  _GUI_three_phase:
   ..  figure:: ./img/GUI_three_phase.png
       :align: center

       Visible three phase wave

#. Disable and enable the three-phase wave with the respective buttons to see that everything is working as intended. If it is successful, close the GUI.
#. It is possible to send values from the GUI to the R5 via the *send_fields*. These will be used to modify the three-phase wave during runtime.

   * Six values are available that can be used as references or setpoints for the user application.
   * For further information refer to :ref:`JavaScope`.

   ..  _GUI_sendfield1:
   ..  figure:: ./img/GUI_sendfield1.png
       :align: center

       general purpose *Send_fields* 

#. In the ``javascope.h`` file we will modify the *send_fields* labels to our needs.
#. Change the description for the *send_fields* from ``send_field_1`` to ``send_field_3`` to ``amplitude`` , ``offset`` and ``frequency`` .
#. You can adjust the labels next to the *send_fields*. Change them for the first three *send_fields* to e.g. *V*.

   * These descriptions and labels are purely cosmetic.
   * They do not change anything in the code basis. They are therefore commented out as well.
  
#. Go to the ``ipc_ARM.c`` file and add the three variables ``amplitude`` , ``frequency`` and ``offset`` from the ``isr.c`` with the extern keyword.
#. In the cases ``Set_Send_Field_1`` to ``Set_Send_Field_3`` give the corresponding variable the value ``value``. 

   * I.e. description says for ``send_field_1`` now ``amplitude``, ``amplitude`` has to be assigned in the ``Set_Send_Field_1`` case.
   * Do not change the name of the case itself. 
   * With these changes, the value in the text box of the *Send_fields* will be given to the specified variable from the R5. 

#. The final version of the ipc_ARM.c file should look similar to this.

   .. code-block:: c
     :linenos:
     :emphasize-lines: 3-5,21,25,29
     :caption: ipc_ARM.c code after changes. ``//....`` marks left out code.  

      //....
      extern bool is_three_phase_active;
      extern float amplitude;
      extern float frequency;
      extern float offset;

      int ipc_Control_func(uint32_t msgId, float value, DS_Data *data)
      {
         //.... 
         case (My_Button_4):
            is_three_phase_active = true;
            ultrazohm_state_machine_set_userLED(true);
            break;

         case (My_Button_5):
            is_three_phase_active = false;
            ultrazohm_state_machine_set_userLED(false);
            break;
         //.... 
         case (Set_Send_Field_1):
            amplitude = value;
            break;

         case (Set_Send_Field_2):
            frequency = value;
            break;

         case (Set_Send_Field_3):
            offset = value;
            break;
         //....
         /* Bit 7 - My_Button_4 */
         if (is_three_phase_active) {
            js_status_BareToRTOS |= ~(1 << 7);
         } else {
            js_status_BareToRTOS &= ~(1 << 7);
         }

         /* Bit 8 - My_Button_5 */
         if (!is_three_phase_active) {
            js_status_BareToRTOS |= ~(1 << 8);
         } else {
            js_status_BareToRTOS &= ~(1 << 8);
	      }
         //....
      }

#. Start up the GUI, select the *ua, ub* and *uc* members in the channel selection and activate the three-phase wave. 
#. Try different values for the *amplitude, offset* and *frequency* and see how the changes reflect in the scope.

   ..  _GUI_sendfield2:
   ..  figure:: ./img/GUI_sendfield2.png
       :align: center

       Visible three phase wave with different config settings and the changes made to the GUI

#. This concludes the third tutorial.