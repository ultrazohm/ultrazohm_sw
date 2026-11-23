.. _ultrazohm_dataviewer:

====================
ultrazohm-dataviewer
====================

.. youtube:: JLRGM1H9AhQ


The UltraZohm Data Viewer plots live measurements and opens CSV and Parquet recordings.
It supports JavaScope CSV logs and recordings from :doc:`../ultrazohm_cli`.
Use Parquet for large recordings.
``ultrazohm_dataviewer`` is based on `ImGUI bundle <https://github.com/pthom/imgui_bundle>`_ (Python API), which in turn uses ImGui/ImPlot.
``ultrazohm_dataviewer`` is a desktop application for Windows and Linux.
Detailed guidelines for building are given in :doc:`ultrazohm_dataviewer_build`.

Features
--------

- Load :ref:`JavaScope` ``.csv`` (delimiter ``;`` *or* ``,`` is auto-detected) and ``.parquet`` log files
- Subplot grid, drag-and-drop signals, adjust layout at runtime, multiple plot types (line/scatter/stairs/*XY*), linked X axes, secondary Y axis, cursors, spy zoom inset, show samples, per-cell ``.csv`` export
- Range-aware downsampling — multi-GB logs pan smoothly and zooming reveals detail
- FFT & Histogram, optional locked time window to time plot, optional logarithmic axes, ``.csv`` export of FFT and histogram data
- Nodes for applying transforms (FFT / math / filter / shift) to signals where the result becomes a new signal. Nodes can be extended with custom Python code for user-specific nodes (:doc:`ultrazohm_dataviewer_plugins`)
- Python automation: control an open viewer through ``ultrazohm_dataviewer.Client`` from a terminal or the Python panel. Save and restore sessions as JSON.

Starting the Data Viewer
========================

The Python package and terminal command are named ``ultrazohm-dataviewer``.
Python scripts import ``ultrazohm_dataviewer``.
Installing the viewer also installs the matching ``ultrazohm-cli`` dependency.
The viewer requires Python 3.12 or later and a desktop display with OpenGL support.

.. tab-set::

    .. tab-item:: Python and uv (Linux and Windows)

       Run the published viewer directly:

       .. code-block:: bash

          uvx --python 3.12 ultrazohm-dataviewer
          uvx --python 3.12 ultrazohm-dataviewer gui measurement.csv

       For persistent commands, install both applications into a tool environment:

       .. code-block:: bash

          uv tool install --python 3.12 --with-executables-from ultrazohm-cli ultrazohm-dataviewer

       For Python scripts, use ``pip install ultrazohm-dataviewer`` in your project's virtual environment.
       Use ``--prerelease allow`` with uv to include development releases, or ``==VERSION`` to select a release.
       Linux uses published wheels; no Linux standalone archive is provided.

    .. tab-item:: Windows standalone ZIP

       Download ``ultrazohm-dataviewer-VERSION-windows-x86_64.zip`` from the GitHub release and extract the entire archive.
       Double-click ``ultrazohm-dataviewer.exe`` to open the GUI without a console.
       Python and uv are not required. Keep the ``_internal`` runtime directory beside the executable.
       The same ZIP includes ``ultrazohm-cli.exe`` for hardware control.
       From an existing PowerShell terminal, use the wrapper to wait for the viewer and retain the calling shell:

       .. code-block:: powershell

          .\ultrazohm-dataviewer.ps1
          .\ultrazohm-dataviewer.ps1 --help
          .\ultrazohm-dataviewer.ps1 status

    .. tab-item:: Git checkout

       From the repository root, run published applications or open a published-library shell:

       .. code-block:: bash

          ./uz dataviewer stable
          ./uz dataviewer prerelease
          ./uz install dataviewer prerelease
          ./uz venv prerelease

       Use ``.\uz.ps1`` on Windows. Channels default to stable.
       These commands use uv-managed environments, independently of the checkout's ``.venv``.
       Inside the activated shell, run ``ultrazohm-dataviewer``, ``ultrazohm-cli``, or Python scripts.
       Use ``exit`` to leave the shell.

       For local development, run ``./uz venv dev``, then ``ultrazohm-dataviewer``.
       On Windows, use ``.\uz.ps1 venv dev``.
       Every invocation builds the local CLI and installs the viewer editable into
       a fresh temporary environment; Rust and a C/C++ toolchain are required.
       Close applications before leaving the shell: its environment is deleted on exit.
       All shell modes include dependencies from root ``requirements.txt``.
       See :ref:`ultrazohm_dataviewer_build` for build and test tasks.


Quickstart
==========

..  _ultrazohm_dataviewer_layout:

..  figure:: ultrazohm_dataviewer_currents.png
    :align: center
    :width: 700px

    Layout of ``ultrazohm_dataviewer``.

:numref:`ultrazohm_dataviewer_layout` shows the Layout of ``ultrazohm_dataviewer`` with data navigation (1),  window control (2), plot setup (3), subplot setup (4), console (5), and settings (6).
The data navigation is used to open log files.
Log files can be opened by clicking the *Open file(s)...* button or by dragging and dropping files onto the navigation panel.
Individual signals of a log can be dragged and dropped into the plot area.
Right click on the log shows information and gives access to additional per-log settings, such as time normalization.
The window control (2) offers settings for the complete window, e.g., the plot, histogram, FFT, or nodes window.
Windows can be closed, floated, docked as tabs and are resizable.
On Windows and Linux X11 sessions, drag a panel tab outside the main window to detach it as a desktop window.
Drag it back to dock it again.
The window control (2) for the plot window gives access to, for example, the plot layout such as 1x1 or 2x1.
Settings of the window control (2) are global for the complete window.
The subplot setup (4) controls individual subplots and gives access to settings such as the plot type (line, scatter, stairs, XY), or secondary y-axis.
The Application log (5) is read-only and hidden by default.
Open it from **View → Application log**.
Use the Python panel or a terminal to automate the viewer.
The settings (6) give access to application settings, such import and export of current application state (session) and settings the view (view), e.g., reset to default view.

For all plots, the following interactions are available: Mouse wheel zooms in and out, right-click and drag creates a zoom rectangle, right-click while holding shift only zooms the x-axis, while holding Alt only zooms the y-axis.
Right-clicking the x-axis or y-axis gives access to additional settings.

Documentation
=============

.. toctree::
   :maxdepth: 1

   ultrazohm_dataviewer_build
   ultrazohm_dataviewer_analysis
   ultrazohm_dataviewer_live
   ultrazohm_dataviewer_workflows
   ultrazohm_dataviewer_usage
   ultrazohm_dataviewer_plugins
   ultrazohm_dataviewer_library
   ultrazohm_dataviewer_architecture
   ultrazohm_dataviewer_roadmap
