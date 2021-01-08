====================
How to use Altium DB
====================

To use the database driven library for Altium, a few settings habe to be made once.
In the following chapters a guideline how to install and set the parameter is given.
The following tools will be needed:

* BitBucket
* ODBC Data Sources (64-Bit)
* Altium
* DBeaver

BitBucket access setup
======================

1. To work with the databased library system in Altium, it is necessary to get access to the BitBucket system of the UltraZohm, exspecially to the folder "altium_libraries"

.. _1_BitBucket:

   .. figure:: img/1_BitBucket.png
   
        BitBucket - altium_libraries.

2. Clone the repository on your local hard disk

3. Create a new feature branch, to work with the system

4. If a new component was added, don´t forget to commit and push the new component to BitBucket by request a push!


Server access setup
===================
1. ``Open`` the ODBC-Datasource App (64-Bit)

.. _20_ODBC_sources_1:

   .. figure:: img/20_ODBC_sources_1.png
   
        OBDC - open App.

2. ``Add`` a new User-DSN

.. _21_ODBC_sources_2:

   .. figure:: img/21_ODBC_sources_2.png
   
        OBDC - add user-DSN.

3. Select the MariaDB ODBC 3.1 Driver

.. _22_ODBC_sources_3:

   .. figure:: img/22_ODBC_sources_3.png
   
        OBDC - select MariaDB.

4. Create a new data source to MariaDB

.. _23_ODBC_sources_4:

   .. figure:: img/23_ODBC_sources_4.png
   
        OBDC - create new data source.

5. Connect it to the ultrazohm server

.. _24_ODBC_sources_5:

   .. figure:: img/24_ODBC_sources_5.png
   
        OBDC - connection to ultrazohm server.

6. Do nothing and press ``Next >``

.. _25_ODBC_sources_6:

   .. figure:: img/25_ODBC_sources_6.png
   
        OBDC - skip.

7. Do nothing and press ``Next >``

.. _26_ODBC_sources_7:

   .. figure:: img/26_ODBC_sources_7.png
   
        OBDC - skip.

8. Force to use TLS and go back for three times ``< Previous``

.. _27_ODBC_sources_8:

   .. figure:: img/27_ODBC_sources_8.png
   
        OBDC - use TLS.

9. Select the database "altium_library" and ``Test DSN``

.. _28_ODBC_sources_9:

   .. figure:: img/28_ODBC_sources_9.png
   
        OBDC - select "altium_library".

10. Finish the settings by pressing three times ``OK``

.. _29_ODBC_sources_10:

   .. figure:: img/29_ODBC_sources_10.png
   
        OBDC - finish settings.


Integration in Altium
=====================

1. Open a schematic document in Altium
2. Choose the point ``place`` --> ``part``; a menue on the left or right side will open with the already installed library preferences called "components"

.. _30_Elsys_mariadb_lib:

   .. figure:: img/30_Elsys_mariadb_lib.png
   
        Altium - component libraries.

3. Click on the three horizontal lines and select the point ``File-based library Preferences``
4. Select the register Installed

.. _31_File_based_lib:

   .. figure:: img/31_File_based_lib.png
   
        Altium - installed libraries.

5. Select ``Install…`` and navigate to the point where the BitBucket folder is cloned on the computer. Select the file "elsys_maria_db_lib.DbLib"
6. ``Close`` this window
7. After installing the DBLib - File you can choose between the different integrated component tables

.. _32_Elsys_mariadb_lib_example:

   .. figure:: img/32_Elsys_mariadb_lib_example.png
   
        Altium - different component tables.

8. Now you can use all already existing components from the databased library

Installation and setup of a front end (DBeaver)
===============================================
To be able to add a new component to the database (MariaDB) as easily as possible, it is graphically to use a front end.

1. Download the Dbeaver software to work with the MariaDB on the UltraZohm server https://dbeaver.io/download/ 

.. note :: There are more software tools, which fulfill the possibilities of adding and editing information in a database, but in the institute ELSYS we use DBeaver.

2. To setup the connection to the MariaDB on the UltraZohm Server the following steps (shown in the screenshots below) must be full filled one time.

3. Select MariaDB

.. _35_DBeaver_1:

   .. figure:: img/35_DBeaver_1.png
   
        DBeaver - select mariaDB.

4. Connect it to the ultrazohm server

.. _36_DBeaver_2:

   .. figure:: img/36_DBeaver_2.png
   
        DBeaver - general settings.

5. Download the MariaDB driver, which is recommended

.. _37_DBeaver_3:

   .. figure:: img/37_DBeaver_3.png
   
        DBeaver - driver settings - 1.

