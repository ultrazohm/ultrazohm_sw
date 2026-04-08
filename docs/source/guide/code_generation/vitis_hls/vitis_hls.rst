.. _vitis_hls:

===============
Vitis HLS (HDL)
===============

Vitis HLS is a tool that simplifies hardware design by allowing designers to create efficient hardware designs from high-level programming languages like C and C++.
It automates the process of converting high-level code into optimized hardware descriptions, reducing development time and enabling the integration of hardware accelerators.
With Vitis HLS, designers can leverage their software skills, experiment with different optimizations, and promote design reuse and modularity.
Overall, it enables faster time-to-market and the development of highly optimized hardware accelerators.

Related Tutorials & Literature

- https://docs.xilinx.com/r/en-US/ug1399-vitis-hls/HLS-Pragmas
- https://github.com/Xilinx/Vitis-HLS-Introductory-Examples
- https://docs.xilinx.com/r/2022.2-English/ug1399-vitis-hls/Introduction-to-Vitis-HLS


Tutorial
========

This tutorial will guide you through the process of creating a simple IP core using Vitis HLS, synthesizing it, and integrating it into the UltraZohm project. 
The example IP core will perform integer multiplication.

Generation using tcl script
---------------------------


- Each Vitis HLS design can be generated using a ``script.tcl``, which includes all the necessary commands to create, synthesize and export your design.
- Example ``script.tcl`` for this tutorial:

   .. code-block:: console
   
      ############################################################
      ## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
      ############################################################
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

- This script adds the necessary source and testbench files, sets the part, clock and export settings, and runs the C simulation, synthesis and RTL export.
- This script can be further adjusted to include additional settings, optimizations and directives as needed for your specific design.
- For more information regarding the possible commands see the `Vitis HLS Command Reference Documentation <https://docs.amd.com/r/2022.2-English/ug1399-vitis-hls/vitis_hls-Command>`_ .
- E.g. (not necessary for this tutorial)
  
   .. code-block:: console

      config_interface -m_axi_addr64=0 -m_axi_alignment_byte_size 32 -m_axi_latency 64 -m_axi_max_bitwidth 32 -m_axi_max_widen_bitwidth 32
      config_rtl -register_reset_num 3
      config_array_partition -complete_threshold 2
      config_compile -no_signed_zeros -unsafe_math_optimizations 


- You can run this script by opening your terminal, navigating to the project directory and running the command ``vitis_hls -f testIP_solution\script.tcl``.
- After the script is finished, the IP core has been generated and exported and can now be integrated into the Vivado project as described in the next section.

Manual Tutorial
---------------

If you don't want to use a script to generate your design, this tutorial will guide you through the process of manually creating a the IP core using Vitis HLS, synthesizing it, and integrating it into the UltraZohm project. 


