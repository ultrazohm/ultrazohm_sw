.. _vitis_hls:

===============
Vitis HLS (HDL)
===============

Vitis HLS generates RTL from C and C++ code.
It is useful for IP cores where the algorithm is easier to describe, test, or optimize in software than directly in HDL.
The generated RTL can be packaged as an IP core, integrated in Vivado, and accessed from Vitis software through AXI drivers.
Good starting point is `User Guide 1399 - Introduction to Vitis HLS <https://docs.xilinx.com/r/2022.2-English/ug1399-vitis-hls/Introduction-to-Vitis-HLS>`_.

Compared with :ref:`HDL Coder <hdl_coder>`, Vitis HLS does not require modeling the algorithm as a Simulink data flow diagram.
It is also well suited for floating-point logic and code-oriented design flows.
Since MATLAB R2025b, Vitis HLS can also be used as a synthesis tool directly within MATLAB, see the MathWorks tutorial `From MATLAB to Optimized RTL Using HDL Coder and AMD Vitis HLS <https://www.mathworks.com/videos/from-matlab-to-optimized-rtl-using-hdl-coder-and-amd-vitis-hls-1774893384578.html>`_ for details.

Recommended workflow
====================

The fastest path is to keep the HLS project reproducible with a ``script.tcl`` file:

#. Create the C/C++ source, header, and test bench.
#. Run Vitis HLS from the Tcl script to simulate, synthesize, and export the IP.
#. Add the exported IP to the UltraZohm Vivado project.
#. Generate the bitstream, export the XSA, and update the Vitis workspace.
#. Use either the generated Vitis HLS driver or a UZ-style wrapper driver from the Baremetal software.

The manual GUI flow is included as an optional reference for learning the Vitis HLS project settings.


Tutorial
========

This tutorial creates a simple IP core named ``uz_HLS_testIP``.
The IP core multiplies two ``int32_t`` values and returns the result through an AXI-Lite interface.

The tutorial uses these files:

- ``uz_HLS_testIP.cpp``: HLS implementation.
- ``uz_HLS_testIP.h``: HLS function declaration.
- ``tb_uz_HLS_testIP.cpp``: C simulation test bench.
- ``testIP_solution/script.tcl``: reproducible Vitis HLS project script.

.. _hls_generation_tcl:

Generate the HLS project with Tcl
---------------------------------

Each Vitis HLS design should be generated using a ``script.tcl``.
The script captures the commands required to create, simulate, synthesize, and export the design.

The example script is in ``ultrazohm_sw\ip_cores\uz_HLS_testIP\testIP_solution\script.tcl``:

.. literalinclude:: ../../../../../ip_cores/uz_HLS_testIP/testIP_solution/script.tcl
   :language: tcl
   :caption: ``script.tcl``

The script adds the source and test bench files, sets the top function, selects the UltraZohm device, creates a 10 ns clock, runs C simulation, runs C synthesis, and exports the RTL as an IP catalog package.

The script can be extended with additional optimization and interface settings.
For the available commands, see the `Vitis HLS Command Reference Documentation <https://docs.amd.com/r/2022.2-English/ug1399-vitis-hls/vitis_hls-Command>`_.
The following commands are examples and are not required for this tutorial:
  
.. code-block:: console

   config_interface -m_axi_addr64=0 -m_axi_alignment_byte_size 32 -m_axi_latency 64 -m_axi_max_bitwidth 32 -m_axi_max_widen_bitwidth 32
   config_rtl -register_reset_num 3
   config_array_partition -complete_threshold 2
   config_compile -no_signed_zeros -unsafe_math_optimizations


**Run the Tcl script**

For this tutorial, the working directory is ``ip_cores\uz_HLS_testIP``.

Run these commands in ``cmd.exe``.

.. code-block:: bat

   cd C:\path\to\ultrazohm_sw\ip_cores\uz_HLS_testIP
   call "C:\Xilinx\Vitis_HLS\2022.2\settings64.bat"
   vitis_hls -f testIP_solution\script.tcl

You only need the ``call "C:\Xilinx\Vitis_HLS\2022.2\settings64.bat"`` line if ``vitis_hls`` is not part of your ``PATH`` variable.
Adjust the Vitis HLS installation path if it is installed somewhere else.
The setup script only changes the environment of the shell in which it is executed.

