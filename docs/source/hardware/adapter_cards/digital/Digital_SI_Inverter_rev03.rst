.. _dig_si_inverter:

===================
Digital SI Inverter
===================

.. image:: Digital_SI_Inverter_rev03/3D_View_Top_UZ_D_Inverter_Variant_V1_Rev03.png
  :height: 500
  :align: center

Functionality
=============

The UltraZohm digital inverter consists of three half-bridges with conventional SI-semiconductors. 
It is equipped with bi-directional current measurement for each phase and the DC-link current, measurements for the phase and DC-link voltages as well as temperature measurements for each semiconductor.  
The voltage measurement is equipped with a 1st order low-pass filter.
The current measurement is realized with shunt resistors.
The inverter has a dedicated PWM enable pin. 
If the ``PWM_EN`` is set to false, both semiconductors of each half-bridge are disabled. 
An over current protection for the three phases and the DC-link is included. 
The OCP is not designed for half-bridge shorts and will only be triggered, if the phase or DC-link currents exceed the safe operating window. 
The OCP, when triggered, only flags a FAULT bit in the corresponding software driver. 
The inverter won't be automatically shut down.
Each half-bridge is designed in a non-bootstrap configuration. 
Each voltage and current measurement signal of the three phases and the DC-link are converted from single-ended into differential transmission to reduce the susceptibility to interference.
The measurement signals are transmitted via ethernet cables and are directly compatible with the :ref:`Analog_LTC2311_16_Rev05`, :ref:`Analog_LTC2311_16_v3` and :ref:`Analog_LTC2311_16_v2` cards.
To increase heat dissipation and keep the switches cooler an additional heatsink can be installed.
For additional information or an in depth look into the circuit design check the schematics in the :ref:`References <dig_si_inverter_references>` section.

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
  - Temperature measurement is not build into the Mosfet. Therefore the heat of the PCB close to the semiconductors is measured. The measured temperature will always be **significantly** lower than the max operating temperature of the semiconductors.
  - DC-link capacitance :math:`C_{DC} = 570\mu F`
  - OPC triggerpoint :math:`I_{OCP}=\pm29.85\ A`
  - Cutoff frequency for voltage measurement :math:`f_g = 2170\ Hz` 
  - Operation up to a PWM frequency of :math:`f_{PWM} = 100\ kHz` has been verified
  
Pinout
------

.. csv-table:: Defined pin mapping uz_d_inverter
   :file: Digital_SI_Inverter_rev03/uz_d_inverter_pin_mapping.csv
   :widths: 40 40 60 50 50 
   :header-rows: 1


Compatibility 
-------------

This digital adapter inverter board is directly compatible with the :ref:`uz_inverter_adapter` IP-Core.
It can be used in any of the D1-D4 digital adapter card slots in the UltraZohm, provided the correct CPLD is flashed. 
The card is directly compatible with the :ref:`Analog_LTC2311_16_Rev05`, :ref:`Analog_LTC2311_16_v3` and :ref:`Analog_LTC2311_16_v2` cards.

Switching behaviour
-------------------

In the figure below the general switching behaviour of the inverter with a PMSM as load is shown. 
The plots were capture during routine operation with the PMSM running with :math:`i_q = 5\ A`. The PWM frequency was :math:`20\ kHz` with a deadtime of :math:`150\ ns`.
The gate resistance has been tuned to such a degree, that there is practically no overshoot and only a minimal degree of oscillation for the drain source voltages.
Whilst there is further optimization potential, the resulting switching behaviour shows a robust enough solution.

.. tikz::
   :include: Digital_SI_Inverter_rev03/switching_behaviour.tikz
   :align: right

Used components
---------------

- Mosfet (100 V, 97 A, 6.0 :math:`m\Omega`) `ISC060N10NM6ATMA1 <https://www.mouser.de/datasheet/2/196/Infineon_ISC060N10NM6_DataSheet_v02_02_EN-3166722.pdf>`_
- Gate-Driver `EiceDRIVER 2EDF7275KXUMA1 <https://www.mouser.de/datasheet/2/196/Infineon_2EDF7275K_DataSheet_v02_07_EN-1731004.pdf>`_
- Isolated DC/DC Converter for gate 12V supply `PDSE1-S24-S12-M-TR <https://www.mouser.de/datasheet/2/670/pdse1_m-1596038.pdf>`_ 
- Bi-directional current measurement `MAX40056TAUA+ <https://www.mouser.de/datasheet/2/609/MAX40056F_MAX40056U-3128585.pdf>`_ 
- Differential operational amplifier `ADA4940-1ARZ <https://www.mouser.de/datasheet/2/609/ada4940_1_4940_2-3120247.pdf>`_ 
- Temperature measurement `LM57CISD-10/NOPB <https://www.ti.com/general/docs/suppproductinfo.tsp?distId=26&gotoUrl=https://www.ti.com/lit/gpn/lm57>`_
- Voltage to PWM frequency converter `LTC6992HS6-4#WTRMPBF <https://www.mouser.de/datasheet/2/609/LTC6992-1-6992-2-6992-3-6992-4-1852873.pdf>`_

Setup before first use and implementation with Inverter Interface IP-Core
=========================================================================

CPLD
----

Make sure, that in the corresponding digital adapter slot the correct CPLD is flashed.
For this adapter card the ``uz_d_3ph_inverter`` CPLD has to be flashed.
Download this CPLD from the `UltraZohm CPLD Repository <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/>`_.
Follow :ref:`this guide  <label_cpld_programming>` on how to flash the correct CPLD onto the UltraZohm.

