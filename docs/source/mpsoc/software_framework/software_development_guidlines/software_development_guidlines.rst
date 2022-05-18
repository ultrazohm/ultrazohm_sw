.. _software_development_guidelines:

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

- Working through the sources is recommended

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
- Use pronounceable, searchable names [#CleanCode]_ (p.21) (e.g., not ``tmrctr`` for ``timer_counter``)
- Encode physical units into variables and functions (``int time_in_seconds``, ``uz_systemTime_get_uptime_us``)
- Favor longer names to prevent misunderstandings (e.g., ``_min`` could be interpreted as minutes or minimum)
- Append units with ``_unit`` (``float id_A``, ``float pwm_frequency_kHz``)
- No encoding of information that the compiler *knows* (e.g., Hungarian notation) (prefixing the variable name by its data type) [#CleanCode]_ (p. 23)

  - Exception are AXI-Ports in Simulink for HDL-Generation! (prefix these with ``axi_`` to prevent name conflicts)
  - Structs that are used with a typedef end with ``_t``
  - AXI read/write functions (the C compiler can not know what data type the PL write to a register)

- Classes (objects) have noun or noun phrase names (``uz_pwmModule``) [#CleanCode]_ (p. 25)
- Method (functions) have verb or verb phrases (they *do* things, e.g., ``uz_pwmModule_set_duty_cycle(uint32_t duty_cycle)``)
- Naming convention:

  - Group composites of the object name with lower case camel case (*pwmModule*)
  - Use snake_case for everything else
  - Encode relationships with underscore (e.g., a method of an object)
  - Everything is lower case except the capital latter in camel case and ``#defines`` which are in capital letters

Interface function names

  - Prefix interface functions with ``uz_`` to prevent name conflicts (lower case)
  - Name of the module in lower camel case (``uz_moduleName``)
  - Name of the function with underscores (``uz_moduleName_set_duty_cycle``)
  - Group multiple, similar functions with additional underscore
  
    - Example: ``uz_systemTime_get_uptime_seconds``, ``uz_systemTime_get_uptime_us``, ``uz_systemTime_get_uptime_minutes``

Functions
*********

- Functions should be small
- Do one thing
- One thing means one cannot extract any meaningful function from the existing function
- One level of abstraction per function
- Descriptive names, the function name tells you what it does
- Do not be afraid to make a name long
- Function arguments: less is better
- Use structs for more than two function arguments (e.g., a config struct)

Error handling
**************

- Error handling is *one thing*
- Fail loudly with :ref:`assertions`

Comments
********

- Comments lie because code changes and comments get outdated
- Comment only why code does things (intend), not how
- Do not comment bad code, rewrite it
- Explain yourself in code with small functions with meaningful names!
- Do not comment out code, delete it!
- *But I want to have it for future reference* - that is what git and the docs are for
- Use :ref:`doxygen` to document the interface of a module

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

Static code analysis
--------------------

Static code analysis checks the source code for potential errors and problems.
We use `cppcheck <https://github.com/danmar/cppcheck>`_ , which is also run in the bitbucket pipeline (see :ref:`ci_static_code_check`)
Usage with the :ref:`vscode_remote_container` in a terminal to check all files in `src` folder (recursive):

::

    cppcheck vitis/software/Baremetal/src/
    cppcheck --addon=misra vitis/software/Baremetal/src/
    cppcheck --addon=cert vitis/software/Baremetal/src/

You can specify a path to only check your currently developed files.
Adding ``--addon=misra`` checks for violations of [#MISRA]_ coding rules.
The output only gives the number of the violated rule, you have to obtain an copy to get readable information.
Adding ``--addon=cert`` checks for violations of [#CERT]_ coding rules.

Additional static code analyser that are not implemented for the UltraZohm project:

- `flawfinder <https://github.com/david-a-wheeler/flawfinder>`_
- `OCLint <https://github.com/oclint/oclint>`_
- `lizard <https://github.com/terryyin/lizard>`_
- `flawfinder list of other tools <https://dwheeler.com/essays/static-analysis-tools.html>`_
- `Infer <https://fbinfer.com/>`_


.. _exampleImplementation:

Example Implementations
-----------------------

Single-instance module
**********************

Encapsulates an object if only one instance of the module can be present in the system.
This only applies to software modules that are hard-coupled to specific hardware and does **not** apply to IP-Core drivers!
This means all initialization is done inside the module function, there is no initialization in code and nothing is passed to init except for configuration if necessary.
All required data of the module is declared in the implementation and no data is leaked outside of the module.
Functions that are only required internally are declared ``static``.
The module offers a public interface in its header.

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
A full example implementation is located at ``ultrazohm_sw/vitis/software/Baremetal/src/IP_Cores/uz_myIP2`` (see :ref:`how_to_create_ipcore_driver`).

- The implementation scheme uses  opaque data types to hide the data of the object
- The ``_init`` function is used to initialize and configure the object
- The ``_init`` function returns a handle to the object, which has to be passed to the functions of the module
- A public interface in the header is used to use the module
- A pointer to the object is passed as the first argument of all functions in the public interface (except initialization)

.. _static_memory_allocation:

Static memory allocation
------------------------

Modules of which multiple instances can exist in the code require a specific way to allocate memory.
This allocation must be facilitated in the implementation (``.c``) to enable the usage of opage data types to hide the data of the object.
The default implementation scheme would be to use ``malloc`` for dynamic memory allocation at run time, which must not be done due to coding rule 35 (forbidden by MISRA rule 21.3 [#misra]_).
This is solved by using a static allocation scheme.
A local memory pool (file scope) is allocated in the implementation and pointers to these instances are returned by an allocation function.

- The header ``uz_global_configuration.h`` holds a define for every multi-instance module that configures how many instances will be used.
- A counter at file scope (static variable ``instance_counter``)
- A memory pool ``instances`` with file scope
- The function ``uz_wavegen_allocation`` which has to be called from the ``_init`` function without arguments and returns a pointer to an unused instance of the object

.. code-block:: c
   :linenos:
   :caption: Static allocation of memory with opaque data type 

   #include "../uz_global_configuration.h"
   #if myIP_MAX_INSTANCES > 0U
   #include <stdbool.h>
   #include "myIP.h"
   
   struct myIP_t {
    bool is_ready;
   };
   
   static uint32_t instance_counter = 0U;
   static myIP_t instances[myIP_MAX_INSTANCES] = { 0 };
   
   static myIP_t* uz_wavegen_allocation(void);
   
   static myIP_t* uz_wavegen_allocation(void){
    uz_assert(instance_counter < UZ_WAVEGEN_CHIRP_MAX_INSTANCES);
    myIP_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
   }

   myIP_t* uz_wavegen_chirp_init() {
     myIP_t* self = uz_wavegen_allocation();
     // more initialization code, configure the object
     return (self);
   }




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


