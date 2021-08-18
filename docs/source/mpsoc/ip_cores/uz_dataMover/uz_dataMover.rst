.. _uz_dataMover:

====================
Data Mover / AXI2TCM
====================

- Moves data from PL to R5 (R5_0) by writing data directly to the BTCM
- Data mover is intended for use with R5 in split mode
- PL IP-Cores can write to TCM by AXI
- Fast possibility to move data from PL to R5
- Used to read ADC values

Tightly Coupled Memory (TCM)
============================

- `See TRM for TCM information <https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf#G6.381281>`_
- Split mode: ATCM and BTCM with 64 KB each (split mode is used in the UltraZohm project).
- ATCM: holds interrupts and exception code (``.vectors`` section in linker script)
- BTCM: used for data processing
- There is no protection to stop the Cortex-R5F processor from accessing the TCM [#UG1085]_,p. 97

.. table:: `Address map of TCM for R5_0 <https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf#G6.381365>`_

   ================= =========== ==============
   -                 R5_0 View   Global Address
   ================= =========== ==============
   R5_0 ATCM (64 KB) 0x0000_0000 0xFFE0_0000
   R5_0 BTCM (64 KB) 0x0002_0000 0xFFE2_0000
   ================= =========== ==============

- The R5_0 view is used by the software of the R5
- The global address is used in Vivado
- ATCM (64 KB) starts at address 0x0000_0000 and ends at 0x0000_FFFF for usage in software
- BTCM (64 KB) starts at address 0x0002_0000 and ends at 0x0002_FFFF for usage in software
- Note that ATCM for R_0 starts at 0x000_0000 to 0x0000_FFFF, then there is a 64 KB gap (`see figure in TRM <https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf#G6.381515>`_).

IP-Core
=======

The data mover uses the AXI2TCM IP-Core.

.. table:: Settings of IP-Core

   ========================== =========== =========================================
   Name                       Default     Description
   ========================== =========== =========================================
   Number of 16 bit blocks    24          -
   AXI TARGET SLAVE BASE ADDR 0xFFE20000  Address to which the IP-Core writes data.
   AXI ID WIDTH               1           -
   AXI ADDR WIDTH             32          -
   ========================== =========== =========================================

.. _dataMover_vivado_picture:

   .. figure:: data_mover.png
      :width: 800
      :align: center
   
      Data mover in Vivado.


Software driver
===============

- Software driver does not need to be initialized
- Two possibilities to read data from the data mover:

    - Directly access the data in the BTCM
    - Read the data from the BTCM into a buffer and access the buffered data

- If data access without buffer is used, the data can change without any action from the processor 
- Software driver uses the :ref:`uz_array` data type

Reference
=========

.. doxygenfunction:: uz_dataMover_get_data_by_pointer

.. doxygenfunction:: uz_dataMover_update_buffer_and_get_data

.. doxygenfunction:: uz_dataMover_update_buffer

.. doxygenfunction:: uz_dataMover_get_data_from_buffer


Sources
-------

.. [#UG1085] `Zynq UltraScale+ Device TRM, UG1085 (v2.2) December 4, 2020 <https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf>`_