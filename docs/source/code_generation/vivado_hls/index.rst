================
Vitis HLS (HDL)
================
Vitis HLS is a high-level synthesis tool that converts C/C++ codes into RTL IP's. This guide will walk you through the process of setting up a project in Vivado and Vitis. A simple hardware design including a processor with DDR Memory connected to user generated IP using Axi-Lite interface will be created. This design will then be exported to the Vitis IDE, and a baremetal software project will be created and run which sets the inputs from the processor and displays the output. ``uz_piController.c`` is used as a template and it is implemented with the 2020.1 version .

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
2. Create new project. Add the


In the Vivado Design Suite

1. Create project in Vivado.
2. In the ``IP Catalog`` window Right click and add the HLS IP through 'Add Repository'.
3. Click on 'Create Block design' under ``IP Integrator``. 
4. Add the Zynq processor to the block diagram.
5. Run Block automation with the board preset.This will create two master interfaces. Disable one master interface and enable an HPC slave interface.
6. Add the HLS IP through '+' sign in the top.
7. Run connection automation.
8. Generate HDL wrapper in the source pane.
9. Generate bitstream. Then click on Export → Export Hardware in the File menu.
10. This will create a ``.XSA`` file including bitstream information.

.. _Block_diagram_Overview:

.. figure:: ./block_diagram.svg
   :width: 800
   :align: center

   Block Diagram of PI Controller.

Launch Vitis.

1. Create a new Application Project.
2. Open the Create a new platform… tab. Browse your XSA file and click Open.
3. Specify Application Project name and click Next.
4. Select Hello World template and click Finish.
5. In Vitis' Explorer pane, find the application projects “src” directory. Right click on it and select New → File.
6. Specify the name "uz_pi_controller.h".
7. Copy the contents from git to the file.
8. Replace the contents of ``helloworld.c`` with the helloworld file provided in git.
9. Build and run the program.

.. note:: Xil_DCacheFlushRange should be used before writing the value into the memory.






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