6. These settings must be selected automatically after the download of MariaDB. 
Before clicking ``Finish`` the settings of SSL must be done.

.. _38_DBeaver_4:

   .. figure:: img/38_DBeaver_4.png
   
        DBeaver - driver settings - 2.

7. Select use SSL and do not verify server certificate

.. _39_DBeaver_5:

   .. figure:: img/39_DBeaver_5.png
   
        DBeaver - SSL settings.

8. Now the connection to the ultrazohm MariaDB should be possible.

9. If the connection failled, control the settings and reconnect via right click on the ``altium_library`` --> ``Invalidate/ Reconnect``

10. If the connection was successful, the following table structure must be visible

.. _40_DBeaver_altium_lib:

   .. figure:: img/40_DBeaver_altium_lib.png
   
        DBeaver - table structure.

**This step completes the one time setup.**

Add a new component to the databased library
********************************************
To make the process of adding a component more visible, it will be described by adding a SMD capacitor.

.. note :: The target of this databased system is that schematic and footprints of generic components should only exist one time.
           This means, that resistors or other generic components only must be as schematic and footprint symbol once in the BitBucket folder system, even if resistors have different values.
           Only if the component has a different geometry a new schematic and/or footprint must be added.
           And be careful when you create new schematics and footprints that the pins and the naming of the pins are equal (very important by connectors and ics).

1. Check if the schematic symbol already exists as a symbol in the BitBucket system. Therefore, open the folder of the cloned BitBucket repository.
If the schematic does not exist, copy the schematic symbol in the suitable folder of the schematics ``...\alitum_libraries\symbols\...``

.. _41_Explorer_SCH:

   .. figure:: img/41_Explorer_SCH.png
   
        Explorer - symbols.
		
2. Regarding the name of the component: **SCH - Folder - Description.SCHLIB**

3. Check if the footprint symbol already exists in the BitBucket system. If not, copy the footprint in the suitable folder of the footprints ``...\alitum_libraries\footprints\...``

.. _42_Explorer_PCB:

   .. figure:: img/42_Explorer_PCB.png
   
        Explorer - footprints.
		
4. Regarding the name of the footprint: **PCB - Folder - Description.PCBLIB**

5. Change to the DBeaver tool

6. Choose the suitable table, where the component should be added

.. _43_DBeaver_table:

   .. figure:: img/43_DBeaver_table.png
   
        DBeaver - choose the suitable table.	

7. A new register on the right side with the table will be opened

.. _44_DBeaver_Properteries:

   .. figure:: img/44_DBeaver_Properteries.png
   
        DBeaver - Editor will open on the right side.

8. Mostly the "Properties" register will open at first. Change to the "Data" register. 
An overview of all already added components will be shown there. (In this case no component is still existing in the table.)

.. _45_DBeaver_Data:

   .. figure:: img/45_DBeaver_Data.png
   
        DBeaver - change to tab "data".

9. Press the ``add`` button and a new row highlighted in green while appear.

10. By clicking on a respective cell, the cell can be filled with content.

11. To switch between the view of all components and the comfortable editing mode for one component --> ``press tab``.

12. If all necessary cells are filled with information, save the components with the ``save`` button (under the current table on the left side or by clicking ``Strg. + S``). Some cells are forseen with a clause that they must be be filled before saving is allowed (to help the user not to forget information, which are neccessary). If something is forgotten the following message will occur.

.. _46_DBeaver_Data_Error:

   .. figure:: img/46_DBeaver_Data_Error.png
   
        DBeaver - error message.

Press ``OK`` and fill out the missing cell (in this example "ComponentLink1Description")

The table cells, which are here described in detail is from "Capacitors - SMD" table as an example

