.. _current_measurement_box:

Current Measurement Box
=======================

The current measurement box is an external analog measurement unit for the UltraZohm platform.
It provides four isolated current sensing channels and fully differential analog outputs via RJ45 connectors.

.. figure:: whole_system_block_diagram.png
   :align: center
   :width: 700px

   Block diagram showing the signal and power flow between the UltraZohm system carrier board, current measurement box, and the LTC2311-16 ADC card.

Common Features
---------------

- 4 independent current sensing channels
- DC and AC current measurement
- Compatible with LEM CASR-NP and Sensitec CAS5000 current sensors
- Fully differential analog output per channel
- RJ45 output interface for connection to UltraZohm analog adapter cards

Power Supply Cable
------------------

The power supply cable is identical for all revisions of the current measurement box.
It can be directly plugged into the :ref:`Analog_LTC2311_16` ADC card to use the 24 V supply from the UltraZohm.
Use an IPD1-102-D connector on the current measurement box side and an IPD1-108-D connector on the UltraZohm side.

.. figure:: power_supply_cable.jpg
   :align: center
   :width: 500px

   Power supply cable for the current measurement box.

.. _current_measurement_box_supported_sensors:

Supported Sensors
-----------------

The table lists the supported current transducers.
The Sensitec CAS5000 values are taken from the :download:`Sensitec CAS5000-Series data sheet <SENSITEC_CAS5000-Series_DSE.pdf>`.

========================  ==============  ============  ======================  ============  ===================  ===================
Sensor Model              Manufacturer    Technology    Nominal Current (Arms)   Range (A)     Sensitivity (mV/A)    Bandwidth (±3 dB)
========================  ==============  ============  ======================  ============  ===================  ===================
CASR 6-NP                 LEM              Fluxgate               6                 ±20               104.2               ~300 kHz
CASR 15-NP                LEM              Fluxgate              15                 ±51                41.67              ~300 kHz
CASR 25-NP                LEM              Fluxgate              25                 ±85                25.0               ~300 kHz
CASR 50-NP                LEM              Fluxgate              50                ±150                12.5               ~300 kHz
STB-6CAS/R/F              Sinomags         Fluxgate               6                 ±20               104.2               ~400 kHz
CAS5015SRA                Sensitec          TMR                  15                 ±51                41.67              ~400 kHz
CAS5025SRA                Sensitec          TMR                  25                 ±85                25.0               ~400 kHz
CAS5050SRA                Sensitec          TMR                  50                ±150                12.5               ~400 kHz
CAS5075KRA                Sensitec          TMR                  75                ±180                 6.25              ~400 kHz
========================  ==============  ============  ======================  ============  ===================  ===================

.. note::
   CAS50xxKRA have higher clearance and different footprint, e.g. CAS5075KRA is only supported by Rev03.

Revisions
---------

..  toctree::
   :maxdepth: 1
   :caption: Revisions

   rev03
   rev02

Downloads
---------

- `Altium project repository <https://bitbucket.org/ultrazohm/uz_per_external_current_sensing/src/master/>`_
- :download:`Current sensor evaluation report <Report_current_sensor_evaluation.pdf>`
- :download:`Current sensor evaluation presentation <Presentation_current_sensor_evalution.pdf>`
- :download:`Sensitec CAS5000-Series data sheet <SENSITEC_CAS5000-Series_DSE.pdf>`
