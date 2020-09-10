==============================
First steps with the UltraZohm
==============================

Aim of the tutorial
*******************

In this tutorial, the :ref:`GUI` (Javascope) is used to visualize the life check variable of the R5 of the UltraZohm. Furthermore, a sine wave calculation is added to the interrupt service routine (isr.c) of the R5. The Javascope is used to visualize the sine wave.

After this tutorial, you can:

- Make changes to the PS of the system
- Build the Vitis project to incorporate the changes
- Transfer the bitstream & software to the UltraZohm
- Start a debug session
- Use the Javascope to visualize variables of the R5

Requirements
************

The following tutorial requires:

- Complete Xilinx Toolchain (Vivado, Vitis) installation
- git installation
- Java installation
- Cloned all UltraZohm repositories from Bitbucket
- UltraZohm connected to your PC by Ethernet and USB (JTAG)


UltraZohm Setup
***************

The UltraZohm has to be connected to a PC by Ethernet and USB (JTAG-Programmer).

.. image:: ./img/physical_setup.jpg

Visualize the life check
************************

The ISR's life check variable (f_ISRLifeCheck) is written to the Javascope struct ``js_ptr_arr`` to display it in the Javascope GUI. The following line achieves this.

.. code-block:: c

    js_ptr_arr[JSO_Sawtooth1] = &f_ISRLifeCheck;

Next, program the UltraZohm and start the debug session (debug-icon).
Start all PS-cores and add ``f_ISRLifeCheck`` to the expressions. Click on refresh (green rectangle in the picture below) to refresh the current values of the expressions. 

.. image:: ./img/1_after_build.png

Start the Javscope, connect it to the UltraZohm, click on ``Run/Stop`` to start the Javascope, and choose ``Sawtooth1`` for channel 1. You might have to change the scale (``setScale CH1``).

.. image:: ./img/3_javascope_lifecheck_sawtooth.png


Visualize sine wave
*******************

The next step is to add a sine wave and display it on the Javascope. In the ``isr.c`` of the R5 already exists the variable ``test_js_sinewave1``, which we can use. Furthermore, a software counter ``i_count_1ms`` is available in the ``isr.c``. We add the following code:

.. code-block:: c

   test_js_sinewave1=10.0 * sin( PI2 * 1.00 * (i_count_1ms*0.001) );
   js_ptr_arr[JSO_SineWave1]=&test_js_sinewave1;


Build the code, if there are problems with the math.h, refer to :ref:`math_h_prob`.
Next, start a debug session, start the UltraZohm and the Javascope. You should see the SineWave if the channel ``SineWave1`` is selected.

.. image:: ./img/7_sine_wave.png