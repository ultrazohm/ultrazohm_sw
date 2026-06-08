.. _vitis_hls:

===============
Vitis HLS (HDL)
===============

Vitis HLS generates RTL from C and C++ code.
It is useful for IP cores where the algorithm is easier to describe, test, or optimize in software than directly in HDL.
The generated RTL can be packaged as an IP core, integrated in Vivado, and accessed from Vitis software through AXI drivers.

Compared with :ref:`HDL Coder <hdl_coder>`, Vitis HLS does not require modeling the algorithm as a Simulink data flow diagram.
It is also well suited for floating-point logic and code-oriented design flows.
Since MATLAB R2025b, Vitis HLS can also be used as a synthesis tool directly within MATLAB.

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

Place the following example in ``ultrazohm_sw\ip_cores\uz_HLS_testIP\testIP_solution\script.tcl``:

.. code-block:: tcl

   open_project uz_HLS_testIP
   set_top uz_HLS_testIP
   add_files ./uz_HLS_testIP.cpp
   add_files ./uz_HLS_testIP.h
   add_files -tb ./tb_uz_HLS_testIP.cpp
   open_solution "testIP_solution" -flow_target vivado
   set_part {xczu9eg-ffvc900-1-e}
   create_clock -period 10 -name default
   config_export -format ip_catalog -rtl verilog
   #source "./testIP_solution/directives.tcl"
   csim_design
   csynth_design
   export_design -rtl verilog -format ip_catalog

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

After the script is finished, the IP core has been generated and exported to ``uz_HLS_testIP\testIP_solution\impl\export.zip``.
The IP core can now be integrated into the Vivado project as described in :ref:`hls_vivado`.

**Open the generated HLS project**

To inspect the generated HLS project, open it with:

.. code-block:: console

   vitis_hls -p uz_HLS_testIP

From ``cmd.exe`` without a configured Vitis HLS environment, use:

.. code-block:: bat

   call "C:\Xilinx\Vitis_HLS\2022.2\settings64.bat"
   vitis_hls -p uz_HLS_testIP

Optional manual project setup
-----------------------------

The manual flow creates the same example project through the Vitis HLS GUI.
Use it when you want to inspect the project settings interactively or learn where the Tcl commands appear in the GUI.

.. dropdown:: Show steps to create project from scratch (collapsed by default)
   
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
   
   .. code-block:: c
   
      #include <stdint.h>
   
      void uz_HLS_testIP(int32_t a, int32_t b, int32_t *result) {
   
         #pragma HLS INTERFACE ap_ctrl_none port=return
         #pragma HLS INTERFACE s_axilite port=a bundle=control
         #pragma HLS INTERFACE s_axilite port=b bundle=control
         #pragma HLS INTERFACE s_axilite port=result bundle=control
   
         *result = a * b;
      }
   
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
   
   .. code-block:: c
   
      #include <stdint.h>

      void uz_HLS_testIP(int32_t a, int32_t b, int32_t *result);

   - To create a test bench file, simply right-click on the **Test Bench** folder in your project and choose **New Test Bench File...** from the menu.
   - When the file window opens, make sure to check the path displayed. 
     If the path is not the same as your project location, you should adjust it accordingly, and write the code to the file.
   - Create a new test bench file ``tb_uz_HLS_testIP.cpp``.
   - The test bench calls the multiplication function with fixed input values and prints the result.
   
   .. figure:: tutorial_img/11_create_testbench.png
      :width: 500px
      :align: center
   
   .. code-block:: c
   	
      #include <stdio.h>
      #include <stdint.h>
   
      void uz_HLS_testIP(int32_t a, int32_t b, int32_t *result);
   
      int main() {
         int32_t a = 5;
         int32_t b = 7;
         int32_t result;
   
         uz_HLS_testIP(a, b, &result);
   
         printf("Multiplication result: %d\n", result);
   
         return 0;
      }
   
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

