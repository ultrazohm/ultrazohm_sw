==================
Ordering at JLCPCB
==================

This is a short guide on how to order an circuit board from `JLCPCB`_. In particular, what is needed for an order with SMT assembly. 
Since there are some preparations necessary in Altium this tutorial is divided in two sections. 
One will handle the things that need to be done in advance and the following up part will give a guide on the ordering process.

---------------------------------
Generating Outjob Files in Altium
---------------------------------
JLCPCB needs the following files for your order: 

* Gerber files
* NC Drill files
* Pick and Place files (CLP)
* Bill Of Material (BOM) 

Usually these files can be found in the project folder under "Project Outputs for...". But if you changed something on the PCB design, if it is the first order of that PCB at JLC or these files are simply not there yet, 
you want to newly generate the aforementioned files. To do so just follow through this brief guide. 

Open your project in Altium Designer and look for the **output job files** folder. 
If the folder or the .OutJob file is missing, you have to add it to your project. 
To do so right click on **Your_Project_Name_Here.PrjPcb**--> **Add New To Project** --> **Output Job File**.

.. figure:: pictures/output_job_files_folder.PNG 
    :width: 200 

Now open the **.OutJob** file. If you have just added the outjob file in the previous step, you have to create the Gerber, NC Drill, Pick and Place and BOM files. 
In order to generate the Gerber files click on **Add New Fabrication Output**--> **[PCB Document]**. In the same manner choose the NC Drill files.   
For the Pick and Place (CLP) files click on **Add New Assembly Output**--> **[PCB Document]** and for BOM click on  **Add New Report Output**--> **[Project]**. 

.. figure:: pictures/Outputs.PNG 
    :width: 600 

.. note:: The Gerber, NC Drill, BOM and Pick and Place (CLP) files must meet JLC's requirements of manufacturing, which can be accessed with the listed links below. 

    - General information on `BOM <https://support.jlcpcb.com/article/80-bill-of-materialsbom-file-for-smt-assembly>`_ and `Pick and Place <https://support.jlcpcb.com/article/79-pick-place-file-for-smt-assembly>`_ files 
    - `Tutorial on how to create the BOM and the Pick and Place files <https://support.jlcpcb.com/article/81-how-to-generate-bill-of-materials-and-component-placement-list-from-altium>`_ 
    - `Gerber and NC Drill files' settings <https://support.jlcpcb.com/article/42-how-to-export-altium-pcb-to-gerber-files>`_ 

    To change the settings just double click on the corresponding file and a window will open where you can make your changes as described in the documents above. 

Since all necessary output job files are added, they have to be generated. To do so add the files to a container as shown in the picture below, and click on **Generate content->**. 
If there is no container yet, create one by clicking on **Add New Output Container** and choose **New folder structure**. 

.. note:: If you are using different variants in your PCB design, make sure to select the one you want to build. 

.. figure:: pictures/Output_Container1.PNG 
    :width: 950 

The generated outjob files can be found in the project folder under "Project Outputs for...". 
Since all necessary files are created, the next part will be about JLCPCB's ordering process for SMT assembled PCBs. 

.. figure:: pictures/Project_Folder1.PNG
    :width: 500 

----------------------------------
Ordering Process with SMT Assembly
----------------------------------

- Go to `JLCPCB`_ and sign in with your account 
- Go to your shopping cart and choose **Add new item** 

.. figure:: pictures/Add_New_Item.PNG 
    :width: 500 

- Click on **Add gerber file** and upload your Gerber and NC Drill files as .zip 

.. figure:: pictures/Add_Gerber_File.PNG 
    :width: 500 

- Choose your preferred settings and quantity for the PCB you want to oder 
- Scroll down, choose **SMT Assembly**, select the side that should be assembled and click on **Confirm** 

.. note:: When choosing SMT assembly some settings are not available e.g. gold fingers. If necessary change them to fit JLC's requirements 

.. figure:: pictures/SMT_Assembly.PNG 
    :width: 500 

- Now upload your BOM and Pick and Place (CPL) files and click on **Next** 

.. figure:: pictures/Upload_BOM_CLP.PNG 
    :width: 500 

- Check if everything in the shown list is correct an click on **Next** 

.. figure:: pictures/Component_Check.PNG 
    :width: 500 

- Check the orientation of the components in the review window (e.g. red and white dot should be on the same side, if not adjust the rotation in the Pick and Place file in Altium) 

.. figure:: pictures/Component_Orientation.PNG 
    :width: 500 

- Press **Save To Cart** 
- Click on **Product Details** to check your settings and then **Secure Checkout** 

.. figure:: pictures/Secure_Checkout.PNG 
    :width: 500 

- Follow the steps of the delivery and payment (recommended delivery method: DHL Express Priority (DDP)) 

.. figure:: pictures/Shipping.PNG 
    :width: 500 

.. _JLCPCB: https://jlcpcb.com/