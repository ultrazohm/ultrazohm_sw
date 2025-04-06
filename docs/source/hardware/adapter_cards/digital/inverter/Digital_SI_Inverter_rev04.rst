.. _dig_si_inverter_rev03:

==========================================
Digital Inverter Rev04
==========================================

.. image:: Digital_SI_Inverter_rev04/3D_View.png
  :height: 500
  :align: center


Changes from Rev03 to Rev04
----------------------------

* Added separate gate resistors for turn-off (16ohm) and turn-on (47ohm) MOSFETs.
* Introduced a new capacitor bank consisting of 8x AEC capacitors (110µF each) and 15x MLCCs (10µF each).
* Eliminated low-side temperature measurement from all phases.
* Added an individual 2.5V (REF4132B25DBVRQ1) supply as a bias reference for (ADA4940-1ARZ-R7).
* Replaced Current sensor (MAX40056TAUA+) with (INA241A2IDGKR).
* Optimized the entire layer stackup and re-engineered the PCB layout.
* Attached a bottom-side heatsink for improved heat management.
Changes from Rev03 to Rev04 production
---------------------------------------

* programmable EEPROM for identifying Inverter Cards
* all components have been reviewed regarding their compatibility with JLCPCB parts


Absolute maximum ratings
------------------------

.. warning ::
  - Current up to :math:`I_{peak}=\pm33.94\ A` or :math:`I_{rms}=\pm24\ A`  
  - Voltage up to :math:`V_{peak}=48\ V` or :math:`V_{rms}=33.94\ V`
  - Operating temperature of the MOSFET :math:`T_{j,max}=175°C`


Additional ratings
------------------

.. note ::
  - Current measurement up to :math:`I_{peak,meas}=\pm35\ A`
  - Voltage measurement up to :math:`V_{peak,meas}= 60\ V`
  - Temperature measurement up to :math:`T_{meas}=105°C`
  - Temperature measurement is not built into the MOSFET. Therefore the heat of the PCB close to the semiconductors is measured. The measured temperature will always be **significantly** lower than the max operating temperature of the semiconductors.
  - DC-link capacitance :math:`C_{DC} = 1030\mu F`
  - OPC trigger point :math:`I_{OCP}=\pm29.85\ A`
  - Cutoff frequency for voltage measurement :math:`f_g = 2170\ Hz` 
  - Operation up to a PWM frequency of :math:`f_{PWM} = 100\ kHz` has been verified
  
Pinout
------


.. image:: Digital_SI_Inverter_rev03/pinout_inverter_rev03.png
  :height: 250
  :align: center

.. csv-table:: Defined pin mapping uz_d_inverter
   :file: Digital_SI_Inverter_rev04/uz_d_inverter_pin_mapping.csv
   :widths: 40 40 60 50 50 
   :header-rows: 1


Compatibility 
-------------

This digital adapter inverter board is directly compatible with the :ref:`uz_inverter_adapter` IP-Core.
It can be used in any of the D1-D4 digital adapter card slots in the UltraZohm, provided the correct CPLD is flashed. 
The card is directly compatible with the :ref:`Analog_LTC2311_16_Rev05`, :ref:`Analog_LTC2311_16_v3` and :ref:`Analog_LTC2311_16_v2` cards.

Switching behavior
-------------------

Double Pulse Test
The DPT is an important experimental technique in power electronics for characterizing the switching behavior of semiconductor devices under realistic operating
conditions. Typically, it offers a comprehensive means of analyzing the dynamic response during the transition (turn-on and turn-off events), revealing useful insights
into device performance and efficiency.
The DC link voltage was set to :math:`V_dc = 48\ V`48V, with a load inductance of :math:`L = 1\ mH` and a load resistance of :math:`RL = 400\ mΩ`. The desired switching current was maintained at :math:`i_D = 30\ A` throughout the test.  the experimental waveforms of the DPT are shown below. 
One must note that, due to design constraints, measurement of the drain current was not included, as it was challenging to obtain on hardware.

.. image:: Digital_SI_Inverter_rev04/DPT_FULL_1.png
  :height: 250
  :align: center

.. image:: Digital_SI_Inverter_rev04/Turn_off_Switching_Transient.png
  :height: 250
  :align: center

.. image:: Digital_SI_Inverter_rev04/Turn_on_Switching_Transient.png
  :height: 250
  :align: center


Setup before first use and implementation with Inverter Interface IP-Core
=========================================================================

CPLD
----

Make sure that the correct CPLD is flashed in the corresponding digital adapter slot.
For this adapter card the ``uz_d_3ph_inverter`` CPLD needs to be flashed.
Download this CPLD from the `UltraZohm CPLD Repository <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/>`_.
Follow :ref:`this guide  <label_cpld_programming>` on how to flash the correct CPLD on the UltraZohm.

