============
Simscape HDL
============

.. note:: 

   This tutorial is optional and only useful for people who plan to use the HDL coder.

The motivation for using Simscape Models on the UltraZohm is to use them as a virtual test bench that can be used with the complete signal chain of the UltraZohm from reading the current value of the Simscape model to the ADC input, transferring data to the PS, calculate the controller on the PS, transfer the duty cycle to the PWM-module and apply the output signal to the Simscape model.
Additionally, Simscape Models on the UltraZohm be used to accelerate specific Simulations compared to using a desktop computer.
This is especially useful for simulating a system with low time constants that you want to simulate for a long time.
However, this is the most basic Mathworks example applied to the UltraZohm, and there is no focus on usability for simulation, nor is the signal chain closed.
The goal of this tutorial is to provide a starting point for the user and showcase the possibilities of using existing tooling with the Ultrazohm.

This tutorial consists of:
  
- Generating HDL-Code from a `Simulink Simscape Modell <https://de.mathworks.com/products/simscape.html>`_
- Implementation of the IP-Core
- Integration of the IP-Core in the UltraZohm Vivado project
- Follows this Mathworks example: `Generate HDL Code for Simscape Models <https://de.mathworks.com/help/hdlcoder/ug/generate-hdl-code-from-simscape-model.html>`_

.. note:: 

   This tutorial is limited to show how it is done, and no explanation is provided.
   Please refer to the source code of the driver and testbench for insight into the details.
   Furthermore, the text on this page only supplements the videos which provide the actual details!

Simscape
--------

Generate IP-Core
****************

1. Follow this `Generate HDL Code for Simscape Models <https://de.mathworks.com/help/hdlcoder/ug/generate-hdl-code-from-simscape-model.html>`_ until the step that opens the HDL version of the model
2. Add Vivado as synthesis tool with ``hdlsetuptoolpath``
3. Right-click the subsystem -> HDL Code -> HDL Workflow Advisor
4. Settings in HDL Workflow Advisor:

  - ``Zynq Ultrascale`` & ``IP-Core``
  - Target Interface: ``AXI4-Lite``
  - Reset: ``Synchronous``
  - Enable native floating point
  - Run Workflow to the last point

5. The IP-Core is now generated
6. Copy the IP-Core to the IP-Core folder in the ultrazohm_sw repository. **Note**: the IP-Core is already present in the repository.
7. Add IP-Core to Vivado, wire the Core to Clocks, Reset and AXI
8. Assign an address to the IP-Core (``Address Editor``)
9. Build bitstream & export XSA

Video
^^^^^

.. youtube:: FqcvIo06e18

Software
********

#. Open Vitis
#. Generate Workspace 
#. The software driver for the IP-core is located in ``Vitis/software/Baremetal/src/IP_Cores/uz_simscapeExample/``
#. Add the following code to ``main.c`` (of R5) to the ``init_ip_cores`` section of the switch-case.

   .. code-block:: c
      :linenos:
      :emphasize-lines: 34
      :caption: Snippet of ``main.c`` with initialization of the simscape IP-Core. ``//....`` marks left out code
 
       #include "IP_Cores/uz_simscapeExample/uz_simscapeExample_staticAllocator.h"
       uz_simscapeExample_handle sim_halfWaveRectifier;
 
      //.... 

       int main(void)
       {
         int status = UZ_SUCCESS;
         while (1)
         {
           switch (initialization_chain)
           {
           case init_assertions:
               uz_assert_configuration(); // This has to be the first line of code in main.c
               initialization_chain = init_gpios;
               break;
           case init_gpios:
               Initialize_AXI_GPIO();               // This has to be the second line of code in main.c since the assertion callback uses the AXI_GPIO to disable the system
               uz_frontplane_button_and_led_init(); // This has to be the third line of code since the assertion callback uses the LEDs to indicate an error
               initialization_chain = init_software;
               break;
           case init_software:
               Initialize_Timer();
               uz_SystemTime_init();
               JavaScope_initalize(&Global_Data);
               initialization_chain = init_ip_cores;
               break;
           case init_ip_cores:
               uz_adcLtc2311_ip_core_init();
               Global_Data.objects.deadtime_interlock_d1 = uz_interlockDeadtime2L_staticAllocator_slotD1();
               uz_interlockDeadtime2L_set_enable_output(Global_Data.objects.deadtime_interlock_d1, true);
               Global_Data.objects.pwm_d1 = initialize_pwm_2l_on_D1();
               Global_Data.objects.mux_axi = initialize_uz_mux_axi();
               sim_halfWaveRectifier = uz_simscapeExample_staticAllocator();
               PWM_3L_Initialize(&Global_Data); // three-level modulator
               initialize_incremental_encoder_ipcore_on_D5(UZ_D5_INCREMENTAL_ENCODER_RESOLUTION, UZ_D5_MOTOR_POLE_PAIR_NUMBER);
               initialization_chain = print_msg;
               break;
           case print_msg:
           //....
         }
       }  


#. Add the following code to ``isr.c``


   * Top of file include:

   .. code-block:: c

       #include "../IP_Cores/uz_simscapeExample/uz_simscapeExample.h"
       extern uz_simscapeExample_handle sim_halfWaveRectifier;

   * In function ISR_Control before ``JavaScope_update()`` function call

   .. code-block:: c

     uz_simscapeExample_step_model_once(sim_halfWaveRectifier);


#. Add the following code to ``javascope.c``

   * Top of file include & declaration:

   .. code-block:: c

     #include "../IP_Cores/uz_simscapeExample/uz_simscapeExample_private.h"
     extern uz_simscapeExample_handle sim_halfWaveRectifier;

   * Assign the GUI variables ``JSO_ISR_ExecTime_us``, ``JSO_lifecheck``, and ``JSO_ISR_Period_us`` to the output variables of the IP-Core:

   .. code-block:: c

       js_ch_observable[JSO_ISR_ExecTime_us] = &sim_halfWaveRectifier->Vin;
       js_ch_observable[JSO_lifecheck] = &sim_halfWaveRectifier->IR;
       js_ch_observable[JSO_ISR_Period_us] = &sim_halfWaveRectifier->Vdiode;

#. Set ``#define UZ_SIMSCAPEEXAMPLE_USE_IP 1`` in ``IP_Cores/uz_simscapeExample/uz_simscapeExample_staticAllocator.h``
#. Build the project
#. Power on the UltraZohm, flash the program
#. Add ``hardware_multiplication`` to expressions of R5
#. Open Javascope, the output signals can be watched and logged to file

Video
^^^^^

.. youtube:: BoiBu5_XFnY

More information
----------------

- `Generate HDL Code for Simscape Models <https://de.mathworks.com/help/hdlcoder/ug/generate-hdl-code-from-simscape-model.html>`_
- `Generate Optimized HDL Implementation Model from Simscape <https://de.mathworks.com/help/hdlcoder/ug/optimize-hdl-implementation-model-from-simscape.html>`_
- `Troubleshoot Conversion of Simscape Permanent Magnet Synchronous Motor to HDL-Compatible Simulink Model <https://de.mathworks.com/help/hdlcoder/ug/troubleshoot-generate-implementation-model-from-simscape-pmsm.html>`_
- `Generate HDL Code Using the Simscape HDL Workflow Advisor <https://de.mathworks.com/help/physmod/simscape/ug/generate-hdl-code-using-the-simscape-hdl-workflow-advisor.html>`_
- `Simscape Hardware-in-the-Loop Workflow <https://de.mathworks.com/help/hdlcoder/simscape-to-hdl.html?s_tid=CRUX_lftnav>`_