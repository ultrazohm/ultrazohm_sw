.. _label_diamond_create_program:

===========================================
Create a CPLD program using Lattice Diamond
===========================================

The main goal of this section is to describe the necessary steps for creating a simple program for the CPLDs on the UltraZohm. 
All signals from the FPGA to the Digital Adapter cards have to pass through the CPLDs. 

Everything is programmed inside the project ``uz_d_slots.ldf`` . Here we can create additional ``implementations`` for the CPLD. 
The advantage of having all CPLD programs within one project is that they can use a global constraint file for the pinout.

Step-by-step
------------

1. Open Lattice Diamond and there the project ``uz_d_slots.ldf``. Click ``Open``.

.. figure:: images_diamond/01.png
  :width: 1000

2. For creating a new CPLD program add a ``New Implementation`` by right click on ``uz_d_slots`` and the subsequent contex menu.

.. figure:: images_diamond/02.png
  :width: 1000

3. Provide a proper ``Name`` and give the ``Directory`` the same name. Select the ``Default Strategy`` to Strategy1. Click ``OK``.

.. figure:: images_diamond/03.png
  :width: 1000

4. In order to modify your new implementation, right click on it an ``Set as Active Implementation``.

.. figure:: images_diamond/04.png
  :width: 1000

5. Right click on the ``InputFile`` folder and add a ``New File``.

.. figure:: images_diamond/05.png
  :width: 1000  

6. Select ``VHDL Files``, provide a proper ``Name`` for the file and select the ``Ext`` to vhdl. Click ``New``

.. figure:: images_diamond/06.png
  :width: 1000   

7. Write VHDL Code for the CPLD and save it.

.. figure:: images_diamond/07.png
  :width: 1000

8. When saving Diamond automatically checks the code and gives feed back. If everything is fine it looks as below.

.. figure:: images_diamond/08.png
  :width: 1000 

9. Switch to the ``Process`` view.

.. figure:: images_diamond/09.png
  :width: 1000   

10. Start the processes shown below by double-clicking on them, one after another.

.. figure:: images_diamond/10.png
  :width: 1000     

11. If every process passed it looks as shown below. You can now use the exported ``JEDEC File`` to flash a CPLD with the Diamond Programmer :ref:`label_cpld_programming`.

.. figure:: images_diamond/11.png
  :width: 1000       

12. Constraints for the D-Slot CPLDs are provided in the existing ``uz_d_slots.ldf`` project. If ever needed, one can check and modify the 
constraints by opening the ``Spreadsheet View``.

.. figure:: images_diamond/12.png
  :width: 1000   