- Vitis HLS IP core generation yields automatically generated AXI-drivers.
- The usage is not yet aligned with the UZ project's typical drivers and will be explained in the following.
- The created files for the example project with the name uz_HLS_testIP are:

  - ``xuz_hls_testip_hw.h``
  - ``xuz_hls_testip_linux.c``
  - ``xuz_hls_testip_sinit.c``
  - ``xuz_hls_testip.c``
  - ``xuz_hls_testip.h``
 
While the ``_hw.h`` file is similar to the HDL Coder generated hardware address file, the last two files include already usable drivers.
These drivers can be used for operation or additional UZ-style drivers can be created around them.
They are automatically included in the exported .xsa file from Vivado and therefore directly included in the platform project within Vitis. 
You can find them in the Vitis workspace (after regenerating the workspace) under ``ultrazohm_sw\vitis\workspace\UltraZohm\hw\drivers\your_ip_core``.
The header file can simply be included, as also done in the following.

Initialization with Vitis HLS generated drivers
***********************************************

To initialize an IP core instance, the instance's define has to be taken from the ``xparameters.h`` file. When we address the IP core, related information is added to the system files. 

.. code-block:: c

      #include <xuz_hls_testip.h>
      
      XUz_hls_testip XUz_hls_testip_instance;
      
      int32_t a = 0;
      int32_t b = 0;

      int main(void) {
   
      XUz_hls_testip_Initialize(&XUz_hls_testip_instance, XPAR_UZ_USER_UZ_HLS_TESTIP_0_DEVICE_ID);
   
   }

Usage of Vitis HLS generated drivers
************************************

To use the write and read with set and get functions, place the initialization code in main / case init_ip_cores: 

