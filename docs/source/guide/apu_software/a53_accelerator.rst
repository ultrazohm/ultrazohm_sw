.. _A53accelerator:

=========================================
A53 as accelerator for code in the R5 ISR 
=========================================


Although very powerful, sometimes the computing power of the R5 processor is not enough.   

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
          B --> C(IPI from R5 to A53)
          C -->E(R5: Poll for acknowledge <br> of IPI on A53)
      end
          E -->|wait until A53 is finished|E
          E --> |ack|G
      subgraph A53: Transfer_ipc_Intr_Handler
          C --> F[A53: crunch the numbers, <br> write results to OCM Bank 2]
      end
          F -->|finished, set ack| G(R5: Invalidate <br> OCM Bank 2)
      subgraph R5: Javascope_update
          G --> H(R5: Read results <br> from A53)
      end
      subgraph R5: ISR_Control
          H --> J(R5: ISR stuff)
          J --> K(uz_systemTime_ISR_Toc)
       end
          X .-> |USER MUST ENSURE THAT ALL COMPUTATIONS ARE FINISHED WITHIN AVAILABLE TIME !!!|K	


Shared header file
------------------

Please refer to :ref:`description of the shared header file <datamoverSharedHeader>` on more information about ``javascope_data_t``.

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



