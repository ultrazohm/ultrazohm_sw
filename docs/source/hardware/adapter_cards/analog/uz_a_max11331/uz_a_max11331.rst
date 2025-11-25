.. _Analog_MAX11331:

=============
uz_a_max11331
=============


Features
--------

* Measurement of 24 differential signals
* Sampling rate per channel up to 1 MSPS 
* Sampling rate to get all 24 channels sampled of up to 125 kSPS (three MAX11331 chips work in parallel, while each of them sequentially samples 8 channels via multiplexer)
* Resolution of 12 bit 
* Input range is 0..+5V with respect to ground of UltraZohm chassis for In_P and In_N, i.e., the maximum delta measuring range is 5V
* ADC `MAX11331 <https://www.analog.com/media/en/technical-documentation/data-sheets/MAX11329-MAX11332.pdf>`_
* ADCs are triggered in groups of 3 (three MAX11331 chips work in parallel, while each of them sequentially samples 8 channels via multiplexer)
* Usage of up to three cards possible

Revisions
---------

..  toctree::
   :maxdepth: 1
   
   MAX11331_Rev02
   MAX11331_Rev03

The remainder of this page summarizes the analog input connector and measurement modes which are identical for all revisions of this PCB. 

.. _Analog_max11331_pinout:

Pinout of Analog Connector 
--------------------------


   .. _rj45maxpinout:

   .. figure:: rj45_pinout_MAX11.png
      :width: 700

      Pinout of the ADC ethernet port.

The pinout of the RJ45 ethernet plug is **NOT** intuitive, as shown in :numref:`rj45maxpinout`. Moreover, the pinout is flipped compared to the LTC2311 analog card, see :ref:`Analog_LTC2311_16_pinout`.

.. note::

   Note that :numref:`rj45maxpinout` shows an ethernet cable according to **T568B**!

.. warning ::
   It is essential to use Ethernet cables with shielding and metallic RJ45 plugs (e.g. CAT7 cables) so that the GND of the MAX11 card (connected from the PCB GND to the RJ45 connector housing) and the GND of the measuring signal source are connected. Without this GND connection, there will be floating signals, i.e. common mode interference on the measurement signal.


We provide a breakout board for the RJ45 cable that matches the ADC card. **P** is the positive analog input, **N** the negative.

.. image:: adc_breakout_PN_MAX11.png
   :width: 400


.. note::

   Note that due to the flipped connection (compared to the LTC2311 assignment) the colored nomenclature applies for MAX11331 adapter board.


The pairs of the RJ45 ethernet connector map to the ADCs as follows:

=========      ==========================    ==========================
Connected                         Pin on RJ45                           
---------      --------------------------------------------------------
 ADC              :math:`V_\mathrm{in,p}`       :math:`V_\mathrm{in,n}`
=========      ==========================    ==========================
ADC 1           1                                2                     
ADC 2           3                                6                     
ADC 3           4                                5                     
ADC 4           7                                8                     
=========      ==========================    ==========================

The MAX11331 adapter card has six of the RJ45 ports described above (Port A...F), whereby two consecutive RJ45 ports are evaluated by one of the three MAX11331 ADC chips. The driver of the IP Core ADC :ref:`ipCore_adc_max11331` shows exactly this nomenclature, i.e., ADC_A1...ADC_F24.

.. figure:: MAX11_AdapterBoard_Blende.png
   :height: 500

   Frontpanel of the MAX11331 adapter card on the UltraZohm.


.. _Analog_max11331_meas_modes:

Measurement modes
-----------------

There are three ways to measure an analog signal with this adapter card

* Fully differential (bipolar)
* Single-ended with reference to an offset voltage (bipolar)
* Single-ended with reference to ground potential (unipolar)

.. figure::  measurement_variants.png
   :width: 250

   Different input voltage forms for measurement.

.. warning ::
   In all cases, the input range for each analog pin (In_P, In_N) is **0..+5V** with respect to UltraZohm ground.  
   It is forbidden to apply voltages above 5V or below 0V on the connector. 

The IP Core ADC :ref:`ipCore_adc_max11331` interacts hereby with the MAX11331 IC and can change the input range of each differential pair by setting the ``UNIPOLAR``,  ``BIPOLAR``, and  ``RANGE`` registers.

.. figure::  MAX11_measurement_variants_differential.png 
   :width: 800

   Analog input configurations and waveforms, see Table 8 in [MAX11331_datasheet]_ 

.. note ::
   In all cases, both input voltages (In_P, In_N) should be transferred over the same twisted-pair cable to get the same common-mode noise on both lines, which is then rejected by the differential amplifier. 

.. _MAX11331_differential_measurement:

1. Fully differential (bipolar) measurement
"""""""""""""""""""""""""""""""""""""""""""

In_P and In_N are fully differential signals, meaning they inverted signals with a common-mode offset of 2.5V e.g. 

* For 0V input voltage, both In_P and In_N have the same voltage level, e.g. 2.5V
* For +1V input voltage, e.g. In_P is 3V and In_N is 2V or, e.g. In_P is 4V and In_N is 3V
* For -3V input voltage, e.g. In_P is 1V and In_N is 4V or, e.g. In_P is 2V and In_N is 5V 

.. figure:: differential_signal.png
   :width: 500

   Fully differential measurement input

This will yield the highest signal-to-noise ratio (SNR) even when using longer cables. 

The IP Core ADC interacts hereby with the hardware in the ``BIPOLAR register = 1`` and  ``RANGE register = 1`` which defines the input range to be ±5V. In this case, all 12 Bits resolution of the ADC are utilized. 
This is the recommended use-case and the **default case setup of the IP core**. 

2. Single-ended with reference to an offset voltage (bipolar) measurement
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

The negative input In_N is set to a fixed offset voltage, e.g. 2.5V which is often provided by the current sensor. The positive input may vary between 0V to 5V. 

In the default case setup of the IP core, i.e., ``RANGE register = 1``, only 11 Bits resolution of the ADC are utilized. 
The full 12 Bits could be used by setting ``RANGE register = 0`` which changes the input range to ±Vref/2, i.e., -2.5V to +2.5V (tbc).

.. figure::  measurement_variants.png
   :width: 250





3. Single-ended with reference to ground potential (unipolar) measurement
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

The negative input In_N is set to ground which is preferably transferred over the same cable as the measurement signal In_P. 

In the default case setup of the IP core, i.e., ``BIPOLAR register = 1``, only 11 Bits resolution of the ADC are utilized.  
Note that the bit pattern has to be interpreted differently, see Figure 4 and 5 in [MAX11331_datasheet]_ . 
The full 12 Bits could (probably) used by setting ``UNIPOLAR register = 0`` which sets the input range to 0..5V (tbc).


References
----------

* :download:`Assembly drawing <Rev02/ASM_UZ_A_MAX11331_Differential_Input_Rev01.pdf>`
* :download:`Schematic <Rev02/SCH_UZ_A_MAX11331_Differential_Input_Rev01-1.pdf>`
* `UZ_A_MAX11331 Repository with Altium project <https://bitbucket.org/ultrazohm/uz_a_max11331/src>`_
* IP Core ADC :ref:`ipCore_adc_max11331`
* `Product page MAX11331 <https://www.analog.com/en/products/max11331.html>`_
* .. [MAX11331_datasheet] `Data sheet ADC MAX11331 <https://www.analog.com/media/en/technical-documentation/data-sheets/MAX11329-MAX11332.pdf>`_
