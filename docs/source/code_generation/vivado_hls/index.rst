================
Vitis HLS (HDL)
================
HLS is a design process in which a high level, functional description of a design is automatically compiled into a RTL implementation that meets certain user specified design constraints.
Vitis HLS is a tool that is responsible for compiling c/c++ code into kernel for acceleration in the programmable logic (PL) region. It provides ease of development and accelerates verification time over RTL by raising the abstraction level for FPGA hardware design.

This guide will walk you through the process of setting up a project in Vivado and Vitis. A simple hardware design including a processor with DDR Memory connected to user generated IP using Axi-Lite interface will be created. This design will then be exported to the Vitis IDE, and a baremetal software project will be created and run which sets the inputs from the processor and displays the output. ``uz_piController.c`` is used as a template and it is coded with the 2020.1 version and implemented in the ZCU104 board. 


Description
-----------

``uz_picontroller_sample`` is the main fuction that does the PI computations. ``Clamping_Circuit`` ensures that the output values does not go beyond specific limit.
Since float compare is not accurate due to the conversion, an ``approx_eqf`` function is written to compare float values with specified error limit in the testbench file.

Interfaces
^^^^^^^^^^

   - The parameters ``kp, ki, samplingTime_sec, upper_limit and lower_limit`` are set as single precision floating point and is grouped inside the struct pointer variable ``self``. This is the config struct in which the user can customize the controller variables.
   - The inputs ``I_rst`` and ``ext_clamping`` are declared as bool.
   - The inputs ``referenceValue`` and ``actualValue`` are set as floating point variables.
   - The IP block returns the ``output`` in float format.

The values of the inputs are set from the processor through ``s_axilite`` interface which is bundled into a single ``DIN`` entity and the output value is written to DDR memory of the processor through ``m_axi_Dout`` interface.
``offset=slave`` is used to set the address of the DDR memory. This creates an additional ``s_axilite_control`` interface to specify the address. 

.. code-block:: c
   :linenos:
   :caption: Interfaces of PI controller IP Block.

        #pragma HLS INTERFACE m_axi port=output offset=slave           bundle=Dout depth=50
	#pragma HLS INTERFACE s_axilite port=self                      bundle = Din
	#pragma HLS INTERFACE s_axilite port=referenceValue            bundle = Din
	#pragma HLS INTERFACE s_axilite port=actualValue               bundle = Din
	#pragma HLS INTERFACE s_axilite port=ext_clamping              bundle = Din
	#pragma HLS INTERFACE s_axilite port=I_rst                     bundle = Din
	#pragma HLS INTERFACE s_axilite port=return                    bundle = Din

Implementation
^^^^^^^^^^^^^^

The algorithm starts by reading all the inputs and calculates the error with the formula ``error = referenceValue - actualValue``. ``I_Sum`` is the integral parameter and preserves its value after every calculation through the ``static`` identifier.
``output_before_saturation`` is calculated with the PI formula mentioned in - "PI-Controller documentation". The necessity of clamping is decided with the values of both ``internal_clamping and ext_clamping``. Then the saturated result is stored in the variable ``output``.
The calculation is reseted with the ``I_rst``.

.. code-block:: c
   :linenos:
   :caption: PI-controller sample code

   bool internal_clamping = false;
	static float I_sum;
	float error = referenceValue - actualValue;
	float old_I_sum = I_sum;
	float preIntegrator = error * self->Ki;
	float P_sum = error * self->Kp;
	float output_before_saturation = old_I_sum + P_sum;
	internal_clamping = uz_PI_Controller_Clamping_Circuit(preIntegrator, output_before_saturation, self->upper_limit, self->lower_limit);
	bool clamping_active  = (ext_clamping == true) || (internal_clamping == true); // clamping is active if internal clamping or external clamping is true
	if ( clamping_active ) {
		I_sum += 0.0f;
	} else {
		I_sum += preIntegrator * self->samplingTime_sec;
	}

	*output = uz_signals_saturation(output_before_saturation, self->upper_limit, self->lower_limit);

	if(I_rst){
		I_sum = 0.0f;
	    internal_clamping = false;
	}