.. dropdown:: Show steps (collapsed by default)
   
   - Start Vitis HLS (2022.2 used for this tutorial)
   - Create a new HLS Project
   
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
   
   - Click **Next** to proceed to the Source and test bench file add sections. We will add these files later in the tutorial.
   - In the Solution Configuration section, you have the option to change the clock settings, board specification, and flow target.
   - Adjust the clock settings based on your project requirements. Specify the clock frequency, and any relevant parameters. Select the appropriate flow target for your project, such as generating a bitstream for FPGA programming or producing simulation files for software testing.
   
   
   .. figure:: tutorial_img/3_project_settings.png
      :width: 500px
      :align: center
   
   - Modify the board specification if needed in future applications, ensuring compatibility between the design and the physical board you're using. When you click the Device Selection Dialog, you will see a list of all the available boards from the Xilinx Library. This dialog allows you to choose the specific board that matches your hardware setup and requirements.
   - For this tutorial, set the device to ``xczu9eg-ffvc900-1-e``.
  
   .. figure:: tutorial_img/4_board_option.png
      :width: 500px
      :align: center
   
   - After completing the configuration part, an empty project will be created. Now, the basic test IP, we will implement integer multiplication and write the test bench.
   - To create a source file, simply right-click on the **Source** folder in your project and choose **New Source File...** from the menu.
   
   .. figure:: tutorial_img/5_add_source.png
      :width: 400px
      :align: center
   
   - When the file window opens, make sure to check the path displayed. If the path is not the same as your project location, you should adjust it accordingly. 
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
   
   - When the file window opens, make sure to check the path displayed. If the path is not the same as your project location, you should adjust it accordingly. 
   - To create the new source file ``uz_HLS_testIP.h``, enter the filename in the file window and click **Save**, and write the code to the file.
   
   .. figure:: tutorial_img/8_create_header.png
      :width: 500px
      :align: center
   
   .. code-block:: c
   
   	void uz_HLS_testIP(int32_t a, int32_t b, int32_t *result);

   - Now, let's move on to the port settings, AXI interface configuration, and other important modifications. HLS gives a space and chance to change the IP core according to the system needs. You can make modifications with Pragmas. 
   - The page includes introductory information about the usage of the `HLS Pragmas <https://docs.xilinx.com/r/en-US/ug1399-vitis-hls/HLS-Pragmas>`_.
   
   - As additional way to check pragmas from code and add specific settings to it, you can use Directive section.
   
   .. figure:: tutorial_img/26_directive.png
      :width: 1200px
      :align: center
   
   - If you have a closer look to inside of the Directive, this is an additional way to add pragmas to the code. 
   
   .. figure:: tutorial_img/27_insert_directive.png
      :width: 400px
      :align: center
   
   - For instance with right click to **a** variable, the tab that includes the pragmas as more visualized version.
   
   .. figure:: tutorial_img/28_directive_editor.png
      :width: 400px
      :align: center
   
   - To create a test bench file, simply right-click on the **Test Bench** folder in your project and choose **New Test Bench File...** from the menu.
   - When the file window opens, make sure to check the path displayed. If the path is not the same as your project location, you should adjust it accordingly, and write the code to the file.
   - Create a new test bench file ``tb_uz_HLS_testIP.cpp``.
   - After reviewing the created files, the source file contains a simple function that performs multiplication and returns the result. On the other hand, the test bench ensures that the result from the source file matches the expected result. It generates random values for a specified number of iterations, compares the results, and prints **"Correct"** if they match, or **"Failed"** if they differ.
   
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
   
   - To simulate the system, you can use the C simulation option. This allows you to execute the simulation using a C-based simulator, which provides an efficient and accurate representation of the system's behavior.
   
   .. figure:: tutorial_img/14_c_simulation.png
      :width: 400px
      :align: center
   
   - As you can see from simulation box, there are several options to debug, clean, build and optimize. You can simply click the OK button to continue with the default settings for now.
   
   .. figure:: tutorial_img/15_c_simulation_box.png
      :width: 400px
      :align: center
   
   - Once the compilation process is complete, you can check the results either from the console output or from the log file. If the compilation is successful and there are no errors reported, it indicates that the compilation has passed.
   - You have successfully created the necessary files and performed the simulation. Now, let's move on to the synthesis part to check the resource usage.
   - During synthesis, the design is converted into a gate-level representation, and resource usage information is provided. This allows you to analyze the utilization of FPGA resources such as logic elements, memory blocks, and I/O pins.
   - Before proceeding with the synthesis step, it is important to specify the top file of your design.
     
   .. figure:: tutorial_img/17_top_setting.png
      :width: 400px
      :align: center
   
   - Inside the Project settings, you have the ability to arrange various settings related to your project, including general, simulation, and synthesis settings. For the current task, let's focus on the synthesis part.
   
   .. figure:: tutorial_img/18_top_file.png
      :width: 600px
      :align: center
   
   - Choose ``uz_HLS_testIP.cpp`` as top function.
   
   .. figure:: tutorial_img/19_top_select.png
      :width: 600px
      :align: center
   
   - Once you have configured the synthesis settings in the Project settings, you can proceed with the C synthesis.
   
   .. figure:: tutorial_img/20_c_synthesis.png
      :width: 400px
      :align: center
   
   - At the beginning of project creation, we have seen the C synthesis parameters. Continue with the default parameter values. However, there may be specific cases where you need to modify these parameters to suit your project requirements.
     
   .. figure:: tutorial_img/21_c_settings.png
      :width: 400px
      :align: center
   
   - Once the synthesis process is complete, you can review the Summary Report of the design. This report provides comprehensive information about various aspects of the synthesized design, making it a valuable resource for analysis and evaluation.
   - The Summary Report typically includes essential data such as resource utilization (logic elements, memory blocks, I/O pins), timing constraints, power estimation, and other relevant statistics. It offers insights into the efficiency and performance of the synthesized design.
   - Take the time to carefully examine the Summary Report to gain a better understanding of the design's resource usage, timing characteristics, and overall quality.
     
   .. figure:: tutorial_img/22_report.png
      :width: 800px
      :align: center
   
   - After that click Export RTL
     
   .. figure:: tutorial_img/30_export_rtl_tab.png
      :width: 350px
      :align: center
   
   - Export your IP to Vivado workspace
   
   .. figure:: tutorial_img/31_export_rtl.png
      :width: 400px
      :align: center
   
   - At the end of the last step, you will have the designed IP core as .zip version. Unzip the file, and place at the ultrazohm_sw/ip_cores folder.

