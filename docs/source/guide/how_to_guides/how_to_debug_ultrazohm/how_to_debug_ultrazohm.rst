.. _how_to_debug_ultrazohm:

==========================
How to debug the UltraZohm
==========================

First steps
**************

In the following are some first steps to debug the UltraZohm (see also :issue:`78`).

- Power-cycle everything
- Check if the LEDs on the front panel blink when programmed 
- Check the output of the Vitis Serial Terminal after programming
- Delete the Vitis workspace folder and rebuild the workspace with the generate workspace tcl 
- Check if you can ping the UltraZohm, if the Javascope does not work
- Delete temporary files of Vivado (i.e., everything in ``/vivado/project`` except ``ultrazohm.xpr``)
- Clone the repo to a new folder and test if this works
- Ask for help in the slack
- Create an issue if you find a problem / bug


	
	
	