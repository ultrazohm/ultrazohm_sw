.. _deskbench_software:

==========
Software 
==========

In this example the step-by-step Software implementation is shown, to successfully commission the deskbench.

1. Make sure you complete the whole :ref:`getting_started` section, to guarantee you can flash the UZ and connect to the :ref:`JavaScope`.

2. :ref:`clone` and checkout the feature-branch feature/ZC/Deskbench.

::

   git clone https://bitbucket.org/ultrazohm/ultrazohm_sw.git
   git checkout feature/ZC/Deskbench

3. Open vitis and create the workspace, see :ref:`genvitis`.

4. Power up UZ, set up power supply to 48V and try to debug the UZ and get a connection to the :ref:`JavaScope` GUI.

.. image:: Deskbench/connected_1.png
  :height: 500
  :align: center

5. Send a speed e.g. 500 rpm with the GUI to the UZ and now after Enable System and Enable Control the load machine should turn with 500rpm.

.. image:: Deskbench/connected_2.png
  :height: 500
  :align: center

6. Set up a current, e.g. 4A with the GUI and check the phase currents and the torque (should be around 1 Nm).
The currents have an offset of +-5A for better visibility, 

.. image:: Deskbench/connected_3.png
  :height: 500
  :align: center

Now everything is properly setup and the deskbench can be extended with various algorithms.

Control structure
==================

The control structure is organized into three components. Two static functions in ``isr.c`` handle the control of the left and right motors. The third component is responsible for reading and converting measurement data, such as phase currents. 
Initialization is managed in the external file  ``pi_foc_init.c``, where the controller settings can also be configured. 
Additionally, controller adjustments can be made in real-time during operation using the Javascope GUI within the ``MoreSendAndReceive`` section.

.. image:: Deskbench/controller_adjustment.png
  :height: 500
  :align: center

