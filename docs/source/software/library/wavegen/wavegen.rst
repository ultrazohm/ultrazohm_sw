.. _wave_generator:

==================
Waveform Generator
==================



The ``uz_wavegen`` functions can be used to create commonly used standard waveforms for general propose usage.
Wherever the functions are called, ``uz_wavegen.h`` has to be included.
Each function reads the current global system time (see :ref:`systemTimeR5`) and calculates the output based on this time.

.. note:: Note that the sampling rate of the signal depends on your sampling frequency of the functions calls  (e.g., by calling it from the ISR). For example, if the wave function are called with :math:`f=20 kHz` this is equal to the sampling frequency, thus limiting the usable frequency of the functions.  

Functions
=========

..	toctree::
    :maxdepth: 1
    :glob:
  
    *