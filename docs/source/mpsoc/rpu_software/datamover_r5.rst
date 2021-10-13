.. _datamoverR5:

=====================
Data mover R5 to A53
=====================


Idea
----

The goal is to move sampled data from the R5 processor via the A53 to the host PC running a GUI, which displays and logs the data.
Important requirements are 


- no data is lost, all samples are transfered and logged
- on the R5 side, it has to run synchronous to the control ISR, since all the data is updated in each call of the ISR, i.e., in each time step.
- the sampling frequency can be up 100kHz
- minimal effort for R5 to avoid stealing computation time from the control ISR

At the same time, a data path in the opposite direction GUI -> A53 -> R5 is needed to enable and disable the system and set references. This path is not time critical and is described in detail at the end of this section.

Please see also the matching :ref:`description of the APU code <datamoverA53>`. ,

.. mermaid::
    :align: center
    :caption: Signal flow of data mover

    graph LR
      subgraph ISR_Control
          A(JavaScope_update)
      end 
      subgraph js_fetchData
          A-->B(Copy Data to Shared Memory)
          B-->C(Flush Cache)
          C-->D(IPI to A53)
      end

Shared header file
------------------
.. _datamoverSharedHeader:

To this end, the shared  header file ``APU_RPU_shared.h`` located at ``vitis\software\shared`` is included in both software projects, i.e., R5 and A53. 
The shared memory can be in OCM or DDR, here we use the OCM (on-chip memory) of the A53.

.. code-block:: c

   #define MEM_SHARED_START          0xFFFF0000
   #define JS_CHANNELS               20
   #define JAVASCOPE_DATA_SIZE_2POW  128

   struct javascope_data_t
   {
      uint32_t    status;
      uint32_t    slowDataContent;
      uint32_t    slowDataID;
      float       scope_ch[JS_CHANNELS];
   };

It defines the following:

- ``struct javascope_data_t`` which will be passed from R5 to A53, 
- the number float channels ``JS_CHANNELS`` inside this struct, and 
- the start address of the shared memory ``MEM_SHARED_START`` used to pass data from R5 to A53. 


Write to shared memory and trigger APU interrupt
------------------------------------------------

Inside  ``javascope.c`` a pointer to type ``struct javascope_data_t`` named ``javascope_data`` is defined and initialized to point to the shared memory starting address ``MEM_SHARED_START``. 

In function ``js_fetchData()``,

- the selected data in ``js_ch_selected`` is written to ``javascope_data``
- Also ``slowDataID``, ``slowDataContent``, ``js_status_BareToRTOS`` are copied to to ``javascope_data``
- The shared memory is cached and the above mentioned changes are not visible to the APU yet. Therefore, we have to flush the cache for the size of ``javascope_data``. This triggers the memory controller to write the updated ``javascope_data`` into the actual OCM.
- Afterwards, with ``XIpiPsu_TriggerIpi``, the IPI (inter processor interrupt), is used to trigger the execution of ``Transfer_ipc_Intr_Handler`` on the APU, as described in the :ref:`section on the APU data mover<datamoverA53>`

.. code-block:: c

   #include "xil_cache.h"
   #include "APU_RPU_shared.h"
   // create pointer of type struct javascope_data_t named javascope_data located at MEM_SHARED_START
   static struct javascope_data_t volatile * const javascope_data = (struct javascope_data_t*)MEM_SHARED_START;

   void js_fetchData(){
      // write data to shared memory
      for(int j=0; j<JS_CHANNELS; j++){
         javascope_data->scope_ch[j] = *js_ch_selected[j];
      }
      javascope_data->slowDataID      = js_cnt_slowData;
      javascope_data->slowDataContent = js_slowDataArray[js_cnt_slowData].u;
      javascope_data->status          = js_status_BareToRTOS;

      // flush data cache of shared memory region to make sure shared memory is updated
      Xil_DCacheFlushRange(MEM_SHARED_START, JAVASCOPE_DATA_SIZE_2POW);
      
     //Trigger IPI interrupt to APU
     status = XIpiPsu_TriggerIpi(&INTCInst_IPI,XPAR_XIPIPS_TARGET_PSU_CORTEXA53_0_CH0_MASK);
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

In ``javascope.c`` in function ``JavaScope_initalize(DS_Data* data)``, the array ``float * js_ch_observable`` is initialized and holds the pointers to all observable data.

.. code-block:: c

   float *js_ch_observable[JSO_ENDMARKER];
   
   int JavaScope_initalize(DS_Data* data)
   {
      js_ch_observable[JSO_Speed_rpm]  = &data->av.mechanicalRotorSpeed;
      js_ch_observable[JSO_ia]         = &data->av.I_U;
      js_ch_observable[JSO_ib]         = &data->av.I_V;
      // ... //
   }

In ``ipc_ARM.c``, the selected channels are written to ``js_ch_selected``. The selection is decided in the :ref:`JavaScope application <JavaScope>`.  

.. code-block:: C

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

Known issues
---------------

See also
"""""""""""""""