Vivado
------

- To use your new IP in the UZ vivado project, make sure, you placed the generated IP at the ultrazohm_sw/ip_cores folder.
- Open Vivado and the block design
- Navigate to ``Window->IP-Catalog`` and ``right-click->Refresh All Repository``
- Extend uz_user subblock
- Extend the smart connect by one master port to connect AXI ports to the processor
- Add the new IP-Core and connect it to the system

.. figure:: tutorial_img/32_vivado_ip_placement.png
   :width: 400px
   :align: center

- Go to the Address editor and assign a base address to the new IP-Core
- For video implementation of these steps check out :ref:`hdl_coder` last step.
- Build the bitstream, export the XSA and update the Vitis workspace as done in :ref:`gen_bitstream`

Vitis
-----

Drivers
*******

- Vitis HLS IP-Core generation yields automatically generated AXI-drivers.
- The usage is not yet aligned with the UZ project's typical drivers and will be explained in the following.
- The created files for the example project with the name uz_HLS_testIP are:

   - xuz_HLS_testip_hw.h
   - xuz_HLS_testip_linux.c
   - xuz_HLS_testip_sinit.c
   - xuz_HLS_testip.c
   - xuz_HLS_testip.h
 
While the ``_hw.h`` file is similar to the HDL-Coder generated hardware address file, the last two files include already usable drivers.
These drivers can be used for operation or additional UZ-style drivers can be created around them.
They are automatically included in the exported .xsa file from Vivado and therefore directly included in the platform project within Vitis. 
You can find them in the Vitis workspace under ``vitis -> UltraZohm/hw/drivers/your_ip_core``.
The header file can simply be included.

Initialization with Vitis HLS generated Drivers
***********************************************

To initialize an IP-core instance, the instance's define has to be taken from the ``xparameters.h`` file. When we address the IP Core, related information is added to the system files. 

.. code-block:: c

      #include <xuz_hls_testip.h>
      
      XUz_hls_testip XUz_hls_testip_instance;
      
      int32_t a = 0;
      int32_t b = 0;

      int main(void) {
   
      XUz_hls_testip_Initialize(&xuz_hls_testip_instance, XPAR_UZ_USER_UZ_HLS_TESTIP_0_DEVICE_ID);
   
   }

Usage of Vitis HLS generated Drivers
************************************

To use the write and read with set and get functions, place the initialization code in main / case init_ip_cores: 

.. code-block:: c

      XUz_hls_testip XUz_hls_testip_instance;

      int32_t a = 5;
      int32_t b = 10;
      int32_t result = 0;


      int main(void) {
   
         //IP Core Initialisation
         XUz_hls_testip_Initialize(&XUz_hls_testip_instance, XPAR_UZ_USER_UZ_HLS_TESTIP_0_DEVICE_ID);
         XUz_hls_testip_Set_a(&XUz_hls_testip_instance, a);
         XUz_hls_testip_Set_b(&XUz_hls_testip_instance, b);
         result = XUz_hls_testip_Get_result(&XUz_hls_testip_instance);
         uz_printf("The result of multiplication is %d\r\n", result);
   }

.. note::
   Using the AXI-write and -read functions is more tricky depending on the desired datatype.
   In the following snippet the AXI-interfaces have a floating point datatype, however the data for the AXI-write functions takes an argument of type ``uint32``.
   This means, the driver expects the bits of a floating point value in the storage item of an unsigned int.
   To achieve this, the user can create the really used float variable, here ``REAL_VAR`` and create a pointer of type ``uint32_t`` to this variable and cast it.
   The AXI-set function is called with the dereferenced, casted pointer, which gives the current value of the ``REAL_VAR`` to the driver.

