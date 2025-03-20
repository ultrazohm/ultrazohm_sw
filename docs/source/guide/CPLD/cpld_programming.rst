.. _label_cpld_programming:

====================
Programming the CPLD 
====================

CPLD Versions
-------------

There are different versions available - for :math:`\leq` ``Rev04``:

* `LA4128V <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/ispMACH/LA4128V/>`_ for old revisions and Rev04 with serial number UZ2021-002-001-200-0001 to UZ2021-001-001-004-0004
* `LC4256V <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/ispMACH/LC4256V/>`_ for all other Rev04 with serial number UZ2022-001-001-401-0007 up to UZ2024-001-001-0401-0031

For UZ  :math:`\geq`  ``Rev05``:

* `MachXO2 LCMXO2-2000HC <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/MachXO2/D_Slot_CPLD_LCMXO2-2000HC-4TG100C/>`_ 5x D-SLot CPLD
* `MachXO2 LCMXO2-4000HC <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/MachXO2/S3C_CPLD_LCMXO2-4000HC-4TG144C/>`_ 1x S3C


**CPLD programs** 

Note that there are separate CPLD programs for each series and type in the `repository <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/>`_.
The folders are structured and named accordingly.
Before programming, make sure the Diamond Programmer by Lattice is installed and clone the CPLD repository, see :ref:`install_lattice` for details. 

**JTAG programmers** 

Different JTAG programmers are used throughout the hardware revisions of the carrier board. The following diagram will help you determine which of 
the following step-by-step guides is appropriate for your UltraZohm system.

.. mermaid::
    :align: center
    :caption: JTAG programmer guide

    flowchart TD;
    A[JTAG programmer] -->|Carrier board revisions below Rev04 and most Rev04|B[Trenz TE0790 <br> for LA4128V or LC4256V] ;
    A -->|Some Rev04 carrier board revisions|C[IsoJTAG <br> for LA4128V or LC4256V];
    A -->|Carrier board revisions Rev05 and later|D[Onboard USB-C <br> for MachXO2];

If you are not sure whether your UltraZohm is equipped with the TE0790 or an IsoJTAG, 
simply remove the bottom cover of the UltraZohm case and take a look at the JTAG programmer board. 
If it is a green PCB, as shown in the figures in the Trenz TE0790 section below, it is a 
TE0790. If the PCB is purple, as shown in the IsoJTAG section below, it is an IsoJTAG.

Step-by-step for Trenz TE0790
-----------------------------

1. Remove the programmer (normally used for programming the Zynq) from X8 of the Carrier Board.
   The best way to access the programmer is to remove the bottom cover of the UltraZohm case (4 screws).
   The TE0790 is the small green PCB with the four dip switches in the figure below.

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

   - D1-D4 with **30Tx**
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

Step-by-step for IsoJTAG :ref:`uz_per_jtag`
--------------------------------------------

1. The IsoJTAG programmer is permanently connected to the SoM and the D-slot CPLDs.

.. image:: images_jtag/isojtag.png
   :width: 300
   
2. Plug the USB cable into JTAG connector on the UltraZohm front panel.
   Start the Diamond Programmer by Lattice and open the file in the git repository ``Programm_all5_CPLDs.xcf`` with regard to the installed CPLD. 

.. image:: cpld_programming/LA4128V.png

In this example the `CPLD LA4128V <https://www.mouser.de/ProductDetail/Lattice/LA4128V-75TN100E?qs=k0CM90KAVUoIZqpZ9HTArg%3D%3D>`_ is installed on the carrier board.

3. Chose the proper CPLD software and chose which CPLDs you want to program. The standard configuration is:

   - D1-D4 with **30Tx**
   - D5 for the encoder with **30Rx** 
   
Note that it is possible to program only one of the CPLDs by the enable check box in each line.

.. image:: cpld_programming/diamond_programmer_settings.jpg

4. Turn on the power of the UltraZohm. 

5. Click **Detect cable** and set the right port for **UltraZohm B Location**. Depending on the OS, the mapping can differ (in this case the UltraZohm B Location Port is mapped on FTUSB-0). 

.. image:: cpld_programming/detect_cable.png

6. Setup a custom clock divider TCK 3.

.. image:: cpld_programming/clockdivider.png

7. Click on "Program", after successful programming it should look like this:

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
"""""""""""

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
"""

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
###############################

.. image:: cpld_programming/error_cannot_find_cplds.png

Close all Vivado and Vitis instances and retry. Restart your PC and retry.

See also
--------

* `Lattice Diamond Programmer download <http://www.latticesemi.com/programmer>`_
* `CPLD software git <https://bitbucket.org/ultrazohm/cpld_lattice/src/master/>`_
* `Trenz Programmer Wiki <https://wiki.trenz-electronic.de/display/PD/TE0790+TRM>`_
