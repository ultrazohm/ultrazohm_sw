.. _wave_generator:

==================
Waveform Generator
==================

The ``uz_wavegen`` can be used to create standard waveform, which, for example, can be displayed in the :ref:`JavaScope`.


Avaivable waveforms
*******************


Sine wave
^^^^^^^^^

.. image:: sine_wave.png
    :scale: 20
   
Creates a continous sine wave. 

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float
     - 
   * - frequency
     - \+ float 
     - Hz

Call the function with the following:

.. code-block:: c

    output = uz_wavegen_sine(amplitude, frequency_Hz);

Sawtooth wave
^^^^^^^^^^^^^

.. image:: sawtooth.png
    :scale: 20
    
Creates a continous sawtooth wave.

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float
     - 
   * - frequency
     - \+ float 
     - Hz

Call the function with the following:

.. code-block:: c

    output = uz_wavegen_sawtooth(amplitude, frequency_Hz);
    
Pulse wave
^^^^^^^^^^^^^

.. image:: pulse.png
    :scale: 20
    
Creates a continous pulse wave. Required input arguments are combined into a struct.

.. list-table:: Required input arguments
   :widths: 25 25 25
   :header-rows: 1

   * - argument
     - value
     - unit
   * - amplitude
     - +/- float
     - 
   * - frequency
     - \+ float 
     - Hz
   * - DutyCycle
     - float 0.0 -> 1.0
     -
  
Call the function with the following:

.. code-block:: c

    wavegen_pulse_settings name = {amplitude, frequency_Hz, DutyCycle};
    output = uz_wavegen_sawtooth(name);


