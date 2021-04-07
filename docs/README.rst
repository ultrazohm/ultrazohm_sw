===============================
Writing Documentation with ReST
===============================

Setup
-----

The restructured Text is a markup language. A good workflow to write ReST docs (under Windows) can be achieved with the following steps:

1. Install the latest Python Version via the Microsoft Store
	1. Make sure, that Python is installed as admin (right clicking on the python.exe), because it may cause problems.
	2. Therefore, install it under **C:\\Program Files\\Python**

2. Install pip, the Python package manager
	1. `Download <https://bootstrap.pypa.io/get-pip.py>`_ the get-pip.py file
	2. Copy the download file to **C:\\Program Files\\Python\\Scripts**
	3. Execute the script by double clicking on it (as admin if its not working)

3. Install sphinx
	1. Open the windows power shell (as admin per rigth clicking)
	2. Check the Python version and wheter access is possible by typing **python --version**
	3. For the setup of the environment type change to the root directory of the documentation (e.g. **cd C:\\Users\\...**). Check if the requirements.txt is in the directory (**ls**) and type **pip install -r requirements.txt**
	4. There will probably be a warning that the files are not in the PATH variable. Add the files to the PATH variable by following `this guide <https://www.architectryan.com/2018/03/17/add-to-the-path-on-windows-10/>`_ .


4. Install an editor of your choice. For Linux I prefer `(x)Emacs <https://www.gnu.org/software/emacs/>`_ but for Windows `Notepad++ <https://notepad-plus-plus.org/downloads/>`_ works fine

5. For ReST syntax highlighting follow the instructions of `this project <https://github.com/steenhulthin/reStructuredText_NPP>`_

6. For quick preview of the docs you wrote perform the following steps in Notepad++:
	1. Hit F5
	2. Select the **make.bat** file
	3. The command must have the following format: **\\path\\to\\make.bat html**
	4. Hit save and select a shortcut that you like (e.g. Alt+B)

7. The generated documents can be viewed, starting from the top folder, under **build\\html\\index.html** in any browser.

Possible issues
---------------

If your project does not build anymore because of a missing package it is likely that someone added a new python package
to build the documentation. Please run **pip install -r requirements.txt** again.

Project Structure
-----------------

The project starts with the toplevel **index.rst**. Here the **toctree(s)** for all other documents is/are defined. Please make use of a clear directory structure
(e.g. subject Hardware -> Directory hardware etc.). Images must be placed in subdirectories named after the document they are related to (e.g. document **carrier_board.rst**
image directory = **images_carrier_board**)

Naming convention: All files lower case and snake case (= snake_case) ecxept README.rst

Writing the docs
----------------

There is a pretty good reference available at `the docs of the sphinx project <https://www.sphinx-doc.org/en/master/contents.html>`_
as well as a `ReST reference <https://rest-sphinx-memo.readthedocs.io/en/latest/ReST.html>`_

The most important element in the project is the **.. toctree::** directive. It defines the structure visible at sidebar of the generated docs.
The elements in the toctree are relative to the document, which means that if only the file name is provided it hast to be in the same
directory as the file with the toctree.

It make sense to always provide an **index.rst** in a directory, which contains the toctree.
If you do not want the toctree visible you can use the expression **:hidden:**
For all further questions refer to the reference.

If you use an additional python package to build the documentation make sure you add it to the **requirements.txt**.

Including raster graphics
-------------------------

To include raster graphics to the documentation use the following command:

.. code-block:: RST

	.. image:: path_to_image/image.png
	 	:width: 300

Please note that there are only two cases in which a raster graphic is acceptable:

	1. The image is a photograph
	2. The image is a screenshot / based on a screenshot

Including searchable images as vector graphics
----------------------------------------------

Every image that does not fit the criteria photograph or based on screenshot has to be included as a searchable vector graphic.
This can be done by the following code, using .svg is advised:

.. code-block:: RST

	.. raw:: html
    :file: path_to_image/image.svg


Including tables
----------------

Including tables in RST is messy, therefore only include .csv tables wit the following command:

.. code-block:: RST

	.. csv-table:: table
  :file: path_to_table/table.csv
  :widths: 50 50 50
  :header-rows: 1


Git Workflow
------------

We use the same git-flow based workflow as in the UltraZohm main repository which means create feature branches and merge them to develop by creating a pull request.
Do not work on master, do not work on develop.