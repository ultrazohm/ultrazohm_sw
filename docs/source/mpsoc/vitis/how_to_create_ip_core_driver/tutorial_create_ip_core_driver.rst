.. _tutorial_create_ipcore_driver:

=================================
Tutorial: Create a IP-core driver
=================================

This tutorial creates an software driver for the :ref:`AXI_testIP`.
Only a part of the functionality of :ref:`AXI_testIP` is implemented here, i.e., the multiplication of two integer values on the PL.
The driver takes two integer values as input, writes them to the PL and reads the result.

.. note:: This example is purely for understanding how to write the driver, using the PL for simple integer multiplication is much slower than just doing it on the PS.

.. tip:: Somethimes, Ceedling fails to build and unclear errors are present. Try to use ``ceedling clean`` to delete temporary files of ceedling or commenting out the last test, , running `ceedling clean``, running all tests again and comment the last test in again.

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

Software module for hardware registers
======================================

To multiply two variables :math:`C=A \cdot B` of type ``int32_t``, the driver has to write :math:`A` and :math:`B` from the PS to the PL by AXI in the correct registers and read back the result :math:`C` from the PL to the PS.
In this section, we write a software module (``uz_myIP_hw``) that only deals with writing and reading the hardware registers of the IP-Core such that software modules can use the module without having to know the hardware addresses.
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
   :caption: Testing asserts

   void test_uz_myIP_hw_write_to_A_with_zero_base_address(void)
   {
       int a=-10;
       // Tell the test that we do not care how often this function is called
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

12. Run the tests, they pass. Note that this assert only prevents calling the function with ``base_address == 0``, e.g., if the variable was automatically initialized by a struct initializer. The function still can be called with a *wrong* base address!

13. We can now write :math:`A` to the IP-Core and have a test that ensures that we write to the correct addresses. Next step: do the same for :math:`B`:

.. warning:: It is tempting to copy & paste everything here - be careful to get all addresses, function, and variable names right!

14. Write a test that checks that ``uz_myIP_hw_write_B`` writes to the correct address and a test that prevents calls with ``base_address == 0``:

.. code-block:: c
   :linenos:
   :caption: Test for writing to register B

   void test_uz_myIP_hw_write_to_B(void)
   {
       int b=100;
       uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+B_int32_Data_uz_axi_testIP,b);
       uz_myIP_hw_write_B(TEST_BASE_ADDRESS,b);
   }
   
15. Run the test. It does not compile since ``uz_myIP_hw_write_B`` is not implemented. Add the implementation in ``uz_myIP_hw.c``:

.. code-block:: c
   :linenos:
   :caption: Function to write to register B_int32_Data_uz_axi_testIP

   void uz_myIP_hw_write_B(uint32_t base_address,int32_t B){
   uz_assert_not_zero(base_address);
   uz_axi_write_int32(base_address+B_int32_Data_uz_axi_testIP,B);    
   }

16. Run the test, it passes. We already implemented the assert for the base address in this case, make sure to add the test for this:

.. code-block:: c
   :linenos:
   :caption: Test that assert fires in write to b

   void test_uz_myIP_hw_write_to_B_with_zero_base_address(void)
   {
       int b=2;
       uz_axi_write_int32_Ignore();
       TEST_ASSERT_FAIL_ASSERT(uz_myIP_hw_write_B(0,b))
   }

17. Run the test, it passes.
18. To get the result of the multiplication, read the register C. Create a test for this. ``uz_axi_read_int32_ExpectAndReturn`` creates a mock for the function ``uz_axi_read_int32`` that returns ``c`` if it is called. Furthermore, we test that the right value is returned form ``uz_myIP_hw_read_C``:

.. code-block:: c
   :linenos:
   :caption: Test that ``uz_myIP_hw_read_C`` returns the correct value

   void test_uz_myIP_hw_read_from_C(void)
   {
       int c=101230;
       uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+C_int32_Data_uz_axi_testIP,c);
       int c_readback=uz_myIP_hw_read_C(TEST_BASE_ADDRESS);
       TEST_ASSERT_EQUAL_INT(c,c_readback);
   }

19. Run the test, this does not compile since there is no implementation of ``uz_myIP_hw_read_C``. Add it to ``uz_myIP_hw.c``:

.. code-block:: c
   :linenos:
   :caption: Implementation of ``uz_myIP_hw_read_C``

   int32_t uz_myIP_hw_read_C(uint32_t base_address){
       
   }

20. Run the test. The test fails since ``uz_myIP_hw_read_C`` did not return the right value.
21. Implement a real version of ``uz_myIP_hw_read_C``:

.. code-block:: c
   :linenos:
   :caption: Implementation of ``uz_myIP_hw_read_C`` with right return value

   int32_t uz_myIP_hw_read_C(uint32_t base_address){
   return (uz_axi_read_int32(base_address+C_int32_Data_uz_axi_testIP));
}

22. Run the tests, they will pass now.
23. Add a test for the missing assert:

.. code-block:: c
   :linenos:
   :caption: Assert test for read C function

   void test_uz_myIP_hw_read_C_with_zero_base_address(void)
   {
       int c=123;
       // Ignores how often the read function is called and returns (c)
       uz_axi_read_int32_IgnoreAndReturn(c);
       TEST_ASSERT_FAIL_ASSERT(uz_myIP_hw_read_C(0));
   }

24. Run the test, the test fails with ``Code under test did not assert``
25. Add 

.. code-block:: c
   :linenos:
   :caption: Add assert to read C function

   int32_t uz_myIP_hw_read_C(uint32_t base_address){
   uz_assert_not_zero(base_address);
   return (uz_axi_read_int32(base_address+C_int32_Data_uz_axi_testIP));
   }

26. Run the tests, all test will pass!

Software module for hardware multiplication
===========================================

Recall that we use the :ref:`AXI_testIP` to calculate :math:`C=A \cdot B`.
Until now, we created an abstraction layer for the hardware registers.
Implement the actual function of the driver. 

1. In the terminal:

::

  ceedling module:create[IP_Cores/uz_myIP/uz_myIP]

2. Create the interface of the IP-Core driver in ``uz_myIP.h``. Notice how the interface is focused on usability: We only have to initialize the module and then use the hardware calculation :math:`C=A \cdot B` without knowledge about hardware registers and addresses.

.. code-block:: c
   :linenos:
   :caption: Software interface of IP-Core

   #ifndef UZ_MYIP_H
   #define UZ_MYIP_H
   #include <stdint.h>

   typedef struct uz_myIP uz_myIP;
   
   uz_myIP* uz_myIP_init(uz_myIP* self);
   int32_t uz_myIP_multiply(uz_myIP* self, int32_t A, int32_t B);
   
   #endif // UZ_MYIP_H

3. Create the file ``uz_myIP_private.h`` in ``src/IP_Cores/uz_myIP/``. Every IP-Core driver should have a private struct with at least these three variables. Notice that all members of the struct ``test_instance`` that are not listed in the initializer are set to zero by default. Thats the main reason for the usage of ``uz_assert_not_zero`` in ``uz_myIP_hw.c``.

.. code-block:: c
   :linenos:
   :caption: ``uz_myIP_private`` with default members

   #pragma once
   
   #include <stdbool.h>
   #include <stdint.h>
   #include "uz_myIP.h"
   
   struct uz_myIP {
       const uint32_t base_address;
       const uint32_t ip_clk_frequency_Hz;
       bool is_ready;
   };

3. Add to following code to ``test_uz_myIP.c``. We isolate the testing by using a mock version of our already implemented ``uz_myIP_hw``.
   
.. code-block:: c
   :linenos:
   :caption: ``test_uz_myIP`` test setup


   #include "test_assert_with_exception.h"
   #include "uz_myIP.h"
   #include "uz_myIP_private.h" // Required to init an instance
   #include "mock_uz_myIP_hw.h" // Mock the _hw functions to isolate testing
   #include <stdint.h>

   #define TEST_BASE_ADDRESS 0x0000000A
   #define TEST_IP_CORE_FRQ 100000000U

   static uz_myIP instance={
    .base_address=TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
   };

4. Run the tests, all tests pass but uz_myIP_test is ignored.
5. Create a first test that makes sure ``uz_myIP_init`` can not be called with a NULL-pointer:

.. code-block:: c
   :linenos:

   void test_uz_myIP_test_init_assert_NULL(void)
   {
       TEST_ASSERT_FAIL_ASSERT(uz_myIP_init(NULL));
   }

6. Run the tests, they do not compile since ``uz_myIP_init`` is not implemented. Add an implementation that makes the test compile:

.. code-block:: c
   :linenos:
   :caption: ``uz_myIP.c`` that is sufficent to compile

   #include "uz_myIP.h"

   uz_myIP* uz_myIP_init(uz_myIP* self){
       
   }

7. Run the tests, ``test_uz_myIP_test_init_asserts`` fails with *Code under test did not assert*
8. Add an assert that fails if a NULL-pointer is used as an argument for (``uz_myIP_init``):

.. code-block:: c
   :linenos:

   #include "uz_myIP.h"
   #include "../../uz/uz_HAL.h"
   
   uz_myIP* uz_myIP_init(uz_myIP* self){
       uz_assert_not_NULL(self);
   }

9. Add another test that passes the right pointer to the init function and makes sure the right pointer is returned. Note that we use a local version of the struct for the init tests to prevent the tests from interfering with each other.

.. code-block:: c
   :linenos:

   void test_uz_myIP_test_right_pointer_returned_form_init(void){
   uz_myIP test_instance={
   .base_address=TEST_BASE_ADDRESS,
   .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
   };
   
   uz_myIP* test_ptr=uz_myIP_init(&test_instance);
   TEST_ASSERT_EQUAL_PTR(test_ptr,&test_instance);
   }

10. Run the test, it will fail since the pointer are not equal.
11. Return the right pointer from ``uz_myIP_init``:

.. code-block:: c
   :linenos:

   uz_myIP* uz_myIP_init(uz_myIP* self){
   uz_assert_not_NULL(self);
   return (self);
   }

12. Add a test that checks if it is possible to init an instance two times (this should not be possible!)

.. code-block:: c
   :linenos:

   void test_uz_myIP_test_double_init(void){
   uz_myIP test_instance={
      .base_address=TEST_BASE_ADDRESS,
      .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
   };
   
   uz_myIP* test_ptr=uz_myIP_init(&test_instance);
   TEST_ASSERT_EQUAL_PTR(test_ptr,&test_instance);
   TEST_ASSERT_FAIL_ASSERT(test_ptr=uz_myIP_init(&test_instance));
   }

13. Include ``uz_myIP_private``, set ``is_ready`` to true in the initialization, and add an assert in ``uz_myIP.c`` to pass the test:

.. code-block:: c
   :linenos:

   #include "uz_myIP.h"
   #include "../../uz/uz_HAL.h"

    uz_myIP* uz_myIP_init(uz_myIP* self){
    uz_assert_not_NULL(self);
    uz_assert_false(self->is_ready);
    return (self);
    }

14. Test to prevent calling init without initialization of the base address:

.. code-block:: c
   :linenos:

   void test_uz_myIP_test_base_address_not_zero(void){
   uz_myIP test_instance={
      .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
   };
   
   TEST_ASSERT_FAIL_ASSERT(uz_myIP* test_ptr=uz_myIP_init(&test_instance));
   }

15. Test fails, add ``    uz_assert_not_zero(self->base_address);``
16. Repeat for ``ip_clk_frequency_Hz``. Add ``assert_not_zero(self->ip_clk_frequency_Hz`` to ``uz_myIP_init`` and the following test:

.. code-block:: c
   :linenos:

   void test_uz_myIP_test_base_address_not_zero(void){
   uz_myIP test_instance={
      .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
   };
   
   TEST_ASSERT_FAIL_ASSERT(uz_myIP* test_ptr=uz_myIP_init(&test_instance));
   }

17. Add a test for the multiplication :math:`C=A \cdot B`:
   
.. code-block:: c
   :linenos:

   void test_uz_myIP_test_A_times_B_equals_C(void){
   uz_myIP* test_ptr=uz_myIP_init(&instance);
   int32_t a=-10;
   int32_t b=200;
   uz_myIP_hw_write_A_Expect(TEST_BASE_ADDRESS,a);
   uz_myIP_hw_write_B_Expect(TEST_BASE_ADDRESS,b);
   uz_myIP_hw_read_C_ExpectAndReturn(TEST_BASE_ADDRESS,a*b);
   int32_t c=uz_myIP_multiply(test_ptr,a,b);
   TEST_ASSERT_EQUAL_INT32(a*b,c);
   }

18. Add ``#include "uz_myIP_hw.h"`` to ``uz_myIP.c`` and implement the calls to the hardware

.. code-block:: c
   :linenos:

   int32_t uz_myIP_multiply(uz_myIP* self, int32_t A, int32_t B){
    uz_myIP_hw_write_A(self->base_address,A);
    uz_myIP_hw_write_B(self->base_address,B);
    return (uz_myIP_hw_read_C(self->base_address));
   }

19. One important last test. We have to prevent calls to ``uz_myIP_multiply`` before initialization since this would cause read/write operations in random memory addresses and make sure it is not called with a NULL-pointer.

.. code-block:: c
   :linenos:

   void test_uz_myIP_no_multiplication_before_initialization_and_no_NULL_pointer_passed(void){
     uz_myIP test_instance_no_init={
        .base_address=TEST_BASE_ADDRESS
     };
    int32_t a=10;
    int32_t b=20;
    uz_myIP_hw_write_A_Ignore();
    uz_myIP_hw_write_B_Ignore();
    uz_myIP_hw_read_C_IgnoreAndReturn(a*b);
    TEST_ASSERT_FAIL_ASSERT(int32_t c=uz_myIP_multiply( &test_instance_no_init,a,b));
    TEST_ASSERT_FAIL_ASSERT(int32_t c=uz_myIP_multiply( NULL,a,b));
   }

20. Add the required asserts to ``uz_myIP_multiply.c``:

.. code-block:: c
   :linenos:
   
   int32_t uz_myIP_multiply(uz_myIP* self, int32_t A, int32_t B){
    uz_assert_not_NULL(self);
    uz_assert_true(self->is_ready);
    uz_myIP_hw_write_A(self->base_address,A);
    uz_myIP_hw_write_B(self->base_address,B);
    return (uz_myIP_hw_read_C(self->base_address));
   }

.. warning:: While we tested our functions with a lot of different error cases and made sure they behave as expected we omitted the fact that the multiplication can overflow. This is especially tricky in this case since the multiplication is implemented in hardware, thus the rules for C do not apply to it. There are two ways to handle it: implement the hardware multiplication in a way that saturates on overflow or check if the multiplication will overflow before writing to the PL. The way :ref:`AXI_testIP` is implemented will *wrap* on overflow, i.e., 2147483647*2 will be read as a negative value. Keep this concept in mind for real IP-Cores that you implement. Additionally, prevent the software driver to write values that are out of range to the IP-Core, e.g., if the register only uses 10 bit. Note that the AXI transaction always is 32-bit.