Vitis HLS design flow
----------------------
1. Open Vitis HLS.
2. Create new project.
    
.. _new_project:
.. figure:: ./new_project.png
   :width: 400
   :align: center

   New Project.

3. Add the files provided in the git. 
 
.. _files:
.. figure:: ./files.png
   :width: 400
   :align: center  

   Adding Git files

4. Set ``uz_piController_sample`` as the top function and click next.

.. _top_function:

.. figure:: ./top_function.png
   :width: 400
   :align: center

   Setting Top function.

.. _top:

.. figure:: ./top.png
   :width: 400
   :align: center

   uz_piController_sample is the Top function

5.Add the simulation file and click next.

.. _tb:

.. figure:: ./tb.png
   :width: 400
   :align: center

   Adding tb file.

6. Set board parameters and click Finish.

.. _board:

.. figure:: ./board.png
   :width: 400
   :align: center

   Setting the board parameters.


An alternate way to steps 1-6 is mentioned below
      - open the Vitis HLS Command Prompt
      - Vitis command promt will be available in the path "..\Programs\Xilinx Design Tools\Vitis 2020.1\Vitis HLS 2020.1 Command Prompt.lnk"
      - cd into project folder
      - run
      - vitis_hls -f script.tcl
      - vitis_hls -p PI_Controller
This will create the project PI_Controller with all the necessary information from the ``.tcl`` script. Then add the files from the git through Right click on source and then selecting "Add files".

7. New project is created with the required files.

.. _project:

.. figure:: ./project.png
   :width: 700
   :align: center

   New project

8. Verify the source code with C simulation by clicking on CSim button(white) and click Ok.

.. _task_bar:

.. figure:: ./task_bar.png
   :width: 800
   :align: center

   Task bar

.. _csim:

.. figure:: ./csim.png
   :width: 800
   :align: center

   Simulation Results.


9. Run high-level synthesis(Green) and generate RTL files(Yellow).

.. _export_RTL:

.. figure:: ./export_RTL.png
   :width: 400
   :align: center

   Export RTL.

10. This will create the Ip files. 

.. _pi_controller_block:

.. figure:: ./pi_controller_block.png
   :width: 400
   :align: center

   PI Controller IP Module.

Vivado Design for UltraZohm
---------------------------
1. Open ``..\ultrazohm\ultrazohm_sw\vivado\project\ultrazohm.xpr``.
2. Open block design.
3. Add uz_piController module by right clicking on the window and selection ``Add IP``.

.. _add_ip:

.. figure:: ./add_ip.png
   :width: 200
   :align: center

   Add IP

4. Double click on AXI Smart connect and increase the number of master interfaces by two since PI_controller has two slave interfaces.
5. Double click on Zynq processor and enable ``AXI HPC0 FPD`` under slave interfaces in PS-PL configurations tab. This will be connected to the master interface of our module.

.. _zynq:

.. figure:: ./zynq.png
   :width: 600
   :align: center

   Master and Slave interfaces of Zynq Processor

6. Run Connection automation and select all the interfaces of the IP module. 

.. _connection_automation:

.. figure:: ./connection_automation.png
   :width: 600
   :align: center

   Connection automation

7. Generate bitstream. Then click on Export → Export Hardware in the File menu.
8. This will create a ``.XSA`` file including bitstream information.

.. _Block_diagram_Overview:

.. figure:: ./block_diagram.png
   :width: 800
   :align: center

   Block Diagram of PI Controller.

.. note:: Having an ILA is optional.

.. note:: Fig.94 is the subset of the ultrazohm block diagram included to give an overall idea and not the original one.

Vitis IDE
----------

Vitis tool provides a framework for developing and delivering FPGA accelerated applications using standard programming languages for both software and hardware components. The software component, or host program, is developed using C/C++ to run on a CPU with XRT API calls to manage runtime interactions with the accelerator. 

Description:
^^^^^^^^^^^^

