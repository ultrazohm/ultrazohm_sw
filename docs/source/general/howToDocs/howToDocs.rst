.. _howToDocs:

===========
How to docs
===========

The documentation for the UltraZohm uses `<https://www.sphinx-doc.org>`_.
Sphinx creates the documentation pages in html based on text files.
These text files use `reStructuredText <https://rest-sphinx-memo.readthedocs.io/en/latest/ReST.html>`_ (RST) as a markup language.
Sphinx takes the different RST files and builds them to the docs page.
The documentation is hosted on a web server, the build and deployment is handled by the :ref:`build pipeline <CI bitbucketPipeline>`.

.. note :: The online version on docs.ultrazohm.com is always the documentation of the **main** branch.
           If you build the documentation locally, you build the documentation of the specific branch that you have checked out!
           Building the documentation locally is useful for writing the documentation and getting a preview of the changes.

Installation
============

.. tip:: Use the :ref:`vscode_remote_container` to handle all installations for you instead of installing all dependencies on your machine and keeping them up to date! Using the :ref:`vscode_remote_container` is strongly recommended!

To build and edit the documentation on your native system, you need to:

#. Install `Python <https://www.python.org/>`_ 
#. Install pip (included in current python versions)
#. Install everything in the ``requirements.txt`` in ``/docs`` by invoking ``pip install -r requirements.txt`` in a command shell inside ``/docs``
#. Install everything required for the extension ``sphinxcontrib.tikz``. `Follow their install guide <https://github.com/sphinx-contrib/tikz>`_!
  
   * As image processing ``suite`` you have to install `Ghostscript <https://www.ghostscript.com/>`_
   * Assuming standard installation path the include path for Ghostscript is: ``C:\Program Files\gs\gs9.54.0\bin`` (Windows)

#. Install everything required for the extension ``Breathe`` (`connects Doxygen to sphinx <https://www.doxygen.nl/index.html>`_. `Install guide <https://github.com/michaeljones/breathe>`_!
#. Build Doxygen by invoking ``make doxygen`` in a shell inside ``/docs``
#. Build the documentation by invoking ``make html``
#. You can open the docs in ``/docs/build/html/index.html``
#. You can edit the documentation by using a text editor of your choice

.. tip:: Sometimes you might need to clean the output with ``make clean`` or generate clean build with ``make clean html``

.. tip:: You can use ``make livehtml`` instead of ``make html`` which opens a new browser that synchronizes live with changes that you make locally (uses `sphinx-autobuild <https://github.com/executablebooks/sphinx-autobuild>`_).

.. image:: https://images2.imgbox.com/ed/32/B0uTI8EZ_o.gif
  :width: 500
  :align: center
  :alt: Alternative text


.. note:: If ``make html`` or ``make livehtml`` do not work due to missing package errors, run ``pip install -r requirements.txt`` again. If this does not solve the problem please open an `issue <https://bitbucket.org/ultrazohm/ultrazohm_sw/issues>`_.

Makefile reference
******************

The following commands are available to call with ``make``.
Generating the sphinx documentation requires that Doxygen was already generated.

====================== ================================
Command                Function
====================== ================================
``make clean``         deletes sphinx build folder
``make doxygen_clean`` deletes the Doxygen build folder
``make html``          builds sphinx documentation
``make doxygen``       builds Doxygen
``make docs``          builds Doxygen and sphinx
``make livehtml``      builds sphinx with live preview
====================== ================================

Video
*****

This video shows how to install python, the requirements, and build the documentation.
Please note that the installation steps for ``sphinxcontrib.tikz`` (i.e., Ghostscript and Latex) is not shown in the video since the installation steps depend on your OS.
Please note that the installation steps for ``breathe`` (i.e., Doxygen) are not shown in the video since the installation steps depend on your OS.

.. youtube:: dxAlD-VzE0c

This video shows how to change something in the documentation, add a new page, commit the changes and create a pull request in Bitbucket.

.. youtube:: pcG1XMzVDc8

Write the docs
==============

