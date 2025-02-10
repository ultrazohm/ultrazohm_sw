.. _digitalVoltage3v3rev01:

=======================
UZ_D_Voltage_3V3 Rev01
=======================

.. grid:: 2
    :outline:

    .. grid-item::

        .. image:: digital_voltage_3v3_rev01/UZ_D_Voltage_3V3_3D_View_Top_Rev01.png
           :width: 95%

    .. grid-item::

        .. image:: digital_voltage_3v3_rev01/UZ_D_Voltage_3V3_3D_View_Bot_Rev01.png
           :width: 95%

The adapter card provides a generic input and output functionality (GPIO) with a voltage level of 3.3V.
The UZ_D_Voltage_3V3 Card is a simplified version of :ref:`digitalVoltage`, i.e., the voltage level is fixed.

Interface
=========

The interface uses the Samtec connectors

- `IPL1-120-01-L-D-RA-K <https://www.samtec.com/products/ipl1-120-01-l-d-ra-k>`_
- `IPL1-115-01-L-D-RA-K <https://www.samtec.com/products/ipl1-115-01-l-d-ra-k>`_
   
The appropriate counterparts are:

- IPL1-115-01-L-D-RA-K: `IPD1-15-D-K <https://de.farnell.com/samtec/ipd1-15-d-k/buchsengeh-use-30pos-nylon-2-54mm/dp/2984590?ost=2984590>`_
- IPL1-120-01-L-D-RA-K: `IPD1-20-D-K <https://de.farnell.com/samtec/ipd1-10-d-k/stecker-2-54mm-crimp-20pol/dp/2308543?st=ipd1-20-d-k>`_ .

The appropriate crimp contact is `CC79L-2630-01-L <https://de.farnell.com/samtec/cc79l-2630-01-l/buchsenkontakt-30-26awg-ipd1-crimp/dp/2308509?ost=cc79l%E2%80%932630%E2%80%9301%E2%80%93l>`_.

Pinout
======


X2: Samtec 30 pin socket `IPL1-120-01-L-D-RA-K <https://www.samtec.com/products/ipl1-120-01-l-d-ra-k>`_

.. image:: digital_voltage_3v3_rev01/dig_3v3_30pol_rev01.png
   :width: 95%
   :align: center

X3: Samtec 40 pin socket `IPL1-120-01-L-D-RA-K <https://www.samtec.com/products/ipl1-120-01-l-d-ra-k>`_

.. image:: digital_voltage_3v3_rev01/dig_3v3_40pol_rev01.png
   :width: 95%
   :align: center


References
==========

.. _dig_3v3_rev01_inverter_references:

* :download:`Schematic Rev01 <digital_voltage_3v3_rev01/SCH_UZ_D_Voltage_3V3_Default_Rev01.pdf>`
* `Repository with Altium project <https://bitbucket.org/ultrazohm/uz_d_voltage_3v3>`_

Compatibility 
=============

Slots D1 to D5 can be used without limitations

See also
========

* `CPLD software git <https://bitbucket.org/ultrazohm/cpld_lattice/>`_
* :ref:`label_cpld_programming`

Designer
========

Designed by Andreas Geiger (TH Nürnberg), 01/2024
