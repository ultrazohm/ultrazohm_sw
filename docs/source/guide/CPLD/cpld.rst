====
CPLD 
====

The Carrier Board has one CPLD for each digital interface slot (D1-D5).
They are used to shift the voltage level from 1.8V (FPGA) to 3.3V (Adapter Cards) .
Additional safety can be implemented, e.g. checking switch combinations or ensuring deadtime.

..	toctree::
    
    cpld_programming
    lattice_toolchain

*****************************************************
ispMACH series (:ref:`carrier_board_rev4` and before)
*****************************************************

UltraZohms :math:`\leq` ``Rev04`` are equipped with CPLDs of the ispMACH series (LA4128V or LC4256V).

..	toctree::
    cpld_create_program

**********************************************
MachXO2 (:ref:`carrier_board_rev5` and later)
**********************************************

UltraZohms :math:`\geq` ``Rev05`` and later are equipped with CPLDs of MachXO2 series. The D-Slots employ the type ``LCMXO2-2000HC-4TG100C``, 
whereas the S3C CPLD for overall system control is of type ``LCMXO2-4000HC-4TG144C``. Creating a new program for these CPLDs is described in the :ref:`label_diamond_create_program` section.

..	toctree::
    diamond_create_program
 