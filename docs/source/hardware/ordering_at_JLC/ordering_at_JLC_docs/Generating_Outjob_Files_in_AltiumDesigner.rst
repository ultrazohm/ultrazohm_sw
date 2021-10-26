=================================
Generating Outjob Files in Altium
=================================
When ordering at JLCPCB the following files are necessary for your order: 

* Gerber files
* NC Drill files
* Pick and Place files (CLP)
* Bill Of Material (BOM) 

These files are generated with help of an output job file. Since there is already a `template.outjob <https://bitbucket.org/ultrazohm/altium_libraries/src/master/templates/output_jobs/>`_
file available at the UltraZohm bitbucket it is recommended to use this file and refactor it to match your project. Just follow the guide below to generate all necessary files:

First of all add the template.outjob to your project folder and add it afterwards to your altium project by right clicking on your project in the projects panel 
``Your_Project_Name_Here.PrjPcb``-> ``Add Existing to Project...`` -> ``template.outjob`` -> ``Öffnen``. 
The outjob file is now included to your Altium project structure and can be found under ``Libraries`` -> ``Output Job Files``.

.. figure:: screencasts/Adding_Templateoutjob_to_Altium_project.gif
    :width: 1200 

    Adding Template Outjob to an Altium Project

Now that the template outjob file was added, you have to make some changes to match it to your project. These steps may vary for every PCB, but the concept stays the same.

1. Delete all unnecessary files (e.g. all the different variants, since you may only have one variant)
2. Change the parameter ``Variant`` to ``No Variant`` by clicking on it in the corresponding row and using the drop down menu
3. Rename the files 

.. figure:: screencasts/refactor_template.gif
    :width: 1200

    Refactor Template Outjob

The next step is to add the BomDoc to your **Source Documents** by right clicking on ``Your_Project_Name_Here.PrjPcb`` -> ``Add New to Project`` -> ``ActiveBOM`` 
and make some small adjustments like adding parameters and giving aliases to a few parameters. To add a new parameter 
right click on ``the header of the column`` -> ``Select columns`` and activate the ones shown in the table below. Afterwards 
right click on ``the header of the column`` -> ``Rename Column...`` and change the aliases regarding to the list beneath.

================ ============
Parameter        Alias
================ ============
Comment          Comment
Designator       Designator
Footprint        Footprint
LCSC Part number LCSC Part #
================ ============   

.. figure:: screencasts/adjust_BOM.gif
    :width: 1200

    Adjustment of the BomDoc

Since the output job file was refactored, the next step is to generate the manufacturing files (namely the Gerber files, NC Drill files, Pick and Place files (CLP) and  Bill Of Material (BOM) ). But before you generate the files, first add the correct template for the BOM. To do so 
double click on the ``BOM file`` -> click on ``...`` next to ``Template`` -> choose  `BOM_Template_THN_JLCPCB.xlsx <https://bitbucket.org/ultrazohm/altium_libraries/src/master/templates/BOM/>`_ -> ``Öffnen``. 
Now everything is set up and the files can finally be generated. 
Choose ``BOM Output Container`` -> ``Generate content->``. Repeat this for the ``Gerber_and_Drill_Files`` and ``Pick_and_Place`` **Output Containers**. 

.. figure:: screencasts/generate_outjob_files.gif 
    :width: 1200 

    Generate Outjob files

.. Note:: 
    The **Data Source** of the **Draftsman file** is still highlighted in red. This is because an extension for Altium is needed for this file, 
    but since it is no necessary file for an order at JLC, you can ignore this. 
    See `here <https://www.altium.com/documentation/altium-designer/draftsman-ad?version=19.0>`_ for more information. 

    .. figure:: pictures/draftsman_file2.png 
        :width: 1200 
        :class: with-shadow

        Draftsman file

The generated outjob files can be found in the project folder under ``Project Outputs for.../ProjectRevision``. 

.. figure:: pictures/Output_Files.png
    :width: 1200
    :class: with-shadow

    Output files

Now all necessary files are generated and you can proceed with the **Ordering Process with SMT Assembly**.

