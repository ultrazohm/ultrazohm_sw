.. _gate_signals:

============
Gate Signals
============

Aim of the tutorial
*******************

In this tutorial, the digital voltage adapter board is used to generate a PWM signal at D1.
You can use a scope to measure the gate Signal.
An assertion is triggered to showcase its use.

After this tutorial, you can:

 - Use the PWM-module
 - Test the optical adapter board

Requirements
************

The following tutorial requires:

- :ref:`The previous tutorial <modify_gui>`.
- :ref:`Digital voltage card <digitalVoltage>` in slot D1.
- Some sort of oscilloscope

Guideline
*********

#. We will use the three-phase wave from the previous tutorial to give out gate signals on the digital voltage card.
#. In your custom if-statement in the isr.c assign the three ``Global_Data.rasv.halfBridgeXDutyCycle`` variables the values from the ``three_phase_output`` struct. 
#. Add an else-if-statement to your if-statement which sets all three ``Global_Data.rasv.halfBridgeXDutyCycle`` to ``0.0f`` again. The else-if-statement should trigger, if either the ``current_state`` is not in the ``control_state`` or the ``is_three_phase_active`` value is ``false``.

   * This is done to reset the DutyCycles and prevents those variables from still carrying a value unequal to zero after the *Control State* has been left.
   * This way, activating the *Running state* will not output the latest value from the ``three_phase_output`` struct, but instead it will output 0 to the gates.

#. Set the initial value of the variables ``amplitude``, ``frequency`` and ``offset`` to ``1.0f``, ``1.0f`` and ``0.5f`` respectively.

   .. code-block:: c
     :linenos:
     :emphasize-lines: 2-4,9-12,14-18
     :caption: isr.c code after changes. ``//....`` signals left out code.  

      //....
      float amplitude = 1.0f;
      float frequency = 1.0f;
      float offset = 0.0f;
      //....
      if (current_state==control_state)
      {
        if (is_three_phase_active) {
            three_phase_output = uz_wavegen_three_phase_sample(amplitude, frequency, offset);
            Global_Data.rasv.halfBridge1DutyCycle = three_phase_output.a;
            Global_Data.rasv.halfBridge2DutyCycle = three_phase_output.b;
            Global_Data.rasv.halfBridge3DutyCycle = three_phase_output.c;
        }
      } else if (current_state!=control_state || !is_three_phase_active) {
          Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
          Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
          Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
      }
      uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
      //....

#. Build the changes and flash the UltraZohm.
#. Switch to the *Debug-View* in *Vitis*, select the *Vitis-Serial-Terminal*, click on the green **+**-Symbol and connect the serial port to the USB-port with which your JTAG-cabel is connected to the computer.

    * This connects the Vitis serial port with the UltraZohm.
    * This way, messages from the UltraZohm can be read in the *Vitis-Serial-Terminal*.
    * On Windows, the Port may be called *COM6*.
  
   ..  _Vitis_serial_port:
   ..  figure:: ./img/Vitis1.png
       :align: center

       Vitis view to connect serial port.

#. Connect the GUI and press the *Enable System* and *Enable Control* buttons.
#. After pressing the ``My_Button4``, the UltraZohm should switch into its *Error State*. This happens, because an assertion got triggered. The red *Error LED* should light up as well.

   * Assertions are used to guarantee that the conditions and limits of a function are met at runtime. 
   * The UltraZohm error handling follows the concept to fail loudly, i.e., all assertions stop the processor and require a power cycle. This means, that if an assertion fires, the UltraZohm is brought into a safe state.
   * For further information see :ref:`assertions`.

#. In the *Vitis-Serial-Terminal* it should say where the assertion triggered (e.g. ``Assertion in file uz_PWM_SS_2L_hw.c on line 13`` ).

   * This message tells you exactly which line in the stated file did trigger the assertion.
   * This can be used to give you a clue, which settings violated the function parameters.

#. In our case the assertion got triggered, because the DutyCycles we gave the function ``uz_PWM_SS_2L_set_duty_cycle`` exceeded the value of ``1.0f`` .
#. To fix this, set the initial value of the ``amplitude`` variable to ``0.5f`` .
#. Build the workspace, flash the UltraZohm and connect the GUI.
#. Enable the System & Control and activate the three-phase wave by pressing the respective button in the GUI, as done in :ref:`the previous tutorial <modify_gui>`.
#. Open up your oscilloscope and measure the output voltages at the pins of the Digital voltage card with a probe. A different PWM signal with a constantly changing DutyCycle should be visible on the first 6 pins (Pin 1-6 in the :ref:`layout <digitalVoltage>`).

   ..  _Picoscope_dutycycles:
   ..  figure:: ./img/Picoscope.png
       :align: center

       Visible PWM signals in an oscilloscope.

#. Delete the function call ``uz_wavegen_three_phase_sample`` and the if-statement regarding ``is_three_phase_active``, but keep the assignment of the ``halfBridgeXDutyCycle`` 's. Adjust the else-if-statement accordingly.

   .. code-block:: c
     :linenos:
     :emphasize-lines: 4-6,7-11
     :caption: isr.c code after changes. ``//....`` signals left out code.  

      //....
      if (current_state==control_state)
      {
            Global_Data.rasv.halfBridge1DutyCycle = three_phase_output.a;
            Global_Data.rasv.halfBridge2DutyCycle = three_phase_output.b;
            Global_Data.rasv.halfBridge3DutyCycle = three_phase_output.c;
      } else {
          Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
          Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
          Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
      }
      uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
      //....

#. In the *Debug view* in *Vitis* go the the expressions tab and add the ``three_phase_output`` struct as a new expression.

   * This lets you modify the value of the ``three_phase_output`` struct during runtime. 
   * Therefore i.e. different values can be sent to or read out from the R5.
  
   .. note:: 

      Refreshing the the value of the expression stops the processor for a couple of cycles. The more expressions are logged, the longer the stoppage takes.

#. Build and flash the UltraZohm and connect the GUI.
#. In *Vitis* select the R5 in the *debug* view on the left side. The value of the expression should now be visible. 

   ..  _Vitis_expression:
   ..  figure:: ./img/Vitis2.png
       :align: center

       Visible expression in Vitis.

#. Try out different values for the three phases (which correlate to the DutyCycles of the gates) by changing the value in the expression tab and visualize them on the oscilloscope again.  

   * Be wary, the value should be positive and not exceed 1.0f. 
   * Otherwise an assertion will trigger again.

#. This concludes the fourth tutorial.