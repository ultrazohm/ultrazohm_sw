.. _uz_dac8831_pcb:

==========
uz_dac8831
==========

The DAC card features 8 independent, 16-bit digital analog conversion channels with one `DAC8831 <https://www.ti.com/product/DAC8831>`_ for each channel.
The DAC8831 has a settling time of :math:`1~\mu s` according to the data sheet which leads to a maximum frequency of :math:`1 MHz` for changing the output voltage (not tested!).
The SPI interface of the DAC8831 has a maximum clock frequency of :math:`50 MHz`, which is tested and working on the adapter card.
The output voltage is bipolar with a range of +-5V (differential).
Each DAC8831 is connected to an individual data channel and all 8 DAC8831 share the chip select (CS) as well as the clock (CLK) of the SPI interface.
The DAC8831 features an LDAC pin that determines when new set-points are applied to the output.
This pin is not used in the design (pulled up).
Therefore, all ADC channels change their set-point according to the data they receive with each rising edge on the CS signal (all channels simultaneously).

.. _dac_colored:

.. figure:: dac_pcb_colored.jpg
   :width: 700

   Assembled DAC pcb with power supply and reference voltage (red and green), LVDS receiver (orange), DAC8831 (blue), output OpAMPs (pink) and ethernet connector (yellow).

The output of the DAC card is fully compatible to :ref:`Analog_LTC2311_16`, i.e., it can directly connected to the card with matching voltage levels and DAC1 corresponds to ADC1 on channel A.
:numref:`dac_adc_loopback` shows the typical application of the DAC card.
The DAC card is used to loop values from the FPGA through the ADC card back to the FPGA.
This setup enables HIL testing including the whole signal chain of the ADC.


.. _dac_adc_loopback:

.. figure:: adc_dac_loopback.jpg
   :width: 700

   Typical application of the DAC card in loopback operation with :ref:`Analog_LTC2311_16`.

Pinout
======

The pinout of the DAC ethernet port follows the pinout outlined in :ref:`Analog_LTC2311_16_pinout`.
See :numref:`rj45pinout` for the detailed pinout, the ADC number is equal to the DAC number (i.e., ADC1 is DAC1).


.. csv-table:: Mapping of signal names on the goldfinger (X5 on carrier, X2 in DAC adapter card schematic)
    :file: dac8831_goldfinger_pinmapping.csv
    :widths: 10 10 
    :header-rows: 1

References
==========

* :download:`Schematic <SCH_UZ_A_DAC_THS_Rev01.pdf>`
* Data sheet of DAC8831: https://www.ti.com/lit/ds/slas449d/slas449d.pdf?ts=1653291212982

Designed by 
===========

Engineer: Michaela Hlatky (TH Nürnberg, ELSYS) in WS 2021/22

Supervision: Tobias Schindler (TH Nürnberg, ELSYS)

Review: Eyke Liegmann (TUM)


