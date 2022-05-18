.. _label_cpld_programming:

====================
Programming the CPLD 
====================



Step-by-step
------------

0. Install the Diamond Programmer by Lattice and clone the CPLD repository, see :ref:`install_lattice` for details. 

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
