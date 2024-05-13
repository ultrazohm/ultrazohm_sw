========================
Overview of the ARM Pins
========================

In the following table you will find an overview of the pin mapping of the SoC MIO pins (fixed pins of the SoC's Processing System).
All connector-accessible MIO pins -- i.e., those having an X... assignment in column **CB-Pin** -- are labeled with the associated net label/name (of the carrier board) in the fifth column and the connector pin in the **CB-Pin** column (CB --> Carrier Board).
The connectivity between MIO pins and the frontpanel I/Os -- four user LEDs and three buttons -- is shown by column **FP_**.

.. csv-table:: Overview of the MIO Pins
  :file: interfaces/MIO_Pinout.csv
  :widths: 5 8 8 5 10 5 5
  :header-rows: 1


Pin capabilities
----------------

For detailed information, see the `Xilinx Technical Reference Manual of the Zynq UltraScale+ aka UG1085 <https://docs.amd.com/r/en-US/ug1085-zynq-ultrascale-trm/Multiplexed-I/O>`_ (i.e., chapter *Multiplexed I/O* and table *MIO Interfaces*).
