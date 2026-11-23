.. _uz_dataviewer_library:

===============
Python library
===============

The data/analysis core runs without a window, i.e., headless.
The library can load logs, compute FFTs, and run the node transforms from a Python script through the facade in ``uz_dataviewer.api``, which is re-exported at the package top level.

.. note::

   **Importing the package does not import the imgui GUI stack.**
   ``import uz_dataviewer`` (and ``uz_dataviewer.api`` / ``.analysis`` / ``.nodes``) only requires numpy/pandas/pyarrow.
   The GUI (``DataViewerApp`` / ``main``) is loaded lazily, only when you actually access it.
   The core is therefore usable on a headless server and ``import`` stays fast.

Quick start
===========

.. code-block:: python

   import uz_dataviewer as uz

   data = uz.read("Log.csv")              # -> Dataset (shared time axis + named signals)
   t, ia = data.time, data["ia"]

   df = data.to_dataframe()               # pandas: column 'time' + one per signal

   spec = uz.fft(t, ia)                   # -> FftResult (.freqs, .mag, .info, .ok); full span
   sdf  = uz.fft_frame(t, ia)             # -> pandas DataFrame [frequency, amplitude]

   # Node transforms — the exact calculations the GUI's node graph uses.
   print(uz.kinds())                      # ('fft', 'math', 'filter', 'shift')
   t2, y2, info = uz.node("filter", (t, ia), type="low", cutoff=40, taps=201)

A runnable version is in ``examples/headless_example.py``.

API reference
=============

The facade adds no compute logic of its own.
The facade reuses the loader, FFT and node transforms used by the GUI.
Thus, the results of library usage matches the results of the GUI.


.. autoclass:: uz_dataviewer.api.Dataset
   :members:

.. autoclass:: uz_dataviewer.analysis.FftResult
   :members:
   :no-index:

.. autofunction:: uz_dataviewer.api.read
.. autofunction:: uz_dataviewer.api.fft
.. autofunction:: uz_dataviewer.api.fft_frame
.. autofunction:: uz_dataviewer.api.node
.. autofunction:: uz_dataviewer.api.filter
.. autofunction:: uz_dataviewer.api.math
.. autofunction:: uz_dataviewer.api.kinds
.. autofunction:: uz_dataviewer.api.load_plugins

