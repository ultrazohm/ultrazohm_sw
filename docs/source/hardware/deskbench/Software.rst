.. _deskbench_software:

==========
Software 
==========

Following, the step-by-step setup of the software implementation is shown, to successfully commission the deskbench.

1. Make sure you complete the whole :ref:`getting_started` section, to guarantee you can flash the UZ and connect to the :ref:`JavaScope`.

2. :ref:`clone` and checkout the feature-branch feature/ZC/Deskbench.

::

   git clone https://bitbucket.org/ultrazohm/ultrazohm_sw.git
   git checkout feature/ZC/Deskbench

3. Open vitis and create the workspace, see :ref:`genvitis`.

4. Power up UZ, set the power supply to 48V and a 5A current limit and try to debug the UZ and get a connection to the :ref:`JavaScope` GUI.

.. image:: Deskbench/connected_1.png
  :height: 500
  :align: center

5. Press ``Enable System`` and ``Enable Control``, set a reference speed for the left motor ,e.g. 500 rpm, in the respective input field of the GUI and press ``set``. Now the load machine should spin at 500 rpm.

.. image:: Deskbench/connected_2.png
  :height: 500
  :align: center

6. Set a q-current reference, e.g. 4A, in the respective input field of the GUI and press ``set``. Now the phase currents, dq-currents and the torque (should be around 1 Nm) are visible in the scope.
For better visibility, the currents have an offset of +-5A. 

.. image:: Deskbench/connected_3.png
  :height: 500
  :align: center

Now everything is properly setup and the deskbench the user can extend functionality with own algorithms or simply investigate the performance of the implemented control algorithm.

Control structure
==================

The control structure in software is organized into three components. Two static functions in ``isr.c`` handle the control of the left and right motors. The third component is responsible for reading and converting measurement data, such as phase currents. 
Initialization of controller parameters is managed in ``pi_foc_init.c``. 
Additionally, controller adjustments can be made in real-time during operation using the Javascope GUI within the ``MoreSendAndReceive`` section.

.. image:: Deskbench/controller_adjustment.png
  :height: 500
  :align: center