The ``xuz_pi_controller_sample.h`` gives access to the xuz_pi_controller_sample drivers, which are used to provide a standard API for controlling AXI peripherals. 
Several functions from this API are used in the example, including set input values and output address like ``XUz_pi_controller_sample_Set_self, XUz_pi_controller_sample_Set_output_r`` e.t.c.

First, Global value for HLS Ip is defined and its initialized with device status through the function ``init_pi_controller()``.
A pointer variable ``result`` is declared and is pointed to the desired memory location of DDR Memory ``float *result = (float*)mem;``. 
First, We initialize the array value to zero. We then set the output_r to the address location ``mem``. Then we call the ``XUz_pi_controller_sample_Start`` and we wait till the operation is done.
Finally, we compare the value with desired results and print the status and outputs.


.. code-block:: c
  :linenos:
  :caption: Assigning the inputs through a function and specifying the output to store in desired memory location through SET function. 

      void pi_controller_hls(float referenceValue, float actualValue) {
      // Write inputs
      XUz_pi_controller_sample_Set_referenceValue(&pi, *((u32*)&referenceValue));
      XUz_pi_controller_sample_Set_actualValue(&pi, *((u32*)&actualValue));

      // Start HLS IP
      XUz_pi_controller_sample_Start(&pi);
      //print("Started HLS pi controller IP \n");

      // Wait until it is finished
      while (!XUz_pi_controller_sample_IsDone(&pi))
         ;
      }

Procedure:
^^^^^^^^^^
1. Create a new Application Project.
2. Open the Create a new platform… tab. Browse your XSA file and click Open.
3. Specify Application Project name and click Next.
4. Select Hello World template and click Finish.
5. In Vitis' Explorer pane, find the application projects “src” directory. Right click on it and select ``New → File``.
6. Specify the name ``uz_pi_controller.h``.
7. Copy the contents from git to the file.
8. Replace the contents of ``helloworld.c`` with the helloworld file provided in git.
9. Build Program to check for syntax error.
10. Connect the board and Run the program. 
11. The results can be seen through UART in the Vitis serial Terminal
12. The memory location can be monitored through memory icon in the right pane of the Debug Window. The active processor should be selected to enable the memory icon.

.. _vitis:

.. figure:: ./vitis.png
   :width: 500
   :align: center

   Vitis memory monitor and serial terminal displays the output

Issues Faced
------------
   - Drivers created while importing the IP in Vitis HLS fails in Vitis IDE. 
      This issue might be faced during the execution of the Vitis IDE code with the bitstream file generated from the block design involving an HLS IP. This issue is related to the Makefile used in the driver output directory of HLS IP and is addressed in the future releases of Vivado. The issue is resolved by modifying the makefile as mentioned in (4).

      .. code-block:: c
         :linenos:
         :caption: Compiler error message

         fatal error: xbasic_types.h: No such file or directory

   - Cache lines has to be invalidated before writing the value into the memory.
      The value written in a memory location might not be reflected untill and unless the cache lines are invalidated. This problem can be faced when one tries to write values in the memory of a processor. Invalidation of a cache or cache line means to clear it of data. This is done by clearing the valid bit of one or more cache lines. The cache must always be invalidated after reset as its contents will be undefined.
      Cleaning a cache or cache line means writing the contents of dirty cache lines out to main memory and clearing the dirty bits in the cache line. This makes the contents of the cache line and main memory are coherent with each other. 
      This is done using the command ``Xil_DCacheFlushRange(mem, (sizeof(mem)*no_elements));`` in our code.
More Information
----------------

1. https://docs.xilinx.com/v/u/2020.1-English/ug1399-vitis-hls
2. https://docs.xilinx.com/v/u/2020.1-English/ug1400-vitis-embedded
3. https://docs.xilinx.com/v/u/en-US/xapp599-floating-point-vivado-hls
4. https://support.xilinx.com/s/article/75527?language=en_US


..	toctree::
		:maxdepth: 2
		:hidden:
		:caption: Vitis HLS (HDL)

		definitions
