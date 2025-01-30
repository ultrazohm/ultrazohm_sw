.. _A53accelerator:

=============================
A53 as accelerator for R5 ISR 
=============================

.. warning::
    This is an experimental feature. Read the documentation and make 
    sure you understand its functionality. Make sure that the total 
    turnaround time of all computations stays within the limits of 
    the available interrupt computation time of the R5 processor. 
    There are no safety mechanisms to prevent the system from crashing.

Although very powerful, sometimes the computing power of the R5 processor is not enough.   
The purpose of the accelerator feature is to make use of the computing power 
of one of the A53 processors. This is achieved by incorporating the existing interrupt routine 
for handling the Javascope data on the A53 into the control loop and providing paths 
for sharing user data between the R5 and the A53 via the on-chip memory (OCM).

The flowchart below provides a brief overview of the process of one ISR cycle on the 
R5 processor, including the datapath incorporating the A53 processor. 
The purple colored blocks highlight the parts where the user has to interface with 
the process.

.. mermaid::
    :align: center
    :caption: Signal flow of A53 accelerator 
  
    flowchart TD
      subgraph R5: ISR_Control
          X(uz_SystemTime_ISR_Tic) -->Y(R5: ISR stuff) -->Z(Javascope_update)
      end
          Z --> A
      subgraph R5: Javascope_update
          A[R5: Write data to <br> OCM Bank 1] -->B(R5: Flush cache of <br> OCM Bank 1)
          style A fill:#f9f
          B --> C(IPI from R5 to A53)
          C -->E(R5: Poll for acknowledge <br> of IPI on A53)
      end
          E -->|wait until A53 is finished|E
          E --> |ack|G
      subgraph A53: Transfer_ipc_Intr_Handler
          C --> F[A53: crunch the numbers <br> with user data from OCM Bank 1, <br> write results to OCM Bank 2]
          style F fill:#f9f
          W(Handle Javascope data <br> for ethernet <br> transmission)
      end
          F -->|finished, set ack| G(R5: Invalidate <br> OCM Bank 2)
      subgraph R5: Javascope_update
          G --> H(R5: Read results <br> from A53)
          style H fill:#f9f
      end
      subgraph R5: ISR_Control
          H --> J(R5: ISR stuff)
          J --> K(uz_systemTime_ISR_Toc)
       end
          X .-> |USER MUST ENSURE THAT ALL COMPUTATIONS ARE FINISHED WITHIN AVAILABLE TIME !!!|K	


How to calculate stuff on the A53
---------------------------------
The following steps are required in order to use the feature:

Enable the feature
******************
In ``APU_RPU_shared.h`` set the respective ``#define`` to ``TRUE``

.. code-block:: C

    // Experimental feature - read docs before use
    #define USE_A53_AS_ACCELERATOR_FOR_R5_ISR		TRUE



Shared header file
******************
In the :ref:`shared header file <datamoverSharedHeader>` are two ``structs``. 
One for sharing data from the R5 (RPU) to the A53 (APU) ``RPU_to_APU_user_data_t`` and 
one for data from the A53 to the R5 ``APU_to_RPU_user_data_t``. Use those 
``structs`` and create variables within them as needed. As a basic example, an internal counter of 
the Javascope is already there and is sent from R5 to A53 and back. It is there for two reasons: 
First, to have a minimal working example, and second, to avoid empty structs, which is bad coding in C.


.. warning::
    Each shared struct is allocated on its own OCM Bank. Each bank has a size
    of 64 kB. User has to take care that both shared structs do not exceed this 
    limit


Send data R5 -> A53
*******************
In the R5 project ``sw/javascope.c`` within the function ``Javascope_update`` look for 
the lines where user data can be assigned to the ``rpu_to_apu_user_data`` struct.

.. code-block:: C

   #if (USE_A53_AS_ACCELERATOR_FOR_R5_ISR == TRUE)
   // write data to a53 in shared memory and flush cache
   rpu_to_apu_user_data->your_shared_data = your_local_data_on_r5; //this is just an example
   //...add further data
   
   Xil_DCacheFlushRange(MEM_SHARED_START_OCM_BANK_1_RPU_TO_APU, CACHE_FLUSH_SIZE_RPU_TO_APU);
   #endif
   
   

