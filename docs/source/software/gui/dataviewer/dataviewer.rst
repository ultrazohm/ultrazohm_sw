.. _dataviewer:

===========
Data viewer
===========

The :ref:`JavaScope` is used to observe log data during operation of the UltraZohm.
In addition, log files can be created which can be further analyzed.

..  _dataviewer_log:

..  figure:: log.png
    :align: center
    :width: 500px

    Javascope logging the lifecheck signal.

Fig. :numref:`dataviewer_log` shows logging the lifecheck signal of the UltraZohm.
Two options are available to further analyze this log file:

   1. `Matlab Data Inspector`_
   2. `Python Data Viewer`_


Matlab Data Inspector
=====================

To open the log file, open Matlab and navigate to ``ultrazohm_sw/javascope``.
Make sure that this is the current working directory for Matlab.
Call the script ``JS_plot_data.m``.

..  _dataviewer_call_matlab:

..  figure:: matlab_js_plot_data.png
    :align: center
    :width: 500px

    Call ``JS_plot_data.m``.

The script opens the latest log that is present in ``ultrazohm_sw/javascope`` in the `Matlab Data Inspector <https://de.mathworks.com/help/simulink/slref/simulationdatainspector.html>`_.
The read data is also available in the Matlab workspace for further processing.

..  _dataviewer_matlab_dataviewer:

..  figure:: dataviewer_matlab.png
    :align: center
    :width: 500px

    Use the Matlab Data Inspector to analyze the data.

To load a specific log file, set the file name accordingly, like so:

.. code-block::

    file_name = Logfile_list(logfile_list_index).name
    paste file name here if you want to open a specific file
    file_name = 'Log_2024-03-11_99-99-99.csv';

Additional settings, such as converting the log file to ``.mat`` for further usage in Matlab can be set:

.. code-block::

   %% settings
   delete_empty_log_files = 0;
   save_all_logged_data = 0; 
   plot_all_channels = 0;
   rename_channels_manually = 0;
   import_data_to_simulink_datainspector = 1;
   overwrite_data_in_simulink_datainspector = 1;

Python Data Viewer
==================

.. note:: The Python Data Viewer works out of the box inside the :ref:`vscode_remote_container`. If the remote container is not used, the dependencies of ``ultrazohm_sw/docs`` are required on the system. 

The following steps start the python based data viewer:

1. Open a terminal and navigate to ``ultrazohm_sw/javascope``
2. Call the dataviewer like so

.. code-block:: python

    python dataviewer.py

..  _dataviewer_python_start:

..  figure:: dataviewer_python.png
    :align: center
    :width: 500px

    Start the python data viewer by calling ``dataviewer.py``. A dash server is started which can be open by typing the IP into the browser or clicking the pop op (right corner).

3. Open the web page of the data viewer
4. Upload the log file that you want to inspect. Note that the data is only *uploaded* to your local machine since the dash app runs on a local server. I.e., all data is only present on your hard drive.

..  _dataviewer_python_open:

..  figure:: dataviewer_python_open.png
    :align: center
    :width: 500px

    Data viewer after uploading log data. The figure dynamically rescales using `plotly resampler <https://github.com/predict-idlab/plotly-resampler>`_. Note that when viewing large timescales, aliasing might be present which is reduced if the x-axis is zoomed in.

5. Inspect the log file

Data format
-----------

The python based data viewer can read ``.csv`` and ``.parquet`` (which stores the logs more efficient, i.e., with less disc space).
Call ``convert_csv_to_parquet.py`` to convert all logs present in the directory to parquet data format, like so

.. code-block:: python

    python convert_csv_to_parquet.py
