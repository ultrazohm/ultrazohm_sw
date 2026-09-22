.. _howToDocs:

===========
How to docs
===========

The documentation for the UltraZohm uses `<https://www.sphinx-doc.org>`_.
Sphinx creates the documentation pages in HTML based on text files.
These text files use `reStructuredText <https://rest-sphinx-memo.readthedocs.io/en/latest/ReST.html>`_ (RST) as a markup language.
Sphinx takes the different RST files and builds them into the docs pages.
The documentation is hosted on a web server, and the build and deployment are handled by the :ref:`build pipeline <ci>`.

.. note:: The online version on docs.ultrazohm.com is always the documentation of the **main** branch.
           If you build the documentation locally, you build the documentation of the specific branch that you have checked out!
           Building the documentation locally is useful for writing the documentation and getting a preview of the changes.

Installation
============

.. tip::

   Use the :ref:`vscode_remote_container` to handle all installations for you instead of installing all dependencies on your machine and keeping them up to date!
   Using the :ref:`vscode_remote_container` is strongly recommended!

To build and edit the documentation on your native system, you need to:

#. Install `Python <https://www.python.org/>`_ 
#. Install pip (included in current Python versions)
#. Install the local ``pyuzlib`` package and everything in ``docs/requirements.txt`` by invoking ``python -m pip install -e ./pyuzlib -r docs/requirements.txt`` in a command shell inside the workspace root
#. Install everything required for the extension ``sphinxcontrib.tikz``.
   `Follow their install guide <https://github.com/sphinx-contrib/tikz>`_!
  
   * As image processing ``suite`` you have to install `Ghostscript <https://www.ghostscript.com/>`_
   * Assuming a standard installation path, the include path for Ghostscript is: ``C:\Program Files\gs\gs9.54.0\bin`` (Windows)

#. Install everything required for the extension ``Breathe`` (`connects Doxygen to Sphinx <https://www.doxygen.nl/index.html>`_).
   `Install guide <https://github.com/michaeljones/breathe>`_!
#. Build Doxygen by invoking ``make doxygen`` in a shell inside ``/docs``
#. Build the documentation by invoking ``make html``
#. You can open the docs in ``/docs/build/html/index.html``
#. You can edit the documentation by using a text editor of your choice

.. tip:: Sometimes you might need to clean the output with ``make clean`` or generate a clean build with ``make clean html``

.. tip:: You can use ``make livehtml`` instead of ``make html`` which opens a new browser that synchronizes live with changes that you make locally (uses `sphinx-autobuild <https://github.com/executablebooks/sphinx-autobuild>`_).

.. tip:: Use ``make docs`` to build doxygen and the sphinx exactly as it is used in the build pipeline, see :ref:`ci`.

.. image:: https://images2.imgbox.com/ed/32/B0uTI8EZ_o.gif
  :width: 500
  :align: center
  :alt: Alternative text


Makefile reference
******************

The following commands are available to call with ``make`` from ``docs/``.
Generating the sphinx documentation requires that Doxygen was already generated.

========================================= =========================================================================
Command                                   Function
========================================= =========================================================================
``make clean``                            deletes sphinx build folder
``make doxygen_clean``                    deletes the Doxygen build folder
``make html``                             builds sphinx documentation
``make doxygen``                          builds Doxygen
``make docs``                             builds Doxygen and sphinx (what the CI docs steps run)
``make livehtml``                         builds sphinx with live preview
``make auto_generate_available_machines`` regenerates the PMSM machine catalog (header and inventory CSV)
``make check_available_machines``         verifies the committed machine catalog matches the CSV sources (CI check)
========================================= =========================================================================

PMSM artifact tooling can also be run directly from the repository root, without building documentation:
``make pyuzlib-check-generated`` checks the committed inventory and all three generated headers without writing files;
``make pyuzlib-generate-machines`` regenerates them.
The ``docs/`` targets ``check_all`` and ``auto_generate_all`` forward to these root targets.
Checks report stale or missing artifacts and a regeneration command; they do not use shared temporary files.

Docs and ceedling test output
*****************************

When ``CEEDLING_GLOBAL_CSV_EXPORT`` is enabled, PMSM model, controller, and integration tests
export CSV results under ``vitis/software/Baremetal/build/artifacts/test-data/``.
Each controller test writes its own matching configuration CSV: a result named``<stem>.csv`` is paired with ``<stem>_config.csv`` in the same directory.
The switch in ``vitis/software/Baremetal/src/uz/uz_global_configuration.h`` defaults to ``0``;
ordinary test runs therefore do not generate these CSVs. Numerical assertions still run.
The C test export helper creates parent directories on demand; no docs setup, Python installation,
or preparation target is required to run these tests.
From the repository root:

