.. _dig_optical_2vxx:

=============================
Digital Optical 16Tx 3Rx 2vXX
=============================

.. image:: optical_16tx_v2/optical_16tx_v2_complete.jpg
   :width: 500

Functionality
-----------------------
* Transmits up to 16 optical signals, e.g. gate signals. 
* Receives up to 3 optical signals, e.g. error signals. 
* The signals are passed through the CPLD first. Here additional functionality can be implemented, e.g. checking for invalid switching combinations or introducing a dead time.


Before first use
----------------------------
Solder in up to 

* 16 optical transmitters: **Broadcom HFBR-1521Z**
* 3 optical receiver: **Broadcom HFBR-2521Z**

Please refer to this page for detailed :ref:`dig_optical_soldering` of the receivers and transmitters.


.. image:: optical_16tx_v2/optical_16tx_v2_transmitter.jpg
   :height: 500
            
           
* Solder resistors (R14, R19) on the bottom side to connect optical receivers 
* Program CPLDs with firmware, see :ref:`label_cpld_programming` for details

Known issues
-----------------------
.. warning:: 
   When turning off the UltraZohm, the optical transmitters turn on shortly, solder in the pull down resistors to avoid this.
   
* Solder pull down resistors, 2kOhm to each gate signal
  
.. image:: optical_16tx_v2/optical_16tx_v2_pulldown.jpg
   :height: 500

.. image:: optical_16tx_v2/optical_16tx_v2_pulldown_schematic.jpg
   :width: 500

Compatibility 
----------------------
Slots D1 to D4 can be used without limitations

See also
"""""""""""""""
* :download:`Schematic 2v02 <optical_16tx_v2/SCH_Optical_16tx_2v02.pdf>`
* :download:`Assembly Drawing 2v02 <optical_16tx_v2/ASM_Optical_16tx_2v02.pdf>`
* :ref:`label_cpld_programming`


Designed by 
"""""""""""""""
Thomas Kreppel (TUM), Eyke Liegmann (TUM) in 09/2019
