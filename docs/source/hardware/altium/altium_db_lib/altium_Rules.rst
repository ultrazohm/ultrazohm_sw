===================================
Design Rules
===================================

Rules are very important for maintaining safety distances.
The rules can derive from the requirements regarding voltage and current to the PCB and the requirement, which are given from the PCB manufacturer

1. The rule and constraint editor can be opened (only in a PCB document " .PcbDoc") ``Design`` --> ``Rules`` (DR)

.. _160_Design_Rules:

   .. figure:: img/160_Design_Rules.png
      :width: 300px

      Altium - Design Rules Editor.

2. In this editor many changes and definitions e.g. regarding clearance, routing width, planes, polygons can be made.

3. Every rule has a priority, which can be change by choosing the main point like "clearance" (shown in the picture above) + Priorities (on the under edge of this column)

.. _161_Rule_Priorities:

   .. figure:: img/161_Rule_Priorities.png
      :width: 300px

      Altium - Rules Priorities.

4. In this window you can increase or decrease the priority of the rules regarding the clearance.
Every rule needs an exclusive name, which could not be used twice in any rule.

5. The rules can be defined separated for each layer with the help of defining nets 
(Net Classes are selected by the drop down menu --> PowerNet_15V).

.. _162_Rules_PowerNet:

   .. figure:: img/162_Rules_PowerNet.png
      :width: 300px

      Altium - Defining rules for each layer.

But these nets must be defined in the schematic by making a net label.

.. _163_Rules_PowerNet:

   .. figure:: img/163_PowerNet.png
      :width: 300px

      Altium - Net label.

6. Furthermore, there is the option to use the "Custom Queries", where you are able to define dependencies by clauses etc.

.. _164_Rules:

   .. figure:: img/164_Rules.png
      :width: 300px

      Altium - Defining rules by clauses.

These settings must be given by the application and must be individually set before starting with the layout.


Differential signals
====================

Differential signals exist of two signals.
Often it is necessary, that these signals have a specific impedance to be robust against malfunctions.

To design suitable parameters for differential signals the open source tool "Saturn PCB Toolkit" is good to use.



Tool Saturn
===========

With the help of this tool it is possible to define a target impedance (in that case 120 Ohm) and calculate the necessary conductor width and conductor spacing.
The conductor height is given by the height of the layer on which the conductor should be lay outed.

.. _165_Tool_Saturn:

   .. figure:: img/165_Tool_Saturn.png
      :width: 300px

      Saturn - PCB tool kit.

Altium Rules
============

If the calculated impedance correspond approximately with the target impedance the values for the conductor width and the conductor spacing can be set in the Altium Rules

.. _166_Altium_Rules:

   .. figure:: img/166_Altium_Rules.png
      :width: 300px

      Altium - Set the calculated values from Saturn in Altium.


Mark Schematic
==============

Before routing these wires it is important to mark these wires with the property "differential pair".

.. _167_Mark_Schematic:

   .. figure:: img/167_Mark_Schematic.png
      :width: 300px

      Altium - Marks in schematics.

Route
=====

By routing differential wires use the routing method "Interactive Differential Pair Routing"

.. _168_Route:

   .. figure:: img/168_Route.png
      :width: 300px

      Altium - Layout differential pairs.


