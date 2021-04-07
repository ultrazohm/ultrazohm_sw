.. _AltiumDB:

====================
Altium DB
====================
Before starting with the description and instructions on how to use the database system in Altium, a brief overview of the different tools is given.

.. _200_Overview_DB_system:

   .. figure:: img/200_Overview_DB_system.png
      :width: 500px

      Overview of the databased system for Altium.

The library system splits up in three different locations:

1. The `altium_libraries repository <https://bitbucket.org/ultrazohm/altium_libraries/src/master/>`_. All schematic symbols and PCB footprints of the individual components as well as the DbLib file that is required to connect to the database on the Ultrazohm server is located in this repository
2. The UltraZohm server: All component parameters like Manufacturer Part Numbers etc. are managed by a MariaDB database on the server. In order to edit database records a separate database client (e.g. `DBeaver <https://dbeaver.io/>`_) is recommended.
3. User's PC: The PC of the PCB developer gets access to the locations 1 and 2 and the developer is able to place the components. In case he has write access he can also edit and add components.

In the following, the individual tools and necessary installation steps are discussed.

.. note :: All usernames and passwords can be optained from the UltraZohm core developer team. Please write an E-Mail to `info@ultrazohm.com <mailto:info@ultrazohm>`_


In order to use the database driven library for Altium, a few settings need to be made initially.
In the following chapters are a guideline on how to install and set the parameter is given.
The following tools are required:

* Bitbucket
* ODBC Data Sources (64-Bit)
* Altium
* DBeaver

Videos of the setup
===================

How to install Altium:

.. youtube:: SS1pZKD2n0Y

How to install the Altium library:

.. youtube:: 0VST-4g3nWA

How to install DBweaver:

.. youtube:: DaSXdXeiYR4


Bitbucket access setup
======================

1. To work with the databased library system in Altium, it is necessary to get access to the Bitbucket system of the UltraZohm, especially to the `altium_libraries repository <https://bitbucket.org/ultrazohm/altium_libraries/src/master/>`_

.. _1_Bitbucket:

   .. figure:: img/1_Bitbucket.png
   
        Bitbucket - altium_libraries.

2. Clone the repository on your local computer

3. If you intent to add new compnents, create a new feature branch. Follow the naming convention feature/<meaningfull name>. If the git shell interface is used the command is ``git checkout -b feature/<branch_name>``

4. If a new component was added, commit and push the new component to Bitbucket

5. When component editing is finished open a pull request on Bitbucket. The components will be reviewed and merged into the master branch.

.. _ServerAccessSetup:

Server access setup
===================

Altium needs to get access to the database system on the UltraZohm server. The interface to the database is an ODBC database driver.

1. If not done yet download and install the `MariaDB ODBC 3.1 Driver <https://downloads.mariadb.org/connector-odbc/>`_

2. ``Open`` the ODBC-Datasource App (64-Bit)

.. _20_ODBC_sources_1:

   .. figure:: img/20_ODBC_sources_1.png
      :width: 300px

      OBDC - open App.

3. ``Add`` a new User-DSN

.. _21_ODBC_sources_2:

   .. figure:: img/21_ODBC_sources_2.png
      :width: 300px

      OBDC - add user-DSN.

4. Select the MariaDB ODBC 3.1 Driver

.. _22_ODBC_sources_3:

   .. figure:: img/22_ODBC_sources_3.png
      :width: 300px

      OBDC - select MariaDB.


5. Create a new data source to MariaDB

.. _23_ODBC_sources_4:

   .. figure:: img/23_ODBC_sources_4.png
      :width: 300px

      OBDC - create a new data source.

6. Connect it to the ultrazohm server

.. _24_ODBC_sources_5:

   .. figure:: img/24_ODBC_sources_5.png
      :width: 300px

      OBDC - connection to ultrazohm server.

.. note :: The ODBC connection is read only because no changes on the database will be made from Altium directly. A separate database client e.g. DBeaver is used to edit the database (see :ref:`IntegrationInAltium`).


7. Do nothing and press ``Next >``

