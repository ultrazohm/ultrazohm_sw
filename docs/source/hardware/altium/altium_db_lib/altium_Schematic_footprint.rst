
.. _SchematicAndFootprints:

======================
Symbols and Footprints
======================



When creating a schematic in Altium, there are many different ways to place components and use their footprints for the layout. In a project for the UltraZohm the UltraZohm component library is used exclusively.
If the required components are not available in the current library status they must be added. Newly added components must fulfill the following requirements:

1. A ``.SchLib`` or ``.PcbLib`` file must contain only a signel symbol or footprint. If this requirement is not fulfilled it is impossible to resolve merge conflicts when people are working on the library
2. The footprint must follow the mapping of the mechanical layers. This is vital in order to generate high quality documentation and production output. The requirements can be found under :ref:`mech_layers` 
3. If the manufacturer supplies a 3D model of the component it must be included to the footprint.

If the user detects a footprint that does not follow the requirements mentioned above he is strongly encouraged to update the component or to open an issue and assign it to the maintainer (i.e. creator) of the component.

Extraction of footprints and symbols
====================================

In the following, 4 different ways will be presented, how to create the appropriate schematic and footprint format for the Altium DB Library used in the UltraZohm project:

.. _SingleFootprint:

Separate files for symbol and footprint
***************************************

If both the schematic as well as the footprint are available from the manufacturer for Altium in separate files and if these files **only contain one symbol or footprint** you can start directly by integrating these components into the library.
Please be aware that you will have to adjust the mechanical layers in the footprint. See :ref:`AltiumDB` for further instructions. If the desired component is combined in a library with several other components, see the following sections.

.. _IncludedInOtherSchematicFootprints:

More than one symbol or fooprint in one file
********************************************

If a component is in a library file (``.SchLib`` or ``.PcbLib``) with several other components this component must be separated from the other components in the schematic symbol library as well as in the footprint library.
Altium provides the ``Library Splitter Wizard`` for this purpose so no manual extraction is required.

1. Open the existing schematic library in Altium

.. _100_OpenSchematic:

   .. figure:: img/100_Open_schematic_lib_Altium.png
      :width: 300px

      Altium - Open schematic lib.

2. Use the Altium Library Splitter Wizard ``Tools`` --> ``Library Splitter Wizard``

.. _101_Use_Lib_Splitter:

   .. figure:: img/101_Use_Lib_Splitter.png
      :width: 300px

      Altium - Use Library Splitter Wizard.

3. Press ``Next``

.. _102_Lib_Splitter_1:

   .. figure:: img/102_Lib_Splitter_1.png
      :width: 300px

      Altium - Next.

4. ``Add`` the schematic and footprint lib

.. _103_Lib_Splitter_2:

   .. figure:: img/103_Lib_Splitter_2.png
      :width: 300px

      Altium - Add schematic and footprint lib.

5. Select both

.. _104_Lib_Splitter_4:

   .. figure:: img/104_Lib_Splitter_4.png
      :width: 300px

      Altium - Select both.

6. Press ``Next``

.. _105_Lib_Splitter_5:

   .. figure:: img/105_Lib_Splitter_5.png
      :width: 300px

      Altium - Next.

7. Select the Output Directory (Therefore, it might be suitable to create one folder for the schematic symbols and one for the footprints.)

.. _106_Lib_Splitter_6:

   .. figure:: img/106_Lib_Splitter_6.png
      :width: 300px

      Altium - Select Output Directory.

8. Press ``Next``

.. _107_Lib_Splitter_7.png:

   .. figure:: img/107_Lib_Splitter_7.png
      :width: 300px

      Altium - Next.

9. Press ``Next``

.. _108_Lib_Splitter_8:

   .. figure:: img/108_Lib_Splitter_8.png
      :width: 300px

      Altium - Next.

10. Press ``Next``

.. _109_Lib_Splitter_9:

   .. figure:: img/109_Lib_Splitter_9.png
      :width: 300px

      Altium - Next.

