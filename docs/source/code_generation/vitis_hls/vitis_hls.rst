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

- Start Vitis HLS (2022.2 used for this tutorial)
- Create a new HLS Project

.. figure:: tutorial_img/1_open_new_project.png
   :width: 600px
   :align: center

- In the Project Configuration window, locate the field for the project name and update it with "uz_axi_mytestIP".
- Next, find the related path field in the Project Configuration window. Update the path to ensure that the project files are stored in the desired location.

.. figure:: tutorial_img/2_project_name.png
   :width: 600px
   :align: center

- Click "Next" to proceed to the Source and Testbench file add sections. We will add these files later in the tutorial.
- In the Solution Configuration section, you have the option to change the clock settings, board specification, and flow target.
- Adjust the clock settings based on your project requirements. Specify the clock frequency, and any relevant parameters. Select the appropriate flow target for your project, such as generating a bitstream for FPGA programming or producing simulation files for software testing.
- Keep the Solution Configuration parameters at their default settings, simply leave them unchanged.

.. figure:: tutorial_img/3_project_settings.png
   :width: 600px
   :align: center

- Modify the board specification if needed in future applications, ensuring compatibility between the design and the physical board you're using. When you click the Device Selection Dialog, you will see a list of all the available boards from the Xilinx Library. This dialog allows you to choose the specific board that matches your hardware setup and requirements.
- Keep the Device Selection at default settings, simply leave them unchanged. This step included for informing.

.. figure:: tutorial_img/4_board_option.png
   :width: 600px
   :align: center

- After completing the configuration part, an empty project will be created. Now, it's time to create your source files and Testbench.
- To create a source file, simply right-click on the 'Source' folder in your project and choose 'New Source File...' from the menu.

.. figure:: tutorial_img/5_add_source.png
   :width: 400px
   :align: center

- When the file window opens, make sure to check the path displayed. If the path is not the same as your project location, you should adjust it accordingly. 
- To create the new source file 'uz_axi_mytestIP.cpp', enter the filename in the file window and click 'Save'.

.. figure:: tutorial_img/6_create_source.png
   :width: 600px
   :align: center

- To create a header file, simply right-click on the 'Source' folder in your project and choose 'New Source File...' from the menu.

.. figure:: tutorial_img/7_add_header.png
   :width: 400px
   :align: center

- When the file window opens, make sure to check the path displayed. If the path is not the same as your project location, you should adjust it accordingly. 
- To create the new source file 'uz_axi_mytestIP.h', enter the filename in the file window and click 'Save'.

.. figure:: tutorial_img/8_create_header.png
   :width: 600px
   :align: center

- For the basic test IP, we will implement unsigned integer multiplication.
- Feel free to write your own code through image or copy and paste the desired code into the 'uz_axi_mytestIP.cpp' file.

.. figure:: tutorial_img/9_source_code.png
   :width: 600px
   :align: center

.. code-block::
	
	#include "stdint.h"
	#include "uz_axi_mytestIP.h"

	uint16_t testIP (uint16_t a, uint16_t b )
	{
		uint16_t result;
		result = a * b;
		return result;
	}

- Feel free to write your own code through image or copy and paste the desired code into the 'uz_axi_mytestIP.h' file.

.. figure:: tutorial_img/10_header_code.png
   :width: 600px
   :align: center

.. code-block::

	uint16_t testIP (uint16_t a, uint16_t b);
	
- To create a testbench file, simply right-click on the 'Test Bench' folder in your project and choose 'New Test Bench File...' from the menu.

.. figure:: tutorial_img/11_create_testbench.png
   :width: 400px
   :align: center

- When the file window opens, make sure to check the path displayed. If the path is not the same as your project location, you should adjust it accordingly. 
- To create the new test bench file 'tb_uz_axi_mytestIP.cpp', enter the filename in the file window and click 'Save'.

.. figure:: tutorial_img/12_add_testbench.png
   :width: 600px
   :align: center

- Feel free to write your own code through image or copy and paste the desired code into the 'tb_uz_axi_mytestIP.cpp' file.

.. figure:: tutorial_img/13_testbench_code.png
   :width: 400px
   :align: center

.. code-block::
	
	#include <cstdint>
	#include <cstdio>
	#include <cstdlib>
	#include "uz_axi_mytestIP.h"

	#define size 32
	#define max_val 1000

	uint16_t a[size],b[size];
	uint16_t result;
	uint16_t hls_result;

	int main (void)
	{
		int i;
		for ( i = 0; i < size; i++){
			a[i] = rand() % max_val;
			b[i] = rand() % max_val;
		}
		for (i = 0; i < size; i++){
			result = a[i] * b[i];
			hls_result = testIP(a[i],b[i]);
			if (result == hls_result){
				std::printf("TestIP result is correct\n\r");
			}
			else
				std::printf("The test has failed\n\r");
		}
	}

- After reviewing the created files, the source file contains a simple function that performs multiplication and returns the result. On the other hand, the test bench ensures that the result from the source file matches the expected result. It generates random values for a specified number of iterations, compares the results, and prints "Correct" if they match, or "Failed" if they differ.

- To simulate the system, you can use the C simulation option. This allows you to execute the simulation using a C-based simulator, which provides an efficient and accurate representation of the system's behavior.

.. figure:: tutorial_img/14_c_simulation.png
   :width: 400px
   :align: center

- As you can see from simulation box, there are several options to debug, clean, build and optimize. You can simply click the OK button to continue with the default settings for now.

