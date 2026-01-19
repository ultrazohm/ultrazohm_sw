.. _how_to_debug_ultrazohm:

===============
Troubleshooting 
===============

In the following are some first steps to debug the UltraZohm (see also :issue:`78`).

- Power-cycle everything (UltraZohm and your computer)
- Check if the LEDs on the front panel blink when programmed 
- Check the output of the Vitis Serial Terminal after programming
- Delete the Vitis workspace folder and rebuild the workspace with the generate workspace tcl 
- If the Javascope does not work, check if you can ping the UltraZohm at the IP stated in the Serial Terminal during the start up procedure (default: ``192.168.1.233``)
- Delete temporary files of Vivado (i.e., everything in ``/vivado/project`` except ``ultrazohm.xpr``) and try to re-generate the bitstream
- Clone the repo to a new folder and test if this works
- Ask for help in the slack
- Create an issue if you find a problem / bug


	
	
	