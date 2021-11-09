.. uz_fixedpoint:

===================
Fixed point library
===================

The fixed point library provides a container for fixed point values to ease the handling of them.
It is aimed to provide a clean way to interact with IP-Cores that use fixed-point data representation.
Intended use is in the lowest software layer of IP-Core drivers to read/write to and from the PL (i.e., functions that are named with ``_hw``).
The fixed point library only provides a way to convert to and from floating-pint, interpret the data, and check against boundraries - the data itself is always a unsigned 32 bit integer.

- Data is stored as unsigned int with 32 bit
- Data is divided into fractional and integer bits
- The first n-bits are the fractional bits depending on the representation
- The following m-bits are the integer bits depending on the representation
- The MSB is used for the sign

Example:

A signed fixed point value with four fractional bits and five integer bits is represented as shown in :numref:`fixedpoint_bitmap`.
The MSB determines the signedness, the bits *between*`the MSB and the integer bits are unused.

.. _fixedpoint_bitmap:

.. figure:: fixedpoint_registermap.drawio.svg

  Binary representation of fixed point values in memory.