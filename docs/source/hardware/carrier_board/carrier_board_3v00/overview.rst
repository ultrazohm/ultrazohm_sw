========
Overview
========

An overview about interfaces is shown in chapter  :ref:`label_carrier_board_overview`.

Short summary of changes towards Carrier_Board_2v00:
------------------------------------------------------

* All five CPLDs are programmed in daisy chain. The possibility to jumper individual CPLDs to the programmer at connector X2 is not present any more. Connector X2 was removed.
* Some fast `Single Ended` signals got series termination resistors (75 Ohm) at signal source
* New level shifter (TXS01018) due to inconsistency behaviour of the LSF0108 chips. Both are implemented on this PCB revision as backup solution and can either be assembled.
* Changed Power-On Sequence according to some inserted cross enable signals between DC/DCs.
* Carrier Board rush-in current limitation implemented

Downloads
---------

:download:`Schematic 3v00 <altium_output/SCH_UltraZOhm_CarrierBoard_3v00.pdf>`

:download:`Assembly Drawing 3v00 <altium_output/ASM_UltraZOhm_CarrierBoard_3v00.pdf>`

:download:`Draftsman 3v00 <altium_output/DFT_UltraZOhm_CarrierBoard_3v00.pdf>`