After the script finishes, Vitis HLS creates the generated project in ``uz_HLS_testIP\`` and exports the packaged IP to ``uz_HLS_testIP\testIP_solution\impl\export.zip``.
The IP core can now be integrated into the Vivado project as described in :ref:`hls_vivado`.

**Open the generated HLS project**

To inspect the generated HLS project, open it with:

.. code-block:: console

   vitis_hls -p uz_HLS_testIP


Optional manual project setup
-----------------------------

The manual flow creates the same example project through the Vitis HLS GUI.
It is not required when the project is generated with ``script.tcl``.
Use it when you want to inspect the project settings interactively or learn where the Tcl commands appear in the GUI.

.. dropdown:: Show manual GUI project creation steps
   
   - Start Vitis HLS (2022.2 used for this tutorial).
   - Create a new HLS Project.
   
   .. figure:: tutorial_img/1_open_new_project.png
      :width: 400px
      :align: center
   
   - In the Project Configuration window, locate the field for the project name and update it with ``uz_HLS_testIP``.
   
   .. note::
     In the pictures the project name is ``uz_axi_myTestIP``. This was the name of the project before the tutorial was adjusted to ``uz_HLS_testIP``. The steps are the same, only the project name is different.

   - Next, find the related path field in the Project Configuration window. Update the path to ensure that the project files are stored in the desired location.
   
   .. figure:: tutorial_img/2_project_name.png
      :width: 600px
      :align: center
   
   - Click **Next** to proceed to the source and test bench file add sections. 
   - These files will be added later in the tutorial.
   - In the Solution Configuration section, you have the option to change the clock settings, board specification, and flow target.
   - Adjust the clock settings based on your project requirements. 
     Specify the clock frequency, and any relevant parameters. Select the appropriate flow target for your project, such as generating a bitstream for FPGA programming or producing simulation files for software testing.
   
   
   .. figure:: tutorial_img/3_project_settings.png
      :width: 500px
      :align: center
   
   - Modify the board specification if needed in future applications, ensuring compatibility between the design and the physical board you are using. 
     When you click the Device Selection Dialog, you will see a list of all the available boards from the Xilinx Library. 
     This dialog allows you to choose the specific board that matches your hardware setup and requirements.
   - For this tutorial, set the device to ``xczu9eg-ffvc900-1-e``.
  
   .. figure:: tutorial_img/4_board_option.png
      :width: 500px
      :align: center
   
   - After completing the configuration part, an empty project will be created. 
     Now, for the basic test IP, we will implement integer multiplication and write the test bench.
   - To create a source file, simply right-click on the **Source** folder in your project and choose **New Source File...** from the menu.
   
   .. figure:: tutorial_img/5_add_source.png
      :width: 400px
      :align: center
   
   - When the file window opens, make sure to check the path displayed. 
     If the path is not the same as your project location, you should adjust it accordingly. 
   - To create the new source file ``uz_HLS_testIP.cpp``, enter the filename in the file window and click **Save**, and write the code to the file.
   
   .. figure:: tutorial_img/6_create_source.png
      :width: 500px
      :align: center
   
   .. literalinclude:: ../../../../../ip_cores/uz_HLS_testIP/uz_HLS_testIP.cpp
      :language: c
      :caption: ``uz_HLS_testIP.cpp``
   
   - To create a header file, simply right-click on the **Source** folder in your project and choose **New Source File...** from the menu.
   
   .. figure:: tutorial_img/7_add_header.png
      :width: 400px
      :align: center
   
   - When the file window opens, make sure to check the path displayed. 
     If the path is not the same as your project location, you should adjust it accordingly. 
   - To create the new source file ``uz_HLS_testIP.h``, enter the filename in the file window and click **Save**, and write the code to the file.
   
   .. figure:: tutorial_img/8_create_header.png
      :width: 500px
      :align: center
   
   .. literalinclude:: ../../../../../ip_cores/uz_HLS_testIP/uz_HLS_testIP.h
      :language: c
      :caption: ``uz_HLS_testIP.h``

   - To create a test bench file, simply right-click on the **Test Bench** folder in your project and choose **New Test Bench File...** from the menu.
   - When the file window opens, make sure to check the path displayed. 
     If the path is not the same as your project location, you should adjust it accordingly, and write the code to the file.
   - Create a new test bench file ``tb_uz_HLS_testIP.cpp``.
   - The test bench calls the multiplication function with fixed input values and prints the result.
   
   .. figure:: tutorial_img/11_create_testbench.png
      :width: 500px
      :align: center
   
   .. literalinclude:: ../../../../../ip_cores/uz_HLS_testIP/tb_uz_HLS_testIP.cpp
      :language: c
      :caption: ``tb_uz_HLS_testIP.cpp``
   