See `write the docs <https://www.writethedocs.org/guide/>`_ as a great resource on how to write documentation.
A good cheat sheet is located here: * `Example usage from Anaconda <https://docs.anaconda.com/restructuredtext/detailed/>`_ 


Style
*****

Do:

* Keep it simple
* Use simple language
* Describe the current state
* Focus on the interface
* Provide examples on how to use the module, software, PCB, ...
* Provide additional information in a dedicated section
* Have a download section with schematics, additional information, ...
* Use one line per sentence for cleaner git diffs

Don't:

* Write long and complicated sentences
* Add unnecessary chatter
* Chatter about what might change in the future (exception: roadmap)
* Mix interface with rational
* Mix implementation details and user interface
* Have random download links in text blocks
* Have random line breaks in the text

Common functions
****************

Use the following examples for reference on how to write the docs.
Basics:

Structure
^^^^^^^^^

The structure of ``.rst`` files is based on indentation with spaces.
These indentations are a vital part of .rst and do **not** solely exist for visual alignment. 

.. note:: Spaces are recommended for indentation, but tabs may also be used. For tabs, refer to :ref:`notepad`.

**Example**

.. code-block:: rst
    
    This is a top-level paragraph.

        This paragraph belongs to a first-level blockquote. *Indentation is 4 spaces from the previous.*

            This paragraph belongs to a second-level blockquote. *Indentation is 4 spaces from the first-level or 8 from the top-level.*

    Another top-level paragraph.

        This paragraph belongs to a second-level blockquote.

    This paragraph belongs to a first-level blockquote.  The
    second-level blockquote above is inside this first-level
    blockquote.
    
    * Level 1
    
        * Level 2
   
**This translates to the following:**

This is a top-level paragraph.

    This paragraph belongs to a first-level blockquote. *Indentation is 4 spaces from the previous.* 

        This paragraph belongs to a second-level blockquote. *Indentation is 4 spaces from the first-level, or 8 from the top-level.*

Another top-level paragraph.

        This paragraph belongs to a second-level blockquote.

    This paragraph belongs to a first-level blockquote.  The
    second-level blockquote above is inside this first-level
    blockquote.
    
* Level 1
    
    * Level 2
   
Code block
^^^^^^^^^^

.. code-block:: rst

    .. code-block:: c

        void function(int argv);

.. code-block:: c

   void function(int argv);


Figures
^^^^^^^

.. code-block:: rst

     .. _labelName:

     .. figure:: figure.svg

       Caption.

Refernce:

.. code-block:: rst

    Reference ::numref:`labelName`.

Links
^^^^^

.. code-block:: rst

    `UltraZohm <ultrazohm.com>`_ 

Mermaid
^^^^^^^

You can and should use `mermaid <https://mermaid-js.github.io/mermaid/#/>`_ to create figures.
Mermaid figures are directly inserted into the docs and **searchable**!

.. code-block:: rst

    .. mermaid::

      graph TD
      A[Text]
      A --> B[More text]


.. mermaid::

  graph TD
  A[Text]
  A --> B[More text]


Tables
^^^^^^

For most information, using a .csv table is preferred:

.. code-block:: rst

    .. csv-table:: table
    :file: path_to_table/table.csv
    :widths: 50 50 50
    :header-rows: 1

Technical details
=================

The UltraZohm project uses the following extensions to sphinx.
All extensions are listed in ``ultrazohm_sw/docs/requirements.txt``.

`sphinx <https://www.sphinx-doc.org/en/master/>`_
 Sphinx-doc is the base software to generate the documentation.

`sphinx_rtd_theme <https://github.com/readthedocs/sphinx_rtd_theme>`_
 The theme of the documentation

`sphinxcontrib-mermaid <https://github.com/mgaitan/sphinxcontrib-mermaid>`_
 Enables to embed `Mermaid <https://mermaid-js.github.io/mermaid/#/>`_ graphs.

`sphinxcontrib.yt <https://github.com/divi255/sphinxcontrib.youtube>`_
 Simple embedding of youtube videos.

`six <https://github.com/benjaminp/six>`_
 Provides compatibility between Python 2 and 3, required by some packages.

