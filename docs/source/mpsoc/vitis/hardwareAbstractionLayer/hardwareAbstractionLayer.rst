.. _HAL:

==========================
Hardware Abstraction Layer
==========================

The UltraZohm uses a hardware abstraction layer (HAL) to make the code portable and enable the development in a local sandbox (your PC).
All IP-core drivers and bare-metal software has to use the HAL (``uz_HAL.h``).
We use simple defines to facilitate the HAL.
The header is located in ``ultrazohm_sw/vitis/software/Baremetal/src/uz/uz_HAL.h``.
Furthermore, the HAL defines functions to read and write values from and to the PL via AXI.

* Include the header in your software and use it.
* Use the standard libs such as ``<stdint>`` or ``<limits.h>`` instead of platform specific libraries.
* Use ``int`` or ``float`` for variables
* Do not use ``unsinged int`` to prevent negative values
* Use ``assert >0`` to make sure a variable is positive instead
* Do use fixed length unsigned variables for hardware adresses (e.g. base adresses of IP-cores)
* Only use fixed length variables (e.g., ``int32_t``) for function that write to hardware registers
* Do not use platform specific data types

.. note :: The UltraZohm offers 32 bit and 64 bit processors, thus the HAL enables portable code between R5 and A53

.. warning:: ``uz_printf`` maps to ``xil_printf`` on the UltraZohm and ``xil_printf`` does not support everything that ``printf`` from ``<stdio.h>`` does, e.g., you can not print floats with ``%f``

HAL Functions
=============

The HAL provides the following functions:

=========================== ====================================================
Define                      Functionality
=========================== ====================================================
uz_assert                   Statement that has to be true
uz_assert_not_NULL          Assert that the statement is not NULL (e.g. pointer)
uz_printf                   Printf to standard i/o, call like printf
uz_convert_sfixed_to_float  Converts signed fixed point to ``float``
uz_convert_float_to_sfixed  Converts ``float`` to signed fixed point
uz_sleep_seconds            Do nothing for X seconds
uz_sleep_useconds           Do nothing for X microseconds
=========================== ====================================================


HAL Defines
===========

========== ===============================================================
Define              Functionality
========== ===============================================================
UZ_SUCCESS Indicates success as zero (``0``, ``0L`` depending on platform)
UZ_FAILURE Indicates failure as one (``1``, ``1L`` depending on platform)
========== ===============================================================

AXI Functions
=============

The header ``uz_AXI.h`` provides the following functions to read/write from/to the PL by using the AXI interface.
Use only these functions for AXI and use them only in the lowest layer of the software.

.. doxygenfunction:: uz_axi_write_float

.. doxygenfunction:: uz_axi_read_float

.. doxygenfunction:: uz_axi_write_uint32

.. doxygenfunction:: uz_axi_read_uint32

.. doxygenfunction:: uz_axi_read_int32

.. doxygenfunction:: uz_axi_write_int32

.. doxygenfunction:: uz_axi_write_bool

.. doxygenfunction:: uz_axi_read_bool

.. doxygenfunction:: uz_convert_sfixed_to_float

.. doxygenfunction:: uz_convert_float_to_sfixed

.. c:function:: int func(int a)

This is a ref to func :func:`func` and this to axi write :func:`uz_axi_write_float`.