Simulate, synthesize, and export in the GUI
-------------------------------------------

This optional section shows the GUI equivalent of the simulation, synthesis, and export commands used by the Tcl script.
Open the generated HLS project in the GUI when you want to modify directives interactively, inspect synthesis reports, or review resource and timing estimates.
If the Tcl script already completed successfully and you do not need to inspect the HLS project, continue with :ref:`hls_vivado`.

.. dropdown:: Show GUI steps to edit directives, run synthesis, and export RTL

   - HLS pragmas configure interfaces, scheduling, resource mapping, and other synthesis behavior.
     The example source uses ``#pragma HLS INTERFACE`` to create AXI-Lite registers for ``a``, ``b``, and ``result``.
     See the `Vitis HLS Pragmas <https://docs.xilinx.com/r/en-US/ug1399-vitis-hls/HLS-Pragmas>`_ documentation for the available pragmas.
   - Pragmas can be written directly in the source code or added through the **Directive** view in Vitis HLS.

   .. figure:: tutorial_img/26_directive.png
      :width: 1200px
      :align: center

   - Open the directive editor to add or modify directives without editing the source code manually.

   .. figure:: tutorial_img/27_insert_directive.png
      :width: 400px
      :align: center

   - For example, right-click a variable such as ``a`` to configure its interface pragma.

   .. figure:: tutorial_img/28_directive_editor.png
      :width: 400px
      :align: center

   - Run **C Simulation** to compile and execute the test bench before synthesis.

   .. figure:: tutorial_img/14_c_simulation.png
      :width: 400px
      :align: center

   - The simulation dialog provides options for debug, clean build, and optimization.
     The default settings are sufficient for this tutorial.

   .. figure:: tutorial_img/15_c_simulation_box.png
      :width: 400px
      :align: center

   - Check the console output or log file after simulation.
     A successful run means the C implementation and test bench compile and execute without errors.
   - Before synthesis, configure the top function of the design.

   .. figure:: tutorial_img/17_top_setting.png
      :width: 400px
      :align: center

   - Open the synthesis settings in the project settings.

   .. figure:: tutorial_img/18_top_file.png
      :width: 600px
      :align: center

   - Select ``uz_HLS_testIP`` as the top function.

   .. figure:: tutorial_img/19_top_select.png
      :width: 600px
      :align: center

   - Run **C Synthesis**.
     Synthesis converts the C/C++ implementation into RTL and reports estimated resource usage and timing.
     The estimated resource usage is usually higher than the final Vivado synthesis result, except for DSP slices and I/O pins.

   .. figure:: tutorial_img/20_c_synthesis.png
      :width: 400px
      :align: center

   - Keep the default synthesis settings for this tutorial.
     Adjust them only when the design requires different clock, interface, or optimization constraints.

   .. figure:: tutorial_img/21_c_settings.png
      :width: 400px
      :align: center

   - Review the Summary Report after synthesis.
     It shows resource estimates, timing information, and other synthesis results.

   .. figure:: tutorial_img/22_report.png
      :width: 800px
      :align: center

   - Click **Export RTL** to package the synthesized design.

   .. figure:: tutorial_img/30_export_rtl_tab.png
      :width: 350px
      :align: center

   - Export the IP for integration in Vivado.

   .. figure:: tutorial_img/31_export_rtl.png
      :width: 400px
      :align: center

   - At the end of the export step, Vitis HLS creates the IP core as a ``.zip`` file.
     Unzip it and place it in the ``ultrazohm_sw\ip_cores`` folder.

.. _hls_vivado:

Integrate the IP in Vivado
--------------------------

- To use the new IP core in the UZ Vivado project, the generated IP core has to be placed in the ``ultrazohm_sw\ip_cores`` folder.
  After following :ref:`hls_generation_tcl`, this is already the case.
  If the IP core was generated in a different project directory, move it to ``ultrazohm_sw\ip_cores`` by unzipping the exported ``.zip`` file.
- Open Vivado and the block design.
- Navigate to ``Window->IP-Catalog`` and ``right-click->Refresh All Repository``.
- Extend ``uz_user`` subblock.
- Extend the smartconnect by one master port to connect AXI ports to the processor.
- Add the new IP core and connect it to the system.

