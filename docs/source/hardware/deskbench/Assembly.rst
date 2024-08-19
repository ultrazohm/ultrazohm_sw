.. _deskbench_asm:

==========
Assembly
==========

In this example the assembly instructions for the setting up the connection between UZ and the Deskbench are explained in detail.

1. Setup the UltraZohm, the power Supply and the deskbench for your needs.

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

3. Connect  DC+ and DC- to both inverters on D1 and D2 with lab cables.

.. image:: Deskbench/3rd_step.jpg
  :height: 350
  :align: center

4. Connect Phase A-C of both inverters to the Deskbench.

.. image:: Deskbench/4th_step.jpg
  :height: 350
  :align: center

5. Connect the two Resolver to the Ultrazohm with the D-SUB 9 Cables.

.. image:: Deskbench/5th_step.jpg
  :height: 350
  :align: center


.. csv-table:: Mapping Motor to the UZ
    :file: Deskbench/motor_inverter_mapping.csv
    :widths: 2 2 
    :header-rows: 1
    :align: center

6. Connect the OUT Slot from the external uz_per_toque_box to A1 A. 
Connect the power supply with the delivered Samtec cable with the Box with the ADC A1 Slot.
Connect the torque sensor  D-SUB 15 cable with the UZ_per_toque_box.

.. image:: Deskbench/6th_step.jpg
  :height: 350
  :align: center

7. Connect the torque sensor Cable with the torque sensor of the deskbench.

.. image:: Deskbench/7th_step.jpg
  :height: 350
  :align: center

8. Connect the UltraZohm to the Computer u are using.

The physical and electrical connections have been successfully completed. 
The next step is to begin with the :ref:`deskbench_software` implementation.