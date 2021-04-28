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

Function call:

.. code-block:: c

    ... = uz_wavegen_sine(amplitude, frequency_Hz);

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

Function call:

.. code-block:: c

    ... = uz_wavegen_sawtooth(amplitude, frequency_Hz);
    
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
  
Function call:

.. code-block:: c

    wavegen_pulse_settings name = {amplitude, frequency_Hz, DutyCycle};
    ... = uz_wavegen_sawtooth(name);

Square wave
^^^^^^^^^^^^^

.. image:: square.png
    :scale: 20
    
Creates a continous square wave.

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

Function call:

.. code-block:: c

    ... = uz_wavegen_square(amplitude, frequency_Hz);

Triangle wave
^^^^^^^^^^^^^

.. image:: triangle.png
    :scale: 20
    
Creates a continous triangle wave.

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

Function call:

.. code-block:: c

    ... = uz_wavegen_triangle(amplitude, frequency_Hz);