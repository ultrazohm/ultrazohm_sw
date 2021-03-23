============
Known issues 
============

How to debug the UltraZohm
**************************

Following are some steps one can take to debug if there are problems with the UltraZohm (see :issue:`78`).

- Powercycle everyhting
- Delete temporary files of Vivado (i.e., everything in ``/vivado/project`` except ``ultrazohm.xpr``)
- Delete the Vitis workspace folder and rebuild the workspace with the generate workspace tcl
- Check the output of the Vitis Terminal in debug mode
- Check if you can ping the UltraZohm if the Javascope does not work
- Clone the repo to a new folder and test if this works
- Create an issue if you find a problem
- Ask for help in the forum / slack


Known issues
************

Wrong path after a Vivado/Vitis project is imported from GIT or another computer
--------------------------------------------------------------------------------

	• During evaluation of the GIT workflow for importing the Vitis project from Bitbucket, it happened sometimes, that during the first integration the path for the "Platform Project" was wrong
	• Respecting all the steps from "Procedure when initially using a GIT project", during the final clean and build, the path for the "Domain" from the "Application projects" was wrong

	..	image:: ./images_problems/problems0.png
	
	• As it can be seen, for both "Application Projects" the "xxx_system.sprj" file must be opened, wherein, the path for platform was missing/wrong.
	• This is due to different folder people saving there Vivado/Vitis projects on their personal computer.
	• Unfortunately, Xilinx uses here an absolute (and not a relative) path.

	..	image:: ./images_problems/problems1.png
	
	• Solution: Click on the Platform name, right from the error x, and select the present application, with the absolute path on your own computer.

	..	image:: ./images_problems/problems2.png
	..	image:: ./images_problems/problems3.png
	
	• Solution: After a new clean and build the present platform will be recognized again. 
	
	..	image:: ./images_problems/problems4.png

	• The problems are also described herein: `Xilinx Forum <https://forums.xilinx.com/t5/Vitis-SDAccel-and-SDSoC/Vivado-and-Vitis-Workflow/m-p/1063234#M4633>`_

Xsa-file is not able to update Platform
---------------------------------------

	• Sometimes it happened, that during Update of the xsa-file, an error occurres:

	..	image:: ./images_problems/problems5.png
	
	• Solution: So far it was the impression, that this error was sporadic from Xilinx. Therefore, just import/update the xsa-file again and again. Sometimes two tries were necessary until it worked. 
	• However, no reproducible way for the error was obvious. 

	
After Update Hardware specification, the "Out-of-Date" message remains
------------------------------------------------------------------------

	• It sometimes happened, that even if the a new Hardware Specification was read (the xsa-file), the "Out-of-Date" remains active. 
	• As long as this message is present, a successful build of the "Application Projects" is impossible!
	
	..	image:: ./images_problems/problems6.png
	
**Solution1**:  As described in "Vitis - Procedure when initially using a GIT project", Reset the BSP Resources of the "Platform Project", Clean and build the "Platform Project" again (needs 5-10 minutes).

**Solution2**: Instead of clicking, you can execute the following lines one-by-one in the XSCT terminal::

   platform active UltraZohm
   domain active FreeRTOS_domain
   bsp regenerate
   domain active Baremetal_domain
   bsp regenerate
   domain active FSBL_domain
   bsp regenerate
   platform generate

After Update Hardware specification, the error message occurs
-------------------------------------------------------------	

	..	image:: ./images_problems/problems7.png
	
	• The "Platform Project" was not correctly updated in this case, after inserting the new xda-file. 
	• Solution:  As in the case before and as described herein Procedure when initially using a GIT project, Reset the BSP Resources of the "Platform Project", Clean and build the "Platform Project" again (needs 5-10 minutes).

	
rtdi.exe stopped working when trying to compile the platform
-------------------------------------------------------------	
  
	• Solution: restart Vitis

	
Porting vivado project to 2019.2
-------------------------------------------------------------

After opening the project in 2019.2 make sure to delete the entire AXI interface and also deactive it in the ZynqUltraScale settings.
Afterwards add all the interconnections and AXI busses again, otherwise it might come to problems later on when writing to the registers 
of the PL, i.e. 0x8000_0000 adresses and above.
	
	
	