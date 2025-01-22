.. _systemTimeR5:

==============
System Time R5
==============

The ``uz_SystemTime`` can be used to read the total uptime of the UltraZohm and the number of executed ISR routines on the R5 processor.
See ``uz/uz_SystemTime/uz_SystemTime.h`` for API.

- Counter with 64-bit at 100 MHz for the uptime of the system.
- Uses Xilinx `AXI Timer v2.0 <https://www.xilinx.com/support/documentation/ip_documentation/axi_timer/v2_0/pg079-axi-timer.pdf>`_
- 64 Bit Mode enabled
- Timer will overflow in >5000 years after system boot
- Works with two 32-bit counter (*lower* and *upper* bits)
- Only one instance of system time is possible and only on the R5

Usage
-----

- Include ``uz/uz_SystemTime/uz_SystemTime.h`` and call the API
- Intended for usage in the ISR of the R5 processor
- Initialize the function outside of the ISR by calling ``uz_SystemTime_init()``
- Call ``uz_SystemTime_ISR_Tic()`` to start a time measurement, e.g., the first line of ISR
- Call ``uz_SystemTime_ISR_Toc()`` to stop the time measurement, e.g., last line of ISR
- Call the getter functions to read the system time that was read by **the last tic call**
- A lock prevents the call to ``toc`` before ``tic`` was called
- Calling ``toc`` before ``tic`` fires an :ref:`assertion <assertions>`
- Calling any function of the component before ``uz_SystemTime_init()`` fires an :ref:`assertion <assertions>`

.. warning:: The getter functions, e.g., ``uz_SystemTime_GetUptimeInMs()``, return the system time that was read out at the last call to ``uz_SystemTime_ISR_Tic()``! This is intended behavior to have the system time aligned with the start of the ISR.

Example
-------

The variable ``uptimeInMs`` holds the uptime in milliseconds at the start of ``ISR_Control``.
The variable ``IsrExectionTimeInUs`` holds the execution time of the ISR, which will be about 100 microseconds + some time for reading the timer.

.. code-block:: c

    void ISR_Control(void *data)
    {
      uz_SystemTime_ISR_Tic();
      float uptimeInMs=uz_SystemTime_GetUptimeInMs();
      usleep(100); // Do nothing for 100 microseconds
      uz_SystemTime_ISR_Toc();
    }

    int main (void){
    float IsrExectionTimeInUs=uz_SystemTime_GetIsrExectionTimeInUs();
    }


IP-Core
-------

- The AXI Timer v2.0 IP-Core is abstracted by ``uz_AxiTimer64Bit.h`` which wraps the Xilinx drivers (``xtmrctr.h``)
- Timer is called ``timer_uptime_64bit`` in Vivado Block Design

.. figure:: SystemTime_CounterVivado.png

   ``timer_uptime_64bit`` IP-Core for system time