
.. _SchematicAndFootprints:

=================================
Schematics and Footprints
=================================

When creating a schematic in Altium, there are many different ways to place components and use their footprints for the layout.
In the following, 4 different ways will be presented, how to create the appropriate schematic and footprint format for the Altium DB Library used in the UltraZohm project:

* Components are available with single schematic and single footprint lib from the manufacturer
* Components are included in other schematic and footprint libraries with other components
* Components are included in an integrated library
* Components are available as an ECAD MODEL


.. _SingleFootprint:

Components are available with single schematic and single footprint lib from the manufacturer
=============================================================================================

If both the schematic as well as the footprint are available from the manufacturer for Altium as a single  component, this is the easiest way and you can start immediately with the instruction:
:ref:`AltiumDB` .
But if the desired component is combined in a library with several other components, see the following sections.

.. _IncludedInOtherSchematicFootprints:

Components are included in other schematic and footprint libraries with other components
========================================================================================

If a component is in a library with several other components, this component must be separated from the other components in the schematic symbol library as well as in the footprint library.
Using the CarrierBoard library as an example, a possible way is described:


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
================================================

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
=========================================
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