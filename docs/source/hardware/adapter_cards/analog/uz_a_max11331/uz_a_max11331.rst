=============
uz_a_max11331
=============

Features
--------

* Measurement of 24 differential signals
* Sampling rate per channel up to 1 MSPS 
* Sampling rate---to get all 24 channels sampled---of up to 125 kSPS (three MAX11 chips work in parallel, while each of them individually samples 8 channels via multiplexer)
* Resolution of 12 bit
* Input range is +-5V 
* ADC `MAX11331-12 <https://www.analog.com/media/en/technical-documentation/data-sheets/MAX11329-MAX11332.pdf>`_
* ADCs are triggered in groups of 3
* Usage of up to three cards possible
* `UZ_A_MAX11331 Repository with Altium project <https://bitbucket.org/ultrazohm/uz_a_max11331/src>`_

Revisions
---------

..  toctree::
   :maxdepth: 1
   
   UZ_A_MAX11331 Rev01
   UZ_A_MAX11331 Rev02

The remainder of this page summarizes the analog input connector and measurement modes which are identical for all revisions of this PCB. 


Pinout of Analog Connector 
--------------------------

The pinout of the RJ45 ethernet plug is **NOT** intuitive, as shown in :numref:`rj45pinout`. Moreover, the pinout is flipped compared to the LTC2311 analog card.

.. _rj45pinout:

.. figure:: rj45_pinout.png
   :width: 700

   Pinout of the ADC ethernet port.

.. note::

   Note that :numref:`rj45pinout` shows an ethernet cable according to **T568B**!


We provide a breakout board for the RJ45 cable that matches the ADC card. **P** is the positive analog input, **N** the negative.

.. image:: adc_breakout_PN.png
   :width: 400

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


References
----------

* :download:`Assembly drawing <ASM_UZ_A_MAX11331_Differential_Input_Rev01.pdf>`
* :download:`Schematic <SCH_UZ_A_MAX11331_Differential_Input_Rev01-1.pdf>`
* `uz_dac8831 Repository with Altium project <https://bitbucket.org/ultrazohm/uz_a_dac8831/>`_
* Product page of MAX11331: https://www.analog.com/en/products/max11331.html
