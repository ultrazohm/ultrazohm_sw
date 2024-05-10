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
in ``uz_global_configuration.h`` set the respective ``#define`` to ``TRUE``

.. code-block:: C

    // Experimental feature - read docs before use
    #define USE_A53_AS_ACCELERATOR_FOR_R5_ISR		TRUE



Shared header file
******************
In the :ref:`shared header file <datamoverSharedHeader>` are two ``structs``. 
One for sharing data from the R5 (RPU) to the A53 (APU) ``RPU_to_APU_user_data_t`` and 
one for data from te A53 to the R5 ``APU_to_RPU_user_data_t``. Use those 
``structs`` and create variables within them as needed.

Send data R5 -> A53
*******************

Crunch the numbers
******************
In the ``isr.c`` on the A53, within the 

Return data A53 -> R5
*********************


Modification on A53
-------------------

in ``isr.c``

.. code-block:: c

   #include "xil_cache.h"
   #include "APU_RPU_shared.h"
   // create pointer of type struct javascope_data_t named javascope_data located at MEM_SHARED_START
   static struct javascope_data_t volatile * const javascope_data = (struct javascope_data_t*)MEM_SHARED_START;

   void Transfer_ipc_Intr_Handler(void *data){
     // flush data cache to make sure shared memory is updated
     Xil_DCacheFlushRange(MEM_SHARED_START, JAVASCOPE_DATA_SIZE_2POW);
     // copy JAVASCOPE_DATA into queue to ethernet thread
     xQueueSendToBackFromISR(OsziData_queue, JAVASCOPE_DATA, &xHigherPriorityTaskWoken);
   }


Known issues
---------------

See also
"""""""""""""""