`sphinx-autobuild <https://github.com/executablebooks/sphinx-autobuild>`_
 Enable autobuild and reload after changes for local development with ``make livehtml``
 
`sphinx-issues <https://github.com/sloria/sphinx-issues>`_
 Link to issues and pull requests with ``:issue:`51``` and ``:pr:`5```, e.g., issue :issue:`5``
 

`sphinx-copybutton <https://github.com/executablebooks/sphinx-copybutton>`_
  Adds a button to the code blocks that copys the content of the block.
 
`sphinxcontrib-tikz <https://github.com/sphinx-contrib/tikz>`_
  Adds the possibility to write tikz pictures in the documentation.
  Example:

::

   .. tikz:: An Example TikZ Directive with Caption
     :align: left
   
     \draw[thick,rounded corners=8pt]
     (0,0)--(0,2)--(1,3.25)--(2,2)--(2,0)--(0,2)--(2,2)--(0,0)--(2,0);

.. tikz:: An Example TikZ Directive with Caption
  :align: left

  \draw[thick,rounded corners=8pt]
  (0,0)--(0,2)--(1,3.25)--(2,2)--(2,0)--(0,2)--(2,2)--(0,0)--(2,0);


`breathe <https://github.com/michaeljones/breathe>`_
  Adds Doxygen documentation to sphinx.
  See their list of `directives <https://breathe.readthedocs.io/en/latest/directives.html>`_.
  The most common directives are ``doxygenfunction``, ``doxygenstruct``, ``doxygentypedef``, ``doxygendefine``.
  See `doxygen documentation <https://www.doxygen.nl/manual/docblocks.html>`_ for how to write Doxygen comments.

.. _doxygen:

Doxygen
=======

Write Doxygen comments to header files that document the API.
Example:

.. code-block:: c

   /**
    * @brief Converts a signed fixed-point value that is stored as a signed 32-bit integer value to a float.
    *        This function should only be used directly after reading the int32_t variable from AXI!
    * 
    * @param data Fixed point value stored as a signed 32-bit integer that is read from AXI.
    * @param number_of_fractional_bits Number of fractional bits of the data, 31-number_of_fractional_bits is the number of integer bits.
    * @return float 
    */
   static inline float uz_convert_sfixed_to_float(int32_t data, int number_of_fractional_bits) {
    uz_assert(number_of_fractional_bits>=0);
    return (ldexpf((float) data, -number_of_fractional_bits));
   }

Adding the following line to a docs page:

.. code-block:: rst

   .. doxygenfunction:: uz_convert_sfixed_to_float

Generates the following ouput in the docs:

.. figure:: img/doxygen_sample_output.png
   :scale: 70
   :align: center

   Example output of Breathe.

Examples in docs:
 - :ref:`HAL`
 - :ref:`AXI_testIP`

.. tip:: Note that all types that are used in the function arguments have to be documented, e.g., typedefed variables (see :ref:`AXI_testIP`).

Known Issues
============

.. _notepad:

Compatibility issue with Notepad++ and .rst files 
*************************************************

.. warning:: This is not recommended! Use the :ref:`vscode_remote_container` instead!

* If u edit ``.rst`` files in the UltraZohm documentation, an issue whilst using the tabulator key in Notepad++ can occur.

  - If you align the command with the tabulator key in Notepad++, everything looks as its supposed to.

  .. image:: ./img/Notepad_tabulator.png

  - However, if you open the saved file with the tabulator alignment in the normal windows editor, the following is visible.

  .. image:: ./img/Editor_tabulator.png

  - This wrong alignment via Notepad++ leads to the following error whilst executing **make html**. You can see the misalignment highlighted in green.

  .. image:: ./img/CMD_tabulator.png
  
  

* To fix this issue, you can do the following:

  1. In Notepad++ go to **Settings** → **Settings** → **Language**
  2. On the right sight, check the box **Replace by space** (Durch Leerzeichen ersetzen) and set the **Tab size** to i.e. 4. 
     4 spaces is the standard indentation size for different levels. 

  .. image:: ./img/Notepad_fix.png
  