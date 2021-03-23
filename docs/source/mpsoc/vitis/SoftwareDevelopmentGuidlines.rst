==============================
Software Development Guidlines
==============================

- Following is the attempt to distill some key concepts of [#CleanCode]_, [#MakingEmbedded]_ and [#TDD]_ and apply them to the UltraZohm for guidence on how to write code for it
- Read the books for the reasoning and more good information about programming!
- Watch the videos of uncle bob:
  
    - https://www.youtube.com/watch?v=7EmboKQH8lM&ab_channel=UnityCoin
  
- Take this as a general goal of how we try to make the software
- Feedback is more than welcome in issue :issue:`96`!
- Use the :ref:`HAL`
- Use :ref:`assertions`

General Rules
-------------

- Write clean code [#CleanCode]_ (p. 2 ff)
    - elegant & efficient
    - logic should be straightforward
    - minimal dependencies
    - ease of maintenance
    - Clean code does **one** thing well
    - simple and direct
    - reads like well-written prose
    - can be read and enhanced by a developer other than its original author
    - has meaningful names
    - clear and minimal API
    - Looks like it was written by someone who cares
    - contains no duplication
    - *you know you are working on clean code when each routine you read turns out to be pretty much what you expect* (priciple of least suprises)
- Do not make a mess
- Use intention revealing names
    - Example: ``int elapsedTimeInDays``
- Use pronouncable, searchable names [#CleanCode]_ (p.21)
- No encoding or hungarian notation [#CleanCode]_ (p. 23)
    - Only exception are AXI-Ports in Simulink for HDL-Generation! (prefix these with ``axi_``)
- Classes (objects) have non or noun phrase names (``Customer``, ``WikiPage``) (p. 25)
- Method (function) have verb or ver phrases (they *do** thinkgs, e.g., ``getAdcValue``)

- Encapsulate modules [#MakingEmbedded]_ (p. 16)
   - Only expose relevant information though the interface (API)
   - Interface hides implementation details!
   - Objects are self-contained

- **Object oriented programming in C**
    - Object orientation is a property of code, not of the language
    - Use object orientated programming
    - Critical idea: data hiding
    - I.e., hide the data in private variables
    - Use interfaces
    - Use structures / pointers to structures to pass it arround as an object
    - Abstract the hardware

- **No premature optimization!**
    - If you think about optimization of the framework code of the UltraZohm, it is probably premature optimization

Functions
*********

- Functions should be small
- Shoudl be smaller then that
- do **one** thing
- One level of abstraction per function
- Descriptive names, the function name tells you what it does
- Do not be afraid to make a name long
- Function Arguments
    - Zero > One > two > three
    - Use structs for more than two function arguments (e.g., config struct)

Error handling
**************

- Error handling is *one thing*
- Fail loudly with assertions

Comments
********

- Comments lie
- Why? Code changes and comments get outdated
- comment only why code does things (intend), not how
- do not comment bad code, rewrite it
- Explain yourself in code with small functions with meaningful names!
- **Never** comment something that a function does to another function in another file! This just means you have to restructure the code!
- **do not comment out code, delete it**
- *But I want to have it for future reference* - that is what git and the docs are for

Prefixing
*********

- We use ``uz_`` as a prefix for our functions such that there are no name conflicts with user code
- There are no real classes or namespaces in ``C``, thus this is our solution for this problem

SOLID Design
------------

`Five Deisgn priciples from Bob Martin <https://en.wikipedia.org/wiki/SOLID>`_: [#TDD]_ (p.189)

- **S**: Single Responsibility Principle
- **O**: Open Closed Principle
- **L**: Liskov Substituion Principle
- **I**: Interface Segregation Principle
- **D**: Dependency Inversion Principle

Applied to C
------------

Single-instance module
**********************

Encapsulates a object if only one object of the type can be present in the system.
This only applies to software modules that are hard-locked to specific hardware and does **not** apply to IP-Core drivers!
This means all initialization is done inside the module function, there is no initialization in code and nothing is passed to init except for configuration if necessary.

See the implementation of :ref:`systemTimeR5` for a reference implementation of a single-instance module.

Example interface from [#TDD]_ (p. 194):

.. code-block:: c

   void module_init(void)
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
   
   typedef struct uz_MyIp uz_MyIp;
   typedef uz_MyIp* uz_MyIp_handle;
   
   uz_MyIp_handle uz_MyIp_init(uint32_t baseAddr);
   void uz_MyIp_setVariable(uz_MyIp_handle self,int variable);
   int uz_MyIp_getVariable(uz_MyIp_handle self);


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

Sources
-------


.. [#CleanCode] Clean Code, A Handbook of Agile Software Craftsmanship, Robert C Martin, 2009
.. [#TDD] Test-Driven Development for Embedded C, James W. Grenning, 2011
.. [#MakingEmbedded] Making Embedded Systems, Elecia White, 2011

