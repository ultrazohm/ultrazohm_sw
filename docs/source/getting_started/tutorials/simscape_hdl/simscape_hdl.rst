============
Simscape HDL
============

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

1. Open Vitis
2. Generate Workspace 
3. The software driver for the IP-core is located in ``Vitis->Baremetal->src/IP_Cores/SimScapeExample/uz_simExpl.h``
4. User code for the model is located at ``Vitis->Baremetal->src/IP_Cores/SimScapeExample/uz_simExpl_testbench.h``
5. Add the following code to ``isr.c``

Top of file include:

.. code-block:: c

   #include "IP_Cores/SimScapeExample/uz_simExpl_testbench.h"

In function ISR_Control before ``JavaScope_update()`` function call

.. code-block:: c

   uz_simExpl_stepTestbench();

6. Add the following code to ``main.h``

.. code-block:: c

   #include "IP_Cores/SimScapeExample/uz_simExpl_testbench.h"

7. Add the following code to ``main.c`` before ``JavaScope_initalize`` is called, e.g., directly after ``uz_SystemTime_init``

.. code-block:: c

   uz_simExpl_testbench_init();

8. Add the following code to ``javascope.c``

Top of file include & declaration:

.. code-block:: c

   #include "IP_Cores/SimScapeExample/uz_simExpl_testbench.h"
   extern uz_simExpl_handle simscapeHDLInstance;

Assign the GUI variables ``Sawtooth1``, ``SineWave1``, and ``SineWave2`` to the output variables of the IP-Core:

.. code-block:: c

   js_ptr_arr[JSO_Sawtooth1]   = &simscapeHDLInstance->IR;
   js_ptr_arr[JSO_SineWave1]   = &simscapeHDLInstance->Iout;
   js_ptr_arr[JSO_SineWave2]   = &simscapeHDLInstance->Vdiode;

9. Power on the UltraZohm, flash the program
10. Add ``SimscapeInput`` to expressions of R5
11. Adjust the input signal for the IP-Core by changing the ``amplitude`` and ``frequency`` of the sine wave
12. Open Javascope, the output signals can be watched and logged to file

Video
^^^^^

.. youtube:: r4CqsMyW1vo

More information
----------------

- `Generate HDL Code for Simscape Models <https://de.mathworks.com/help/hdlcoder/ug/generate-hdl-code-from-simscape-model.html>`_
- `Generate Optimized HDL Implementation Model from Simscape <https://de.mathworks.com/help/hdlcoder/ug/optimize-hdl-implementation-model-from-simscape.html>`_
- `Troubleshoot Conversion of Simscape Permanent Magnet Synchronous Motor to HDL-Compatible Simulink Model <https://de.mathworks.com/help/hdlcoder/ug/troubleshoot-generate-implementation-model-from-simscape-pmsm.html>`_
- `Generate HDL Code Using the Simscape HDL Workflow Advisor <https://de.mathworks.com/help/physmod/simscape/ug/generate-hdl-code-using-the-simscape-hdl-workflow-advisor.html>`_
- `Simscape Hardware-in-the-Loop Workflow <https://de.mathworks.com/help/hdlcoder/simscape-to-hdl.html?s_tid=CRUX_lftnav>`_