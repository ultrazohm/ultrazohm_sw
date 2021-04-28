.. _tutorial_create_ipcore_driver:

=================================
Tutorial: Create a IP-core driver
=================================

This tutorial creates an software driver for the :ref:`AXI_testIP`.
Only a part of the functionality of :ref:`AXI_testIP` is implemented here, i.e., the multiplication of two integer values on the PL.
The driver takes two integer values as input, writes them to the PL and reads the result.

.. note:: This example is purely for understanding how to write the driver, using the PL for simple integer multiplication is much slower than just doing it on the PS.

Setup
=====

1. Open VS Code with :ref:`vscode_remote_container`
2. Open new terminal (``Terminal -> New Terminal``)
3. Change directory of the terminal by typing:
  
::

  cd vitis/software/Baremetal
    
4. Create a new software module ``uz_myIP_hw`` and specify the path ``IP_Cores/uz_myIP/``:
  
::
    
  ceedling module:create[IP_Cores/uz_myIP/uz_myIP_hw]

5. Ceedling creates the files:
    
    - ``uz_myIP_hw.c`` in ``vitis/software/Baremetal/src/IP_Cores/uz_myIP/``
    - ``uz_myIP_hw.h`` in ``vitis/software/Baremetal/src/IP_Cores/uz_myIP/``
    - ``test_uz_myIP_hw.c`` in ``vitis/software/Baremetal/test/IP_Cores/uz_myIP/``

6. Create the file ``uz_myIP_hwAddresses.h`` in ``vitis/software/Baremetal/src/IP_Cores/uz_myIP/`` and add an include guard to it (``#pragma once`` in first line)
7. Open ``uz_axi_testIP_addr.h`` in ``ultrazohm_sw/ip_cores/AXI_testIP/uz_axi_testIP/ipcore/uz_axi_testIP_v1_0/include``
8. Copy all defines in this file
9. Paste the defines of ``uz_axi_testIP_addr.h`` into ``uz_myIP_hwAddresses.h``
10. Open ``test_uz_myIP_hw.c`` and add:


.. code-block:: c

  #include "test_assert_with_exception.h"
  #include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
  #include "uz_myIP_hwAddresses.h"
  #define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

11. Rename the existing test ``test_uz_myIP_hw_NeedToImplement`` to ``test_uz_myIP_hw_write_to_A``
12. Run the tests by typing ``ceedling test:all`` in the terminal
13. The tests pass but a message a ignore message is printed

::

  --------------------
  IGNORED TEST SUMMARY
  --------------------
  [test_uz_myIP_hw.c]
    Test: test_uz_myIP_hw_write_to_A
    At line (21): "Need to Implement uz_myIP_hw"

14. This means that the test build, but no test is implemented for the new IP-Core.

First test
==========

To multiply two variables :math:`C=A \cdot B` of type ``int32_t``, the driver has to write :math:`A` and :math:`B` from the PS to the PL by AXI in the correct registers and read back the result :math:`C` from the PL to the PS.
See :ref:`AXI_testIP` for the available hardware registers of the IP-Core.
The address of the registers are listed in ``uz_myIP_hwAddresses.h``.
Read/write operations on AXI are done by using the :ref:`HAL`.
Therefore, we expect that the driver first has to call the function ``uz_axi_write_int32`` with the register address of :math:`A` and an integer as arguments.
Write the test for this behavior:

1. Delete the line ``TEST_IGNORE_MESSAGE("Need to Implement uz_myIP_hw");`` and add a first test in ``test_uz_myIP_hw.c``.

.. code-block:: c
   :linenos:

   void test_uz_myIP_hw_write_to_A(void)
   {
       int a=-10;
       // Test passes if uz_axi_write_int32 is called once with these arguments
       uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+A_int32_Data_uz_axi_testIP,a); 
       uz_axi_write_int32
       uz_myIP_hw_write_A(TEST_BASE_ADDRESS,a);
   }

2. Run the tests (type ``ceedling test:all`` in terminal)
3. Tests fail with a warning that ``uz_myIP_hw_write_to_A`` has an implicit declaration
4. Declare the required functions to read and write from the IP-core in ``uz_myIP_hw.h``

.. code-block:: c
   :linenos:
   :caption: ``uz_myIP_hw.h``

   #ifndef UZ_MYIP_HW_H
   #define UZ_MYIP_HW_H
   #include <stdint.h>
   void uz_myIP_hw_write_A(uint32_t base_address,int32_t A);
   void uz_myIP_hw_write_B(uint32_t base_address,int32_t B);
   int32_t uz_myIP_hw_read_C(uint32_t base_address);
   #endif // UZ_MYIP_HW_H

5. Run the tests, they will fail due to undefined references to ``uz_myIP_hw_write_A``
6. Implement the write function in ``uz_myIP_hw.c``

.. code-block:: c
   :linenos:
   :caption: ``uz_myIP_hw.c``

   #include "uz_myIP_hw.h"
   #include "uz_myIP_hwAddresses.h"
   #include "../../uz/uz_AXI.h"
   
   void uz_myIP_hw_write_A(uint32_t base_address,int32_t A){
       uz_axi_write_int32(base_address+A_int32_Data_uz_axi_testIP,A);    
   }

7. Run the tests, they will pass
8. Currently, we only test the *good* case in which everything works as expected. However, we need to protect agains some basic errors.
9. Add a test that protect agains calling the write function without a valid base address:

.. code-block:: c
   :linenos:
   :caption: Testing asserts1

   void test_uz_myIP_hw_write_to_A_with_zero_base_address(void)
   {
       int a=-10;
       // we just test the failing assert, do not care what else is called
       uz_axi_write_int32_Ignore();
       // Test passes if an assert fails in the function under test
       TEST_ASSERT_FAIL_ASSERT(uz_myIP_hw_write_A(0,a))
   }

10. Run the tests, they fail with the following message because we expected that an :ref:`assertion` fires in ``uz_myIP_hw_write_A`` to prevent calling the function with base address ``0``:

::

  FAILED TEST SUMMARY
  -------------------
  [test_uz_myIP_hw.c]
    Test: test_uz_myIP_hw_write_to_A_with_zero_base_address
    At line (31): "Code under test did not assert"

11. Add the following to ``uz_myIP_hw.c``

.. code-block:: c
   :linenos:
   :caption: ``uz_myIP_hw.c`` with assert to prevent call with ``base_address == 0``

   #include "uz_myIP_hw.h"
   #include "uz_myIP_hwAddresses.h"
   #include "../../uz/uz_AXI.h"
   #include "../../uz/uz_HAL.h"
   
   void uz_myIP_hw_write_A(uint32_t base_address,int32_t A){
       uz_assert_not_zero(base_address);
       uz_axi_write_int32(base_address+A_int32_Data_uz_axi_testIP,A);    
   }

12. Run the tests, they pass. Note that this assert only prevents calling the function with ``base_address == 0``, e.g., if some variable was automatically initialized thought a struct initializer. The function still can be called with a *wrong* base address!