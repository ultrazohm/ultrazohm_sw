.. _deskbench_asm:

==========
Assembly
==========

Below, the assembly instructions for the setting up the connection between UZ and the Deskbench are explained in detail.

1. Setup the UltraZohm, the power supply and the deskbench for your needs.

.. image:: Deskbench/1st_step.jpg
  :height: 350
  :align: center

2. Connect the two Inverters to the ADC Cards.

.. csv-table:: Mapping of the RJ45 Connection for the deskbench
    :file: Deskbench/connection_inverter.csv
    :widths: 2 2 
    :header-rows: 1
    :align: center

.. image:: Deskbench/2nd_step.jpg
  :height: 350
  :align: center

3. Connect  DC+ and DC- to both inverters on D1 and D2 with lab cables. Ensure that the current carrying capability of the cables is sufficient!

.. image:: Deskbench/3rd_step.jpg
  :height: 350
  :align: center

4. Connect Phase A-C of both inverters to the Deskbench terminal boxes. Ensure that the current carrying capability of the cables is sufficient!

.. image:: Deskbench/4th_step.jpg
  :height: 350
  :align: center

5. Connect the two Resolver to the Ultrazohm with the D-SUB 9 Cables. Ensure that the cable is a "straight through" cable with one to one connection of the pins!

.. image:: Deskbench/5th_step.jpg
  :height: 350
  :align: center


.. csv-table:: Mapping Motor to the UZ
    :file: Deskbench/motor_inverter_mapping.csv
    :widths: 2 2 
    :header-rows: 1
    :align: center

6. Connect the ``OUT to ADC`` connector from the :ref:`torque_box` to A1 A with a RJ45 cable. 
Connect the ``Supply IN`` connector of the box with the ADC A1 supply connector, using the delivered Samtec cable ``MMSD-08-28-F-xx.xx-D-K-LDX``.
Connect the torque sensor D-SUB 15 cable with the :ref:`torque_box` ``IN Torque Sensor connector``.

.. image:: Deskbench/6th_step.jpg
  :height: 350
  :align: center

7. Connect the torque sensor cable with the torque sensor of the deskbench.

.. image:: Deskbench/7th_step.jpg
  :height: 350
  :align: center

8. Make sure that the deskbench is proper grounded. There is a fastener for the connection to ground in the top left-hand corner.

.. image:: Deskbench/grounding_desk.jpg
  :height: 350
  :align: center

9. Connect the UltraZohm to your host computer.

The physical and electrical connections have been successfully completed. 
The next step is to setup the :ref:`deskbench_software` implementation.