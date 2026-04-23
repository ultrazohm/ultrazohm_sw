.. _datamoverA53:

=====================
Data mover: A53 side
=====================


Please refer first to the :ref:`description of the RPU code <datamoverR5>`.

.. mermaid::
    :align: center
    :caption: A53-side view of the data mover

    graph TB
      subgraph R5ISR["R5: ISR_Control"]
          r5update[JavaScope_update] --> r5ipi[Trigger IPI to A53]
      end

      subgraph ISR["APU ISR: APU_IPI_ISR"]
          ipi([IPI from R5]) --> read[Invalidate cache\nread javascope_data_t]
          read --> check{Client\nactive?}
          check -- no --> drop([skip])
          check -- yes --> enq[enqueue sample]
          read --> pop[pop command]
          pop -- command --> reply([Return command to R5])
          pop -- empty --> nop([Return no-op to R5])
      end

      r5ipi --> ipi
      enq --> jsQ[(js_queue)]
      ctrlQ[(js_control_queue)] --> pop

      subgraph TCP["TCP worker: process_request_thread"]
          jsQ --> batch[Collect full batch]
          batch --> send([Pack & lwip_send])
          tcpIn([TCP stream]) --> asm[Reassemble APU_to_RPU_t]
          asm --> push[enqueue command]
          push --> ctrlQ
      end

      


Shared header file
------------------

Please refer to the :ref:`description of the shared header file <datamoverSharedHeader>` for more information about ``javascope_data_t``.

Current implementation on A53
-----------------------------

The A53 data mover has a streaming path from the R5 to the TCP socket and a control path from the TCP socket back to the R5.

The A53 implementation is split into a fast ISR path and a TCP worker path.

Streaming path
""""""""""""""

- ``APU_IPI_ISR`` is triggered by the IPI issued from ``ISR_Control`` on the R5, so its sample handling runs synchronously with the R5 control ISR.
- ``APU_IPI_ISR`` invalidates the cache lines for ``MEM_SHARED_START_OCM_BANK_3_JAVASCOPE``, reads the current ``javascope_data_t`` sample, and appends it to ``js_queue`` only while a JavaScope client is connected.
- The ISR updates the local ``javascope_data_status`` mirror and only calls ``portYIELD_FROM_ISR`` when the queue depth reaches one full batch, i.e. ``JS_SAMPLES_PER_PACKET`` samples.
- ``process_request_thread`` only starts building an Ethernet payload once at least one full batch is queued.
- The queued samples are packed into one ``NetworkSendStruct`` and sent with non-blocking ``lwip_send``, so streaming does not depend on an immediate receive-side reply from the TCP client.
- Partial writes are tracked with ``tx_pending_offset`` and retried until the whole frame has been transmitted.

Control path
""""""""""""

- ``process_request_thread`` reads the JavaScope control connection with non-blocking ``lwip_recv`` and treats the incoming data as a TCP byte stream rather than as one message per ``recv`` call.
- Complete ``APU_to_RPU_t`` messages are reassembled from the byte stream, while trailing partial bytes are kept in a buffer for the next ``lwip_recv`` call.
- Reassembled control messages are queued in ``js_control_queue`` for the ISR-to-R5 path.
- ``APU_IPI_ISR`` forwards at most one command from ``js_control_queue`` to the R5 per ISR invocation.
- If no command is pending, the ISR returns an explicit no-op ``{id = 0, value = 0.0f}`` so that the R5 does not accidentally process an old command again.
- If ``js_control_queue`` is full, newly received control messages are dropped and logged via ``uz_printf`` instead of blocking the TCP worker.

Connection and recovery behavior
""""""""""""""""""""""""""""""""

- ``application_thread`` and ``process_request_thread`` enforce a single active JavaScope client at a time using atomic replace/release helpers around ``js_connection_established``.
- When a new client becomes active, both ``js_queue`` and ``js_control_queue`` are reset so that no stale samples or commands survive the reconnect.
- ``js_queue`` holds ``JS_QUEUE_SIZE_ELEMENTS`` = 1,000,000 samples, which corresponds to 100 s of buffering at 10 kHz. 
- If ``js_queue`` overflows, the ISR increments the dropped counter and requests a purge. The TCP worker then resets the queue, reports how many samples were dropped or purged, and resumes real-time streaming.
- If the TCP send buffer is full, the worker waits with ``lwip_select`` instead of busy-spinning. If transmission makes no progress for ``JS_TX_STALL_TIMEOUT_TICKS``, the socket is closed as stale.
- If ``USE_A53_AS_ACCELERATOR_FOR_R5_ISR`` is enabled, the A53 also exchanges user data with the R5 via OCM banks 1 and 2, using cache invalidate and flush operations around those shared-memory accesses.


See also
--------

- :ref:`Data mover: R5 side <datamoverR5>`
- :ref:`A53 as accelerator for R5 ISR <A53accelerator>`
- :ref:`JavaScope GUI <JavaScope>`