.. code-block:: bash

   make ceedling-test             # C tests only
   make ceedling-test-with-inport # all C tests with PMSM CSV export enabled
   make -C docs docs             # Doxygen and Sphinx only
   make ceedling-test && make -C docs docs   # explicitly run both

Python validation is separate from the C and documentation builds:

.. code-block:: bash

   python -m pip install -e './pyuzlib[dev]' bokeh
   make pyuzlib-test
   make pyuzlib-smoke-pmsm-plot

CI runs these commands in its ``pyuzlib tests`` job, alongside ``make pyuzlib-check-generated``.
The Bokeh dependency enables the optional Bokeh reader test without installing the full docs stack.
The smoke test builds only the PMSM model tests with CSV export enabled, checks real CSV columns,
finite values, and timestamps, and renders the actual Matplotlib docs plot to a PNG without a GUI.
It uses fresh temporary build and output directories and removes them afterwards; it cannot pass
using stale artifacts and does not modify the configuration header or ordinary Ceedling build.
It requires Ceedling and the host C compiler, but neither Sphinx nor Doxygen.

Direct ``ceedling test:all`` and individual targets such as ``ceedling test:test_uz_pmsm_swmodel``
also work from ``vitis/software/Baremetal``.
The old docs targets ``ceedling_tests``, ``docs_with_ceedling_tests``, and ``ceedling_test_output``
have been removed. ``make ceedling_clean`` in ``docs/`` still invokes ``ceedling clobber``;
this explicitly cleans Ceedling build outputs, including default test artifacts.
Test execution itself does not delete previous artifacts. Files from tests not run may therefore remain;
use a fresh output directory when collecting results for publication.

To generate plot data for manual inspection, use the ``config/csv_export.yml`` Ceedling mixin.
It overrides ``CEEDLING_GLOBAL_CSV_EXPORT`` for compilation and preprocessing and keeps its
build outputs in ``build/artifacts/csv-export-build/``, separate from ordinary tests.
No tracked header needs editing, and normal test builds retain the default of ``0``.
The root target ``make ceedling-test-with-inport`` runs the full suite with this mixin;
integration-test exports can produce large CSV files.
To select an isolated output directory, set ``UZ_TEST_DATA_DIR`` to the same absolute path
for C tests and Python plot readers (the directory override does not enable exports):

.. code-block:: bash

   export UZ_TEST_DATA_DIR="$(mktemp -d)/test-data"
   (cd vitis/software/Baremetal && ceedling --mixin=config/csv_export.yml test:test_uz_pmsm_swmodel)
   python3 docs/source/software/control/uz_pmsm_swmodel/view_pmsm_model_test_results.py

The plotting scripts require pyuzlib and their plotting dependencies to be installed.
Their shared path resolver also accepts an explicit ``artifact_dir`` argument in Python.
Relative overrides are interpreted against each process's working directory; prefer absolute paths.
Custom directories are not removed by ``ceedling clobber``.
Plot readers only consume files: they never invoke tests or create missing data, and report missing
CSV files with the command needed to generate them.

The PMSM test-result plot directives remain disabled in :ref:`uz_pmsm_swmodel`.
Ordinary docs builds and their CI job do not require these artifacts.
Before enabling the plots, explicitly order successful test execution before the docs build and
pass artifacts from the same revision to the plotting step; do not rely on leftover files or parallel CI steps.

This separation applies to the new PMSM exports. Older PRNG tests still write CSVs directly into
``docs/source/software/library/uz_prng/``; migrating those legacy documentation examples is separate work.

Video
*****

This video shows how to install Python, the requirements, and build the documentation.
Please note that the installation steps for ``sphinxcontrib.tikz`` (i.e., Ghostscript and LaTeX) are not shown in the video since the installation steps depend on your OS.
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
* Mix interface with rationale
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

.. note::

   Spaces are recommended for indentation, but tabs may also be used.
   For tabs, refer to :ref:`notepad`.

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

Reference:

.. code-block:: rst

    Reference ::numref:`labelName`.


Math
^^^^

- `See sphinx documentation regarding math <https://sphinx-rtd-trial.readthedocs.io/en/latest/ext/math.html>`_
- Equations can be inline with ``:math:`i_1=\sqrt{i_d^2 +i_q^2}``` to render :math:`i_1=\sqrt{i_d^2 +i_q^2}` using Latex syntax
- Equations can also be in a dedicated blocks

.. code-block::

  .. math::

    i_1=\sqrt{i_d^2 +i_q^2}

.. math::

  i_1=\sqrt{i_d^2 +i_q^2}

