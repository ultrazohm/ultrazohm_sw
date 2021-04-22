
.. _LayerStackManager:

=======================
PCB Layer Stack Manager
=======================

The layer stack manager defines the structure and the width of the different layers.

If the PCB should correspond to "standard" layer stack structure the best way would be to use the described and given layer stack recommendations of the PCB manufacturer.

In the following the layer stack for the manufacturer MultiCB is used:

https://www.multi-circuit-boards.eu/leiterplatten-design-hilfe/lagenaufbau/standard-lagenaufbau.html

.. _153_MultiCB:

   .. figure:: img/153_MultiCB.png
      :width: 300px

      Altium - Layer Stack of MultiCB.

To configure this information in Altium
========================================

1. Open the layer stack manager (only possible if you select a PCB Dokument ".PcbDoc") by clicking ``Design`` --> ``Layer Stack Manager``

.. _154_Layer_Stack:

   .. figure:: img/154_Layer_Stack.png
      :width: 300px

      Altium - Layer Stack Manager.

2. Load an existing template ``File`` --> ``load template`` or

3. Add/ Change the necessary thickness to given ones

4. With the ``Tools`` --> ``Layerstack Visualizer`` a 3D picture of the layer stack is given, additionally, shown with the defined via types

.. _155_Layer_Stack_3D:

   .. figure:: img/155_Layer_Stack_3D.png
      :width: 300px

      Altium - Layer Stack in 3D.

5. If you want you can save the configuration with ``File`` --> ``Save Template`` as


Defining Via Types
==================

Different via types are possible to use.
As well as by the layer stack the possibility of using different vias types is depending on the PCB manufacturer.
Because of that, the kind and size of vias that should be used in the project must be checked with the capabilities of the manufacturer.
As general rule use only through-hole vias that drill from top to bottom, everything else is more expensive. 

1. Open the layer stack manager (only possible if you select a PCB Document ".PcbDoc") by clicking ``Design`` --> ``Layer Stack Manager``

2. Choose the register "Via types" (Below the layer stack table)

3. Configure the types of possible via types for this project (through hole vias, blind vias or burried vias)

.. _156_Via_Types:

	.. figure:: img/156_Via_Types.png
		:width: 300px
	  

      Altium - Via Types.