.. code-block:: c

      float REAL_VAR = 0.0f;
      uint32_t* INT_VAR = (uint32_t*)&REAL_VAR;
      
      int main(void) {
         
         XEXAMPLE_Initialize(&example_instance, XPAR_EXAMPLE_0_DEVICE_ID);
         float value = 99.0f;
         XEXAMPLE_Set_axi_example_signal(&example_instance, *INT_VAR);
      }


How to create the driver
************************

The driver is already provided in ``ultrazohm_sw/software/Baremetal/src/IP_Cores/uz_HLS_testIP``.
To gain a better understanding of driver creation, you can follow the steps below to create a driver for the IP Core yourself.

.. dropdown:: Show steps (collapsed by default)

   - The detailed explanation for AXI test IP created with HDL Coder can be found here. 
   - Our HLS IP scenario is similar to the example. To multiply two variables result=A⋅B of type int32_t, the driver has to write A and B from the PS to the PL by AXI in the correct registers and read back the result from the PL to the PS.
   - For that reason, we need set and get functions. You can also call them as write and read. 
   - Create ``uz_HLS_testIP`` folder and move to ``ultrazohm_sw -> software -> Baremetal -> src -> IP_Cores`` 
   - In the folder, create the files: 
      
      * uz_HLS_testIP.c
      * uz_HLS_testIP.h
      * uz_HLS_testIP_hw.c
      * uz_HLS_testIP_hw.h
      * uz_HLS_testIP_hwAddresses.h
   
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
         uint32_t base_address; /**< Base address of the IP-Core */
         uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
      };

      /**
      * @brief Initializes an instance of the myTestIP driver
      *
      * @param config Configuration values for the IP-Core
      * @return Pointer to initialized instance
      */
      uz_HLS_testIP* uz_HLS_testIP_init(struct uz_HLS_testIP_config_t config);

      /**
      * @brief Calculates result=A*B
      *
      * @param self Pointer to IP-Core instance that was initialized with init function
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
      :caption: ``test_uz_HLS_testIP_hw.h``

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
      :caption: ``test_uz_HLS_testIP.h``

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



Testing the IP core with the Vitis Serial Terminal
**************************************************

- Create the file ``uz_myHLSIP.h`` in the ``include`` folder

.. code-block:: c
   :linenos:
   :caption: ``uz_myHLSIP.h``

   #pragma once

   void uz_myIP(void);

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

- Build the software.
- Include ``#include "include/uz_myHLSIP.h"`` in ``main.c`` (Baremetal R5) and call ``uz_myHLSIP();`` before the ISR is initialized!
- Connected the serial port to the Vitis Serial Terminal
- Run the program, The success message should be printed to the Vitis Serial Terminal.

.. figure:: tutorial_img/33_vitis_result.png
   :width: 400px
   :align: center


.. figure:: tutorial_img/34_vitis_serial_term.png
   :width: 400px
   :align: center

Further Reading Material
========================

* `AMD Vitis HLS User Guide <https://docs.xilinx.com/r/2022.2-English/ug1399-vitis-hls>`_
* `Parallel Programming for FPGAs <https://kastner.ucsd.edu/hlsbook/>`_
* `Vivado HLS Learnings <https://hansgiesen.net/wordpress/vivado-hls-learnings/>`_
* `When FPGAs Meet ADMM with High-level Synthesis (HLS): A Real-time Implementation of Long-horizon MPC for Power Electronic Systems <https://ieeexplore.ieee.org/document/10213796>`_
* `Vitis HLS Tutorial <https://byu-cpe.github.io/ComputingBootCamp/tutorials/vitis_hls/>`_
* `Transformations of High-Level Synthesis Codes for High-Performance Computing <https://arxiv.org/abs/1805.08288>`_
* `hls4ml <https://fastmachinelearning.org/hls4ml/>`_
* `FPGA Teaching Resources <https://sharclab.ece.gatech.edu/teaching/2023-spring-fpga/>`_
* `A floating-point matrix multiplication implemented in hardware example <https://github.com/twaclaw/matmult>`_
