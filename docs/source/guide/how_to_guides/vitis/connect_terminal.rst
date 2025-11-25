==========================================
Connection with the Vitis Serial Terminal
==========================================

* The serial terminal outputs messages from the SoM
* For debugging purposes of the software, errors or assertions are displayed on the serial terminal
* The serial terminal connects the computer with the UZ using UART

JTAG module :ref:`uz_per_jtag`
--------------------------------------

The  Iso_JTAG Debugger has 4 channels:

1. JTAG to the Zynq-SoM
2. JTAG to the CPLD
3. UART Zynq-SoM
4. UART not connected

In the usual use case, the Channel 2 or Channel B is automatically mapped to the CPLD. 
When connecting to the computer, three new COM channels appear in the windows device manager.

.. image:: images_serial_terminal/com_ports.png
   :width: 500

Usually the channel in the middle is the right one to connect to the serial terminal (in this case COM9). Click the **+** Button on the *Vitis Serial Terminal* section an select the right COM Port.
The picture displays the connection in windows, in ubuntu the naming can be different see :ref:`linux_com`.

.. image:: images_serial_terminal/connect_com.png
   :width: 500


Connection with JTAG module `Trenz TE0790 <https://wiki.trenz-electronic.de/download/attachments/43680347/TE0790-02%20top-numbered.png?version=1&modificationDate=1507707618000&api=v2>`_
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

The Trenz JTAG Debugger has two channels:

1. JTAG to the Zynq-SoM
2. UART Zynq-SoM

The JTAG Channel is automatically mapped and the second port is the remaining COM Port in Vitis.
