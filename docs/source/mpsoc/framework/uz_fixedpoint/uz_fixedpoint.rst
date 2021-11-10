.. uz_fixedpoint:

===================
Fixed point library
===================

The fixed point library provides a container for fixed point values to ease the handling of them.
It is aimed to provide a clean way to interact with IP-Cores that use fixed-point data representation.
The library is only intended to be used in the lowest software layer of IP-Core drivers to read/write to and from the PL (i.e., functions that are named with ``_hw``).
The read and write functions check against boundaries of the fixed point data type - the data itself is always a unsigned 32 bit integer internally (not exposed to the user).


- Data is stored as unsigned int with 32 bit
- Data is divided into fractional and integer bits
- The first n-bits are the fractional bits depending on the representation
- The following m-bits are the integer bits depending on the representation
- The MSB is used for the sign

Example: A signed fixed point value with four fractional bits and five integer bits is represented as shown in :numref:`fixedpoint_bitmap`.
The MSB determines the signedness, the bits *between* the MSB and the integer bits are unused.

.. _fixedpoint_bitmap:

.. figure:: fixedpoint_registermap.drawio.svg

  Binary representation of fixed point values in memory.

.. note:: This is not intended to do fixed point math on the processor!

Reference
=========

.. doxygenstruct:: uz_fixedpoint_definition_t
  :members:

.. doxygenfunction:: uz_fixedpoint_axi_read

.. doxygenfunction:: uz_fixedpoint_axi_write

.. doxygenfunction:: uz_fixedpoint_check_limits

.. doxygenfunction:: uz_fixedpoint_get_precision

.. doxygenfunction:: uz_fixedpoint_get_max_representable_value

.. doxygenfunction:: uz_fixedpoint_get_min_representable_value


Resources
=========

- https://github.com/PetteriAimonen/libfixmath
- https://en.wikipedia.org/wiki/Q_(number_format)
- https://github.com/jcarrano/fixed_point_arith
- https://en.wikipedia.org/wiki/Fixed-point_arithmetic
- https://de.mathworks.com/help/dsp/ug/concepts-and-terminology.html