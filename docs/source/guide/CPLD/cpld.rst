====
CPLD 
====

The Carrier Board has one CPLD for each digital interface slot (D1-D5).
They are used to shift the voltage level from 1.8V (FPGA) to 3.3V (Adapter Cards) .
Additional safety can be implemented, e.g. checking switch combinations or ensuring deadtime.

*******************************************
ispMACH series (uz_carrier Rev4 and before)
*******************************************

UltraZohms until ``Rev4`` are equipped with CPLDs of the ispMACH series (LA4128V or LC4256V).



***********************************
MachXO2 (uz_carrier Rev5 and later)
***********************************

UltraZohms with carrier board ``Rev5`` and later are equipped with CPLDs of MachXO2 series. The D-Slots employ the type ``LCMXO2-2000HC-4TG100C``, 
whereas the S3C CPLD for overall system control is of type ``LCMXO2-4000HC-4TG144C``. Creating a program for a D-Slot CPLD in the :ref:`label_diamond_create_program` section.


..	toctree::
    lattice_toolchain
    cpld_create_program
    diamond_create_program
    cpld_programming
 