===========
Vivado HLS 
===========

Tutorial
========

- Start Vitis HLS (2022.1 used for this tutorial)
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

-In the Solution Configuration section, you have the option to change the clock settings, board specification, and flow target.
Adjust the clock settings based on your project requirements. Specify the clock frequency, and any relevant parameters.
Select the appropriate flow target for your project, such as generating a bitstream for FPGA programming or producing simulation files for software testing.

- Keep the Solution Configuration parameters at their default settings, simply leave them unchanged.

.. figure:: tutorial_img/3_project_settings.png
   :width: 600px
   :align: center

- Modify the board specification if needed in future applications, ensuring compatibility between the design and the physical board you're using.
When you click the Device Selection Dialog, you will see a list of all the available boards from the Xilinx Library. 
This dialog allows you to choose the specific board that matches your hardware setup and requirements.

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

For the basic test IP, we will implement unsigned integer multiplication.

- Feel free to write your own code through image or copy and paste the desired code into the 'uz_axi_mytestIP.cpp' file.

.. figure:: tutorial_img/9_source_code.png
   :width: 600px
   :align: center

.. code-block::
	
	#include "stdint.h"
	
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
