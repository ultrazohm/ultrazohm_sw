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
- Encode physical units into variables and functions (``int time_s``, ``uz_systemTime_getUptime_us``)
- Append units with ``_unit`` (``float id_A``, ``float pwmFrequency_kHz``)
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
  - Name of the function in lower camel case(``uz_moduleName_setDutyCycle``)
  - (Optional) Group multiple, similar functions with additional underscore
  
    - Example: ``uz_systemTime_getUptime_seconds``, ``uz_systemTime_getUptime_us``, ``uz_systemTime_getUptime_minutes``

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

- Import UltraZohm settings for Vitis
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

- Use Vitis autoformat function (``ctrl`` + ``shift`` + ``f``) to conform with coding style


.. _exampleImplementation:

Example Implementations
-----------------------

Single-instance module
**********************

Encapsulates a object if only one object of the type can be present in the system.
This only applies to software modules that are hard-locked to specific hardware and does **not** apply to IP-Core drivers!
This means all initialization is done inside the module function, there is no initialization in code and nothing is passed to init except for configuration if necessary.

See the implementation of :ref:`systemTimeR5` for a reference implementation of a single-instance module.

Example interface from [#TDD]_ (p. 194):

.. code-block:: c

   void module_init(void);
   void module_TurnOn(void);
   void module_TurnOff(void);
   void module_SetDeadTime(float DeadTime);
   float module_GetDeadTime();

Multiple-instance module
************************

Encapsulates a module and lets you create multiple instances of the module / object, e.g., IP-core drivers.

In a header ``uz_MyIp.h``:

.. code-block:: c

   #include <stdint.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include "hardwareAdr.h"
   #include "../../uz/uz_HAL.h"
   
   typedef struct uz_myIp uz_myIp;
   typedef uz_myIp* uz_myIp_handle;
   
   uz_myIp_handle uz_MyIp_init(uint32_t baseAddr);
   void uz_myIp_setVariable(uz_MyIp_handle self,int variable);
   int uz_myIp_getVariable(uz_MyIp_handle self);


In ``uz_MyIp.c``:

.. code-block:: c

   #include "uz_MyIp.h"
      
   struct uz_MyIp{
     uint32_t baseAddr;
     int variable; 
   };
   
   uz_MyIp_handle uz_MyIp_init(uint32_t baseAddr){
     uz_assertNotNull(baseAddr);
     uz_MyIp_handle self=malloc(sizeof(uz_MyIp));
     uz_assertNotNull(self);
     self->baseAddr=baseAddr;
     return self;
    }
   
    void uz_MyIp_setVariable(uz_MyIp_handle self,int variable){
      uz_assertNotNull(self);
      self->variable=variable;
    }
   
    int uz_MyIp_getVariable(uz_MyIp_handle self){
      uz_assertNotNull(self);
      return (self->variable);
    };

Usage:

.. code-block:: C

   uz_MyIp_handle MyIp=uz_MyIp_init(baseAddr);
   int var=10;
   uz_MyIp_setVariable(MyIp,var);
   int readback=0;
   readback=uz_MyIp_getVariable(MyIp);

See ``vitis/Sandbox/MyIp`` for an example implementation.

.. _codingRules:

Coding rules
------------

.. csv-table:: table
    :file: codingRules.csv
    :widths: 3 50 50 30
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


