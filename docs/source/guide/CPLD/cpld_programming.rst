.. _label_cpld_programming:

====================
Programming the CPLD 
====================

CPLD Versions
--------------

There are different versions available - for :math:`\leq` ``Rev04``:

* `LA4128V <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/LA4128V/>`_ for old revisions and Rev04 with serial number UZ2021-002-001-200-0001 to UZ2021-001-001-004-0004
* `LC4256V <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/LC4256V/>`_ for all other Rev04 with serial number UZ2022-001-001-401-0007 up to UZ2024-001-001-0401-0031

For UZ  :math:`\geq`  ``Rev05``:

* `MachXO2 LCMXO2-2000HC <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/MachXO2/D_Slot_CPLD_LCMXO2-2000HC-4TG100C/>`_ 5x D-SLot CPLD
* `MachXO2 LCMXO2-4000HC <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/MachXO2/S3C_CPLD_LCMXO2-4000HC-4TG144C/>`_ 1x S3C


Note that there different folders for the CPLD programs in the `repository <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/>`_.
Before programming, make sure  the Diamond Programmer by Lattice is installed and clone the CPLD repository, see :ref:`install_lattice` for details. 

Step-by-step for `Trenz TE0790 <https://wiki.trenz-electronic.de/download/attachments/43680347/TE0790-02%20top-numbered.png?version=1&modificationDate=1507707618000&api=v2>`_
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 

1. Remove the programmer (normally used for programming the Zynq) from X8 of the Carrier Board.

.. image:: cpld_programming/Programmer_Zynq_position.jpg
   :width: 500

2. Set the DIP-switches S2 on the programmer to **(1on-2off-3off-4off)**.

3. Plug the programmer onto X1. Make sure that the hole in the programmer aligns exactly with the mounting hole on the carrier board.

.. image:: cpld_programming/Programmer_CPLD_position.jpg
   :width: 500

4. Have all jumpers on the Carrier Board plugged on to X2 to create the daisy chain. This step is not necessary for Rev04 and later. 

.. _cpldjumper:

.. image:: cpld_programming/jumper_chain.png
   :width: 500

.. image:: cpld_programming/schematic.png
   :width: 500


5. Start the Diamond Programmer by Lattice and open the file in the git ``Programm_all5_CPLDs.xcf``

.. image:: cpld_programming/diamond_programmer_getting_started2.png

6. Chose the proper CPLD software and chose which CPLDs you want to program. The standard configuration is:

   - D1-D4 with **26Tx_with_enable**
   - D5 for the encoder with **30Rx** 
   
Note that it is possible to program only one of the CPLDs by the enable check box in each line.

.. image:: cpld_programming/diamond_programmer_settings.jpg

7. Plug in the USB cable and turn on the power of the UltraZohm. The programmer on X1 should light up.

8. Click on "Program", after successful programming it should look like this:

.. image:: cpld_programming/diamond_programmer_successful_closeup.png

9. Turn off the UltraZohm. Remove the programmer from X1 of the Carrier Board, put the DIP switches back in their original position **(1on-2off-3off-4on)** and plug it back to X8 next to the Zynq processor. Make sure that the mounting hole in the programmer aligns exactly with the hole on the carrier board.

.. image:: cpld_programming/Programmer_Zynq_position.jpg
   :width: 500


.. _label_cpld_programming_ftdi4ch:

Step-by-step for :ref:`uz_per_jtag`
--------------------------------------

1. Start the Diamond Programmer by Lattice and open the file in the git repository ``Programm_all5_CPLDs.xcf`` with regard to the installed CPLD. 

.. image:: cpld_programming/LA4128V.png

In this example the `CPLD LA4128V <https://www.mouser.de/ProductDetail/Lattice/LA4128V-75TN100E?qs=k0CM90KAVUoIZqpZ9HTArg%3D%3D>`_ is installed on the carrier board.

2. Chose the proper CPLD software and chose which CPLDs you want to program. The standard configuration is:

   - D1-D4 with **26Tx_with_enable**
   - D5 for the encoder with **30Rx** 
   
Note that it is possible to program only one of the CPLDs by the enable check box in each line.

3. Plug in the USB cable and turn on the power of the UltraZohm. The three green LED's on the programmer should light up.

4. Click **Detect cable** and set the right port for **UltraZohm B Location**. Depending on the OS, the mapping can differ (in this case the UltraZohm B Location Port is mapped on FTUSB-0). 
**
.. image:: cpld_programming/detect_cable.png

5. Setup a custom clock divider TCK 3.

.. image:: cpld_programming/clockdivider.png

6. Click on "Program", after successful programming it should look like this:

.. image:: cpld_programming/cpld_programmed.png

Step-by-step for MachXO2
-------------------------

For programming MachXO2 CPLDS, the settings must be equivalent to :ref:`label_cpld_programming_ftdi4ch`
* Setup a custom clock divider TCK 3. 
* Click **Detect cable** and set the right port for **UltraZohm B Location**. 
* Depending on the OS, the mapping can differ (in this case the UltraZohm B Location Port is mapped on FTUSB-1). 

.. image:: images_diamond/scan_blocation.png  
   :width: 1000

D-Slot CPLD
############

1. Powering On the UZ

   * Connect the device to a 230V power source using the port on the back.
   * Press the Power Button to turn on the Carrier.
   * The green power button and red stop button will indicate that the system is on.
   * Connect your computer to the USB-C slot on the front panel.

.. image:: images_diamond/d_00.jpg  
   :width: 1000

2. Perform a JTAG Scan on the UZ to ensure the correct configuration.

.. image:: images_diamond/d_verify.png  
   :width: 1000

3. The scan should detect five CPLDs, confirming the correct package.

.. image:: images_diamond/d_01.png  
   :width: 1000

4. The programming files are now ready for selection. If programming is successful, a green "PASS" checkbox will confirm the process.

.. image:: images_diamond/d_02.png  
   :width: 1000
   
S3C
####

1. Powering On the UZ

   * Connect the device to a 230V power source using the port on the back.
   * The blue power button will indicate that the system is off.
   * Connect your computer to the USB-C slot on the front panel.

.. image:: images_diamond/s3c_00.jpg  
   :width: 1000

2. Perform a JTAG Scan on the UZ to ensure the correct configuration.

.. image:: images_diamond/s3c_verify.png  
   :width: 1000

3. The scan should detect one CPLD, confirming the correct package.

.. image:: images_diamond/s3c_02.png  
   :width: 1000

4. The programming file is now ready for selection. If programming is successful, a green "PASS" checkbox will confirm the process.

.. image:: images_diamond/s3c_03.png  
   :width: 1000

Known issues
------------

Not possible to find the CPLDs
""""""""""""""""""""""""""""""

.. image:: cpld_programming/error_cannot_find_cplds.png

Close all Vivado and Vitis instances and retry. Restart your PC and retry.

See also
--------

* `Lattice Diamond Programmer download <http://www.latticesemi.com/programmer>`_
* `CPLD software git <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/>`_
* `Trenz Programmer Wiki <https://wiki.trenz-electronic.de/display/PD/TE0790+TRM>`_