.. figure:: tutorial_img/32_vivado_ip_placement.png
   :width: 400px
   :align: center

- Go to the Address editor and assign a base address to the new IP core.
- For video implementation of these steps, check out the last step of :ref:`hdl_coder`.
- Build the bitstream, export the XSA, and update the Vitis workspace as done in :ref:`gen_bitstream`.

Use the IP core from Vitis
--------------------------

Generated drivers
*****************

Vitis HLS generates AXI driver files for the exported IP core.
Use these generated drivers for quick tests.
For production code in the UltraZohm software structure, prefer a small UZ-style wrapper driver around the hardware access, as shown in the next section.

The generated driver files for ``uz_HLS_testIP`` are:

  - ``xuz_hls_testip_hw.h``
  - ``xuz_hls_testip_linux.c``
  - ``xuz_hls_testip_sinit.c``
  - ``xuz_hls_testip.c``
  - ``xuz_hls_testip.h``
 
The ``_hw.h`` file contains register offsets and low-level definitions.
The ``xuz_hls_testip.c`` and ``xuz_hls_testip.h`` files provide the initialization, setter, and getter functions used by software.
Vivado includes these generated drivers in the exported XSA, and Vitis imports them into the platform project after the workspace is regenerated.
They can be found under ``ultrazohm_sw\vitis\workspace\UltraZohm\hw\drivers\your_ip_core``.

Initialization with Vitis HLS generated drivers
***********************************************

To initialize an IP core instance, include the generated header and use the device ID from ``xparameters.h``.
The device ID is generated from the Vivado block design and becomes available after the XSA has been exported and the Vitis workspace has been updated.

.. code-block:: c

   #include <xuz_hls_testip.h>

   XUz_hls_testip XUz_hls_testip_instance;

   int main(void) {
      XUz_hls_testip_Initialize(&XUz_hls_testip_instance, XPAR_UZ_USER_UZ_HLS_TESTIP_0_DEVICE_ID);
   }

Usage of Vitis HLS generated drivers
************************************

After initialization, use the generated setter and getter functions to write input registers and read output registers.
For a quick test, the generated driver can be used directly from ``main`` or from the ``init_ip_cores`` case:

.. code-block:: c

   XUz_hls_testip XUz_hls_testip_instance;

   int32_t a = 5;
   int32_t b = 10;
   int32_t result = 0;

   int main(void) {
      XUz_hls_testip_Initialize(&XUz_hls_testip_instance, XPAR_UZ_USER_UZ_HLS_TESTIP_0_DEVICE_ID);
      XUz_hls_testip_Set_a(&XUz_hls_testip_instance, a);
      XUz_hls_testip_Set_b(&XUz_hls_testip_instance, b);
      result = XUz_hls_testip_Get_result(&XUz_hls_testip_instance);
      uz_printf("The result of multiplication is %d\r\n", result);
   }

.. note::
   Using the AXI-write and -read functions is more tricky depending on the desired datatype.
   In the following example snippet the AXI-interfaces have a floating point datatype.
   However, the data for the AXI-write functions takes an argument of type ``uint32``.
   This means, the driver expects the bits of a floating point value in the storage item of an unsigned int.
   To achieve this, the user can create the really used float variable, here ``REAL_VAR`` and create a pointer of type ``uint32_t`` to this variable and cast it.
   The AXI-set function is called with the dereferenced, casted pointer, which gives the current value of the ``REAL_VAR`` to the driver.

.. code-block:: c

   float REAL_VAR = 0.0f;
   uint32_t* INT_VAR = (uint32_t*)&REAL_VAR;

   int main(void) {
      XEXAMPLE_Initialize(&example_instance, XPAR_EXAMPLE_0_DEVICE_ID);
      XEXAMPLE_Set_axi_example_signal(&example_instance, *INT_VAR);
   }


Optional UZ-style driver
************************

The driver is already provided in ``ultrazohm_sw/software/Baremetal/src/IP_Cores/uz_HLS_testIP``.
To gain a better understanding of driver creation, you can follow the steps below to create a driver for the IP core yourself.

