=======================
Binary Export (to SD)
=======================

To be able to work with the UltraZohm without the need of flashing it before each usage, you can generate a bootable binary from your code and replace the default boot.bin. 

How to use
----------

1. Open the UltrZohm workspace in Vitis
2. ``Xilinx`` -> ``Create Boot Image``
3. ``Import from existing BIF file``->Import file path: ``Path to UZ-repo\vitis\software\BootImage\GenerateBootImage.bif``
4. Probably you need to adjust the file paths to the boot image partitions in the corresponding submenu (see gif 2)
    Variant 1: Exchange everything before ``\vitis`` with the path to the UZ-repo
    Variant 2: Exchange everything before ``\vitis`` with as much "..\" as you have folder-levels to your repo-path. If you have the correct number, Vitis stops writing "partition file does not exist"
5. ``create Image``
6. Move boot.bin from the BootImage folder to the SD


.. figure:: GenerateBootImage.gif

  Create Image with unchanged BIF (only works if your UZ-repo is at the same path as in the example)
.. figure:: ChangePaths.gif

  Adjust paths in the partitions menu
