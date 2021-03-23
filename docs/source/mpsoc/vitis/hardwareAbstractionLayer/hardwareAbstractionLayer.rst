==========================
Hardware Abstraction Layer
==========================

The UltraZohm uses a hardware abstraction layer (HAL) to make the code portable and enable the development in a local sandbox (your PC).
All IP-core drivers and bare-metal software has to use the HAL (``uz_HAL.h``).
We use simple defines to facilitate the HAL.
The header is located in ``ultrazohm_sw/vitis/export/Baremetal/uz/uz_HAL.h``.
The sandbox header is located in ``ultrazohm_sw/vitis/Sandbox/uz_HAL_sandbox.h``.
Furthermore, HAL defines functions to read and write values from and to the PL via AXI.

* Include the header in your software and use it.
* Use the standard libs such as ``<stdint>`` or ``<limits.h>`` instead of platform specific libraries.
* Use ``int`` or ``float`` for variables
* Do not use ``unsinged int`` to prevent negative values (use ``assert >0`` instead)
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
uz_assertNotNull            Assert that the statement is not NULL (e.g. pointer)
uz_printf                   Printf to standard i/o, call like printf
uz_readFloatFromAxi         Read ``float`` from a hardware register by AXI
uz_writeFloatToAxi          Write ``float`` from a hardware register by AXI
uz_writeUnsingedInt32ToAxi  Write ``uint32_t`` from a hardware register by AXI
uz_readUnsingedInt32FromAxi Read ``uint32_t`` from a hardware register by AXI
uz_writeInt32ToAxi          Write ``int32_t`` from a hardware register by AXI
uz_readInt32FromAxi          Read ``int32_t`` from a hardware register by AXI
uz_writeBoolToAxi           Write ``_Bool`` from a hardware register by AXI
uz_sfixedToFloat            Converts signed fixed point to ``float``
uz_FloatToSfixed            Converts ``float`` to signed fixed point
=========================== ====================================================


HAL Defines
===========

========== ===============================================================
Define              Functionality
========== ===============================================================
UZ_SUCCESS Indicates success as zero (``0``, ``0L`` depending on platform)
UZ_FAILURE Indicates failure as one (``1``, ``1L`` depending on platform)
========== ===============================================================
