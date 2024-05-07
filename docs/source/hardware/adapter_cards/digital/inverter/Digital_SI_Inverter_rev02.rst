.. _dig_si_inverter_rev02:

==========================================
Digital Inverter Rev02
==========================================

.. danger:: Please note that the Rev02 is a non-working, deprecated version. 

.. image:: Digital_SI_Inverter_rev02/3D_View_Top_UZ_D_Inverter_Variant_V1_Rev02.png
  :height: 500
  :align: center


References
==========

.. _dig_si_inverter_references:

* :download:`Schematic Rev02 <Digital_SI_Inverter_rev02/UZ_D_Inverter.pdf>`
* `uz_d_inverter Repository with Altium project <https://bitbucket.org/ultrazohm/uz_d_inverter>`_

Known issues
============

* 2.5V reference voltage source dies on first startup of the inverter. This is traced back to an inexplicable high current demand during start up of the shunt amplifiers.
* Gate resistors of 10 Ohm lead to a unacceptable ringing during switching. Can be fixed with higher gate resistance. 

Inverter Card without the fixes are not working and deprecated. 
The fixes have been implemented in the Rev03 version.
See :ref:`dig_si_inverter_rev03` for further information.

Designed by 
===========

Dennis Hufnagel (THN)

Acknowledgments
---------------

Special thank you for their support during the design and testing phase goes to Eyke Aufderheide (TUM), Michael Hoerner (THN) and Tobias Schindler (THN).