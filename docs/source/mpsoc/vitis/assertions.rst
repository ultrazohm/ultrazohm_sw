.. _assertions:

==========
Assertions
==========

The UltraZohm uses assertions to handle errors.

.. warning:: The UltraZohm error handling follows the concept to fail loudly.

How to use
----------

Use assertions to guarantee that the conditions and limits of a function are met at runtime.
Use ``uz_assert()`` or ``uz_assertNotNull()`` from the :ref:`HAL`.

Example code:

.. code :: c

    #include "uz/HAL.h"
    #define LIMIT 10

    function void fnc(int *foo, int bar){
        uz_assertNotNull(foo);
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