Software implementation
-----------------------

This adapter card interacts with the user via the highly sophisticated :ref:`uz_inverter_adapter` IP-Core and its associated driver.
Follow :ref:`this guide <inverter_adapter_usage>` to integrate the IP-Core into the FPGA and to set up the software driver.
While following this guide, be sure to adjust the `linear interpolation parameters` for the ``inverter_adapter_config``. 
For this inverter card they should be:

.. code-block:: c
 :caption: linear interpolation parameters for config struct

 .linear_interpolation_params = {-289.01f, 218.72f}

Set the deadtime in the ``uz_interlockDeadtime2L_staticAllocator.c`` file to an appropriate value. 
A safe value with a considerable safety margin is ``200ns``. 
No matter what, the deadtime should not be lower than ``150ns``.

.. code-block:: c
 :caption: set the deadtime in the ``uz_interlockDeadtime2L_staticAllocator.c`` file. Shown is an example for the D1 slot.

 static uz_interlockDeadtime2L interlock_slotD1_pin_0_to_5 = { 
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_UZ_INTERLOCKDEADTIME_0_BASEADDR,
    .clock_frequency_MHz = 100,
    .deadtime_us = 0.2,
    .inverse_bottom_switch = false };

To enable or disable the ``PWM_EN`` for normal operation, add the following code to the isr.c. 
It should always be ensured, that the ``PWM_EN`` is handled correctly. 
I.e. if the UltraZohm transitions into its error-state e.g. because the OCP is triggered, it must be ensured, that the ``PWM_EN`` is retracted.
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
 i_abc_Amps.a = Global_Data.aa.A1.me.ADC_A4 * 12.5f;
 i_abc_Amps.b = Global_Data.aa.A1.me.ADC_A3 * 12.5f;
 i_abc_Amps.c = Global_Data.aa.A1.me.ADC_A2 * 12.5f;
 i_DC_Amps = Global_Data.aa.A1.me.ADC_B5 * 12.5f; 

In order to use the over current and over temperature protection, the following code has to be added to the isr.c as well. 
These are optional features and can be left out if they aren't required.

.. code-block:: c
 :caption: Additions for isr.c if OCP or OTP are used
 
 //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
 //Overtemperature for H1
 if (!Global_Data.av.inverter_outputs_d1.FAULT_H1) {
    ultrazohm_state_machine_set_error(true);
 }
 //Overtemperature for L1
 if (!Global_Data.av.inverter_outputs_d1.FAULT_L1) {
    ultrazohm_state_machine_set_error(true);
 }
 //Overtemperature for H2
 if (!Global_Data.av.inverter_outputs_d1.FAULT_H2) {
    ultrazohm_state_machine_set_error(true);
 }
 //Overtemperature for L2
 if (!Global_Data.av.inverter_outputs_d1.FAULT_L2) {
    ultrazohm_state_machine_set_error(true);
 }
 //Overtemperature for H3
 if (!Global_Data.av.inverter_outputs_d1.FAULT_H3) {
    ultrazohm_state_machine_set_error(true);
 }
 //Overtemperature for L3
 if (!Global_Data.av.inverter_outputs_d1.FAULT_L3) {
    ultrazohm_state_machine_set_error(true);
 }
 //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
 //Binding of the signals to the driver is slightly unintuitive 
 //Overcurrent for Phase A
 if (!Global_Data.av.inverter_outputs_d1.OC_L1) {
    ultrazohm_state_machine_set_error(true);
 }
 //Overcurrent for Phase B
 if (!Global_Data.av.inverter_outputs_d1.OC_H1) {
    ultrazohm_state_machine_set_error(true);
 }
 //Overcurrent for Phase C
 if (!Global_Data.av.inverter_outputs_d1.OC_L2) {
    ultrazohm_state_machine_set_error(true);
 }
 //Overcurrent for DC-link
 if (!Global_Data.av.inverter_outputs_d1.OC_H2) {
    ultrazohm_state_machine_set_error(true);
 }
 

References
==========

.. _dig_si_inverter_references:

* :download:`Schematic Rev03 <Digital_SI_Inverter_rev03/UZ_D_Inverter_rev03.pdf>`
* `uz_d_inverter Repository with Altium project <https://bitbucket.org/ultrazohm/uz_d_inverter>`_

Known issues
============

As of this moment, no issue in Rev04 is known.

Designed by 
===========

Krunal Patel/ Dennis Hufnagel (THN), 06/2025

Acknowledgments
---------------

Special thank you for their support during the design and testing phase goes to Eyke Aufderheide (TUM), Michael Hoerner (THN) and Tobias Schindler (THN).