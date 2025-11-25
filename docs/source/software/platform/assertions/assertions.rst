.. _assertions:

==========
Assertions
==========

The UltraZohm uses assertions to handle errors.

.. warning:: The UltraZohm error handling follows the concept to fail loudly, i.e., all assertions stop the processor and require a power cycle (and code changes to fix the bug that caused the failing assertion).

Reference
---------

.. doxygendefine:: uz_assert

.. doxygendefine:: uz_assert_not_NULL

.. doxygendefine:: uz_assert_not_zero_uint32

.. doxygendefine:: uz_assert_not_zero_int32

.. doxygendefine:: uz_assert_not_zero_int

.. doxygendefine:: uz_assert_not_zero_unsigned_int

.. doxygendefine:: uz_assert_false

How to use
----------

Use assertions to guarantee that the conditions and limits of a function are met at runtime.
Use ``uz_assert()`` or ``uz_assert_not_NULL()`` from the :ref:`HAL`.

Example code:

.. code :: c

    #include "uz/HAL.h"
    #define LIMIT 10

    function void fnc(int *foo, int bar){
        uz_assert_not_NULL(foo);
        uz_assert(bar < LIMIT);
        // do something 
    };


If the assertion fails, the following message is printed to the serial console to see where the assertions failed:

.. code :: c

    Assertion in file /home/ts/Dokumente/ultrazohm_testbench/ultrazohm_sw/vitis/software/Baremetal/src/main.c on line 135


Assertion callback
------------------

The assertion callback tells the UltraZohm to execute the function ``uz_assertCallback`` if an assertion fires:

.. code :: c

    Xil_AssertSetCallback((Xil_AssertCallback) uz_assertCallback);

The function ``uz_assertCallback`` prints the file and line to the terminal in which the assertion failed.
Furthermore,  the callback turns the system and the ISR off.
Use the Vitis Serial Terminal to display the messages.
After that, the system is kept in an infinite error loop.
To reset the error, you have to reboot.
Note that there is no error handling / exceptions since assertions are used to prevent wrong function calls which have to be fixed in the source code.
Common examples are the passing of ``NULL`` pointers or passing wrong arguments to init function (e.g. wrong base address, violation of min/max values). 

Implementation
--------------

The implementation relies on ``xil_assert.h`` (part of libmetal).
While ``xil_assert.h`` provides assert makros (e.g., ``Xil_AssertVoid``), these use ``return`` in the marko.
This results in multiple warnings, MISRA violations and causes bugs in functions that return a ``struct``.
Thus, we do not use them!
The ``uz_assert`` makro is *function like* but has to be implemented as a makro to use ``__FILE__`` and ``__LINE``.
The ``uz_assert`` makro is wraped in a ``do{..}while(0)`` statement to ensure the right behavior regarding ``;``

Further information:

- https://interrupt.memfault.com/blog/asserts-in-embedded-systems
- https://stackoverflow.com/questions/154136/why-use-apparently-meaningless-do-while-and-if-else-statements-in-macros
- https://github.com/zephyrproject-rtos/zephyr/blob/b8add4aa0b20b3b15c989ee1a03443ba154d06a7/include/sys/__assert.h#L54-L60
- https://wiki.sei.cmu.edu/confluence/display/c/PRE10-C.+Wrap+multistatement+macros+in+a+do-while+loop