.. code-block:: c

      XUz_hls_testip XUz_hls_testip_instance;

      int32_t a = 5;
      int32_t b = 10;
      int32_t result = 0;


      int main(void) {
   
         // IP core initialization
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
   
   .. code-block:: c
      :linenos:
      :caption: ``uz_HLS_testIP_hw.c``
   
      #include "uz_HLS_testIP_hw.h"
      #include "uz_HLS_testIP_hwAddresses.h"
      #include "../../uz/uz_AXI.h"

      void uz_HLS_testIP_hw_write_A(uint32_t base_address,int32_t A){
         uz_assert_not_zero_uint32(base_address);
         uz_axi_write_int32(base_address+XUZ_HLS_TESTIP_CONTROL_ADDR_A_DATA,A);
      }

      void uz_HLS_testIP_hw_write_B(uint32_t base_address,int32_t B){
         uz_assert_not_zero_uint32(base_address);
         uz_axi_write_int32(base_address+XUZ_HLS_TESTIP_CONTROL_ADDR_B_DATA,B);
      }

      int32_t uz_HLS_testIP_hw_read_result(uint32_t base_address){
         uz_assert_not_zero_uint32(base_address);
         return (uz_axi_read_int32(base_address+XUZ_HLS_TESTIP_CONTROL_ADDR_RESULT_DATA));
      }
   
   .. code-block:: c
      :linenos:
      :caption: ``uz_HLS_testIP_hw.h``
   
      #ifndef UZ_HLS_TESTIP_HW_H
      #define UZ_HLS_TESTIP_HW_H
      #include <stdint.h>

      void uz_HLS_testIP_hw_write_A(uint32_t base_address,int32_t A);
      void uz_HLS_testIP_hw_write_B(uint32_t base_address,int32_t B);
      int32_t uz_HLS_testIP_hw_read_result(uint32_t base_address);

      #endif // UZ_HLS_TESTIP_HW_H
   
   .. code-block:: c
      :linenos:
      :caption: ``uz_HLS_testIP_hwAddresses.h``
   
      #ifndef UZ_HLS_TESTIP_HWADDRESSES_H
      #define UZ_HLS_TESTIP_HWADDRESSES_H

      #define XUZ_HLS_TESTIP_CONTROL_ADDR_A_DATA      0x10
      #define XUZ_HLS_TESTIP_CONTROL_BITS_A_DATA      32
      #define XUZ_HLS_TESTIP_CONTROL_ADDR_B_DATA      0x18
      #define XUZ_HLS_TESTIP_CONTROL_BITS_B_DATA      32
      #define XUZ_HLS_TESTIP_CONTROL_ADDR_RESULT_DATA 0x20
      #define XUZ_HLS_TESTIP_CONTROL_BITS_RESULT_DATA 32
      #define XUZ_HLS_TESTIP_CONTROL_ADDR_RESULT_CTRL 0x24

      #endif // UZ_HLS_TESTIP_HWADDRESSES_H
   
   .. code-block:: c
      :linenos:
      :caption: ``uz_HLS_testIP.c``
   
      #include "../../uz/uz_global_configuration.h"
      #if UZ_HLS_TESTIP_MAX_INSTANCES > 0U
      #include <stdbool.h>
      #include "../../uz/uz_HAL.h"
      #include "uz_HLS_testIP.h"
      #include "uz_HLS_testIP_hw.h"

      struct uz_HLS_testIP {
         bool is_ready;
         struct uz_HLS_testIP_config_t config;
      };

      static uint32_t instance_counter = 0U;
      static uz_HLS_testIP instances[UZ_HLS_TESTIP_MAX_INSTANCES] = { 0 };

      static uz_HLS_testIP* uz_HLS_testIP_allocation(void);

      static uz_HLS_testIP* uz_HLS_testIP_allocation(void){
         uz_assert(instance_counter < UZ_HLS_TESTIP_MAX_INSTANCES);
         uz_HLS_testIP* self = &instances[instance_counter];
         uz_assert_false(self->is_ready);
         instance_counter++;
         self->is_ready = true;
         return (self);
      }

      uz_HLS_testIP* uz_HLS_testIP_init(struct uz_HLS_testIP_config_t config) {
         uz_HLS_testIP* self = uz_HLS_testIP_allocation();
         self->config = config;
         return (self);
      }

      int32_t uz_HLS_testIP_multiply(uz_HLS_testIP* self, int32_t A, int32_t B){
         uz_assert_not_NULL(self);
         uz_assert(self->is_ready);
         uz_HLS_testIP_hw_write_A(self->config.base_address,A);
         uz_HLS_testIP_hw_write_B(self->config.base_address,B);
         return (uz_HLS_testIP_hw_read_result(self->config.base_address));
      }
      #endif
   
   
   .. code-block:: c
      :linenos:
      :caption: ``uz_HLS_testIP.h``
   
      #ifndef UZ_HLS_TESTIP_H
      #define UZ_HLS_TESTIP_H
      #include <stdint.h>

      /**
      * @brief Data type for object uz_HLS_testIP
      *
      */
      typedef struct uz_HLS_testIP uz_HLS_testIP;

      /**
      * @brief Configuration struct for myTestIP
      *
      */
      struct uz_HLS_testIP_config_t{
         uint32_t base_address; /**< Base address of the IP core */
         uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP core */
      };

      /**
      * @brief Initializes an instance of the myTestIP driver
      *
      * @param config Configuration values for the IP core
      * @return Pointer to initialized instance
      */
      uz_HLS_testIP* uz_HLS_testIP_init(struct uz_HLS_testIP_config_t config);

      /**
      * @brief Calculates result=A*B
      *
      * @param self Pointer to IP core instance that was initialized with init function
      * @param A First factor
      * @param B Second factor
      * @return Product of A times B
      */
      int32_t uz_HLS_testIP_multiply(uz_HLS_testIP* self, int32_t A, int32_t B);

      #endif // UZ_HLS_TESTIP_H

   - Open ``uz_global_configuration.h`` and add ``#define UZ_HLS_TESTIP_MAX_INSTANCES 0U`` to the normal configuration section and ``#define UZ_HLS_TESTIP_MAX_INSTANCES 20U`` to the test configuration section.
   - For the unit tests navigate to ``vitis/software/Baremetal/test/IP_Cores`` and create the folder ``uz_HLS_testIP``.
   - Within this folder create the file ``test_uz_HLS_testIP.c`` and ``test_uz_HLS_testIP_hw.c``.

   .. code-block:: c
      :linenos:
      :caption: ``test_uz_HLS_testIP_hw.c``

      #include "unity.h"
      #include "uz_HLS_testIP_hw.h"
      #include <stdbool.h>
      #include <stdint.h>
      #include "test_assert_with_exception.h"
      #include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
      #include "uz_HLS_testIP_hwAddresses.h"

      #define BASE_ADDRESS 0x0F0000000U // random hex value that represents a fictional base address
      #define ZERO_BASE_ADDRESS 0x00000000U


      void test_uz_HLS_testIP_hw_write_A_base_address_zero(void) {
      	TEST_ASSERT_FAIL_ASSERT(uz_HLS_testIP_hw_write_A(ZERO_BASE_ADDRESS, 10));
      }

      void test_uz_HLS_testIP_hw_write_B_base_address_zero(void) {
      	TEST_ASSERT_FAIL_ASSERT(uz_HLS_testIP_hw_write_B(ZERO_BASE_ADDRESS, 10));
      }

      void test_uz_HLS_testIP_hw_read_result_base_address_zero(void) {
      	TEST_ASSERT_FAIL_ASSERT(uz_HLS_testIP_hw_read_result(ZERO_BASE_ADDRESS));
      }

      void test_uz_HLS_testIP_hw_write_A(void) {
      	int32_t testvalue = 10;
      	uz_axi_write_int32_Expect(BASE_ADDRESS + XUZ_HLS_TESTIP_CONTROL_ADDR_A_DATA, testvalue);
      	uz_HLS_testIP_hw_write_A(BASE_ADDRESS, testvalue);
      }

      void test_uz_HLS_testIP_hw_write_B(void) {
      	int32_t testvalue = 10;
      	uz_axi_write_int32_Expect(BASE_ADDRESS + XUZ_HLS_TESTIP_CONTROL_ADDR_B_DATA, testvalue);
      	uz_HLS_testIP_hw_write_B(BASE_ADDRESS, testvalue);
      }

      void test_uz_HLS_testIP_hw_read_result(void) {
      	int32_t expected_result = 42;
      	uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS + XUZ_HLS_TESTIP_CONTROL_ADDR_RESULT_DATA, expected_result);
      	uz_HLS_testIP_hw_read_result(BASE_ADDRESS);
      }


   .. code-block:: c
      :linenos:
      :caption: ``test_uz_HLS_testIP.c``

      #ifdef TEST

      #include "unity.h"
      #include "uz_HLS_testIP.h"
      #include "mock_uz_HLS_testIP_hw.h"
      #include "test_assert_with_exception.h"

      #define TEST_BASE_ADDRESS 0x000F0000

      uz_HLS_testIP* successful_init(void);
      uz_HLS_testIP* successful_init(void) {
      	struct uz_HLS_testIP_config_t config = {
      		.base_address = TEST_BASE_ADDRESS,
      		.ip_clk_frequency_Hz = 100000000U};
      	uz_HLS_testIP* instance = uz_HLS_testIP_init(config);
      	return(instance);
      }

      void test_uz_HLS_testIP_init_successful(void) {
      	successful_init();
      }

      void test_uz_HLS_testIP_multiply_assert_NULL(void) {
      	TEST_ASSERT_FAIL_ASSERT(uz_HLS_testIP_multiply(NULL, 5, 10));
      }

      void test_uz_HLS_testIP_multiply(void) {
      	uz_HLS_testIP* instance = successful_init();
      	uz_HLS_testIP_hw_write_A_Expect(TEST_BASE_ADDRESS, 5);
      	uz_HLS_testIP_hw_write_B_Expect(TEST_BASE_ADDRESS, 10);
      	uz_HLS_testIP_hw_read_result_ExpectAndReturn(TEST_BASE_ADDRESS, 50);
      	int32_t result = uz_HLS_testIP_multiply(instance, 5, 10);
      	TEST_ASSERT_EQUAL_INT32(50, result);
      }

      #endif // TEST



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
