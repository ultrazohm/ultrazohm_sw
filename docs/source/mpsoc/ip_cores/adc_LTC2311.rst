.. _ipCore_LTC23:

===========
ADC LTC2311
===========

.. warning:: This IP-Core is deprecated and should not be used! Use :ref:`ipCore_LTC2311_v3` instead.

..	image:: ./images_adc/adc2.png

Idea
----

1. This IP Core allows to read the ADC values of 1-4 LTC2311 ADCs

2. The idea is, to have one IP Core, which can be configured to generically read between 1-4 ADCs, that all use the same conversion factor.

3. The signals are all differential (LVDS).


Basics
------

1. The basic configuration allows:

	..	image:: ./images_adc/adc0.png

	a.) The definition of the ADC Bits. In case of the LTC2311, 16 Bits are available.
	
	b.) The definition of the word length for the output signals. However, the fraction length is always 11 Bits.
	
	c.) Every of the 1-4 ADCs can have their own clock signal, or can share one. However, the used hardware shares one clock signal.
	
2. The conversion allows:

	..	image:: ./images_adc/adc1.png

	a.) The "Trigger_cnv" flag in Vivado
		1.) If the first check box is NOT activated, the ADC converts always and restart as soon as the previous conversion is done. The "Trigger_cnv" flag is not used.
		
		2.) If the first check box is activated, the ADC converts after the trigger "Trigger_cnv" flag is regognized.
	
	b.) The "ADC_SET_OFFSET" flag in Vivado
		1.) If the second check box is NOT activated, the offset is determined by the last measured value. No averaging is used. 
		
		2.) If the second check box is activated, the offset is determined by the variable "ADC_USER_OFFSET", which is received by the processor via AXI. In this case, averaging can be carried out on the processor to ensure a valid offset.
		
		
		
Designed by
-----------

Sebastian Wendel (THN) in 08/2018