.. figure:: tutorial_img/15_c_simulation_box.png
   :width: 400px
   :align: center

- Once the compilation process is complete, you can check the results either from the console output or from the log file. If the compilation is successful and there are no errors reported, it indicates that the compilation has passed.

.. figure:: tutorial_img/16_log_passed.png
   :width: 400px
   :align: center

- Up until this point, you have successfully created the necessary files and performed the simulation. Now, let's move on to the synthesis part to check the resource usage.
- During synthesis, the design is converted into a gate-level representation, and resource usage information is provided. This allows you to analyze the utilization of FPGA resources such as logic elements, memory blocks, and I/O pins.
- Before proceeding with the synthesis step, it is important to specify the top file of your design.
  
.. figure:: tutorial_img/17_top_setting.png
   :width: 400px
   :align: center

- Inside the Project settings, you have the ability to arrange various settings related to your project, including general, simulation, and synthesis settings. For the current task, let's focus on the synthesis part.

.. figure:: tutorial_img/18_top_file.png
   :width: 600px
   :align: center

- Choose 'uz_axi_mytestIP.cpp' as top function.

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

- For the next part of the tutorial, you have the option to either create a new project or modify the current one, depending on your preferences.
  
So far, you have gained an understanding of the basics of Vitis HLS. Now, let's move on to the port settings, AXI interface configuration, and other important modifications.
HLS gives a space and chance to change the IP core according to the system needs. You can make modifications with Pragmas. 
This page includes introductory information about the usage of the `HLS Pragmas <https://docs.xilinx.com/r/en-US/ug1399-vitis-hls/HLS-Pragmas>`_.

- As the next step, we will read the data from the AXI ports and write it back.
- So we need to add the pragmas which specifies the AXI port type in the 'uz_axi_mytestIP.cpp'

.. code-block::

   #include <stdint.h>
   #include "uz_axi_mytestIP.h"

   int32_t testIP (int32_t a, int32_t b ) {
   
   #pragma HLS INTERFACE mode=s_axilite port=a
   #pragma HLS INTERFACE mode=s_axilite port=b
   #pragma HLS INTERFACE mode=s_axilite port=return
   
      int32_t result = a * b;
      return result; 
   }

.. figure:: tutorial_img/23_source_code_ip.png
   :width: 400px
   :align: center

- mode = s_axilite: This specifies the interface mode as s_axilite, which stands for AXI Lite.
- port =  " ": This specifies that the interface is connected to the input port of the module. You can replace input with the name of the actual port in your design.
- Feel free to write your own code through image or copy and paste the desired code into the 'uz_axi_mytestIP.h' file.

.. figure:: tutorial_img/24_header_code_ip.png
   :width: 400px
   :align: center

.. code-block::

	int32_t testIP (int32_t a, int32_t b);

- Feel free to write your own code through image or copy and paste the desired code into the 'tb_uz_axi_mytestIP.cpp' file.

.. figure:: tutorial_img/25_tb_code_ip.png
   :width: 600px
   :align: center

.. code-block::
	
	#include <cstdint>
	#include <cstdio>
	#include <cstdlib>
	#include "uz_axi_mytestIP.h"

	#define size 32
	#define max_val 1000

	int32_t a[size],b[size];
	int32_t result;
	int32_t hls_result;

	int main (void)
	{
		int i;
		for ( i = 0; i < size; i++){
			a[i] = rand() % max_val;
			b[i] = rand() % max_val;
		}
		for (i = 0; i < size; i++){
			result = a[i] * b[i];
			hls_result = testIP(a[i],b[i]);
			if (result == hls_result){
				std::printf("TestIP result is correct\n\r");
			}
			else
				std::printf("The test has failed\n\r");
		}
	}

- As additional way to check pragmas from code and add specific settings to it, you can use Directive section.

.. figure:: tutorial_img/26_directive.png
   :width: 1200px
   :align: center

- If you have a closer look to inside of the Directive,  This is an additional way to add pragmas to the code. 

.. figure:: tutorial_img/27_insert_directive.png
   :width: 400px
   :align: center

- For instance with right click to 'a' variable, the tab that includes the pragmas as more visualized version.

.. figure:: tutorial_img/28_directive_editor.png
   :width: 400px
   :align: center

- Click the C Synthesis. Change the period with 100MHz, and choose a MPSoC+ board.

.. figure:: tutorial_img/29_c_synt.png
   :width: 400px
   :align: center

- After that click Export RTL
  
.. figure:: tutorial_img/30_export_rtl_tab.png
   :width: 400px
   :align: center

- Export your IP to Vivado workspace

.. figure:: tutorial_img/31_export_rtl.png
   :width: 400px
   :align: center

- At the end of the last step, you will have the designed IP core as .zip version. Unzip the file, and place at the ultrazohm_sw/ip_cores folder.
- For video implementation of these steps check out :ref:`hdl_coder` last step.
- Open Vivado and the block design
- Right click into the block design and select IP settings
- Refresh the IP catalogue
- Extend uz_user subblock
- Extend the smartconnect by one master port to connect AXI ports to the processor
- Add the new IP-Core and connect it to the system
- Go to the Address editor and assign a base address to the new IP-Core
- Build the bitstream, export the XSA and update the Vitis workspace as done in :ref:`gen_bitstream`
- Follow the :ref:`how_to_create_ipcore_driver` tutorial to create a software driver for the IP-Core


..	toctree::
		:maxdepth: 2
		:hidden:
		:caption: Vitis HLS

		definitions