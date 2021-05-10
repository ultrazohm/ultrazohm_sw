.. _software_development_guidlines:

===============================
Software Development Guidelines
===============================

The software development guidelines for the UltraZohm consists of:

1. :ref:`codingGuidelines` on how to develop software
2. :ref:`codingStyle` describes how to format the code visually
3. :ref:`exampleImplementation` for common code modules
4. :ref:`codingRules` to follow when writing code

The guidelines are based on concepts described by:

  - Clean Code [#CleanCode]_
  - Making Embedded Systems [#MakingEmbedded]_
  - Test-Driveen Development for Embedded C [#TDD]_
  - `Video series on Clean Code <https://www.youtube.com/watch?v=7EmboKQH8lM&ab_channel=UnityCoin>`_ by the author
  - Modern C [#ModernC]_
  - MISRA guidlines [#misra]_
  - `Linux kernel coding style <https://www.kernel.org/doc/html/v4.14/process/coding-style.html>`_ [#linuxCodingStyle]_
  - The C Programming Language [#TheCProgrammingLanguage]_

- Working through the sources is strongly recommended
- Feedback & questions regarding software guidelines are gathered in issue :issue:`96`


.. _codingGuidelines:

Guidelines
----------

- Write clean code [#CleanCode]_ (p. 2 ff):

  - Elegant & efficient
  - Logic should be straightforward
  - Minimal dependencies
  - Ease of maintenance
  - Clean code does one thing well
  - Simple and direct
  - Reads like well-written prose
  - Can be read and enhanced by a developer other than its original author
  - Has meaningful names
  - Clear and minimal API
  - Looks like it was written by someone who cares
  - Contains no duplication
  - *You know you are working on clean code when each routine you read turns out to be pretty much what you expect* (principle of least surprises)

- Do not make a mess
- Encapsulate modules [#MakingEmbedded]_ (p. 16)

  - Only expose relevant information through the interface (API)
  - Interface hides implementation details!
  - Objects are self-contained

- Object oriented programming in C

  - Object orientation is a property of code, not of the language
  - Use object orientated programming
  - Critical idea: data hiding
  - Hide the data in private variables
  - Use interfaces
  - Use structures / pointers to structures to pass it around as an object
  - Abstract the hardware

- No premature optimization!

  - If you think about optimization of the framework code of the UltraZohm, it is probably premature optimization
  - The compiler is better at optimization than a developer

Names
*****

- Write code to be readable by other humans
- Use intention revealing names, e.g., ``int pwm_frequency_kHz``
- Use pronounceable, searchable names [#CleanCode]_ (p.21) (e.g., not ``tmrctr`` for timerCounter)
- Encode physical units into variables and functions (``int time_in_seconds``, ``uz_systemTime_get_uptime_us``)
- Favor longer names to prevent misunderstandings (e.g., ``_min`` could be interpreted as minutes or minimum)
- Append units with ``_unit`` (``float id_A``, ``float pwm_frequency_kHz``)
- No encoding or Hungarian notation (prefixing the variable name by its data type) [#CleanCode]_ (p. 23)

  - Only exception are AXI-Ports in Simulink for HDL-Generation! (prefix these with ``axi_``)

- Classes (objects) have noun or noun phrase names (``uz_pwmModule``) [#CleanCode]_ (p. 25)
- Method (functions) have verb or verb phrases (they *do* things, e.g., ``uz_pwmModule_setDutyCycle(uint32_t dutyCycle)``)
- Naming convention:

  - Group composites with camel case (*ThisIsCamelCase*)
  - Encode relationships with underscore (e.g., a method of an object)
  - Everything is lower case except the capital latter in camel case and ``#defines`` which are in capital letters

Interface function names

  - Prefix interface functions with ``uz_`` to prevent name conflicts (lower case)
  - Name of the module in lower camel case (``uz_moduleName``)
  - Name of the function with underscores, group with in lower camel case where appropriate (``uz_moduleName_set_dutyCycle``)
  - Group multiple, similar functions with additional underscore
  
    - Example: ``uz_systemTime_get_uptime_seconds``, ``uz_systemTime_get_uptime_us``, ``uz_systemTime_get_uptime_minutes``

Functions
*********

- Functions should be small, even smaller than that.
- Do one thing
- One thing means one cannot extract any meaningful function from the existing function
- One level of abstraction per function
- Descriptive names, the function name tells you what it does
- Do not be afraid to make a name long
- Function arguments: less is better
- Use structs for more than two function arguments (e.g., config struct)

Error handling
**************

- Error handling is *one thing*
- Fail loudly with :ref:`assertions`

Comments
********

- Comments lie
- Why? Code changes and comments get outdated
- Comment only why code does things (intend), not how
- Do not comment bad code, rewrite it
- Explain yourself in code with small functions with meaningful names!
- Do not comment out code, delete it
- *But I want to have it for future reference* - that is what git and the docs are for

.. _codingStyle:

Coding style
------------

- Coding style is K&R except:

  - Opening braces of functions are in the same line (``int myFunction(int x) {``)
  - All control statements have braces (if, else, ..) [#misra]_ 

- Indentation is a tab with size 8 [#linuxCodingStyle]_
- Use Vitis autoformat function (``ctrl`` + ``shift`` + ``f``) to conform with coding style
- To use the UltraZohm coding style import the UltraZohm Vitis settings:
- In Vitis follow these steps:
    1. ``Window``
    2. ``Preferences``
    3. ``Import`` (bottom left) 
    4. ``Browse``
    5. ``ultrazohm_sw/vitis/ultrazohm_vitis_settings.epf``
    6. ``Finish``
    7. Restart Vitis
    8. (Optional): Change theme (Light/Dark)
    9. ``Window``
    10. ``Preferences``
    11. ``Additional`` -> ``General`` -> ``Appearance``
    12. Choose a ``Theme`` to adjust color palette

.. _exampleImplementation:

Example Implementations
-----------------------

Single-instance module
**********************

Encapsulates a object if only one object of the type can be present in the system.
This only applies to software modules that are hard-locked to specific hardware and does **not** apply to IP-Core drivers!
This means all initialization is done inside the module function, there is no initialization in code and nothing is passed to init except for configuration if necessary.

See the implementation of :ref:`systemTimeR5` for a reference implementation of a single-instance module.

Example interface for a LED [#TDD]_ (p. 194):

.. code-block:: c
  :linenos:
  :caption: Single-instance module

   void uz_led_init(void);
   void uz_led_turn_on(void);
   void uz_led_turn_off(void);
   void uz_led_set_toggle_frequency_Hz(float blink_frequency_in_Hz);
   float uz_led_get_toggle_frequency_Hz(void);

Multiple-instance module
************************

Encapsulates a module of which multiple instances can be used.
This is the default for IP-core drivers.
A full example implementation is located at ``ultrazohm_sw/vitis/Sandbox/uz_ipCoreDriver_template``.

- The ``allocateAndInit`` function is used to get a handle (pointer) to an instance of the IP-core
- To allocate multiple instances a specific allocator function has to be called individually
- Use meaningful names for allocator functions instead of ``_instance1``
- Pass the handle to the interface to use the specific instance (e.g., line 10)

.. code-block:: c
   :linenos:
   :caption: Example main for multiple-instance module (``uz_ipCoreDriver_testbench.c``)

    #include <stdio.h>
    #include "uz_ipCore.h"
    #include "uz_ipCore_staticAllocator.h"
    
    int main(){
        uz_ipCore* ipCore_handle_instance1=uz_ipCore_allocateAndInit_instance1();
        uz_ipCore* ipCore_handle_instance2=uz_ipCore_allocateAndInit_instance2();
        int var=10;
        uz_ipCore_set_variable(ipCore_handle_instance1,var);
        uz_ipCore_set_variable(ipCore_handle_instance2,var*2);
        int readback=uz_ipCore_get_variable(ipCore_handle_instance1);
        int readback2=uz_ipCore_get_variable(ipCore_handle_instance2);
        assert(readback==var);
        assert(readback2==var*2);
    }

- All instances of the module are declared as a static variable in the static allocator (:ref:`static-allocator`)
- The ipCore header as well as the ``_private`` header are included in the allocator
- The ``_private`` header holds the struct definition (see :ref:`private-header`).
- The inclusion of the private header in the allocator is required since the compiler needs to know the size of the object.
- The initialization of the object is done using designators
- This enables the usage of the ``const`` qualifier for configuration parameters that do not change at runtime (e.g., base address of IP-Core)

.. code-block:: c
   :linenos:
   :name: static-allocator
   :caption: Static allocator of IP-Core driver (``uz_ipCore_staticAllocator.c``)

   #include "uz_ipCore_staticAllocator.h"
   
   static uz_ipCore ipCore_instance1={
     .base_address=0,
     .variable=0
   };
   
   static uz_ipCore ipCore_instance2={
     .base_address=1,
     .variable=0
   };
   
   uz_ipCore* uz_ipCore_allocateAndInit_instance1(void){
     return (uz_ipCore_init(&ipCore_instance1) );
   }
   
   uz_ipCore* uz_ipCore_allocateAndInit_instance2(void){
     return (uz_ipCore_init(&ipCore_instance2) );
   }

.. code-block:: c
   :linenos:
   :name: private-header
   :caption: Private header for struct definition (``uz_ipCore_private.h``)

   #pragma once
   #include <stdint.h>
   #include <stdbool.h>

   struct uz_ipCore{
     const uint32_t base_address;
     const uint32_t ip_clk_frequency_Hz;
     bool is_ready;
     int variable; 
   };

.. code-block:: c
   :linenos:
   :name: example-implementation
   :caption: Implementation of the IP-Core driver (``uz_ipCore.c``)

   #include "uz_ipCore.h"
   #include "uz_ipCore_private.h"
   #include "../../uz/uz_HAL.h"
   
   uz_ipCore* uz_ipCore_init(uz_ipCore_handle self){
     uz_assert_not_NULL(self); // prevent calls with NULL-pointer
     uz_assert(!self->is_ready); // prevent double initialization
     self->is_ready=true; // module is ready for usage with other functions
     return (self);
   }
   
    void uz_ipCore_set_variable(uz_ipCore_handle self,int variable){
      uz_assert_not_NULL(self);
      uz_assert(self->is_ready);
      self->variable=variable;
   }
   
   int uz_ipCore_get_variable(uz_ipCore_handle self){
      uz_assert_not_NULL(self);
      uz_assert(self->is_ready);
      return (self->variable);
   }

.. code-block:: c
   :linenos:
   :name: example-header
   :caption: Header of the IP-core driver (``uz_ipCore.h``)

   #pragma once
   #include <stdint.h>
   #include <stdio.h>
   #include <stdlib.h>
   
   typedef struct uz_ipCore uz_ipCore;
   
   uz_ipCore* uz_ipCore_init(uz_ipCore* self);
   void uz_ipCore_set_variable(uz_ipCore* self,int variable);
   int uz_ipCore_get_variable(uz_ipCore* self);



.. _codingRules:

Coding rules
------------

.. csv-table:: table
    :file: coding_rules.csv
    :widths: 1 50 50 50
    :header-rows: 1

Sources
-------

.. [#CleanCode] Clean Code, A Handbook of Agile Software Craftsmanship, Robert C Martin, 2009
.. [#MakingEmbedded] Making Embedded Systems, Elecia White, 2011
.. [#TDD] Test-Driven Development for Embedded C, James W. Grenning, 2011
.. [#ModernC] `Modern C, Jens Gusted <https://gforge.inria.fr/frs/download.php/latestfile/5298/ModernC.pdf>`_
.. [#misra] Guidelines for the Use of the C Language in Critical Systems, ISBN 978-1-906400-10-1 (paperback), ISBN 978-1-906400-11-8 (PDF), March 2013.
.. [#cert] `SEI CERT C Coding Standard <https://wiki.sei.cmu.edu/confluence/display/c/3+Recommendations>`_
.. [#linuxCodingStyle] `Linux kernel coding style <https://www.kernel.org/doc/html/v4.14/process/coding-style.html>`_
.. [#TheCProgrammingLanguage] The C Programming Language, Kernighan, Ritchie, 2000


