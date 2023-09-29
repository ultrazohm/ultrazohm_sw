.. _vitis_hls:

=========
Vitis HLS 
=========

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

General Steps
-------------

- Start Vitis HLS (2022.2 used for this tutorial)
- Create a new HLS Project

.. figure:: tutorial_img/1_open_new_project.png
   :width: 400px
   :align: center

- In the Project Configuration window, locate the field for the project name and update it with ``uz_axi_myTestIP``.
- Next, find the related path field in the Project Configuration window. Update the path to ensure that the project files are stored in the desired location.

.. figure:: tutorial_img/2_project_name.png
   :width: 600px
   :align: center

- Click **Next** to proceed to the Source and test bench file add sections. We will add these files later in the tutorial.
- In the Solution Configuration section, you have the option to change the clock settings, board specification, and flow target.
- Adjust the clock settings based on your project requirements. Specify the clock frequency, and any relevant parameters. Select the appropriate flow target for your project, such as generating a bitstream for FPGA programming or producing simulation files for software testing.
- Keep the Solution Configuration parameters at their default settings, simply leave them unchanged.

.. figure:: tutorial_img/3_project_settings.png
   :width: 500px
   :align: center

- Modify the board specification if needed in future applications, ensuring compatibility between the design and the physical board you're using. When you click the Device Selection Dialog, you will see a list of all the available boards from the Xilinx Library. This dialog allows you to choose the specific board that matches your hardware setup and requirements.
- Keep the Device Selection at default settings, simply leave them unchanged. This step included for informing.

.. figure:: tutorial_img/4_board_option.png
   :width: 500px
   :align: center

- After completing the configuration part, an empty project will be created. Now, the basic test IP, we will implement integer multiplication and write the test bench.
- To create a source file, simply right-click on the **Source** folder in your project and choose **New Source File...** from the menu.

.. figure:: tutorial_img/5_add_source.png
   :width: 400px
   :align: center

- When the file window opens, make sure to check the path displayed. If the path is not the same as your project location, you should adjust it accordingly. 
- To create the new source file ``uz_axi_myTestIP.cpp``, enter the filename in the file window and click **Save**, and write the code to the file.

.. figure:: tutorial_img/6_create_source.png
   :width: 500px
   :align: center

