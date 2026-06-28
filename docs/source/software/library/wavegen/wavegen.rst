.. _wave_generator:

==================
Waveform Generator
==================



The ``uz_wavegen`` functions can be used to create commonly used standard waveforms for general purpose usage.
Wherever the functions are called, ``uz_wavegen.h`` has to be included.
The periodic waveform generators use internal phase accumulators based on ``uz_SystemTime_GetUptimeInUs()`` (see :ref:`systemTimeR5`).
This avoids loss of precision at long uptimes because only the elapsed time between two calls is converted to ``float``.

.. note:: The phase accumulator time base has microsecond resolution. This avoids the long-uptime staircase caused by ``float`` seconds, but sampling periods that are not representable as integer microseconds, for example 73 kHz, are represented by the corresponding integer-microsecond delta pattern.

.. note:: Note that the sampling rate of the signal depends on your sampling frequency of the functions calls  (e.g., by calling it from the ISR). For example, if the wave function are called with :math:`f=20 kHz` this is equal to the sampling frequency, thus limiting the usable frequency of the functions.  

Functions
=========

..	toctree::
    :maxdepth: 1
    :glob:
  
    *