.. dropdown:: Show steps (collapsed by default)

   - The detailed explanation for AXI test IP created with HDL Coder can be found :ref:`here<hdl_coder>`. 
   - This HLS IP scenario is similar to the example. 
     To multiply two variables result=A⋅B of type int32_t, the driver has to write A and B from the PS to the PL by AXI in the correct registers and read back the result from the PL to the PS.
   - For that reason, we need set and get functions, also called write and read functions. 
   - Create ``uz_HLS_testIP`` folder and move to ``ultrazohm_sw -> software -> Baremetal -> src -> IP_Cores`` 
   - In the folder, create the files: 
      
      * ``uz_HLS_testIP.c``
      * ``uz_HLS_testIP.h``
      * ``uz_HLS_testIP_hw.c``
      * ``uz_HLS_testIP_hw.h``
      * ``uz_HLS_testIP_hwAddresses.h``
   
   .. literalinclude:: ../../../../../vitis/software/Baremetal/src/IP_Cores/uz_HLS_testIP/uz_HLS_testIP_hw.c
      :language: c
      :linenos:
      :caption: ``uz_HLS_testIP_hw.c``
   
   .. literalinclude:: ../../../../../vitis/software/Baremetal/src/IP_Cores/uz_HLS_testIP/uz_HLS_testIP_hw.h
      :language: c
      :linenos:
      :caption: ``uz_HLS_testIP_hw.h``
   
   .. literalinclude:: ../../../../../vitis/software/Baremetal/src/IP_Cores/uz_HLS_testIP/uz_HLS_testIP_hwAddresses.h
      :language: c
      :linenos:
      :caption: ``uz_HLS_testIP_hwAddresses.h``
   
   .. literalinclude:: ../../../../../vitis/software/Baremetal/src/IP_Cores/uz_HLS_testIP/uz_HLS_testIP.c
      :language: c
      :linenos:
      :caption: ``uz_HLS_testIP.c``

   .. literalinclude:: ../../../../../vitis/software/Baremetal/src/IP_Cores/uz_HLS_testIP/uz_HLS_testIP.h
      :language: c
      :linenos:
      :caption: ``uz_HLS_testIP.h``

   - Open ``uz_global_configuration.h`` and add ``#define UZ_HLS_TESTIP_MAX_INSTANCES 0U`` to the normal configuration section and ``#define UZ_HLS_TESTIP_MAX_INSTANCES 20U`` to the test configuration section.
   - For the unit tests navigate to ``vitis/software/Baremetal/test/IP_Cores`` and create the folder ``uz_HLS_testIP``.
   - Within this folder create the file ``test_uz_HLS_testIP.c`` and ``test_uz_HLS_testIP_hw.c``.

   .. literalinclude:: ../../../../../vitis/software/Baremetal/test/IP_Cores/uz_HLS_testIP/test_uz_HLS_testIP_hw.c
      :language: c
      :linenos:
      :caption: ``test_uz_HLS_testIP_hw.c``

   .. literalinclude:: ../../../../../vitis/software/Baremetal/test/IP_Cores/uz_HLS_testIP/test_uz_HLS_testIP.c
      :language: c
      :linenos:
      :caption: ``test_uz_HLS_testIP.c``



Test on hardware with the Vitis Serial Terminal
-----------------------------------------------

- Create the file ``uz_myHLSIP.h`` in the ``include`` folder.

.. code-block:: c
   :linenos:
   :caption: ``uz_myHLSIP.h``

   #pragma once

   void uz_myHLSIP(void);

- Create the file ``uz_myHLSIP.c`` in the ``sw`` folder.

.. code-block:: c
   :linenos:
   :caption: ``uz_myHLSIP.c``

   #include "../include/uz_myHLSIP.h"
   #include "../uz/uz_HAL.h"
   #include "../IP_Cores/uz_HLS_testIP/uz_HLS_testIP.h"
   #include "xparameters.h"

   void uz_myHLSIP(void){
      struct uz_HLS_testIP_config_t config={
            .base_address= XPAR_UZ_USER_UZ_HLS_TESTIP_0_S_AXI_CONTROL_BASEADDR,
            .ip_clk_frequency_Hz=100000000U
      };
      uz_HLS_testIP *instance = uz_HLS_testIP_init(config);
      int32_t a = 5;
      int32_t b = 10;
      int32_t c = uz_HLS_testIP_multiply(instance, a, b);
      uz_printf("Hardware multiply: %i, Software multiply: %i\n", c, a*b);
      if (c==a*b){
         uz_printf("Success: hardware and software multiply are equal! \n");
      }else{
         uz_printf("Fail: hardware and software multiply are NOT equal! \n");
      }

      while(1){
         // do nothing and loop forever
      }
   }