.. _25_ODBC_sources_6:

   .. figure:: img/25_ODBC_sources_6.png
      :width: 300px

      OBDC - skip.

8. Do nothing and press ``Next >``

.. _26_ODBC_sources_7:

   .. figure:: img/26_ODBC_sources_7.png
      :width: 300px

      OBDC - skip.

9. Force to use TLS and go back for three times ``< Previous``

.. _27_ODBC_sources_8:

   .. figure:: img/27_ODBC_sources_8.png
      :width: 300px

      OBDC - use TLS.

10. Select the database "altium_library" and ``Test DSN``

.. _28_ODBC_sources_9:

   .. figure:: img/28_ODBC_sources_9.png
      :width: 300px

      OBDC - select "altium_library".

11. Finish the settings by pressing three times ``OK``

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

4. Select the register Installed. While not necessary it is strongly recommended to remove all not required libraries at this point (e.g. the standard "Miscellanious Devices" library from Altium)

.. _31_File_based_lib:

   .. figure:: img/31_File_based_lib.png
      :width: 300px

      Altium - installed libraries.

5. Select ``Install…`` and navigate to the path where the Bitbucket repository is cloned on the computer. Select the file "user.DbLib"

6. ``Close`` this window

7. After installing the DBLib - File, you can choose between the different integrated component tables

.. _32_Elsys_mariadb_lib_example:

   .. figure:: img/32_Elsys_mariadb_lib_example.png
      :width: 300px

      Altium - different component tables.

8. Now you can use all already existing components from the databased library

Installation and setup of a front end (DBeaver)
===============================================

If new components are required the developer will need write access to the Bitbucket repository and to the database on the UltraZohm server.
A dedicated user called ``altium_developer`` is available on the database system for this purpose. He has write access to the whole library database.
As a graphical database client DBeaver is recommended.

1. `Download the Dbeaver software <https://dbeaver.io/download/>`_ to work with the MariaDB on the UltraZohm server  

2. Open DBeaver

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

.. _38_DBeaver_4:

   .. figure:: img/38_DBeaver_4.png
      :width: 300px

      DBeaver - driver settings - 2.

7. Select ``use SSL`` and uncheck ``Verify server certificate`` in the SSL tab

.. _39_DBeaver_5:

   .. figure:: img/39_DBeaver_5.png
      :width: 300px

      DBeaver - SSL settings.

8. Click ``Finish``. At this time, you are able to connect to the database

9. If the connection failed, control the settings and reconnect via right click on the ``altium_library`` --> ``Invalidate/ Reconnect``

10. If the connection was successful, the following table structure must be visible

.. _40_DBeaver_altium_lib:

   .. figure:: img/40_DBeaver_altium_lib.png
      :width: 300px

      DBeaver - table structure.

**This step completes the initial setup.**

.. _AddANewComponentToTheDatabasedLibrary:

Add a new component to the databased library
********************************************

In the following chapter the procedure to add a new component is illustrated by adding an SMD capacitor.

.. note :: The goal of this database system is that schematic and footprints of generic components only exist once.
           This means that schematics and footprints symbols of generic components only have to be in the Bitbucket repository once, even if there are multiple physical components available (e.g. different manufacturers and values).
           Only if the component has a different geometry or pinout, a new schematic and/or footprint must be added.
           The number of pins on the symbol must match the number of pins on the footprints. The mapping of the pins is done with the pin numbering (pin 1 of the symbol is mapped to pin 1 of the footprint and so on).
           In case of doubt the symbol and the footprint supplied by the manufacturer must be used instead of using an existing footprint.


1. Check if the schematic symbol already exists as a symbol in the Bitbucket system. The schematic symbols are located under ``alitum_libraries\symbols`` If the schematic does not exist, copy the schematic symbol in the suitable directory under ``alitum_libraries\symbols``. It is vital that the ``.SchLib`` file **only contains one symbol**. See :ref:`SchematicAndFootprints` on how to extract the symbol from different sources.

.. _41_Explorer_SCH:

   .. figure:: img/41_Explorer_SCH.png
      :width: 300px

      Explorer - symbols.