- Numbering and referencing equations using the Sphinx built-in reference system

.. code-block::

  .. math:: 
   :label: eq_example_number

    i_1=\sqrt{i_d^2 +i_q^2}

.. math:: 
    :label: eq_example_number

      i_1=\sqrt{i_d^2 +i_q^2}

- This text references :eq:`eq_example_number` by using ``:eq:`eq_example_number```
- The built-in sphinx numbering can not label multiple equations, e.g., in align environments
- Alternative according to https://www.mail-archive.com/sphinx-users@googlegroups.com/msg04040.html

.. code-block::

    .. math::
        :nowrap:

        \begin{align}
                    i_1 &=\sqrt{i_d^2 +i_q^2} \label{eq_example_1} \\ 
                    i_1 &=\sqrt{i_d^2 +i_q^2} \label{eq_example_2}
        \end{align}

    - :math:`\eqref{eq_example_1}` and :math:`\eqref{eq_example_2}` are the same equations

.. math::
    :nowrap:

    \begin{align}
                i_1 &=\sqrt{i_d^2 +i_q^2} \label{eq_example_1} \\ 
                i_1 &=\sqrt{i_d^2 +i_q^2} \label{eq_example_2}
    \end{align}

- :math:`\eqref{eq_example_1}` and :math:`\eqref{eq_example_2}` are the same equations



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

`sphinxcontrib.youtube <https://github.com/divi255/sphinxcontrib.youtube>`_
 Simple embedding of youtube videos.

`six <https://github.com/benjaminp/six>`_
 Provides compatibility between Python 2 and 3, required by some packages.

`sphinx-autobuild <https://github.com/executablebooks/sphinx-autobuild>`_
 Enable autobuild and reload after changes for local development with ``make livehtml``
 
`sphinx-issues <https://github.com/sloria/sphinx-issues>`_
 Link to issues and pull requests with ``:issue:`51``` and ``:pr:`5```, e.g., issue :issue:`5``
 

`sphinx-copybutton <https://github.com/executablebooks/sphinx-copybutton>`_
  Adds a button to the code blocks that copies the content of the block.
 
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

Alternative to using the Tikz extension for complicated tikz pictures: Create a standalone .tex document with the following boiler plate in an folder called ``img`` next the the .rst that includes the picture.
Navigate the the folder of the .tex file using the terminal of the remote container and call ``pdflatex -shell-escape FILE.tex``.
This generates a .svg from the .tex file that can be included as a regular figure.
Add the .tex **and** the .svg to git since this is currently a manual process.

.. code-block: tex

   \documentclass[crop,tikz,convert={outext=.svg,command=\unexpanded{pdf2svg \infile\space\outfile}},multi=false]{standalone}[2012/04/13]
   \usepackage{tikz}
   \usepackage{pgfplots}
   \begin{document}
   \begin{tikzpicture}[]
   
   \end{tikzpicture}
   \end{document}

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

Generates the following output in the docs:

.. figure:: img/doxygen_sample_output.png
   :scale: 70
   :align: center

   Example output of Breathe.

Examples in docs:
 - :ref:`HAL`
 - :ref:`AXI_testIP`

.. tip:: Note that all types that are used in the function arguments have to be documented, e.g., typedefed variables (see :ref:`AXI_testIP`).

Cards
=====

.. grid:: 2

    .. grid-item-card:: Hardware
        :link: hardware
        :link-type: ref


    .. grid-item-card:: Software
        :link: software_framework
        :link-type: ref

Known Issues
============

.. _notepad:

Compatibility issue with Notepad++ and .rst files 
*************************************************

.. warning::

   This is not recommended!
   Use the :ref:`vscode_remote_container` instead!

* If u edit ``.rst`` files in the UltraZohm documentation, an issue whilst using the tabulator key in Notepad++ can occur.

  - If you align the command with the tabulator key in Notepad++, everything looks as its supposed to.

  .. image:: ./img/Notepad_tabulator.png

  - However, if you open the saved file with the tabulator alignment in the normal windows editor, the following is visible.

  .. image:: ./img/Editor_tabulator.png

  - This wrong alignment via Notepad++ leads to the following error whilst executing **make html**.
    You can see the misalignment highlighted in green.

  .. image:: ./img/CMD_tabulator.png
  
  

* To fix this issue, you can do the following:

  1. In Notepad++ go to **Settings** → **Settings** → **Language**
  2. On the right sight, check the box **Replace by space** (Durch Leerzeichen ersetzen) and set the **Tab size** to i.e. 4. 
     4 spaces is the standard indentation size for different levels. 

  .. image:: ./img/Notepad_fix.png
  
