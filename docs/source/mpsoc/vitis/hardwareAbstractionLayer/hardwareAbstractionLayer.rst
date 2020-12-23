==========================
Hardware Abstraction Layer
==========================

The UltraZohm uses a hardware abstraction layer (HAL) to make the code portable and enable the development in a local sandbox (your PC).
All IP-core drivers and bare-metal software has to use the HAL (``uz_HAL.h``).
We use simple defines to facilitate the HAL.
The header is located in ``ultrazohm_sw/vitis/export/Baremetal/uz/uz_HAL.h``.

* Include the header in your software and use it.
* Use the standard libs such as ``<stdint>`` or ``<limits.h>`` instead of platform specific libraries.
* Use ``int`` or ``float`` for variables
* Do not use ``unsinged int`` to prevent negative values (use ``assert >0`` instead)
* Do use fixed length unsigned variables for hardware adresses (e.g. base adresses of IP-cores)
* Only use fixed length variables (e.g. ``int32_t``) for function that write to hardware registers
* Do not use platform specific data types

.. note :: The UltraZohm offers 32 bit and 64 bit processors, thus the HAL enables portable code between R5 and A53

HAL Functions
=============

The HAL provides the following functions:

========================= ====================================================
Define                    Functionality
========================= ====================================================
uz_assert                 Statement that has to be true
uz_assertNotNull          Assert that the statement is not NULL (e.g. pointer)
uz_printf                 Printf to standard i/o
uz_Write32BitToRegister   Write to hardware register by AXI
uz_Read32BitFromRegister  Read form hardware register by AXI
========================= ====================================================


HAL Defines
===========

========== ===============================================================
Define              Functionality
========== ===============================================================
UZ_SUCCESS Indicates success as zero (``0``, ``0L`` depending on platform)
UZ_FAILURE Indicates failure as one (``1``, ``1L`` depending on platform)
========== ===============================================================

Set Target
==========

The defines ``TARGET_ULTRAZOHM`` and ``TARGET_SANDBOX`` are used to determine which target is used. Set the target to true that is used.

Snippet
=======

The concept of the HAL is shown in the following:

.. code-block:: c

    #define uz_assert Xil_AssertVoid
    #define uz_assertNotNull(Expression) \
    {                              \
    uz_assert(Expression!=NULL);        \
    }
    #define uz_printf xil_printf
    #define uz_Write32BitToRegister Xil_Out32
    #define uz_Read32BitFromRegister Xil_In32

    #define UZ_SUCCESS XST_SUCCESS
    #define UZ_FAILURE XST_FAILURE