.. code-block:: c

   #include <stdint.h>

   void uz_axi_myTestIP(int32_t a, int32_t b, int32_t *result) {

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
- To create the new source file ``uz_axi_myTestIP.h``, enter the filename in the file window and click **Save**, and write the code to the file.

.. figure:: tutorial_img/8_create_header.png
   :width: 500px
   :align: center

.. code-block::

	void uz_axi_myTestIP(int32_t a, int32_t b, int32_t *result);

- To create a test bench file, simply right-click on the **Test Bench** folder in your project and choose **New Test Bench File...** from the menu.
- When the file window opens, make sure to check the path displayed. If the path is not the same as your project location, you should adjust it accordingly, and write the code to the file.
- Create a new test bench file ``tb_uz_axi_myTestIP.cpp``.
- After reviewing the created files, the source file contains a simple function that performs multiplication and returns the result. On the other hand, the test bench ensures that the result from the source file matches the expected result. It generates random values for a specified number of iterations, compares the results, and prints **"Correct"** if they match, or **"Failed"** if they differ.

.. figure:: tutorial_img/11_create_testbench.png
   :width: 500px
   :align: center

.. code-block:: c
	
   #include <stdio.h>
   #include <stdint.h>

   void uz_axi_myTestIP(int32_t a, int32_t b, int32_t *result);

   int main() {
      int32_t a = 5;
      int32_t b = 7;
      int32_t result;

      uz_axi_myTestIP(a, b, &result);

      printf("Multiplication result: %d\n", result);

      return 0;
   }


Simulation, Synthesis and Export
--------------------------------

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

- Choose ``uz_axi_myTestIP.cpp`` as top function.

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
 
- So far, you have gained an understanding of the basics of Vitis HLS. Now, let's move on to the port settings, AXI interface configuration, and other important modifications. HLS gives a space and chance to change the IP core according to the system needs. You can make modifications with Pragmas. 
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

- Click the C Synthesis. Change the period with 10ns for 100MHz or you can directly write frequency, and choose a MPSoC+ board.

.. figure:: tutorial_img/29_c_synt.png
   :width: 400px
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
- Right click into the block design and select IP settings
- Refresh the IP catalogue
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
- The created files for the example project with the name uz_axi_myTestIP are:

   - uz_axi_myTestIP_hw.h
   - uz_axi_myTestIP_linux.c
   - uz_axi_myTestIP_sinit.c
   - uz_axi_myTestIP.c
   - uz_axi_myTestIP.h
 
While the ``_hw.h`` file is similar to the HDL-Coder generated hardware address file, the last two files include already usable drivers.
These drivers can be used for operation or additional UZ-style drivers can be created around them.

- You can find the files from ``solution -> impl -> ip -> drivers -> src`` 
- Copy them to the new folder as named with the IP core ``uz_axi_myTestIP`` and move to ``ultrazohm_sw -> software -> Baremetal -> src -> IP_Cores`` 


Initialization with Vitis HLS generated Drivers
***********************************************

To initialize an IP-core instance, the instance's define has to be taken from the ``xparameters.h`` file. When we address the IP Core, related information is added to the system files. 

.. code-block:: c

      #include "IP_Cores/uz_axi_myTestIP/xuz_axi_myTestIP.h"
      
      XUz_axi_myTestIP xuz_axi_myTestIP_instance;
      
      int32_t a = 0;
      int32_t b = 0;

      int main(void) {
   
      XUz_axi_myTestIP_Initialize(&xuz_axi_myTestIP_instance, XPAR_UZ_USER_UZ_AXI_MYTESTIP_0_DEVICE_ID);
   
   }

Usage of Vitis HLS generated Drivers
************************************

To use the write and read with set and get functions, place the initialization code in main / case init_ip_cores: 

.. code-block:: c

      XUz_axi_mytestip xuz_axi_mytestip_instance;

      int32_t a = 5;
      int32_t b = 10;
      int32_t result = 0;


      int main(void) {
   
         //IP Core Initialisation
         XUz_axi_mytestip_Initialize(&xuz_axi_mytestip_instance, XPAR_UZ_USER_UZ_AXI_MYTESTIP_0_DEVICE_ID);
         XUz_axi_mytestip_Set_a(&xuz_axi_mytestip_instance, a);
         XUz_axi_mytestip_Set_b(&xuz_axi_mytestip_instance, b);
         result = XUz_axi_mytestip_Get_result(&xuz_axi_mytestip_instance);
         uz_printf("The result of multiplication is %d\r\n", result);
   }

.. note::
   Using the AXI-write and -read functions is more tricky depending on the desired datatype.
   In the example the AXI-interfaces have a floating point datatype, however the data for the AXI-write functions takes an argument of type ``uint32``.
   This means, the driver expects the bits of a floating point value in the storage item of an unsigned int.
   To achieve this, the user can create the really used float variable, here ``REAL_VAR`` and create a pointer of type ``uint32_t`` to this variable and cast it.
   The AXI-set function is called with the dereferenced, casted pointer, which gives the current value of the ``REAL_VAR`` to the driver.

.. code-block:: c

      float REAL_VAR = 0.0f;
      uint32_t* INT_VAR = (uint32_t*)&REAL_VAR;
      
      int main(void) {
         
         XEXAMPLE_Initialize(&example_instance, XPAR_EXAMPLE_0_DEVICE_ID);
         REAL_VAR = 99.0f;
         XEXAMPLE_Set_axi_example_signal(&example_instance, *INT_VAR);
      }


How to create the driver
************************

- The detailed explanation for AXI test IP created with HDL Coder can be found here. 
- Our HLS IP scenerio is similar to the example. To multiply two variables result=A⋅B of type int32_t, the driver has to write A and B  from the PS to the PL by AXI in the correct registers and read back the result from the PL to the PS.
- For that reason, we need set and get functions. You can also call them as write and read. 
- Create ``uz_axi_myTestIP`` folder and move to ``ultrazohm_sw -> software -> Baremetal -> src -> IP_Cores`` 
- In the folder, create the files: 
   
   * xuz_axi_myTestIP.c
   * xuz_axi_myTestIP.h
   * xuz_axi_myTestIP_hw.c
   * xuz_axi_myTestIP_hw.h
   * xuz_axi_myTestIP_hwAddresses.h

- In the file ``uz_myTestIP_hwAddresses.h`` add an include guard to it (``#pragma once`` in first line)

.. code-block:: c
   :linenos:
   :caption: ``xuz_axi_myTestIP_hw.c``

   #include "xuz_axi_myTestIP_hw.h"
   #include "xuz_axi_myTestIP_hwAddresses.h"
   #include "../../uz/uz_AXI.h"

   void uz_myTestIP_write_A(uint32_t base_address,int32_t A){
      uz_axi_write_int32(base_address+XUZ_AXI_MYTESTIP_CONTROL_ADDR_A_DATA,A);
   }

   void uz_myTestIP_write_B(uint32_t base_address,int32_t B){
      uz_axi_write_int32(base_address+XUZ_AXI_MYTESTIP_CONTROL_ADDR_B_DATA,B);
   }

   int32_t uz_myTestIP_read_result(uint32_t base_address){
      return (uz_axi_read_int32(base_address+XUZ_AXI_MYTESTIP_CONTROL_ADDR_RESULT_DATA));
   }

.. code-block:: c
   :linenos:
   :caption: ``xuz_axi_myTestIP_hw.h``

   #ifndef UZ_MYTESTIP_HW_H
   #define UZ_MYTESTIP_HW_H
   #include <stdint.h>

   void uz_myTestIP_write_A(uint32_t base_address,int32_t A);
   void uz_myTestIP_write_B(uint32_t base_address,int32_t B);
   int32_t uz_myTestIP_read_result(uint32_t base_address);

   #endif // UZ_MYTESTIP_HW_H

.. code-block:: c
   :linenos:
   :caption: ``xuz_axi_myTestIP_hwAddresses.h``

   #define XUZ_AXI_myTestIP_CONTROL_ADDR_A_DATA      0x10
   #define XUZ_AXI_myTestIP_CONTROL_BITS_A_DATA      32
   #define XUZ_AXI_myTestIP_CONTROL_ADDR_B_DATA      0x18
   #define XUZ_AXI_myTestIP_CONTROL_BITS_B_DATA      32
   #define XUZ_AXI_myTestIP_CONTROL_ADDR_RESULT_DATA 0x20
   #define XUZ_AXI_myTestIP_CONTROL_BITS_RESULT_DATA 32
   #define XUZ_AXI_myTestIP_CONTROL_ADDR_RESULT_CTRL 0x24

.. code-block:: c
   :linenos:
   :caption: ``xuz_axi_myTestIP.c``

   #include "../../uz/uz_global_configuration.h"
   #if UZ_MYTESTIP_MAX_INSTANCES > 0U
   #include <stdbool.h>
   #include "../../uz/uz_HAL.h"
   #include "xuz_axi_myTestIP.h"

   struct uz_myTestIP_t {
      bool is_ready;
   };

   static uint32_t instance_counter = 0U;
   static uz_myTestIP_t instances[UZ_MYTESTIP_MAX_INSTANCES] = { 0 };

   static uz_myTestIP_t* uz_myTestIP_allocation(void);

   static uz_myTestIP_t* uz_myTestIP_allocation(void){
      uz_assert(instance_counter < UZ_MYTESTIP_MAX_INSTANCES);
      uz_myTestIP_t* self = &instances[instance_counter];
      uz_assert_false(self->is_ready);
      instance_counter++;
      self->is_ready = true;
      return (self);
   }

   uz_myTestIP_t* uz_myTestIP_init() {
      uz_myTestIP_t* self = uz_myTestIP_allocation();
      return (self);
   }

   int32_t uz_myTestIP_multiply(uz_myIP_t* self, int32_t A, int32_t B){
   uz_assert(self->is_ready);
   uz_myTestIP_write_A(self->config.base_address,A);
   uz_myTestIP_write_B(self->config.base_address,B);
   return (uz_myTestIP_read_result(self->config.base_address));
   }
   #endif


.. code-block:: c
   :linenos:
   :caption: ``xuz_axi_myTestIP.h``

   #ifndef UZ_MYTESTIP_H
   #define UZ_MYTESTIP_H
   #include <stdint.h>

   /**
   * @brief Data type for object myTestIP
   *
   */
   typedef struct uz_myTestIP_t uz_myTestIP_t;

   /**
   * @brief Configuration struct for myTestIP
   *
   */
   struct uz_myTestIP_config_t{
      uint32_t base_address; /**< Base address of the IP-Core */
      uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
   };

   /**
   * @brief Initializes an instance of the myTestIP driver
   *
   * @param config Configuration values for the IP-Core
   * @return Pointer to initialized instance
   */
   uz_myTestIP_t* uz_myTestIP_init(struct uz_myTestIP_config_t config);

   /**
   * @brief Calculates result=A*B
   *
   * @param self Pointer to IP-Core instance that was initialized with init function
   * @param A First factor
   * @param B Second factor
   * @return Product of A times B
   */
   int32_t uz_myTestIP_multiply(uz_myTestIP_t* self, int32_t A, int32_t B);

   #endif // UZ_MYTESTIP_H

- Open ``uz_global_configuration.h`` if you already renamed the sample configuration. If not, see :ref:`global_configuration`.
- Add ``#define UZ_MYTESTIP_MAX_INSTANCES 5U`` to ``uz_global_configuration.h`` inside the test ifdef (at the bottom of the file). We can now use up to 5 instances of the IP-core driver for five different instances of the IP-Core in the tests.
- Create the file ``uz_myTestIP.h`` in the ``include`` folder

.. code-block:: c
   :linenos:
   :caption: ``uz_myTestIP.h``

   #pragma once

   void uz_myIP(void);

- Create the file ``uz_myTestIP.c`` in the ``sw`` folder.

.. code-block:: c
   :linenos:
   :caption: ``uz_myTestIP.c``

   #include "../include/uz_myTestIP.h"
   #include "../uz/uz_HAL.h"
   #include "../IP_Cores/uz_axi_myTestIP/uz_axi_myTestIP.h"
   #include "xparameters.h"

   void uz_myTestIP(void){
      struct uz_myTestIP_config_t config={
            .base_address= XPAR_UZ_USER_UZ_AXI_myTestIP_0_S_AXI_CONTROL_BASEADDR,
            .ip_clk_frequency_Hz=100000000U
      };
      uz_myIP_t *instance = uz_myIP_init(config);
      int32_t a = 5;
      int32_t b = 10;
      int32_t c = uz_myIP_multiply(instance, a, b);
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

- Add ``#define UZ_MYTESTIP_MAX_INSTANCES 1U`` between ``ifndef TEST`` and the first ``#endif`` to use one instance of the module in the software.
- Build the software.
- Include ``#include "include/uz_myTestIP.h"`` in ``main.c`` (Baremetal R5) and call ``uz_myTestIP();`` before the ISR is initialized!
- Connected the serial port to the Vitis Serial Terminal
- Run the program, The success message should be printed to the Vitis Serial Terminal.

.. figure:: tutorial_img/33_vitis_result.png
   :width: 400px
   :align: center


.. figure:: tutorial_img/34_vitis_serial_term.png
   :width: 400px
   :align: center


..	toctree::
		:maxdepth: 2
		:hidden:
		:caption: Vitis HLS

		definitions


