=================================
Generating Outjob Files in Altium
=================================
When ordering at JLCPCB the following files are necessary for your order: 

* Gerber files
* NC Drill files
* Pick and Place files (CLP)
* Bill Of Material (BOM) 

These files are generated with help of an output job file. Since there is already the template `UZ_Outputjob.outjob <https://bitbucket.org/ultrazohm/altium_libraries/src/master/templates/output_jobs/>`_ 
available at the UltraZohm bitbucket it is recommended to use this file and refactor it to match your project. Just follow the guide below to generate all necessary files:

.. note:: The UZ_Outputjob.outjob meets JLC's requirements of manufacturing for the **Gerber**, **NC Drill**, **BOM** and **Pick and Place (CLP)** files, that can be accessed with the links below. The links below should be understood as a 'FYI', there is no need to make any changes to UZ_Outputjob.outjob.

    - General information on `BOM <https://support.jlcpcb.com/article/80-bill-of-materialsbom-file-for-smt-assembly>`_ and `Pick and Place <https://support.jlcpcb.com/article/79-pick-place-file-for-smt-assembly>`_ files 
    - `Tutorial on how to create the BOM and the Pick and Place files <https://support.jlcpcb.com/article/81-how-to-generate-bill-of-materials-and-component-placement-list-from-altium>`_ (Attention: JLC doesn't use the ActiveBOM in Altium.)
    - `Gerber and NC Drill files' settings <https://support.jlcpcb.com/article/42-how-to-export-altium-pcb-to-gerber-files>`_ 

    To change the settings just double click on the corresponding file and a window will open where you can make your changes as described in the documents above.

First of all add the UZ_Outputjob.outjob to your project folder and add it afterwards to your altium project by right clicking on your project in the projects panel 
``Your_Project_Name_Here.PrjPcb``-> ``Add Existing to Project...`` -> ``UZ_Outputjob.outjob`` -> ``Öffnen``. 
The outjob file is now included to your Altium project structure and can be found under ``Libraries`` -> ``Output Job Files``.

.. figure:: screencasts/Adding_UZ_Outjob_Template_to_an_Altium_Project.gif
    :width: 1200 

    Adding Template Outjob to an Altium Project

The next step is to add the BomDoc to your **Source Documents** by right clicking on ``Your_Project_Name_Here.PrjPcb`` -> ``Add New to Project`` -> ``ActiveBOM`` 
and make some small adjustments like adding parameters and giving aliases to a few parameters. To add a new parameter 
go to ``Properties`` -> ``Columns`` and activate the ones shown in the table below. Afterwards rename the aliases regarding to the table beneath.

================ ============
Parameter        Alias
================ ============
Comment          Comment
Designator       Designator
Footprint        Footprint
LCSC Part number LCSC Part #
================ ============   

.. figure:: screencasts/Adjustment_of_the_BOMDoc.gif
    :width: 1200

    Adjustment of the BomDoc

Since the output job file was refactored, the next step is to generate the manufacturing files (namely the Gerber files, NC Drill files, Pick and Place files (CLP) and  Bill Of Material (BOM) ). 
But before you generate the files, first add the correct template for the BOM. To do so 
double click on the ``BOM file`` -> click on ``...`` next to ``Template`` -> choose  `BOM_Template_THN_JLCPCB.xlsx <https://bitbucket.org/ultrazohm/altium_libraries/src/master/templates/BOM/>`_ -> ``Öffnen``. 
Now everything is set up and the files can finally be generated. 
Choose ``BOM_JLC Output Container`` -> ``Generate content->``. Repeat this for the ``Gerber_and_Drill_Files`` and ``Pick_and_Place`` **Output Containers**. 

.. figure:: screencasts/Generating_outjob_Files.gif 
    :width: 1200 

    Generating Outjob files

The generated outjob files can be found in the project folder under ``Project Outputs for.../ProjectRevision``. 

.. figure:: pictures/Output_Files.png
    :width: 1200
    :class: with-shadow

    Output files

Now all necessary files are generated and you can proceed with the **Ordering Process with SMT Assembly**.
