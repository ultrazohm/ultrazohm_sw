.. _dig_si_inverter:

===================
Digital SI Inverter
===================

.. image:: Digital_SI_Inverter_rev03/3D_View_Top_UZ_D_Inverter_Variant_V1_Rev03.png
  :height: 500

.. image:: Digital_SI_Inverter_rev03/3D_View_Bot_UZ_D_Inverter_Variant_V1_Rev03.png
  :height: 500

Source
------

* `uz_d_inverter Repository with Altium project <https://bitbucket.org/ultrazohm/uz_d_inverter>`_


Functionality
-------------

The UltraZohm digital inverter consists of three half-bridges with conventional SI-semiconductors. 
It is equipped with bi-directional current measurement for each phase and the DC-link current, measurements for the phase and DC-link voltages as well as temperature measurements for each semiconductor.  
The voltage measurement is equipped with a 1st order low-pass filter.
An over current protection for the three phases and the DC-link is included. 
The OCP is not designed for half-bridge shorts and will only be triggered, if the phase or DC-link currents exceed the safe operation window. 
The OCP, when triggered, only flags a FAULT bit in the corresponding software driver. 
The inverter won't be automatically shut down.
Each half-bridge is designed in a non-bootstrap configuration. 
This means, that each semiconductor has its own power-supply for charging the gate and therefore no minimum switch-on time for the semiconductors is necessary.
Each the phase and current measurement signals are converted from single-ended into differential transmission to reduce the susceptibility to interference.
The measurement signals are transmitted via ethernet cables and are directly compatible with the :ref:`Analog_LTC2311_16_Rev05`, :ref:`Analog_LTC2311_16_v3` and :ref:`Analog_LTC2311_16_v2` cards.
To increase heat dissipation and keep the switches cooler an additional heatsink can be installed.

Maximum operation ratings
-------------------------

.. warning ::
  - Current up to :math:`I_{peak}=\pm33.94\ A` or :math:`I_{rms}=\pm24\ A`  
  - Voltage up to :math:`V_{peak}=48\ V` or :math:`V_{rms}=33.94\ V`
  - Operating temperature of the Mosfets :math:`T_{j,max}=175°C`


Additional ratings
------------------

.. note ::
  - Current measurement up to :math:`I_{peak,meas}=\pm35\ A`
  - Voltage measurement up to :math:`V_{peak,meas}= 60\ V`
  - Temperature measurement up to :math:`T_{meas}=105°C`
  - Temperature measurement is not build into the Mosfet. Therefore the heat of the PCB close to the semiconductors is measured. The measured temperature should always be **significantly** lower than the max operating temperature of the semiconductors.
  - DC-link capacitance :math:`C_{DC} = 570\mu F`
  - OPC triggerpoint :math:`I_{OCP}=\pm29.85\ A`
  - Cutoff frequency for voltage measurement :math:`f_g = 2170Hz` 

Used components
---------------

- Mosfet (100 V, 97 A, 6.0 :math:`m\Omega`) `ISC060N10NM6ATMA1 <https://www.mouser.de/datasheet/2/196/Infineon_ISC060N10NM6_DataSheet_v02_02_EN-3166722.pdf>`_
- Gate-Driver `EiceDRIVER 2EDF7275KXUMA1 <https://www.mouser.de/datasheet/2/196/Infineon_2EDF7275K_DataSheet_v02_07_EN-1731004.pdf>`_
- Isolated DC/DC Converter for gate 12V supply `PDSE1-S24-S12-M-TR <https://www.mouser.de/datasheet/2/670/pdse1_m-1596038.pdf>`_ 
- Bi-directional current measurement `MAX40056TAUA+ <https://www.mouser.de/datasheet/2/609/MAX40056F_MAX40056U-3128585.pdf>`_ 
- Differential operational amplifier `ADA4940-1ARZ <https://www.mouser.de/datasheet/2/609/ada4940_1_4940_2-3120247.pdf>`_ 
- Temperature measurement `LM57CISD-10/NOPB <https://www.ti.com/general/docs/suppproductinfo.tsp?distId=26&gotoUrl=https://www.ti.com/lit/gpn/lm57>`_
- Voltage to PWM frequency converter `LTC6992HS6-4#WTRMPBF <https://www.mouser.de/datasheet/2/609/LTC6992-1-6992-2-6992-3-6992-4-1852873.pdf>`_

Switching behavior
------------------

- include pictures


Known issues
------------

The reference input of the MAX40056TAUA+ current amplifier was initially designed to work with 2.5V to allow for a higher max amplitude for the current measurements. 
This ref-input pin is however *buggy* and draws too much current during startup operation of the amplifier. 
This kills any 2.5V reference voltage source. 
Therefore it was decided, to only use the 1.5V internal reference of the MAX40056TAUA+. 
The maximum current to be measured is therefore lower and is stated in the note above. 

Compatibility 
-------------

Pinout
------

.. csv-table:: Defined pin mapping uz_d_inverter
   :file: Digital_SI_Inverter_rev03/uz_d_inverter_pin_mapping.csv
   :widths: 40 40 60 50 50 
   :header-rows: 1


Implementation with Inverter Interface IP-Core
----------------------------------------------


References
""""""""""

* :download:`Schematic Rev01 <Digital_Resolver_rev01/SCH_UZ_D_Resolver_Default_Rev01.pdf>`
* :download:`Datasheet AD2S1210 IC <Digital_Resolver_rev01/AD2S1210.pdf>`
* :ref:`dig_encoder_v1`
* :ref:`label_cpld_programming`

Designed by 
"""""""""""""""
Dennis Hufnagel (THN), Eyke Aufderheide (TUM), Michael Hoerner (THN)