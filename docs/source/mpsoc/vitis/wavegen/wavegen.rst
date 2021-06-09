.. _wave_generator:

==================
Waveform Generator
==================

..	toctree::
  :maxdepth: 2
  :hidden:
  :glob:

  *

The ``uz_wavegen`` functions can be used to create commonly used standard waveforms for general propose usage.
Wherever the functions are called, ``uz_wavegen.h`` has to be included.
Each function reads the current global system time (see :ref:`systemTimeR5`) and calculates a the output based on this time.