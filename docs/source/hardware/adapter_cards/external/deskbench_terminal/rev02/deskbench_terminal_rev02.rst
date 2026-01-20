.. _deskbench_terminal_rev02:

============================
Deskbench terminal PCB Rev02
============================
      

.. figure:: Terminal_PCB_rev02.jpg
   :width: 60%

   uz_per_deskbench_terminal PCB Rev02 in housing

Source
******

- `uz_per_deskbench_terminal PCB repository <https://bitbucket.org/ultrazohm/uz_per_deskbench_terminal/>`_

Variants
*********

The PCB is available in two variants: one with an optional motor-brake connection and one without it.
Currently, only the version without the brake connection is in use.

In the Rev02 variant, the clearance distances between the copper areas of phases A, B, and C have been increased to support a DC-link voltage of up to 300 V.
Furthermore, two 0-Ω resistors are used to bridge specific pin pairs on the D-Sub connector, ensuring compatibility with the different pin assignments of both the :ref:`dig_resolver_rev01` and the uz_d_abs_encoder.
By default, these resistors are populated.

.. _deskbench_terminal_function_rev02:

.. figure:: Terminal_PCB_functional.jpg
   :width: 60%

   Functional areas of the uz_per_deskbench_terminal PCB rev02


Layout
------

The PCB is structured by functional areas as shown in :ref:`deskbench_terminal_function_rev02` above.

1. Terminal Connector for resolver or absolute encoder
2. Terminal Connector for motor
3. Output DSUB to UZ with :ref:`dig_resolver_rev01`
4. Lab socket to inverter :ref:`dig_si_inverter_rev03`


.. csv-table:: Mapping Absolute Encoder/Resolver to Terminal
   :file: resolver_mapping.csv
   :widths: 5 5 5
   :header-rows: 1
   :align: center

.. csv-table:: Mapping Motor to Terminal
   :file: motor_mapping.csv
   :widths: 5 5 5
   :header-rows: 1
   :align: center

Downloads
*********

:download:`Schematics Rev02 <SCH_UZ_PER_deskbench_terminal_Differential_Input_Rev02b.pdf>`


Designer
********

Designed by Dennis Hufnagel(TH Nürnberg), 04/2023
