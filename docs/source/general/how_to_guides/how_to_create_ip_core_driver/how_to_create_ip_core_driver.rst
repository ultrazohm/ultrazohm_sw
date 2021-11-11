.. _how_to_create_ipcore_driver:

==============================
How to create a IP-core driver
==============================

This tutorial creates a software driver for the :ref:`AXI_testIP`.
Only a part of the functionality of :ref:`AXI_testIP` is implemented here, i.e., the multiplication of two integer values on the PL.
The driver takes two integer values as input, writes them to the PL, and reads the result.
The implementation is done in a way that implements the driver and the :ref:`unit_tests` in parallel. 

.. note:: This example is purely for understanding how to write the driver. Using the PL for simple integer multiplication is much slower than just doing it on the PS.

.. tip:: Sometimes, Ceedling fails to build, and unclear errors are present. Try to use ``ceedling clean`` to delete temporary files of Ceedling or commenting out the last test, running `ceedling clean``, running all tests again, and comment in the last test again. If this does not work, run ``ceedling clobber`` to delete more temporary files and run the tests again.

Video
=====

.. youtube::  ZlqpPEV-CBg

.. youtube:: ndCJcFavay0


Setup
=====

1. Open VS Code with :ref:`vscode_remote_container`
2. Open a new terminal (``Terminal -> New Terminal``)
3. Change the directory of the terminal by typing:
  
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
13. The tests pass, but a message a ignore message is printed

::

  --------------------
  IGNORED TEST SUMMARY
  --------------------
  [test_uz_myIP_hw.c]
    Test: test_uz_myIP_hw_write_to_A
    At line (21): "Need to Implement uz_myIP_hw"

14. This means that the test builds, but no test is implemented for the new IP-Core.

IP-Core driver: Hardware registers
==================================

To multiply two variables :math:`C=A \cdot B` of type ``int32_t``, the driver has to write :math:`A` and :math:`B` from the PS to the PL by AXI in the correct registers and read back the result :math:`C` from the PL to the PS.
In this section, we write a software module (``uz_myIP_hw``) that only deals with writing and reading the hardware registers of the IP-Core such that software modules can use the module without having to know the hardware addresses.
See :ref:`AXI_testIP` for the available hardware registers of the IP-Core.
The addresses of the registers are listed in ``uz_myIP_hwAddresses.h``.
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
       uz_myIP_hw_write_A(TEST_BASE_ADDRESS,a);
   }

1. Run the tests (type ``ceedling test:all`` in terminal)
2. Tests fail with a warning that ``uz_myIP_hw_write_to_A`` has an implicit declaration
3. Declare the required functions to read and write from the IP-core in ``uz_myIP_hw.h``

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

5. Run the tests. They will fail due to undefined references to ``uz_myIP_hw_write_A``
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

7. Run the tests. They will pass
8. Currently, we only test the *good* case in which everything works as expected. However, we need to protect against some basic errors.
9. Add a test that protects against calling the write function without a valid base address:

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

10. Run the tests, they fail with the following message because we expected that an :ref:`assertions` fires in ``uz_myIP_hw_write_A`` to prevent calling the function with base address ``0``:

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

12. Run the tests. They pass. Note that this assertion only prevents calling the function with ``base_address == 0``, e.g., if a struct initializer automatically initialized the variable. The function still can be called with a *wrong* base address!

13. We can now write :math:`A` to the IP-Core and have a test that ensures that we write to the correct addresses. Next step: do the same for :math:`B`:

.. warning:: It is tempting to copy & paste everything here - be careful to get all addresses, functions, and variable names right!

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

16. Run the test. It passes. We already implemented the assert for the base address in this case. Make sure to add the test for this:

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

22. Run the tests. They will pass now.
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

26. Run the tests. All tests will pass!

IP-Core driver: User software
=============================

Recall that we use the :ref:`AXI_testIP` to calculate :math:`C=A \cdot B`.
Until now, we created an abstraction layer for the hardware registers.
We implement the actual function of the driver in the following. 

1. Type in the terminal:

::

  ceedling module:create[IP_Cores/uz_myIP/uz_myIP]

2. Create the interface of the IP-Core driver in ``uz_myIP.h``. Notice how the interface is focused on the user: We only have to initialize the module and use the hardware calculation :math:`C=A \cdot B` without knowledge about hardware registers and addresses. We use :ref:`doxygen` to document the interface. Type ``/**`` above a function, struct or typedef you want to comment and press enter, VSCode will auto-generate the doxygen boiler plate. We only use doxygen comments for the interface (in the ``.h`` file) and later include these in the sphinx documentation.

.. code-block:: c
   :linenos:
   :caption: Software interface of IP-Core

   #ifndef UZ_MYIP_H
   #define UZ_MYIP_H
   #include <stdint.h>
   
   /**
    * @brief Data type for object myIP
    * 
    */
   typedef struct uz_myIP_t uz_myIP_t;
   
   /**
    * @brief Configuration struct for myIP
    * 
    */
   struct uz_myIP_config_t{
       uint32_t base_address; /**< Base address of the IP-Core */
       uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
   };
   
   /**
    * @brief Initializes an instance of the myIP driver
    * 
    * @param config Configuration values for the IP-Core
    * @return Pointer to initialized instance 
    */
   uz_myIP_t* uz_myIP_init(struct uz_myIP_config_t config);
   
   /**
    * @brief Calculates C=A*B
    * 
    * @param self Pointer to IP-Core instance that was initialized with init function
    * @param A First factor
    * @param B Second factor
    * @return Product of A times B
    */
   int32_t uz_myIP_multiply(uz_myIP_t* self, int32_t A, int32_t B);
   
   #endif // UZ_MYIP_H

3. Run Ceedling, the tests will pass but the test for ``uz_myIP`` is ignored.
4. Open the file ``uz_myIP.c`` in ``src/IP_Cores/uz_myIP/``.
5. Use the *allocation* VSCode snippet  for the static memory allocation boiler plate code (see :ref:`static_memory_allocation` for details). If you use :ref:`vscode_remote_container`, you can use the snippet by typing ``allocator`` in the file. Alternatively copy the following code.


.. image:: https://images2.imgbox.com/6d/39/mL1WUwjP_o.gif

.. code-block:: c
   :linenos:
   :caption: Boilerplate code and static allocation for the module

   #include "../../uz/uz_global_configuration.h"
   #if UZ_MYIP_MAX_INSTANCES > 0U
   #include <stdbool.h> 
   #include "../../uz/uz_HAL.h"
   #include "uz_myIP.h" 
   
   struct uz_myIP_t {
       bool is_ready;
   };
   
   static size_t instance_counter = 0U;
   static uz_myIP_t instances[UZ_MYIP_MAX_INSTANCES] = { 0 };
   
   static uz_myIP_t* uz_myIP_allocation(void);
   
   static uz_myIP_t* uz_myIP_allocation(void){
       uz_assert(instance_counter < UZ_MYIP_MAX_INSTANCES);
       uz_myIP_t* self = &instances[instance_counter];
       uz_assert_false(self->is_ready);
       instance_counter++;
       self->is_ready = true;
       return (self);
   }
   
   uz_myIP_t* uz_myIP_init() {
       uz_myIP_t* self = uz_myIP_allocation();
       return (self);
   }
   #endif

6. Open ``uz_global_configuration.h`` if you already renamed the sample configuration. If not, see :ref:`global_configuration`.
7. Add ``#define UZ_MYIP_MAX_INSTANCES 5U`` to ``uz_global_configuration.h`` inside the test ifdef (at the bottom of the file). We can now use up to 5 instances of the IP-core driver for five different instances of the IP-Core in the tests.
8. Add the following code to ``test_uz_myIP.c``. We isolate the testing by using a mock version of our already implemented ``uz_myIP_hw``.
   
.. code-block:: c
   :linenos:
   :caption: ``test_uz_myIP.c`` test setup


   #include "test_assert_with_exception.h"
   #include "uz_myIP.h"
   #include "mock_uz_myIP_hw.h" // Mock the _hw functions to isolate testing
   #include <stdint.h>

   #define TEST_BASE_ADDRESS 0x0000000A
   #define TEST_IP_CORE_FRQ 100000000U

9. Change the implementation of ``uz_myIP_init`` in ``uz_myIP.c`` to match the interface in ``uz_myIP.h``

.. code-block:: c
   :linenos:

   uz_myIP_t* uz_myIP_init(struct uz_myIP_config_t config){
    uz_myIP_t* self = uz_myIP_allocation();
    return (self);
   }

10. Run the tests, all tests pass, but ``uz_myIP_test`` is ignored.
11.  Start writing a test for the multiplication :math:`C=A \cdot B` by initializing an instance of the IP-Core driver:
   
.. code-block:: c
   :linenos:

   void test_uz_myIP_test_A_times_B_equals_C(void)
   {
       struct uz_myIP_config_t config={
           .base_address= TEST_BASE_ADDRESS,
           .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
       };
       uz_myIP_t *instance = uz_myIP_init(config);
   }

12. Run the tests, they will pass but a warning about unused variables ``config`` and ``instance`` is shown.
13. Add to the test:

.. code-block:: c
   :linenos:

    void test_uz_myIP_test_A_times_B_equals_C(void)
    {
        struct uz_myIP_config_t config={
            .base_address= TEST_BASE_ADDRESS,
            .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
        };
        uz_myIP_t *instance = uz_myIP_init(config);
        int32_t a = -10;
        int32_t b = 200;
        uz_myIP_hw_write_A_Expect(TEST_BASE_ADDRESS, a);
        uz_myIP_hw_write_B_Expect(TEST_BASE_ADDRESS, b);
        uz_myIP_hw_read_C_ExpectAndReturn(TEST_BASE_ADDRESS, a * b);
        int32_t c = uz_myIP_multiply(instance, a, b);
        TEST_ASSERT_EQUAL_INT32(a * b, c);
    }

14. Run the tests, we have a linker error since ``uz_myIP_multiply`` is not implemented yet.
15. Add ``#include "uz_myIP_hw.h"`` to ``uz_myIP.c`` and implement the calls to the hardware registers.

.. code-block:: c
   :linenos:

   int32_t uz_myIP_multiply(uz_myIP_t* self, int32_t A, int32_t B){
   uz_assert(self->is_ready);
   uz_myIP_hw_write_A(self->config.base_address,A);
   uz_myIP_hw_write_B(self->config.base_address,B);
   return (uz_myIP_hw_read_C(self->config.base_address));
   }

1.  Run the tests, we have several errors since we have no struct member ``config``. Add config to the struct ``uz_myIP_t``:

.. code-block:: C
   :linenos:

   struct uz_myIP_t {
    bool is_ready;
    struct uz_myIP_config_t config;
   };

17. Run the tests, they fail since ``uz_myIP_hw_write_A`` is not called with the correct base address.
18. Assign the passed config value to the instance in ``uz_myIP_init()``:

.. code-block:: c
   :linenos:

   uz_myIP_t* uz_myIP_init(struct uz_myIP_config_t config){
    uz_myIP_t* self = uz_myIP_allocation();
    self->config=config;
    return (self);
   }

19. Run the tests, they pass!
20. Add a test to prevent calling init without initialization of the base address:

.. code-block:: c
   :linenos:

   void test_uz_myIP_fail_assert_if_base_address_is_zero(void)
   {
       struct uz_myIP_config_t config={
           .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
       };
       TEST_ASSERT_FAIL_ASSERT(uz_myIP_init(config) );
   }

21. Test fails, add ``uz_assert_not_zero(config.base_address);`` to ``uz_myIP_init`` before the allocation is done.
22. Run the test again, it passes now.
23. Repeat for ``ip_clk_frequency_Hz``. Add ``uz_assert_not_zero(config.ip_clk_frequency_Hz);`` to ``uz_myIP_init`` and the following test:

.. code-block:: c
   :linenos:

   void test_uz_myIP_fail_assert_if_ip_frequency_is_zero(void)
   {
       struct uz_myIP_config_t config={
           .base_address=TEST_BASE_ADDRESS
       };
       TEST_ASSERT_FAIL_ASSERT(uz_myIP_init(config) );
   }

24. Add a test to prevent calling ``uz_myIP_multiply()`` with a NULL pointer

.. code-block:: C

   void test_uz_myIP_fail_assert_if_multiply_is_called_with_NULL_pointer(void)
   {
       TEST_ASSERT_FAIL_ASSERT(uz_myIP_multiply(NULL, 5, 1));
   }

25. Add an assertion to prevent calls with NULL pointer:

.. code-block:: C

   int32_t uz_myIP_multiply(uz_myIP_t* self, int32_t A, int32_t B){
       uz_assert_not_NULL(self);
       uz_assert(self->is_ready);
       uz_myIP_hw_write_A(self->config.base_address,A);
       uz_myIP_hw_write_B(self->config.base_address,B);
       return (uz_myIP_hw_read_C(self->config.base_address));
   }

26.  We now have a working and fully tested driver for our IP-Core! 

.. warning:: While we tested our functions with different error cases and made sure they behave as expected, we omitted the fact that the multiplication can overflow. This is especially tricky in this case since the multiplication is implemented in hardware. Thus the rules for C do not apply to it. There are two ways to handle this: implement the hardware multiplication to saturate on overflow or check if the multiplication will overflow before writing to the PL. The way :ref:`AXI_testIP` is implemented will *wrap* on overflow, i.e., 2147483647*2 will be a negative value. Keep this concept in mind for real IP-Cores that you implement. Additionally, prevent the software driver from writing values that are out of range to the IP-Core, e.g., if the register only uses 10 bit. Note that the AXI data width is always 32-bit.

Integration in Vitis
====================

1. Open Vitis
2. (if not already done) Run the tcl script to generate the workspace (:ref:`tcl_scripts`)
3. Navigate to the Baremetal code
4. Create the file ``uz_myIP_testebench.h`` in the ``include`` folder

.. code-block:: c
   :linenos:
   :caption: ``uz_myIP_testbench.h``

   #pragma once

   void uz_myIP_testbench(void);

5. Create the file ``uz_myIP_testebench.c`` in the ``sw`` folder. Note how the code is basically the same as the test ``test_uz_myIP2_test_A_times_B_equals_C`` without the assertions and ceedling function calls.

.. code-block:: c
   :linenos:
   :caption: ``uz_myIP_testbench.c``

   #include "../include/uz_myIP_testbench.h"
   #include "../uz/uz_HAL.h"
   #include "../IP_Cores/uz_myIP/uz_myIP.h"
   #include "xparameters.h"
   
   void uz_myIP_testbench(void){
       struct uz_myIP_config_t config={
            .base_address= XPAR_UZ_AXI_TESTIP_0_BASEADDR,
            .ip_clk_frequency_Hz=100000000U
       };
       uz_myIP_t *instance = uz_myIP_init(config);
       int32_t a = -10;
       int32_t b = 200;
       int32_t c = uz_myIP_multiply(instance, a, b);
       uz_printf("Hardware multiply: %i, Software multiply: %i\n", c, a*b);
       if (c==a*b){
         uz_printf("Success: hardware and software multiply are equal! \n");
       }else{
         uz_printf("Fail: hardware and software multiply are NOT equal! \n");
       }
   
       while(1){
         // do nothing and loop forever
       }
   }
   

6. Add ``#define UZ_MYIP_MAX_INSTANCES 1U`` between ``ifndef TEST`` and the first ``#endif`` to use one instance of the module in the software.
7. Build the software.
8. Include ``#include "include/uz_myIP_testbench.h"`` in ``main.c`` (Baremetal R5) and call ``uz_myIP_testbench();`` before the ISR is initialized!
9. Connected the serial port to the Vitis Serial Terminal
10. Run the UltraZohm. The success message should be printed to the Vitis Serial Terminal.