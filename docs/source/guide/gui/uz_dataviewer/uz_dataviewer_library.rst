.. _uz_dataviewer_library:

=======================================
Using uz_dataviewer as a Python library
=======================================

The data/analysis core runs **without a window**.
You can load logs, compute FFTs, and run the node transforms from a plain script or a notebook through the ergonomic facade in ``uz_dataviewer.api`` — re-exported at the package top level.

.. note::

   **Importing the package does not import the imgui GUI stack.**
   ``import uz_dataviewer`` (and ``uz_dataviewer.api`` / ``.analysis`` / ``.nodes``) needs only numpy/pandas/pyarrow.
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

The facade adds no compute logic of its own — it reuses the same loader, FFT and node transforms as the GUI, so results match what you see in the app.
For internals see :doc:`uz_dataviewer_architecture`.
