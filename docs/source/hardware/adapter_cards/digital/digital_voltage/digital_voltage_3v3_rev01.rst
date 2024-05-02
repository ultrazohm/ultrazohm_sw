.. _digitalVoltage3v3rev01:

=======================
UZ_D_Voltage_3V3 Rev01
=======================

Top View
""""""""""

.. image:: digital_voltage_3v3_rev01/UZ_D_Voltage_3V3_3D_View_Top_Rev01.png
   :width: 500px

Bottom View
""""""""""""

.. image:: digital_voltage_3v3_rev01/UZ_D_Voltage_3V3_3D_View_Bot_Rev01.png
   :width: 500px

Functionality
-------------

The UZ_D_Voltage_3V3 Card is the simplified version of the base variant of :ref:`digitalVoltage`. 
The adapter card outputs digital signals from 3.3V Input Voltage to 3.3V Output.

IO Interface
------------

In order to enable maximal user flexibility and to save costs, the PCB comes without an IO interface connector. Originaly, the
PCB has been designed for the Samtec `IPL1-120-01-L-D-RA-K <https://www.samtec.com/products/ipl1-120-01-l-d-ra-k>`_
and `IPL1-115-01-L-D-RA-K <https://www.samtec.com/products/ipl1-115-01-l-d-ra-k>`_ connectors but any connector with
a 1" (2.54mm) pin pitch can be used. 

The appropriate plug for the IPL1-115-01-L-D-RA-K is the `IPD1-15-D-K <https://de.farnell.com/samtec/ipd1-15-d-k/buchsengeh-use-30pos-nylon-2-54mm/dp/2984590?ost=2984590>`_
and for the IPL1-120-01-L-D-RA-K it is the `IPD1-20-D-K <https://de.farnell.com/samtec/ipd1-10-d-k/stecker-2-54mm-crimp-20pol/dp/2308543?st=ipd1-20-d-k>`_ .
Additionally, the crimp contact 
`CC79L-2630-01-L <https://de.farnell.com/samtec/cc79l-2630-01-l/buchsenkontakt-30-26awg-ipd1-crimp/dp/2308509?ost=cc79l%E2%80%932630%E2%80%9301%E2%80%93l>`_
is required.

References
==========

.. _dig_3v3_rev01_inverter_references:

* :download:`Schematic Rev01 <digital_voltage_3v3_rev01/SCH_UZ_D_Voltage_3V3_Default_Rev01.pdf>`
* `Repository with Altium project <https://bitbucket.org/ultrazohm/uz_d_voltage_3v3>`_

Compatibility 
"""""""""""""
Slots D1 to D4 can be used without limitations

See also
""""""""

* `CPLD software git <https://bitbucket.org/ultrazohm/cpld_lattice/>`_
* :ref:`label_cpld_programming`

Designer
""""""""

Designed by Andreas Geiger (TH Nürnberg), 01/2024
