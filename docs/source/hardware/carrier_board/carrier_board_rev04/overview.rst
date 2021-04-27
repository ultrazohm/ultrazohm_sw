========
Overview
========

An overview about interfaces is shown in chapter  :ref:`label_carrier_board_overview`.

Short summary of new features:
------------------------------------------------------

* New connector for front panel buttons and LEDs to provide the isolated GPIO interface available for other purposes (e.g. interaction with external systems)
* External stop circuitry integrated on isolated GPIO interface. It is for the default UltraZohm system software usage not neccessary any more to connect the dummy connector to keep the safety loop closed. The external stop function now can be used independantly of the front panel button.
* Isolated GPIO interface extended to 12 I/Os available at connector X12. The external stop functionality is dedicated to isoGPIO12, but could also be freely used if required. 
* Second ethernet port accessible
* GTH lanes on analog socket A1 available
* GTR lanes on new SATA sockets available
* Changed position of main power supply input connector (X14).
* More SMD connector for faster assembly process of PCB.
* Simplified power supply of 1V8_PER (now: uses same DCDC as 1V8_MOD)
* The PS pins PS_ANL_GPIO_02, PS_DIG_GPIO_01 and PS_DIG_GPIO_02 were removed to have more GPIO pins for the isolated GPIO interface available.
* Each of the analog sockets A1..A3 have their unique chip select signal to trigger the ADCs. To stay backward compatible with previous carrier boards, the pins X5-53 and X5-54 are shorted. For more information see this `forum entry <https://forum.ultrazohm.com/t/ultrazohm-carrier-v4/46/post/179/>`_.

Downloads
---------

:download:`Schematic Rev04 <altium_output/SCH-UZ_Carrier_Board_Rev04.pdf>`

:download:`Assembly Drawing Rev04 <altium_output/AD-UZ_Carrier_Board_Rev04.pdf>`

:download:`Draftsman Rev04 <altium_output/DFT-UltraZOhm_CarrierBoard_Rev04.pdf>`

:download:`Gerber and Drill Files Rev04 <altium_output/UZ_Carrier_Board_Rev04_Gerber_and_Drill_Files.zip>`