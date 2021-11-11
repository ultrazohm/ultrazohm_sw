.. uz_fixedpoint:

===================
Fixed point library
===================

Fixed point data types store fractional numbers as integer values with a fixed number of bits used for the integer part of the value and a fixed number of bits used for the fractional part.
The fixed point data type have a arbitrary number of total bits and are distinguished between signed and unsigned data.
For signed data, the MSB indicates the sign of the value.
A signed fixed point data with :math:`N` integer bits can represent all integers from :math:`-(2^{(N-1)})` to :math:`2^{(N-1)} -1`.


The fixed point data type uses `two's complement <https://en.wikipedia.org/wiki/Two%27s_complement>`_ for Vitis HLS and Matlab HDL-Coder (https://de.mathworks.com/help/simulink/ug/fixed-point-numbers.html)
Please note that are conflicting definitions of fixed point data types.
The definition outlined here is consistent with Vitis HLS (see https://www.xilinx.com/html_docs/xilinx2021_1/vitis_doc/use_arbitrary_precision_data_type.html) and Matlab HDL-Coder (https://de.mathworks.com/help/dsp/ug/concepts-and-terminology.html).



The fixed point library provides a container for the PS to store fixed point values and to ease the handling of them.
It is aimed to provide a clean way to interact with IP-Cores that use fixed-point data representation.
The library is only intended to be used in the lowest software layer of IP-Core drivers to read/write to and from the PL (i.e., functions that are named with ``_hw``).
The read and write functions check against boundaries of the fixed point data type - the data itself is always a 32 bit integer internally (not exposed to the user).

- Data is stored as 32 bit
- Data is divided into fractional and integer bits
- The first n-bits are the fractional bits depending on the representation
- The following m-bits are the integer bits depending on the representation

Example: A signed fixed point value with four fractional bits and five integer bits is represented as shown in :numref:`fixedpoint_bitmap`.
The MSB determines the signedness, the bits *between* the MSB and the integer bits are unused.

.. _fixedpoint_bitmap:

.. figure:: fixedpoint_bitfield.drawio.svg

  Binary representation of fixed point values in memory.

.. note:: This is not intended to do fixed point math on the processor!

Example
=======

Write
*****

Write a value that is a ``float`` in the processor to an IP-Core that expects signed fixed point data with 3 integer and 4 fraction bits.

.. code-block:: c

    #include "uz_fixedpoint.h"
    #define TEST_ADDRESS 0x00F
    float write_value=1.0f;
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=4,
        .integer_bits=3
    };
    uz_fixedpoint_axi_write(TEST_ADDRESS,write_value,def);


Read
****

Read a value from an IP-Core that is an unsigned fixed point with 10 integer bits and 2 fractional bits and pass it to the processor as a ``float``.


.. code-block:: c

    #include "uz_fixedpoint.h"
    #define TEST_ADDRESS 0x00F
    struct uz_fixedpoint_definition_t def={
        .is_signed=false,
        .fractional_bits=2,
        .integer_bits=10
    };
    float data=uz_fixedpoint_axi_read(TEST_ADDRESS,def);

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