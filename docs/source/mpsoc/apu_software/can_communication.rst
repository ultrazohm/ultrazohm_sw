.. _can_communication:

=====================
Communication via CAN 
=====================

.. mermaid::
    :align: center
    :caption: Signal flow of data

    graph LR
      subgraph Queue
          A(FIFO)
      end
      subgraph process_request_thread
          A-.waits.->B(restructure data)-->C(ethernet frame)
          C-->D(lwip_write)
      end
      subgraph can_thread
          B(restructure data)-->E(create CAN frames)
          E-->F(can send)
      end

CAN-Communication-Thread
------------------------

The idea behind this thread is the ability to write each value of the SlowData-Array to a connected CAN-Bus. This software-extension will simplify the integration of the UltraZohm in existing testrigs, since every value from the UltraZohm can be given to superimposed control units.
To keep this CAN-Communication-thread simple and scalable, all needed information are either given in the included header-file or will be calculated during compile-time. So if you change the amount of the SlowData, the thread will adapt to the edited SlowData-Array.

.. code-block:: c
  :linenos:
  :caption: Adding Values to the SlowData-Array
  
  enum JS_SlowData {
	JSSD_ZEROVALUE=0,
	JSSD_FLOAT_SecondsSinceSystemStart,
    .
    .
    .
	JSSD_FLOAT_totalRotorInertia,
	JSSD_FLOAT_Test1,       // New Value
	JSSD_FLOAT_Test2,       // New Value
	JSSD_FLOAT_Test3,       // New Value
	JSSD_ENDMARKER
    };

A single CAN-Message contains two SlowData-Values, each has a length of four Bytes. To transmit float-values, the function 'CAN_Thread_SendSlowData' will simply shift the Value to send by the number of decimal-places specified in the header-file.
A pre-configured CAN-DBC/DBF-File with all standard-Variables of the UltraZohm can be found in the folder ``\ultrazohm_sw\vitis\CAN_Database``.

Shared header file
------------------

Please refer to :ref:`description of the shared header file <datamoverSharedHeader>` on more information about ``javascope_data_t``.

Defines and functions
---------------------

The CAN-Thread relies on the following defines and functions

.. doxygendefine:: ThreadDelay_CAN_Thread1

.. doxygendefine:: CAN_Msg_Control

.. doxygendefine:: CAN_Msg_Start

.. doxygendefine:: CAN_Msg_DecimalPlaces

.. doxygenfunction:: CAN_Thread_Init_CAN1

.. doxygenfunction:: CAN_Thread_SendSlowData

.. doxygenfunction:: CAN_Thread_CAN1


Known issues
---------------

* It's necessary to compile both Software-parts (FreeRTOS and Baremetal) if any change to the javascope.h is made.
* Javascope has to be connected to the UltraZohm to have the SlowData-Array synchronized to the CAN-Bus since in the ``process_request_thread`` the Data were received from the queue.

See also
"""""""""""""""
