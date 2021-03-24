============
Simscape HDL
============

The motivation for using Simscape Models on the UltraZohm is to use them as a virtual test bench that can be used with the complete signal chain of the UltraZohm from reading the current value of the simscape model to the ADC input, transfering data to the PS, calculate the controller on the PS, transfer the duty cycle to the PWM-module and apply the output signal to the Simscape model.
Additionally, Simscape Models on the UltraZohm be used to accelerate specific Simulations compared to using a desktop computer.
This is especially useful for simulating system with low time constants which you want to simulate for a long time.
However, this is the most basic Mathworks example applied to the UltraZohm and there is no focus on usability for simulation nor is the signal chain closed.
The goal of this tutorial is to provide a starting point for the user and showcase the possibilities of using existing tooling with the Ultrazohm.

This tutorial consists of:
  
- Generating HDL-Code from a `Simulink Simscape Modell <https://de.mathworks.com/products/simscape.html>`_
- Implementation of the IP-Core
- Integration of the IP-Core in the UltraZohm Vivado project
- Follows this Mathworks example: `Generate HDL Code for Simscape Models <https://de.mathworks.com/help/hdlcoder/ug/generate-hdl-code-from-simscape-model.html>`_

Simscape
--------

Generate IP-Core
****************

1. Follow this `Generate HDL Code for Simscape Models <https://de.mathworks.com/help/hdlcoder/ug/generate-hdl-code-from-simscape-model.html>`_ until the stept that opens the HDL version of the model
2. Add Vivado as synthesistool with ``hdlsetuptoolpath``
2. Right click the subsystem -> HDL Code -> HDL Workflow Advisor
3. In HDL Workflow Advisor:
   
   - ``Zynq Ultrascale`` & ``IP-Core``
   - Target Interface: ``AXI4-Lite``
   - Reset: ``Synchronous``
   - Enable native floating point
   - Run Workflow to last point

4. The IP-Core is now generated
5. Copy the IP-Core to IP-Core folder in the ultrazohm_sw repository. **Note**: the IP-Core is already present in the repository.
6. Add IP-Core to Vivado, wire the Core to Clocks, Reset and AXI
7. Assign an adress to the IP-Core (``Address Editor``)
8. Build bitstream & export XSA


Software
********

1. Open Vitis
2. Generate Workspace 





More information
----------------

- `Generate HDL Code for Simscape Models <https://de.mathworks.com/help/hdlcoder/ug/generate-hdl-code-from-simscape-model.html>`_
- `Generate Optimized HDL Implementation Model from Simscape <https://de.mathworks.com/help/hdlcoder/ug/optimize-hdl-implementation-model-from-simscape.html>`_
- `Troubleshoot Conversion of Simscape Permanent Magnet Synchronous Motor to HDL-Compatible Simulink Model <https://de.mathworks.com/help/hdlcoder/ug/troubleshoot-generate-implementation-model-from-simscape-pmsm.html>`_
- `Generate HDL Code Using the Simscape HDL Workflow Advisor <https://de.mathworks.com/help/physmod/simscape/ug/generate-hdl-code-using-the-simscape-hdl-workflow-advisor.html>`_
- `Simscape Hardware-in-the-Loop Workflow <https://de.mathworks.com/help/hdlcoder/simscape-to-hdl.html?s_tid=CRUX_lftnav>`_