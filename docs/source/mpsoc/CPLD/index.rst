====
CPLD 
====

The Carrier Board has one CPLD for each digital interface slot (D1-D5).
They are used to shift the voltage level from 1.8V (FPGA) to 3.3V (Adapter Cards) .
Additional safety can be implemented, e.g. checking switch combinations or ensuring deadtime.



..	toctree::
    lattice_toolchain
    cpld_create_program
    cpld_programming
 