+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Cell name                 | Value                                 | Explanation                             | Must be filled |
+===========================+=======================================+=========================================+================+
| PartID                    | Automatically added                   |                                         |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Created On                | Automatically added                   |                                         |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Comment                   | Value                                 |                                         |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| ComponentLink1Description |                                       | Homepage, Datasheet                     | X              |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| ComponentLink1URL         | https://www.mouser.de/datasheet/2     | URL Link to homepage or datasheet       | X              |
|                           | /281/c03e-516224.pdf                  | (could be reaced in Altium by right     |                |
|                           |                                       | click in the schematic on the component |                |
|                           |                                       |  --> direct connection to datasheet)    |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| ComponentLink2Description |                                       | See "ComponentLink1Description"         |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| ComponentLink2URL         |                                       | See "ComponentLink1URL"                 |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| ComponentLink3Description |                                       | See "ComponentLink1Description"         |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| ComponentLink3URL         |                                       | See "ComponentLink1URL"                 |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| ComponentLink4Description |                                       | See "ComponentLink1Description"         |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| ComponentLink4URL         |                                       | See "ComponentLink1URL"                 |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| ComponentLink5Description |                                       | See "ComponentLink1Description"         |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| ComponentLink5URL         |                                       | See "ComponentLink1URL"                 |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| ComponentLink6Description |                                       | See "ComponentLink1Description"         |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| ComponentLink6URL         |                                       | See "ComponentLink1URL"                 |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Component Type            |                                       | Type of the component                   | X              |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Description               |                                       | A descritption make the usage of the    | X              |
|                           |                                       | component easier to the designer        |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Device Package            |  0603                                 | 0603, 0805,…                            |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Footprint Path            | footprints\Capacitor - Chip\PCB       |Path were the footprint is saved         | X              |
|                           | - CAPACITOR - CHIP - CAPC_0603.PCBLIB |                                         |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Footprint Path 2          |                                       | See "Footprint Path"                    |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Footprint Path 3          |                                       | See "Footprint Path"                    |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Footprint Ref             |  C_0603                               |Name in the Altium Library               | X              |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Footprint Ref 2           |                                       | See "Footprint Ref"                     |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Footprint Ref 3           |                                       | See "Footprint Ref"                     |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Last Updated              |  Automatically added                  | Last Updated                            |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Manufacturer              |  muRata                               | Manufacturer                            | X              |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Manufacturer Part Number  |  GCJ188R71H103KA01D                   | Manufacturer Part Number                | X              |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Minimum Order             |                                       | Minimum Order                           |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Mounting Type             |  SMD                                  | SMD, THT                                |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Operating Temperature     |  -55 - 125°C                          | Operating Temperature                   |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Series                    |  GCJ                                  | Series                                  |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Supplier 1                |  Mouser                               | Supplier                                | X              |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Supplier Part Number 1    |  81-GCJ188R71H103KA1D                 | Supplier part number                    | X              |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Supplier 2                |                                       | Supplier                                |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Supplier Part Number 2    |                                       | Supplier part number                    |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Supplier 3                |                                       | Supplier                                |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Supplier Part Number 3    |                                       | Supplier part number                    |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Supplier 4                |                                       | Supplier                                |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Supplier Part Number 4    |                                       | Supplier part number                    |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Supplier 5                |                                       | Supplier                                |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Supplier Part Number 5    |                                       | Supplier part number                    |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Supplier 6                |                                       | Supplier                                |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Supplier Part Number 6    |                                       | Supplier part number                    |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Library Path              |symbols\Passives\SCH - PASSIVES        | Path were the schematic symbol is saved | X              |
|                           |- CAPACITOR.SCHLIB                     |                                         |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Library Ref               |  Capacitor                            | Name in Altium schematic library        | X              |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Type                      |                                       | Type                                    | X              |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Tolerance                 |  10 %                                 | Tolerance                               |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Voltage Rating            |  50 VDC                               | Voltage Rating                          |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Value                     |  0.01 µF                              | Value                                   | X              |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Created from              |  MGremer                              | Designer                                |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Verified by               |                                       | Verfikator                              |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Live Cycle Status         |   1                                   | 1. new design                           | X              |
|                           |                                       | 2. verified                             |                |
|                           |                                       | 3. in use                               |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| JLC CPL                   |                                       | JLC CPL component description for order-|                |
|                           |                                       | ing and commissioning the PCB by JLC    |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+
| Stock number              |   Labor SMD Container                 | Were the component is stored            |                |
+---------------------------+---------------------------------------+-----------------------------------------+----------------+

13. If the component is saved in DBeaver refresh the view in Altium via ``F5`` --> choose ``place`` --> ``part`` and select the library, where the component where added --> the new component is shown with all the inserted database information

.. _47_Altium_Parameter1:

   .. figure:: img/47_Altium_Parameter1.png
   
        Altium - component information - 1.

.. _48_Altium_Parameter2:

   .. figure:: img/48_Altium_Parameter2.png
   
        Altium - component information - 2.

.. _49_Altium_Parameter3:

   .. figure:: img/49_Altium_Parameter3.png
   
        Altium - component information - 3.

14. The component can now be used in the schematic by ``drag and drop`` or by selecting via right click ``place ...``
15. If the added component is not visibile in the library, refresh via ``F5`` again
16. If a new table was added in the database, open the elsys_mariadb_lib.DbLib File (also included in the BitBucket folder)

.. _50_Altium_database_include:

   .. figure:: img/50_Altium_database_include.png
   
        Altium - elsys_mariadb_lib.DbLib File.

17. At the end of the adding process of a component don´t forget to commit and to push the new components for other users in BitBucket. 



