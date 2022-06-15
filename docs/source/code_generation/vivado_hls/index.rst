================
Vitis HLS (HDL)
================
Vitis HLS is a high-level synthesis tool that converts C/C++ codes into RTL IP's. This guide will walk you through the process of setting up a project in Vivado and Vitis. A simple hardware design including a processor with DDR Memory connected to user generated IP using Axi-Lite interface will be created. This design will then be exported to the Vitis IDE, and a baremetal software project will be created and run which sets the inputs from the processor and displays the output. ``uz_piController.c`` is used as a template.

1. Open the uz_piController project in vitis hls. Synthesize and export RTL IP.
2. Import the IP into the Vivado design Suite. Run the ``pi_bd.tcl`` in Vivado block design tcl environment.
3. Generate bitstream and export hardware.
4. Create new application platform in vitis with the generated ``.XSA`` file. 
5. Use helloworld template while creating a Vitis project and replace its contents provided in the git.
6. Build and run program. 

How to use
----------

``uz_picontroller_sample`` is the main function of the HLS program and this should be included as the top function.



First usage
-----------

Following is the Vitis HLS design flow:

1. Open Vitis HLS.
2. Create new project. Add 





More Information
----------------

1. https://docs.xilinx.com/v/u/2020.1-English/ug1399-vitis-hls
2. https://docs.xilinx.com/v/u/2020.1-English/ug1400-vitis-embedded


**Placeholder**

..	toctree::
		:maxdepth: 2
		:hidden:
		:caption: Vitis HLS (HDL)

		definitions
