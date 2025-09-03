.. _label_diamond_create_program:

===========================================
Create a CPLD program using Lattice Diamond
===========================================

The main goal of this section is to describe the necessary steps for creating a simple program for the 
``MACHXO2`` CPLDs on the UltraZohm :math:`\geq` Rev05.
All signals from the FPGA to the digital adapter cards pass through the CPLDs.


D-Slot CPLDs
############

Everything is programmed inside the project ``uz_d_slots.ldf``.
It is located in the repository at ``MACHXO2/D_Slot_CPLD_LCMXO2-2000HC-4TG100C/uz_d_slots/``.
Here we can create additional ``implementations`` for the CPLD.
The advantage of having all CPLD programs within one project is that VHDL code from other files can be used, but every file has its constraints (e.g., all signals function as inputs versus all signals function as outputs).

Step-by-step
------------

1. Open Lattice Diamond and there the project ``uz_d_slots.ldf``. Click ``Open``.

.. figure:: images_diamond/01.png
  :width: 1000

2. For creating a new CPLD program, click ``Clone Implementation`` by right-clicking on the template ``template_dslots`` and the subsequent context menu.

.. figure:: images_diamond/02.png
  :width: 1000

3. Provide a proper ``Name`` and give the ``Directory`` the same name. Select the ``Default Strategy`` to Strategy1 and check the box ``Copy files into new implementation source directory``. Click ``OK``.

.. figure:: images_diamond/03.png
  :width: 1000

4. To modify the new implementation, right-click on it and ``Set as Active Implementation``.

.. figure:: images_diamond/04.png
  :width: 1000

5. The template ``VHDL File`` is copied to the source directory. Remove it by right-clicking the ``InputFile`` and ``Remove`` .

.. figure:: images_diamond/05.png
  :width: 1000

6. Right-click the project file and ``Open Containing Folder``.

.. figure:: images_diamond/06.png
  :width: 1000

7. Edit the template ``VHDL File`` and name it according to your project.

.. figure:: images_diamond/07.png
  :width: 1000

8. Add the renamed ``VHDL File`` to your project by right clicking the ``InputFiles`` - ``Add``- ``Existing File``.

.. figure:: images_diamond/08.png
  :width: 1000

9. Set ``Files of type:`` to ``All Files``, navigate to your source directory and add your previously renamed ``VHDL File``.

.. figure:: images_diamond/09.png
  :width: 1000

10. Write VHDL Code for the CPLD and save it.

.. figure:: images_diamond/10.png
  :width: 1000

.. note::

 The table in :ref:`carrier_board_rev05_s3cfunc` shows the dedicated wiring between the S3C and the D-Slot CPLDs.
 In the accompanying VHDL snippet, the default setting keeps the forwarding from SoM to card permanently enabled:

.. code-block:: vhdl

 user_enable_forwarding <= '1';
 --user_enable_forwarding <= '1' when (fpga_26 = '0' AND fpga_27 = '0' AND  fpga_28 = '1' AND fpga_29 = '1') else '0';

The commented line underneath illustrates an alternative scheme in which the FPGA drives a specific pin pattern (0011) to turn forwarding on or off (already known as ``..._w(ith)_enable`` from the old LC4xxx CPLDs).
The user can freely adapt or expand that logic to suit any custom forwarding rules.
Note that this “user-enable” path is later OR-ed with the **reqsafestate** signal -- forced low by the S3C during regular operation -- and the resulting value feeds the enable_forwarding net.
In other words, forwarding is active only when both the (per-slot) user permission and the (system-wide) S3C safety request allow it.

.. _dcpld_vhdl_example:

.. code-block:: vhdl

 --Fixed definitions
 reqoe <= NOT tristate_outputs;
 enable_forwarding <= user_enable_forwarding AND NOT reqsafestate;

 -- Specific safety definitions for card
 slotok <= enable_forwarding;
 -- tristate_outputs <= NOT pilot_in; -- set to pilot_in if card is driven by pilot_in, definition can be extended by user based on card-specific logic AND internal states
 tristate_outputs <= '0';

 -- Define the user-specific enable_forwarding signal logic
 user_enable_forwarding <= '1'; -- for tx30
 --user_enable_forwarding <= '1' when (fpga_26 = '0' AND fpga_27 = '0' AND  fpga_28 = '1' AND fpga_29 = '1') else '0'; -- for tx26_w_enable

.. note::

 Example for IO

.. code-block:: vhdl

 -- Input Port Example
 fpga_00 <=  d_00; -- This port is an input

 -- Output Port Example
 d_00 <= fpga_00 AND enable_forwarding; -- This port is an output

There is no dedicated enable logic between the S3C and the D-Slot CPLD for input signals. From the systems standpoint, signal validity should be handled by the SoM, so -- rather than adding complexity -- the signal is simply forwarded unchanged through every instance.

11. When saving, Diamond automatically checks the code and gives feedback. If everything is fine, it looks as below.

.. figure:: images_diamond/11.png
  :width: 1000

12. Switch to the ``Process`` view.

.. figure:: images_diamond/12.png
  :width: 1000

13. Start the processes shown below by double-clicking on them, one after another.

.. figure:: images_diamond/13.png
  :width: 1000

14. If every process passed, it looks as shown below. You can now use the exported ``JEDEC File`` to flash a CPLD with the Diamond Programmer as per :ref:`label_cpld_programming`.

.. figure:: images_diamond/14.png
  :width: 1000

15. Constraints for the D-Slot CPLDs are provided in the existing ``uz_d_slots.ldf`` project. If ever needed, one can check and modify the 
constraints by opening the ``Spreadsheet View``.

.. figure:: images_diamond/15.png
  :width: 1000

S3C
###

The same procedure can be applied to create a program for the S3C.
Everything is programmed inside the project ``UZ_Rev05_S3C.ldf``.
It is located in the repository at ``MACHXO2/S3C_CPLD_LCMXO2-4000HC-4TG144C/``.

.. danger::
 Modifying the bitstream of the S3C fundamentally alters the startup and power-down behavior of the UZ.
 Such changes may render the carrier board inoperative, requiring physical recovery through soldering.
 Exercise caution in your actions within this context.

.. note::
 Check the schematic from the Carrierboard to see which signals are inputs, outputs, open-drain or bidirectional.
 The pins have a dedicated direction and cannot be freely configured.
