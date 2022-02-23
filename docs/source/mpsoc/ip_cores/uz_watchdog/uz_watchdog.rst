.. _uz_watchdog:

===============
Watch Dog Timer
===============

The main goal of the Watch Dog Timer (WDT) is to detect real-time violations, e.g. if the control routine on the R5 takes longer than the available control period. 
In this case an interrupt is thrown that can be handled in the PS and PL. Component based on the Xilinx AXI Watchdog Timer (WDT) IP-core [#PG128]_:

- 32-bit slave device on a AXI4-Lite interface
- Window watchdog feature with programmable open and close windows
- Additional features for better controllability such as Second Sequence Timer and Fail Counter


Introduction
============

The Xilinx IP-core `AXI Timebase Watchdog Timer <https://www.xilinx.com/products/intellectual-property/axi_timebase_wdt.html>`_ [#PG128]_ forms the bases of this module.
The IP offers two morking modes [#PG128]_:

- The **Timebase WDT** working mode implements an incremental counter which after one expiration of the timeout interval, an interrupt is generated. However, it does not offer a resolution in the order of microseconds that is needed.
- The **Window WDT** working mode is the chosen one. It offers extended functionality and the required resolution of the window length. 

.. _XWDTTB_ModuleOverview:

.. figure:: ./uz_watchdog_module_components.png
   :width: 609
   :align: center

   Top view of the Module.

Window working mode
*******************

The Window Watchdog Timer (WWDT) starts with an adjustable period called **close window**, followed by another period called **open window**.
The WWDT has to be restarted within the **open window**. 
If the WWDT is restarted outside of the open window time period, it generates a reset.

.. figure:: ./uz_watchdog_windows.png
   :width: 510
   :align: center

Integration in Baremetal project
================================

- **Inside the int Initialize_ISR()** function we have to invoke the initialization of the IP XWdtTb \*uz_watchdog_init() setting the timer to the default timeout and default configuration as it is explained in the API section (see below).
- **Inside the int Rpu_GicInit()**  function we have to make the following changes to integrate the device:
    1.	We have to change the priority of the system timer. In order to allow the interrupt preemption, meaning that the ISR_Control() function than handles the timing interruption can be interrupted itself, we have to modify these lines:
	
    -     XScuGic_GetPriorityTriggerType(IntcInstPtr,Interrupt_ISR_ID,&prio,&trigger);
    -     prio = 15;
    -     trigger = 0b11;
    -     XScuGic_SetPriorityTriggerType(IntcInstPtr,Interrupt_ISR_ID,prio,trigger);



    2.	We have to initialize the interruption of the watchdog using a new private function added to the isr.c file: 
	
    - int WdtTbSetupIntrSystem(XScuGic_Config \*IntcConfig, XScuGic \*IntcInstancePtr). This function sets the INT Output signal through the GIC System. The GIC has to be previously set, using its functions (XScuGic_LookupConfig(), XScuGic_CfgInitialize() and Xil_Exception*() functions to initialize, register and enable the Interruption system. It is already done in the Initialize_ISR() and Rpu_GicInit() functions. A default handler is provided in our driver uz_watchdog.h. It counts the error and resumes normal execution. It should use the future uz_error_handler module to set the error and handle it properly



    3.	We have to enable the WDT and launch first kick with:

    - uz_watchdog_Start(WdtTbInstancePtr);
	
- And finally, **inside the ISR_Control()** function, we have to:
    1.	Enable the preemption or the interruption nesting invoking

    - Xil_EnableNestedInterrupts(); 


    2.	Restart the WD Timer, to assure the time violation does not happen. It is done by calling the function:


    - uz_watchdog_Restart(WdtTbInstancePtr);


Register Description
====================

A brief summary of the most important registers are given below. 

Function Control Register (FCR)
*******************************

The ``FCR`` (Function Control Register) defines the interruption assertion point in time in the second window, at which an interrupt is triggered. 
This choice is made by a combination of  the ``SBC`` (Select Byte Count) and the ``BSS`` (Byte Segement Selection of Second Window Count).  
An illustrative example is given in the next section. 

.. _XWDTTB_FunctionControlRegister:

.. figure:: ./uz_watchdog_FunctionControlRegister.png
   :width: 634
   :align: center

   Function Control Register (FCR) fields to set INT point.

First Window Count Register (FWR)
*********************************
This field provides the count value for the first window.
FW Counter is a down counter and it starts from the programmed FWR value and ends at 0.
First window continue. When completed, it is followed by the second window.
This field can be set as 0. In this case, it achieves “close” window absent case.

Second Window Count Register (SWR)
**********************************
This register provides the count value for the second window.
SW Counter is a down counter and it starts with the programmed SWR value and ends at 0.
``SW[31:0]`` is used to place the interrupt assertion with the help of ``BSS[1:0]`` and ``SBC[7:0]``. (See the ``FCR`` Register above)
Any good or bad event ends the second window. Absence of a good or bad event allows the second window timeout. This is considered a bad event.

.. _XWDTTB_SecondWindowConstants:

.. figure:: ./uz_watchdog_SecondWindowConstants.png
   :width: 586
   :align: center

   Second Window Constants in uz_watchdog.h file to set INT point.

So we split the second window in two parts (as can be seen in the next picture):

- A: 0x2710 = 10,000 clock ticks => 100 microsec.
- B: 0xFF00 = 65,280 clock ticks more than 650 microsec. to execute the handler function (enough time to resume execution or to save working state).

.. _XWDTTB_SecondWindowTimingDiagram:

.. figure:: ./uz_watchdog_SecondWindowTimingDiagram.png
   :width: 510
   :align: center

   Second Window Timing Diagram.

Instead of using a fixed amount of clock ticks for the second window (as can be seen with the previous constant). We have added in the last version two more constants that define the window size as a function of the UZ_PWM_FREQUENCY and Interrupt_ISR_freq_factor).

.. _XWDTTB_SecondWindowConstants_v2:

.. figure:: ./uz_watchdog_SecondWindowConstants2.png
   :width: 586
   :align: center

   Second Window Constants upgraded in uz_watchdog.h file to set INT point.

Driver function reference
=========================

.. doxygentypedef:: uz_watchdog_ip_t

.. doxygenstruct:: uz_watchdog_ip_config_t
  :members:

.. doxygenfunction:: uz_watchdog_ip_start

.. doxygenfunction:: uz_watchdog_ip_restart

.. doxygenfunction:: uz_watchdog_ip_init

.. doxygenfunction:: uz_watchdog_IntrHandler


Additional information
======================

The lack of precision of the System Watchdog Timer leads as to use the IP provided by Xilinx.  For more information about the System WDT (option discarded) see the Zynq UltraScale+: technical reference manual [#UG1085]_, chapter 14, page 361.

Sources
=======

.. [#UG1085] `Zynq UltraScale+ Device TRM, UG1085 (v2.2) December 4, 2020 <https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf>`_
.. [#PG128] `AXI Timebase Watchdog Timer v3.0, Vivado Design Suite, PG128 October 4, 2017 <https://www.xilinx.com/support/documentation/ip_documentation/axi_timebase_wdt/v3_0/pg128-axi-timebase-wdt.pdf>`_