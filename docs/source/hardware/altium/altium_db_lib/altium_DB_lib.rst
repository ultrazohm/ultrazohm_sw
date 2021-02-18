.. _AltiumDB:

====================
Altium DB
====================
Before starting with the description and instructions on how to use the database system in Altium, a brief overview of the different tools will be given.

.. _200_Overview_DB_system:

   .. figure:: img/200_Overview_DB_system.png
      :width: 500px

      Overview of the databased system for Altium.

The entire system is located in a total of three different places. 
Once on the BitBucket server in the altium_library repository.
Here are all schematic symbols and footprints of the individual components, as well as the DbLib file that is needed to connect to the database on the Ultrazohm server.
The second system is the server of the Ultrazohm. 
Here is a MariaDB system running, in which all relevant component information are stored.
The third system is the local PC, which gets access to the database via the user DbLib file by including it in Altium.
If you only want to use components that are in the database, this access is sufficient. 
But if it is necessary to add components, then a write access to the MariaDB must be used.
For this purpose, the graphical front end "Dbeaver" is recommended, with its help it is easy to add new components, modify existing ones or delete them.


In the following, the individual tools and necessary installation steps are discussed.

.. note :: All usernames and passwords are to be obtained from the Ultrazohm responsible people.


To use the database driven library for Altium, a few settings have to be made once.
In the following chapters, a guideline on how to install and set the parameter is given.
The following tools will be needed:

* BitBucket
* ODBC Data Sources (64-Bit)
* Altium
* DBeaver

Videos of setup
===============

How to install Altium:

.. youtube:: SS1pZKD2n0Y

How to install the Altium library:

.. youtube:: 0VST-4g3nWA

How to install DBweaver:

.. youtube:: DaSXdXeiYR4


BitBucket access setup
======================

1. To work with the databased library system in Altium, it is necessary to get access to the BitBucket system of the UltraZohm, especially to the folder "altium_libraries"

.. _1_BitBucket:

   .. figure:: img/1_BitBucket.png
   
        BitBucket - altium_libraries.

2. Clone the repository on your local hard disk

3. Create a new feature branch to work with the system

4. If a new component was added, don´t forget to commit and push the new component to BitBucket by pull request!

.. _ServerAccessSetup:

Server access setup
===================

1. ``Open`` the ODBC-Datasource App (64-Bit)

.. _20_ODBC_sources_1:

   .. figure:: img/20_ODBC_sources_1.png
      :width: 300px

      OBDC - open App.

2. ``Add`` a new User-DSN

.. _21_ODBC_sources_2:

   .. figure:: img/21_ODBC_sources_2.png
      :width: 300px

      OBDC - add user-DSN.

3. Select the MariaDB ODBC 3.1 Driver

.. _22_ODBC_sources_3:

   .. figure:: img/22_ODBC_sources_3.png
      :width: 300px

      OBDC - select MariaDB.

If MariaDB ODBC 3.1 Driver could not be selected, install the driver by downloading the MariaDB ODBC 3.1 from the homepage:
https://downloads.mariadb.org/connector-odbc/.

4. Create a new data source to MariaDB

.. _23_ODBC_sources_4:

   .. figure:: img/23_ODBC_sources_4.png
      :width: 300px

      OBDC - create a new data source.

5. Connect it to the ultrazohm server

.. _24_ODBC_sources_5:

   .. figure:: img/24_ODBC_sources_5.png
      :width: 300px

      OBDC - connection to ultrazohm server.

.. note :: At this point, user access is used with read-only rights, since the database is never modified from within Altium, and changes are made specifically via DBeaver (see :ref:`IntegrationInAltium`).


6. Do nothing and press ``Next >``

.. _25_ODBC_sources_6:

   .. figure:: img/25_ODBC_sources_6.png
      :width: 300px

      OBDC - skip.

7. Do nothing and press ``Next >``

.. _26_ODBC_sources_7:

   .. figure:: img/26_ODBC_sources_7.png
      :width: 300px

      OBDC - skip.

8. Force to use TLS and go back for three times ``< Previous``

.. _27_ODBC_sources_8:

   .. figure:: img/27_ODBC_sources_8.png
      :width: 300px

      OBDC - use TLS.

9. Select the database "altium_library" and ``Test DSN``

.. _28_ODBC_sources_9:

   .. figure:: img/28_ODBC_sources_9.png
      :width: 300px

      OBDC - select "altium_library".

10. Finish the settings by pressing three times ``OK``

.. _29_ODBC_sources_10:

   .. figure:: img/29_ODBC_sources_10.png
      :width: 300px

      OBDC - finish settings.

.. _IntegrationInAltium:

Integration in Altium
=====================

1. Open a schematic document in Altium

2. Choose the point ``place`` --> ``part``; a menu on the left or right side will open with the already installed library preferences called "components"

.. _30_Elsys_mariadb_lib:

   .. figure:: img/30_Elsys_mariadb_lib.png
      :width: 300px

      Altium - component libraries.

