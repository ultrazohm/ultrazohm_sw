====
CPLD 
====

The Carrier Board has one CPLD for each digital interface slot (D1-D5).
They are used to shift the voltage level from 1.8V (FPGA) to 3.3V (Adapter Cards) .
Additional safety can be implemented, e.g. checking switch combinations or ensuring deadtime.

*******************************************
ispMACH series (uz_carrier Rev4 and before)
*******************************************

UltraZohms until ``Rev4`` are equiped with CPLDs of the ispMACH series (LA4128V or LC4256V).



***********************************
MachXO2 (uz_carrier Rev5 and later)
***********************************

UltraZohms with carrier board ``Rev5`` and later are equiped with CPLDs of MachXO2 series (LCMXO2-2000HC-4TG100C).


..	toctree::
    lattice_toolchain
    cpld_create_program
    cpld_programming
 