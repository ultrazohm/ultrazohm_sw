.. _datamoverA53:

=====================
Data mover for scope 
=====================


Please refer first to the :ref:`description of the RPU code <datamoverA53>`.

.. mermaid::
    :align: center
    :caption: Signal flow of data mover

    graph LR
      subgraph Transfer_ipc_Intr_Handler
          E(IPI from R5)
          E-->F(Flush Cache)
          F-->G(Copy javascope_data)
      end 
      subgraph Queue
          G-->H
          H(FIFO)
      end
      subgraph process_request_thread
          H-.waits.->K(restructure data)-->L(ethernet frame)
          L-->M(lwip_write)
      end

      


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