11. Press ``Finish``

.. _110_Lib_Splitter_10:

   .. figure:: img/110_Lib_Splitter_10.png
      :width: 300px

      Altium - Finish.

12. All schematic symbols are separated from the others

.. _111_Splitted_Schematic_11:

   .. figure:: img/111_Splitted_Schematic_11.png
      :width: 300px

      Altium - Schematic are separated.

13. All footprints are separated from the others

.. _112_Splitted_Footprint_12:

   .. figure:: img/112_Splitted_Footprint_12.png
      :width: 300px

      Altium - Footprints are separated.

Now all components are separated from each other and it is possible to proceed with the instructions of :ref:`AltiumDB` .

.. _IntegratedLibrary:

Components are included in an integrated library
************************************************

1. Open the integrated library in Altium and choose ``Extract Sources``

.. _120_Open_Integrated_Lib:

   .. figure:: img/120_Open_Integrated_Lib.png
      :width: 300px

      Altium - Extract Souces.

2. All included schematic and footprint libs will be listed in Alitum

.. _121_Open_Integrated_Lib:

   .. figure:: img/121_Open_Integrated_Lib.png
      :width: 300px

      Altium - All included libs are visible.

3. If more than one schematic and one footprint lib exist in the integrated library, choose the necessary footprint library and press ``File`` -> ``Save as``.

.. _122_Save_as_footprint:

   .. figure:: img/122_Save_as_footprint.png
      :width: 300px

      Altium - Save the footprint lib.

4. Save also the necessary schematic library.

.. _123_Save_as_schematic:

   .. figure:: img/123_Save_as_schematic.png
      :width: 300px

      Altium - Save the schematic lib.

5. The integrated library is separated in schematic and footprint library.

.. _104_124_Schematic_and_footprint_lib.png:

   .. figure:: img/124_Schematic_and_footprint_lib.png
      :width: 300px

      Altium - Schematic and footprint lib are available.

Now it can be continued with the instuction: :ref:`IncludedInOtherSchematicFootprints`.

.. _ECADModel:

Components are available as an ECAD MODEL
*****************************************
Sometimes, there are no symbols or footprints directly from the manufacturer available.
Then you can use  the component search engine (https://componentsearchengine.com/logPartRequest.php), where you can access a large number of already existing components or request new models for Altium. 

To enter these components into the database, proceed as follows:

1. Download the Model from the homepage - Part 1

.. _130_Download_Model:

   .. figure:: img/130_Download_Model.png
      :width: 300px

      Altium - Download - Part 1.

2. Download the Model from the homepage - Part 2

.. _131_Download_Model:

   .. figure:: img/131_Download_Model.png
      :width: 300px

      Altium - Download - Part 2.

3. Save the model ``Ok``

.. _132_Download_Model:

   .. figure:: img/132_Download_Model.png
      :width: 300px

      Altium - Save.

4. Extract the zip-file

.. _133_Extrahieren.png:

   .. figure:: img/133_Extrahieren.png
      :width: 300px

      Altium - Extract.

5. Open Altium and a schematic file before the Altium Loader will be opened by selecting ``File`` --> ``Symbols Footprints 3D Models``
(If this tab does not exist, the necessary plug in is missing.
Therefore read and install the Altium Library Loader https://www.samacsys.com/altium-designer-library-instructions/)

.. _134_Open_ECAD:

   .. figure:: img/134_Open_ECAD.png
      :width: 300px

      Altium - Open Altium Loader.

6. Open the ECAD model

.. _135_Open_ECAD_MODEL.png:

   .. figure:: img/135_Open_ECAD_MODEL.png
      :width: 300px

      Altium - Open ECAD Model.

7. Navigate to the unzipped epw-file and select it

.. _136_Open_ECAD_MODEL:

   .. figure:: img/136_Open_ECAD_MODEL.png
      :width: 300px

      Altium - Select epw- file.

8. After a short load time the following message appears. Press ``OK``.

.. _137_Altium_Library_Loader:

   .. figure:: img/137_Altium_Library_Loader.png
      :width: 300px

      Altium - Altium Library Loader.

9. The component is included in the SamacSys schematic and footprint lib (default generated)

.. _138_SamacSys:

   .. figure:: img/138_SamacSys.png
      :width: 300px

      Altium - SamacSys.

At this point, the SamacSys lib can be reused or the respective symbols with the corresponding footprint can be stored in a temporary lib.
Afterwards you have to continue with the instructions: :ref:`IncludedInOtherSchematicFootprints`


.. _mech_layers:

Mapping of the mechanical layers
================================

When creating a component several layers types can be defined. Besides the standard layers like Top and Bottom copper overlay etc. mechanical layers can be defined.
These layers carry information for the generated documentation output. In order to be able to reuse a certain output job to generate the documentation and production output
the mechanical layers must follow a uniform mapping. The mapping is distinguished in two different categories:

1. `Component Layer Pairs <https://www.altium.com/documentation/altium-designer/working-with-mechanical-layers-ad?version=19.1#!component-layer-pairs>`_: These layers exist symetrically on top and bottom
2. `Other mechanical layers <https://www.altium.com/documentation/altium-designer/working-with-mechanical-layers-ad?version=19.1#!mechanical-layers>`_: These layers only exist once


:numref:`table_mech_layer_pairs` shows the mapping of the component layer pairs to the functions. Even if Altium can handle the numbering of the layers automatically when assigning component layer pairs
in the UltraZohm library only components that follow this layer mapping are accepted. The mapping of the additional mechanical layers from :numref:`table_other_mech_layers` must be considered especially
in the PCB design when putting certain meta information in the layout.


.. _table_mech_layer_pairs:
.. csv-table:: Mapping of the mechanical layer pairs
	:file: mech_layer_pairs.csv
	:widths: 10 40
	:header-rows: 1


.. _table_other_mech_layers:
.. csv-table:: Mapping of the other mechanical layers
	:file: other_mech_layer.csv
	:widths: 10 40
	:header-rows: 1


Unfortunately, the footprints that can be optained from the manufacturer usually do not follow the mapping from the table above.
:numref:`mech_layers_base_case` shows a typical mechanical layer stackup when a component is freshly downloaded from the manufacturer homepage.

	.. _mech_layers_base_case:	
	.. figure:: img/mech_layers/base_case.png
		:width: 500px
		:alt: Typical layer stack in AD before editing
	   
		Typical layer stack in AD before editing


In order to adapt those componennts to the required mapping the following steps are necessary:

#. Create all required mechanical layer pairs. You do not need to create all layer pairs defined in :numref:`table_mech_layer_pairs`
	
	* ``Right-click`` in the layer area
	* Select ``Add component layer pair`` and fill out the dialog with the mapping from :numref:`table_mech_layer_pairs`
	
	.. figure:: img/mech_layers/add_component_layer.png
		:width: 500px
		:alt: Dialog to add a component layer pair
		
		Dialog to add a component layer pair
		
#. Move the objects from the previous layer to the new layer. Example: Moving the 3D body from layer M1 to M3

	Hide all layers except M1
	
	.. figure:: img/mech_layers/m1.png
		:width: 500px
		:alt: Dialog to add a component layer pair
		
		Dialog to add a component layer pair
	
	Select everything on M1 (Ctrl-A) and move selected objects to M3 in the propertiers panel.
	
	.. figure:: img/mech_layers/m1_move.png
		:width: 500px
		:alt: Dialog to add a component layer pair
		
		Dialog to add a component layer pair
	
	Delete M1
	
	.. figure:: img/mech_layers/m1_delete.png
		:width: 500px
		:alt: Dialog to add a component layer pair
		
		Dialog to add a component layer pair
		
#. Repeat step 1 and 2 for all objects that are on the wrong layer


