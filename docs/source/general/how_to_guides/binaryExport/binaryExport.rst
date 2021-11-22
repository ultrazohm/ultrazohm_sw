=======================
Binary Export (to SD)
=======================

To be able to work with the UltraZohm without flashing it before each usage, a bootable binary can be generated. 
This binary replaces the default ``BOOT.bin`` and the custom code executes after power-cycle of the UltraZohm. 

Generate boot image
===================

1. Open the UltrZohm workspace in Vitis
2. In the top menu, select``Xilinx`` -> ``Create Boot Image``
3. Select ``Import from existing BIF file`` (radio buttons)
4. Set the ``Import BIF file path`` to ``~vitis\software\BootImage\GenerateBootImage.bif`` (see :numref:`gen_boot_gif`)

.. _gen_boot_gif:

.. figure:: GenerateBootImage.gif

  Select existing BIF file.


5. Adjust the file paths at ``Boot image partitions`` (see :numref:`boot_adjust_paths`) since the .BIF file uses absolute paths
6. Select each of the boot partitions, select ``Edit`` and browse to their absolute path on the local machine
7. Alternative: Change the path to the boot image partitions in the corresponding sub-menu (see :numref:`boot_adjust_paths`)
   
   - Option 1: Exchange everything before ``\vitis`` with the path to the UZ-repo
   - Option 2: Exchange everything before ``\vitis`` with as much "..\" as you have folder-levels to your repo-path. If you have the correct number, Vitis stops writing "partition file does not exist"


.. _boot_adjust_paths:

.. figure:: ChangePaths.gif

  Adjust paths of boot image partitions. 


8. Select ``create Image``

Change BOOT.bin on SD-Card
==========================

1. Shut-down the UltraZohm
2. Unplug the power connection and make sure that power is off
3. Remove the SD-Card
4. Connect the SD-Card to the local machine
5. Copy ``BOOT.bin`` from the ``uz-repo\vitis\software\BootImage`` folder to the SD-Card of the UltraZohm (replace the existing ``BOOT.bin``
6. Plug in the power connection and power-cycle the UltraZohm


Resources
=========

- https://www.xilinx.com/html_docs/xilinx2021_1/vitis_doc/jed1590410655455.html
- https://www.xilinx.com/html_docs/xilinx2018_1/SDK_Doc/SDK_tasks/task_creatingabootimage.html