- Open ``uz_global_configuration.h`` and increase ``#define UZ_HLS_TESTIP_MAX_INSTANCES`` to ``1U``.
- Build the software.
- Include ``#include "include/uz_myHLSIP.h"`` in ``main.c`` (Baremetal R5) and call ``uz_myHLSIP();`` before the ISR is initialized!
- Connect the serial port to the Vitis Serial Terminal.
- Run the program. The success message should be printed to the Vitis Serial Terminal.

.. figure:: tutorial_img/33_vitis_result.png
   :width: 400px
   :align: center


.. figure:: tutorial_img/34_vitis_serial_term.png
   :width: 400px
   :align: center

More complex HLS use cases
==========================

The ``uz_HLS_testIP`` example is intentionally small and shows the mechanics of generating, exporting, integrating, and driving a Vitis HLS IP core.
For more complex HLS-based IP cores, see the following examples.

Neural network accelerator
--------------------------

The :ref:`uz_NN_acc` IP core implements a configurable floating-point MLP accelerator and shows additional topics that are relevant for larger HLS designs:

- multiple C/C++ source files and reusable layer functions,
- multiple Vitis HLS solutions with separate ``script.tcl`` and ``directives.tcl`` files,
- HLS directives for performance and resource tradeoffs,
- AXI-Lite control together with memory access from the programmable logic,
- a UZ-style software driver for integrating the accelerator into the UltraZohm software stack.

The number of layers and neurons is fixed during HLS synthesis.
Changing the network structure therefore requires resynthesizing the IP core, as described in :ref:`uz_NN_customize_setup`.

FCS-MPC with prediction horizon one
-----------------------------------

Another HLS example is a finite-control-set model predictive control (FCS-MPC) implementation with prediction horizon one.
This use case is currently developed on the remote branch ``origin/feature/fcs_mpc_n1`` and is not part of ``develop`` yet.
The branch contains the HLS source files under ``ip_cores/fcs_mpc_n1``.

Compared with ``uz_HLS_testIP``, the FCS-MPC example is useful for studying an HLS design that is closer to a real control algorithm:

- prediction of candidate switching states,
- cost-function evaluation in hardware,
- selection of the optimal switching state within a fixed control cycle,
- AXI-Lite control together with AXI-Stream inputs and direct ``ap_none`` outputs,
- integration of controller logic as an IP core in the FPGA fabric,
- C simulation, C synthesis, co-simulation, and VHDL IP export from one ``script.tcl``.

Once the branch is merged, this section should be extended with links to the generated IP core, its HLS ``script.tcl``, and the corresponding software driver.

Further reading
===============

* `User Guide 1399 - Introduction to Vitis HLS <https://docs.xilinx.com/r/2022.2-English/ug1399-vitis-hls/Introduction-to-Vitis-HLS>`_
* `User Guide 1399 - HLS Pragmas <https://docs.amd.com/r/2022.2-English/ug1399-vitis-hls/HLS-Pragmas>`_
* `Introductory Examples <https://github.com/Xilinx/Vitis-HLS-Introductory-Examples>`_
* `From MATLAB to Optimized RTL Using HDL Coder and AMD Vitis HLS <https://www.mathworks.com/videos/from-matlab-to-optimized-rtl-using-hdl-coder-and-amd-vitis-hls-1774893384578.html>`_
* `AMD Vitis HLS User Guide <https://docs.xilinx.com/r/2022.2-English/ug1399-vitis-hls>`_
* `Parallel Programming for FPGAs <https://kastner.ucsd.edu/hlsbook/>`_
* `Vivado HLS Learnings <https://hansgiesen.net/wordpress/vivado-hls-learnings/>`_
* `When FPGAs Meet ADMM with High-level Synthesis (HLS): A Real-time Implementation of Long-horizon MPC for Power Electronic Systems <https://ieeexplore.ieee.org/document/10213796>`_
* `Vitis HLS Tutorial <https://byu-cpe.github.io/ComputingBootCamp/tutorials/vitis_hls/>`_
* `Transformations of High-Level Synthesis Codes for High-Performance Computing <https://arxiv.org/abs/1805.08288>`_
* `hls4ml <https://fastmachinelearning.org/hls4ml/>`_
* `FPGA Teaching Resources <https://sharclab.ece.gatech.edu/teaching/2023-spring-fpga/>`_
* `A floating-point matrix multiplication implemented in hardware example <https://github.com/twaclaw/matmult>`_