Software implementation
-----------------------

This adapter card interacts with the user via the highly sophisticated :ref:`uz_inverter_adapter` IP-Core and its corresponding driver.
Follow :ref:`this guide <inverter_adapter_usage>` on how to integrate the IP-Core in the FPGA and how to set up the software driver.
Whilst following this guide, make sure to adjust the `linear interpolation parameters` for the ``inverter_adapter_config``. 
For this inverter card they should be:

.. code-block:: c
 :caption: linear interpolation parameters for config struct

 .linear_interpolation_params = {-289.01f, 218.72f}

Set the deadtime in the ``uz_interlockDeadtime2L_staticAllocator.c`` file to an appropriate value. 
A safe value with a considerable safety margin is ``200ns``. 
No matter what, the deadtime should not be lower than ``150ns``.

To enable respectively disable the ``PWM_EN`` for normal operation add the following code to the isr.c. 
It should always be ensured, that the ``PWM_EN`` is handled correctly. 
I.e. if the UltraZohm transitions into its error-state because e.g. the OCP is triggered, it must be ensured, that the ``PWM_EN`` is retracted.
Pay attention to this during your error handling.

.. code-block:: c
 :caption: Additions for isr.c in regards to the ``PWM_EN``

 if (current_state == running_state || current_state == control_state) {
   // enable inverter adapter hardware
   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
 } else {
   // disable inverter adapter hardware
   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
 }


To read out the measured current and voltage signals both ethernet cables have to be connected to an ADC-Card.
In the ``isr.c`` add the following conversion factors to the measured signals.

.. code-block:: c
 :caption: Additions for isr.c if the ADC-Card is in the A1 slot. For the A2/A3 slot adjust the code accordingly

 struct uz_3ph_abc_t v_abc_Volts = {0};
 struct uz_3ph_abc_t i_abc_Amps = {0};
 float v_DC_Volts = 0.0f;
 float i_DC_Amps = 0.0f;
 v_abc_Volts.a = Global_Data.aa.A1.me.ADC_B8 * 12.0f;
 v_abc_Volts.b = Global_Data.aa.A1.me.ADC_B7 * 12.0f;
 v_abc_Volts.c = Global_Data.aa.A1.me.ADC_B6 * 12.0f;
 v_DC_Volts = Global_Data.aa.A1.me.ADC_A1 * 12.0f;
 i_abc_Volts.a = Global_Data.aa.A1.me.ADC_A4 * 12.5f;
 i_abc_Volts.b = Global_Data.aa.A1.me.ADC_A3 * 12.5f;
 i_abc_Volts.c = Global_Data.aa.A1.me.ADC_A2 * 12.5f;
 i_DC_Volts = Global_Data.aa.A1.me.ADC_B5 * 12.5f; 

In order to use the over current and over temperature protection, the following code has to be added to the isr.c as well. 
These are optional features and can be left out if they aren't required.

.. code-block:: c
 :caption: Additions for isr.c if OCP or OTP are used
 
 //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
 //Overtemperature for H1
 if (!Global_Data.av.inverter_outputs_d1.FAULT_H1) {
    uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    ultrazohm_state_machine_set_error(true);
 }
 //Overtemperature for L1
 if (!Global_Data.av.inverter_outputs_d1.FAULT_L1) {
    uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    ultrazohm_state_machine_set_error(true);
 }
 //Overtemperature for H2
 if (!Global_Data.av.inverter_outputs_d1.FAULT_H2) {
    uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    ultrazohm_state_machine_set_error(true);
 }
 //Overtemperature for L2
 if (!Global_Data.av.inverter_outputs_d1.FAULT_L2) {
    uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    ultrazohm_state_machine_set_error(true);
 }
 //Overtemperature for H3
 if (!Global_Data.av.inverter_outputs_d1.FAULT_H3) {
    uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    ultrazohm_state_machine_set_error(true);
 }
 //Overtemperature for L3
 if (!Global_Data.av.inverter_outputs_d1.FAULT_L3) {
    uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    ultrazohm_state_machine_set_error(true);
 }
 //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
 //Binding of the signals to the driver is slightly unintuitive 
 //Overcurrent for Phase A
 if (!Global_Data.av.inverter_outputs_d1.OC_L1) {
    uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    ultrazohm_state_machine_set_error(true);
 }
 //Overcurrent for Phase B
 if (!Global_Data.av.inverter_outputs_d1.OC_H1) {
    uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    ultrazohm_state_machine_set_error(true);
 }
 //Overcurrent for Phase C
 if (!Global_Data.av.inverter_outputs_d1.OC_L2) {
    uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    ultrazohm_state_machine_set_error(true);
 }
 //Overcurrent for DC-link
 if (!Global_Data.av.inverter_outputs_d1.OC_H2) {
    uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    ultrazohm_state_machine_set_error(true);
 }
 


References
==========

.. _dig_si_inverter_references:

* :download:`Schematic Rev03 <Digital_SI_Inverter_rev03/UZ_D_Inverter.pdf>`
* `uz_d_inverter Repository with Altium project <https://bitbucket.org/ultrazohm/uz_d_inverter>`_

Known issues
============

As of this moment, no issue in Rev03 is known.

Designed by 
===========
Dennis Hufnagel (THN)

Acknowledgments
---------------

Special thank you for their support during the design and testing phase goes to Eyke Aufderheide (TUM), Michael Hoerner (THN) and Tobias Schindler (THN).