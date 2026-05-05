.. _datamoverR5:

=====================
Data mover: R5 side
=====================


Idea
----

The goal is to move sampled data from the R5 processor via the A53 to the host PC running a GUI, which displays and logs the data.
Important requirements are:

- minimal effort on the R5 to avoid stealing computation time from the control ISR
- synchronous operation with the control ISR, because the data is updated in each ISR call
- sampling frequencies up to 100 kHz
- buffering, batching, and TCP transport are handled on the A53 side

The current implementation prioritizes deterministic R5 behavior over lossless buffering on the A53.
If the Ethernet sender on the A53 falls behind long enough for its sample queue to overflow, the queued backlog is purged on the A53 so that streaming can return quickly to real-time operation.

At the same time, a data path in the opposite direction GUI -> A53 -> R5 is needed to enable and disable the system and set references.
On the A53, incoming TCP control messages are buffered and commands are forwarded one by one back to the R5 in each ISR call.
If no command is pending, the A53 returns an explicit no-op message so that the R5 receives the commands only once.

.. mermaid::
    :align: center
    :caption: R5-side view of the data mover

    graph LR
      subgraph ISR_Control
          JavaScope_update --> write["Write sample, slow data, and status to OCM bank 3"]
          write --> flush["Flush cache"]
          flush -->|"Trigger IPI to A53"| APU_IPI_ISR
          APU_IPI_ISR -->|"Read one A53 response message"| ipc_Control_func
      end

Shared header file
------------------
.. _datamoverSharedHeader:

To this end, the shared header file ``APU_RPU_shared.h`` located at ``vitis/software/shared`` is included in both software projects, i.e., R5 and A53.
The shared memory can be in OCM or DDR, here we use the `OCM (on-chip memory) <https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf#G20.364401>`_ of the A53.
The start address of the OCM is hard-coded into the software since it is specific to the `UltraScale+ memory map <https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf#G20.375357>`_.

.. literalinclude:: ../../../../vitis/software/shared/APU_RPU_shared.h
    :language: c

It defines the following:

- ``struct javascope_data_t`` which is written by the R5 and read by the A53
- ``struct APU_to_RPU_t`` for the command path from the A53 back to the R5
- the number of float channels ``JS_CHANNELS`` inside ``javascope_data_t``
- the OCM start addresses for the three shared-memory regions used by the R5 and A53


Current implementation on R5
----------------------------

Inside ``javascope.c``, ``JavaScope_update`` writes the current sample to OCM bank 3 at ``MEM_SHARED_START_OCM_BANK_3_JAVASCOPE``.
The function also reads the response message from the A53 and forwards it to ``ipc_Control_func``.

The R5-side sequence is:

- write the selected channels into ``javascope_data->scope_ch[]``
- write ``slowDataID``, ``slowDataContent``, and ``status`` into the same shared-memory struct
- flush the cache for OCM bank 3 so the A53 sees the updated sample
- trigger the IPI to the A53
- read exactly one ``APU_to_RPU_t`` response message from the A53 and pass it to ``ipc_Control_func``

If ``USE_A53_AS_ACCELERATOR_FOR_R5_ISR`` is enabled, the R5 additionally exchanges user data with the A53 via OCM banks 1 and 2 and polls for the IPI acknowledge before continuing.
If the accelerator mode is disabled, the R5 still reads the A53 response message but does not block on ``XIpiPsu_PollForAck``.

.. code-block:: c

   #include "xil_cache.h"
   #include "APU_RPU_shared.h"

   void JavaScope_update(DS_Data* data){
      struct javascope_data_t volatile * const javascope_data =
         (struct javascope_data_t*)MEM_SHARED_START_OCM_BANK_3_JAVASCOPE;
      struct APU_to_RPU_t Received_Data_from_A53 = {0};

      for(int j=0; j<JS_CHANNELS; j++){
         javascope_data->scope_ch[j] = *js_ch_selected[j];
      }
      javascope_data->slowDataID      = js_cnt_slowData;
      javascope_data->slowDataContent = *js_slowDataArray[js_cnt_slowData];
      javascope_data->status          = js_status_BareToRTOS;

      Xil_DCacheFlushRange(MEM_SHARED_START_OCM_BANK_3_JAVASCOPE, JAVASCOPE_DATA_SIZE);
      status = XIpiPsu_TriggerIpi(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK);

      status = XIpiPsu_ReadMessage(&IPI_instance,
                                   XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK,
                                   (u32*)(&Received_Data_from_A53),
                                   sizeof(Received_Data_from_A53)/sizeof(float),
                                   XIPIPSU_BUF_TYPE_RESP);
      ipc_Control_func(Received_Data_from_A53.id, Received_Data_from_A53.value, data);
   }


Selection of transmitted channels
---------------------------------

In ``javascope.h`` an enumeration variable ``enum JS_OberservableData`` is defined that is used to identify the observable data with a unique name.

.. code-block:: c

   enum JS_OberservableData {
      JSO_ZEROVALUE=0,
      JSO_ia,
      JSO_ib,
      JSO_Speed_rpm,
      //...//
      JSO_ENDMARKER
   };

In ``javascope.c`` in function ``JavaScope_initialize(DS_Data* data)``, the array ``float * js_ch_observable`` is initialized and holds the pointers to all observable data.

.. code-block:: c

   float *js_ch_observable[JSO_ENDMARKER];

   int JavaScope_initialize(DS_Data* data)
   {
      js_ch_observable[JSO_Speed_rpm]  = &data->av.mechanicalRotorSpeed;
      js_ch_observable[JSO_ia]         = &data->av.I_U;
      js_ch_observable[JSO_ib]         = &data->av.I_V;
      // ... //
   }

In ``ipc_ARM.c``, the selected channels are written to ``js_ch_selected``. The selection is decided in the :ref:`JavaScope application <JavaScope>`.

.. code-block:: c

   extern float *js_ch_observable[JSO_ENDMARKER];
   extern float *js_ch_selected[JS_CHANNELS];

   void ipc_Control_func(uint16_t msgId, uint16_t value, DS_Data* data)
   {
      if (msgId == 1) {}
      else if (msgId == 204) // SELECT_DATA_CH1_bits{
         if ( value >= 0 && value < JSO_ENDMARKER ) {
            js_ch_selected[0] = js_ch_observable[value];
         }
      }
      else if (msgId == 205) // SELECT_DATA_CH2_bits{
         if ( value >= 0 && value < JSO_ENDMARKER ){
            js_ch_selected[1] = js_ch_observable[value];
         }
      }
      // ... same for all other channels  //
   }

Where ``value`` relates to an entry in ``enum JS_OberservableData`` which is also known to the JavaScope application.
For instructions on adding new observable variables, see :ref:`JavaScope Customization <javascope_customizing>`.

See also
--------

- :ref:`Data mover: A53 side <datamoverA53>`
- :ref:`JavaScope GUI <JavaScope>`
- :ref:`JavaScope Customization <javascope_customizing>`