3. Click on the three horizontal lines and select the point ``File-based library Preferences``

4. Select the register Installed

.. _31_File_based_lib:

   .. figure:: img/31_File_based_lib.png
      :width: 300px

      Altium - installed libraries.

5. Select ``Install…`` and navigate to the point where the BitBucket folder is cloned on the computer. Select the file "user.DbLib"

6. ``Close`` this window

7. After installing the DBLib - File, you can choose between the different integrated component tables

.. _32_Elsys_mariadb_lib_example:

   .. figure:: img/32_Elsys_mariadb_lib_example.png
      :width: 300px

      Altium - different component tables.

8. Now you can use all already existing components from the databased library

Installation and setup of a front end (DBeaver)
===============================================

For the next steps it is important to have not only read permissions for MariaDB, but also write permissions.
Therefore, the same procedure, described in chapter :ref:`ServerAccessSetup`, for the altium_developer must be done.
For this purpose the developer access in Altium must now be used.

To be able to add a new component to the database (MariaDB) as easily as possible, it is comfortable to use a graphical front end.

1. Download the Dbeaver software to work with the MariaDB on the UltraZohm server https://dbeaver.io/download/ 

.. note :: There are more software tools that allow for adding and editing information in a database, but DBeaver is recommended to keep the tooling consistent in the UltraZohm community.

2. To set up the connection to the MariaDB on the UltraZohm Server, the following steps (shown in the screenshots below) must be fully filled one time.

3. Select MariaDB

.. _35_DBeaver_1:

   .. figure:: img/35_DBeaver_1.png
      :width: 300px

      DBeaver - select mariaDB.

4. Connect it to the ultrazohm server

.. _36_DBeaver_2:

   .. figure:: img/36_DBeaver_2.png
      :width: 300px

      DBeaver - general settings.

5. Download the MariaDB driver, which is recommended

.. _37_DBeaver_3:

   .. figure:: img/37_DBeaver_3.png
      :width: 300px

      DBeaver - driver settings - 1.

6. These settings must be selected automatically after the download of MariaDB. 
Before clicking ``Finish`` the settings of SSL must be done.

.. _38_DBeaver_4:

   .. figure:: img/38_DBeaver_4.png
      :width: 300px

      DBeaver - driver settings - 2.

7. Select use SSL and do not verify the server certificate

.. _39_DBeaver_5:

   .. figure:: img/39_DBeaver_5.png
      :width: 300px

      DBeaver - SSL settings.

8. Now, the connection to the ultrazohm MariaDB should be possible.

9. If the connection failled, control the settings and reconnect via right click on the ``altium_library`` --> ``Invalidate/ Reconnect``

10. If the connection was successful, the following table structure must be visible

.. _40_DBeaver_altium_lib:

   .. figure:: img/40_DBeaver_altium_lib.png
      :width: 300px

      DBeaver - table structure.

**This step completes the one-time setup.**

.. _AddANewComponentToTheDatabasedLibrary:

Add a new component to the databased library
********************************************

To make the process of adding a component more visible, it will be described by adding a SMD capacitor.

.. note :: The target of this database system is that schematic and footprints of generic components should only exist one time.
           This means that schematics and footprints symbols of generic components only have to be in the Bitbucket folder system once, even if resistors have different values.
           Only if the component has a different geometry, a new schematic and/or footprint must be added.
           And be careful when you create new schematics and footprints that the pins and the naming of the pins are equal (very important by connectors and ics).
           (If you are unsure, you should use the footprint and the symbol of the manufacturer instead of using an already existing footprint.)


1. Check if the schematic symbol already exists as a symbol in the BitBucket system. Therefore, open the folder of the cloned BitBucket repository.
If the schematic does not exist, copy the schematic symbol in the suitable folder of the schematics ``...\alitum_libraries\symbols\...`` (at this point, it is assumed that missing schematics or footprints are each available separately (not in integrated libs or libraries with multiple parts)). To get single schematic symbols and footprints from different starting points see chapter :ref:`SchematicAndFootprints`.

.. _41_Explorer_SCH:

   .. figure:: img/41_Explorer_SCH.png
      :width: 300px

      Explorer - symbols.

2. Regarding the name of the component: **SCH - Folder - Description.SCHLIB**

.. note :: The extension of the file is written in capital letters.

3. Check if the footprint symbol already exists in the BitBucket system.
If not, copy the footprint in the suitable folder of the footprints ``...\alitum_libraries\footprints\...``

.. _42_Explorer_PCB:

   .. figure:: img/42_Explorer_PCB.png
      :width: 300px

      Explorer - footprints.

4. Regarding the name of the footprint: **PCB - Folder - Description.PCBLIB**

.. note :: The extension of the file is written in capital letters.

5. Change to the DBeaver tool

