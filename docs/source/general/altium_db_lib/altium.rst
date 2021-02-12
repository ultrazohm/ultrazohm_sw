===================================
Altium: Create a new Altium Project
===================================

1. Open Altium

2. ``File`` --> ``New`` --> ``Project``

.. _140_Create_Project:

   .. figure:: img/140_Create_Project.png
      :width: 300px

      Altium - Create new project.

3. Give a describing name for the project

4. Choose a location for saving the project (often it is suitable to save the project in a folder with BitBucket reference)

5. Click ``Create``

6. A new project with no content was created

.. _141_New_Project:

   .. figure:: img/141_New_Project.png
      :width: 300px

      Altium - New empty project.

7. Add a new schematic sheet: right mouse click --> ``Add new to project`` --> ``Schematic``

8. Save the new schematic sheet: right mouse click --> ``save as``

.. _142_New_Schematic:

   .. figure:: img/142_New_Schematic.png
      :width: 300px

      Altium - New schematic sheet.


New schematic sheet was added.

9. In general the symbol * marks that this sheet/ project is not saved. This can be done be clicking ``File`` --> ``save`` or ``save all``

10. If you develop the PCB for the ELSYS institute the template A4_CoBo_THN should be used. It is also part of the BitBucket content and can be found under the following path (for working with BitBucket and Libraries look at the instruction for Altium DB Lib) …\pcb_libraries\templates\schematics\A4_CoBo_THN

11. To use the template in the schematic open the schematic click ``Design`` --> ``Templates`` --> ``Project Templates`` --> ``Choose a File``

.. _143_Template_0:

   .. figure:: img/143_Template_0.png
      :width: 300px

      Altium - Choose template.

and select the suitable template

.. _143_Template:

   .. figure:: img/143_Template.png
      :width: 300px

      Altium - Select template.

12. Then you get a schematic sheet with this header

.. _144_Template_Sheet:

   .. figure:: img/144_Template_Sheet.png
      :width: 300px

      Altium - Templates.

13. To fill the * marked fields, select the schematic sheet, open the properties (``Panels`` --> ``Properties``)

.. _145_Properties:

   .. figure:: img/145_Properties.png
      :width: 300px

      Altium - Properties.

14. Change the register from general to parameters

.. _146_Parameters:

   .. figure:: img/146_Parameters.png
      :width: 300px

      Altium - Parameters.

15. Enter the necessary missing parameters

.. _147_Parameters_2:

   .. figure:: img/147_Parameters_2.png
      :width: 300px

      Altium - Parameters.

16. The result should look like this

.. _148_Templates_2:

   .. figure:: img/148_Templates_2.png
      :width: 300px

      Altium - Template filled.

17. The field Project Revision can be neglect or combined with a repository version tool or set manually.

18. The way for the manual edit process is select ``Project`` --> ``Project Options``

19. Select the register "Parameters"

20. Add "ProjectRevision" and a value e.g. 0.1

.. _149_Options_PCB:

   .. figure:: img/149_Options_PCB.png
      :width: 300px

      Altium - Options for PCB Project.

21. Now the schematic workstation is prepared and you are able to place components on the schematic sheet

22. If components are placed, it is necessary to annotate them by ``Tools`` --> ``Annotate`` --> ``Annotate Schematics``

.. _150_Annotate_Schematic_1:

   .. figure:: img/150_Annotate_Schematic_1.png
      :width: 300px

      Altium - Annotate schematic.

23. ``Update Changes List``

.. _150_Annotate_Schematic_2:

   .. figure:: img/150_Annotate_Schematic_2.png
      :width: 300px

      Altium - Update Changes List.

24. ``OK``

.. _150_Annotate_Schematic_3:

   .. figure:: img/150_Annotate_Schematic_3.png
      :width: 300px

      Altium - OK.

25. ``Accept Changes (Create ECO)``

.. _150_Annotate_Schematic_4:

   .. figure:: img/150_Annotate_Schematic_4.png
      :width: 300px

      Altium - Accept Changes.

26. ``Validate Changes`` --> ``Execute Changes`` --> ``Close``

.. _150_Annotate_Schematic_5:

   .. figure:: img/150_Annotate_Schematic_5.png
      :width: 300px

      Altium - Validate/ Execute/ Close.

27. Every component should have a designator. Most important thing is to be consistent within one project. See `Wikipedia <https://en.wikipedia.org/wiki/Reference_designator>`_ for an example list. 

.. _150_Annotate_Schematic_6:

   .. figure:: img/150_Annotate_Schematic_6.png
      :width: 300px

      Altium - Designator D1.

28. If you placed some components on the schematic sheet(s) and annotated them compile the project right mouse click on the project --> ``Compile PCB Project Guide.PrjPcb``

.. _150_Compile_Project:

   .. figure:: img/150_Compile_Project.png
      :width: 300px

      Altium - Compile Project.

If errors exist --> debug problems

If no errors --> create PCB

29. Create PCB

Right mouse click --> ``Add new to project`` --> ``PCB``

.. _150_Add_PCB:

   .. figure:: img/150_Add_PCB.png
      :width: 300px

      Altium - Add PCB to project.

30. Save PCB

Right mouse click --> ``Save as``

31. Import Components from the schematic to the PCB Design --> ``Import Changes from Guide.PrjPcb`` (short cut: di)

.. _150_PCB.png:

   .. figure:: img/150_PCB.png
      :width: 300px

      Altium - Import components from schematic.

Be careful not to use ``Update Changes from Guide.PrjPcb``. In this case you update the schematic with no content of the PCB. All components included in the schematic sheets are placed on the right edge of the PCB.

By pressing the numbers ``1``, ``2`` and ``3`` you can select between the following views

``1`` = Board planning mode --> define the shape of the PCB

``2`` = 2D view --> routing view

``3`` = 3D view

Often it is helpful to define null- point on the left corner because then the x and y dimension is without any offset

To do this:

1. Open the created PCB 

.. _151_Change_Board_Shape:

   .. figure:: img/151_Change_Board_Shape.png
      :width: 300px

      Altium - Open PCB.


2. Go to board planing mode by clicking ``1``

3. ``Design`` --> ``move board shape`` --> ``move it to the x``

.. _152_Change_Board_Shape_0:

   .. figure:: img/152_Change_Board_Shape_0.png
      :width: 300px

      Altium - Select move board shape.


.. _152_Change_Board_Shape:

   .. figure:: img/152_Change_Board_Shape.png
      :width: 300px

      Altium - Move the board in the corner.

4. Go back to the layout view (``2``) and start with the configuration of the layer stack
--> have a look at the chapter Layer Stack Manager