Crunch the numbers
******************
In the A53 FreeRTOS project ``src/sw/isr.c`` within the function ``Transfer_ipc_Intr_Handler`` 
look for the lines where you get the shared data from the R5 and calculate stuff you want 
the A53 to calculate faster.

.. code-block:: C

   // get data from r5 from shared memory
   local_copy_of_shared_data_from_r5 = rpu_to_apu_user_data->your_shared_data;
   
   /* do your computations that you want to accelerate here... */
   accelerated_computation_result = 2.0f*local_copy_of_shared_data_from_r5; // again just a useless example
   //...add further heavy calculations here
   

After that, the interrupt acknowledge flag is set by the A53 to tell the R5 that it can 
continue with it's own interrupt routine. Always keep in mind, that the R5 processor is waiting for this flag 
and will not continue until it is set. Therefore, the user can easily crash the system if the overall computational load 
becomes too high. It is the user's responsibility to make sure that this never happens. This makes the whole feature ``experimental``. 

Return data A53 -> R5
*********************
Still in the same function, write the results of your accelerated computations to the shared memory.

.. code-block:: C

   // write data to r5 in shared memory and flush cache
   apu_to_rpu_user_data->result_to_share = accelerated_computation_result;
   //...add further results to share here
   
   Xil_DCacheFlushRange( MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU, CACHE_FLUSH_SIZE_APU_TO_RPU);

   /* ...until here */


Use the results on the R5
*************************
Back on the R5 processor, in the ``Javascope_update`` function, look for the lines where you get the shared results of 
your calculations from the shared memory.

.. code-block:: C

   #if (USE_A53_AS_ACCELERATOR_FOR_R5_ISR == TRUE)
   // invalidate cache and read data from a53 shared memory
   Xil_DCacheInvalidateRange(MEM_SHARED_START_OCM_BANK_2_APU_TO_RPU, CACHE_FLUSH_SIZE_APU_TO_RPU);
   local_results_of_accelerated_calculations = apu_to_rpu_user_data->result_to_share; // still just an example
   #endif
   

Hints and best practices
------------------------
Here, one can find (and add) some hints and best practices for 
using the feature for specific applications.

Delay of one sample for the control signal
******************************************
The A53 accelerator feature uses the Javascope data path. The function ``JavaScope_update``
in the ``isr.c`` file on the R5 thus initiates all calculations outsourced to the A53. 
Since this is done by default at the end of the ISR on the R5, but the ``halfBridge$DutyCycle`` 
variables, i.e. the control signals for the PWM module, are already written in the R5 ISR, 
an offset of one ISR cycle must be taken into account when a controller is implemented on the A53. 
To avoid this, the ``Javascope_update`` function call can be moved within ``isr.c`` on the R5, 
for example to a point before the control signals are written to the PWM module. This means that 
the controller's control signals are first calculated on the A53 and output at the end of the present ISR cycle. 
When logging data with the Javascope, it must then be noted that the control signals in the logging 
now have a time delay of one ISR cycle.

Use uz library functions on the A53 processor
*********************************************
All uz library functions are only accessible to the R5 processor and are located 
in the folder ``\vitis\software\Baremetal\src\uz``. If you need one of them, 
copy the respective folder to ``\vitis\software\FreeRTOS\uz`` and recreate the 
vitis workspace via the tcl script. Afterwards the sources are available on the 
A53 processor.

Share data of types that are part of uz library functions
*********************************************************
For example, if you want to share data of the type ``uz_3ph_dq_t``, which is part of the ``uz_Transformation`` library function, 
this will not work. Even if copied to the correct folder as above, the compiler cannot handle the header file ``#include`` 
within the ``APU_RPU_shared.h`` file and throws an error. The fastest workaround for the example mentioned so far is to share single members of 
the ``uz_3ph_dq_t`` struct as separate ``float`` values.

Known issues
------------
It cannot run Crysis ;-)