2. Follow the naming convention for the ``.SchLib`` file **SCH - <directory> - <description>.SCHLIB**

.. note :: The extension of the file is written in capital letters.

3. Check if the footprint symbol already exists in the Bitbucket system. If the component does not exist copy the footprint in the suitable folder of the footprints ``\alitum_libraries\footprints``. It is vital that the ``.PcbLib`` file **only contains one symbol**. See :ref:`SchematicAndFootprints` on how to extract the symbol from different sources.

.. _42_Explorer_PCB:

   .. figure:: img/42_Explorer_PCB.png
      :width: 300px

      Explorer - footprints.

4. Follow the naming convention for the ``.PcbLib`` file **SCH - <directory> - <description>.PCBLIB**


.. note :: The extension of the file is written in capital letters.

5. Switch to the DBeaver tool

6. Choose a suitable table where the component should be added. If no table is suitable go on with the instruction given in section :ref:`AddANewTableToTheDatabasedLibrary`.

.. warning :: This option must only be chosen after talking to your supervisor and must be announced in a pull request. 
			  When adding a new table, the ``.DbLib`` file, which implements the connection from Altium to the database, must be changed and all users need to update the file in order to get access to the new table.
			  In case of doubt put the component in an existing table. The current amount of tables should be sufficient to fulfill the requirements.

.. _43_DBeaver_table:

   .. figure:: img/43_DBeaver_table.png
      :width: 300px

      DBeaver - choose a suitable table.

7. A new register on the right side with the table will appear

.. _44_DBeaver_Properteries:

   .. figure:: img/44_DBeaver_Properteries.png
      :width: 300px

      DBeaver - Editor will open on the right side.

8. Switch to the "Data" register. An overview of all already added components will be shown there.

.. _45_DBeaver_Data:

   .. figure:: img/45_DBeaver_Data.png
      :width: 300px

      DBeaver - change to tab "data". In this case, no component is still existing in the table.

9. Press the ``add`` button and a new row highlighted in green appears.

10. Double click on a cell to enter content.

11. To switch between the view of all components and the comfortable editing mode for one component --> ``press tab``.

12. If all necessary cells are filled with information, save the components with the ``save`` button (under the current table on the left side or by pressing ``Ctrl + S``).
Some cells are constraint to be ``NOT NULL``. These cells must be filled before saving is allowed. If those cells are not filled the following message will occur.

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


13. If the component is saved in DBeaver, refresh the view in Altium via ``F5`` --> choose ``place`` --> ``part`` and select the library where the component has been added --> the new component is shown with all the inserted database information

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

16. If a new table was added in the database, open the user.DbLib File (also included in the Bitbucket folder)

.. _50_Altium_database_include:

   .. figure:: img/50_Altium_database_include.png
      :width: 300px

      Altium - user.DbLib File.

17. At the end of the adding process of a component commit and to push the new components for other users in Bitbucket and open a pull request to the master branch.



.. _AddANewTableToTheDatabasedLibrary:

Add a new table to the databased library
****************************************

.. warning :: This option must only be chosen after talking to your supervisor and must be announced in a pull request. 
			  When adding a new table, the ``.DbLib`` file, which implements the connection from Altium to the database, must be changed and all users need to update the file in order to get access to the new table.
			  In case of doubt put the component in an existing table. The current amount of tables should be sufficient to fulfill the requirements.

If the component you intend to add does not fit in the existing tables a new table must be created. In the following this procedure is described:

1. Open the SQL Editor in DBeaver

.. _190_Open_SQL_Editor:

   .. figure:: img/190_Open_SQL_Editor.png
      :width: 300px

      DBeaver - Open the SQL Editor in DBeaver.

2. On the Bitbucket system the sql File "create_tables.sql" is available

.. _191_Create_File:

   .. figure:: img/191_Create_File.png
      :width: 300px

      Bitbucket folder - Open the sql File "create_tables.sql".

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

10. Save the new settings in the "user.DbLib" file and commit it to the Bitbucket system for all the other users.