6. Choose a suitable table where the component should be added. 
If no table is suitable go on with the instruction given in section :ref:`AddANewTableToTheDatabasedLibrary`.

.. _43_DBeaver_table:

   .. figure:: img/43_DBeaver_table.png
      :width: 300px

      DBeaver - choose a suitable table.

7. A new register on the right side with the table will appear

.. _44_DBeaver_Properteries:

   .. figure:: img/44_DBeaver_Properteries.png
      :width: 300px

      DBeaver - Editor will open on the right side.

8. Mostly, the "Properties" register will open at first. Change to the "Data" register. 
An overview of all already added components will be shown there. (In this case, no component is still existing in the table.)

.. _45_DBeaver_Data:

   .. figure:: img/45_DBeaver_Data.png
      :width: 300px

      DBeaver - change to tab "data".

9. Press the ``add`` button, and a new row highlighted in green appears.

10. By clicking on a respective cell, the cell can be filled with content.

11. To switch between the view of all components and the comfortable editing mode for one component --> ``press tab``.

12. If all necessary cells are filled with information, save the components with the ``save`` button (under the current table on the left side or by pressing ``Ctrl + S``).
Some cells have a clause that they must be filled before saving is allowed (to help the user not to forget information, which is necessary).
If something is forgotten, the following message will occur.

.. _46_DBeaver_Data_Error:

   .. figure:: img/46_DBeaver_Data_Error.png
      :width: 300px

      DBeaver - error message.

Press ``OK`` and fill out the missing cell (in this example, "ComponentLink1Description").
The table cells, which are here described in detail is from "Capacitors - SMD" table as an example.


.. csv-table:: Capacitors - SMD
  :file: Table_1.CSV
  :widths: 40 40 40 40
  :header-rows: 1


13. If the component is saved in DBeaver, refresh the view in Altium via ``F5`` --> choose ``place`` --> ``part`` and select the library, where the component was added --> the new component is shown with all the inserted database information

.. _47_Altium_Parameter1:

   .. figure:: img/47_Altium_Parameter1.png
      :width: 300px

      Altium - component information - 1.

.. _48_Altium_Parameter2:

   .. figure:: img/48_Altium_Parameter2.png
      :width: 300px

      Altium - component information - 2.

.. _49_Altium_Parameter3:

   .. figure:: img/49_Altium_Parameter3.png
      :width: 300px

      Altium - component information - 3.

14. The component can now be used in the schematic by ``drag and drop`` or by selecting via right-click ``place ...``

15. If the added component is not visible in the library, refresh via ``F5`` again

16. If a new table was added in the database, open the elsys_mariadb_lib.DbLib File (also included in the BitBucket folder)

.. _50_Altium_database_include:

   .. figure:: img/50_Altium_database_include.png
      :width: 300px

      Altium - elsys_mariadb_lib.DbLib File.

17. At the end of the adding process of a component, don´t forget to commit and to push the new components for other users in BitBucket.



.. _AddANewTableToTheDatabasedLibrary:

Add a new table to the databased library
****************************************

If a component is to be added for which no table exists yet, a new table must be created as follows:

1. Open the SQL Editor in DBeaver

.. _190_Open_SQL_Editor:

   .. figure:: img/190_Open_SQL_Editor.png
      :width: 300px

      DBeaver - Open the SQL Editor in DBeaver.

2. On the BitBucket system the sql File "create_tables.sql" is available

.. _191_Create_File:

   .. figure:: img/191_Create_File.png
      :width: 300px

      BitBucket folder - Open the sql File "create_tables.sql".

In this file you can find the syntax for creating a new table.

3. Create the various relevant table columns by copying the following rows:

.. _192_Table_Parameter_1:

   .. figure:: img/192_Table_Parameter_1.png
      :width: 300px

      DBeaver - Parameter - Part 1.

Edit only the name of the table (in this example: "Logic - Buffer and Driver") to the new one.
Copy all rows without editing

4. Add between the field "Type" and "Value" all categorie specific values like "power loss", "tolerance", "voltage rating" etc.

.. _193_Table_Parameter_2:

   .. figure:: img/193_Table_Parameter_2.png
      :width: 300px

      DBeaver - Parameter -Part 2.

5. Excute the sql statement

.. _194_Execute_statement:

   .. figure:: img/194_Execute_statement.png
      :width: 300px

      DBeaver - Execute the sql statement.

6. Now it is possible to add new components to this table by following the instructions in section :ref:`AddANewComponentToTheDatabasedLibrary`.

7. If components were added to the table, it is necessary to change one setting in Altium for this table once.
Therefore, open the "user.DbLib" file in Altium.

8. Select the necessary table.

9. Change under Field Settings the point Database field from "choose field" to Manufacturer Part Number

.. _195_Database_field:

   .. figure:: img/195_Database_field.png
      :width: 300px

      Altium - Change database field.

10. Save the new settings in the "user.DbLib" file and commit it to the BitBucket system for all the other users.

