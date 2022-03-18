.. interface_powerelectronics:

==============================
Interface of power electronics
==============================


To control an inverter with the UltraZohm the power electronic should be controlled directly by the gate signals. In order to get your inverter compatible with the UltraZohm platform, follow the instructions below. The signals to handle with might be gate signals, error-flags and current or voltage measurements. 

Digital Signals
================

Multiple options are available to handle input or output signals of your inverter:

- Optical signals with optical adapter card (adapter_cards/digital/optical_general)
- Voltage signals with digital voltage adapter card ()
    - Single ended signals from inverter to UltraZohm with 3.3V or 5V
    - Single ended signals from UltraZohm to inverter with 3.3V, 5V or 15V
    - Differentials signals with RS422 transmitter and receiver (Input and Output)


Analog Signals
==============

For measurement of phase currents or voltages an analog adapter card is available. It is equipped with an 16 bit ADC of +-5V and an OPV to adjust the incoming signal. To use the basic configuration without setting up the OPV on the adapter card, scale your voltage signals to +-5V. An overview of possible signal types is listed below. Pleas refer the documentation of the latest analog adapter card for more technical details (link analog adapter card). The adapter card is equipped with two RJ45-sockets --> See .. _adapter_cards for pinout configuration.

- Voltage signals
    - Single ended with offset voltage
    - Single ended with ground potential
    - Differential signal
- Current signals
    - Using internal shunt resistor on adapter card