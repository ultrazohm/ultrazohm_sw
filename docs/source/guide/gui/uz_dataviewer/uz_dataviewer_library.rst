.. _uz_dataviewer_library:

===============
Python library
===============

The data/analysis core runs without a window, i.e., headless.
The library can load logs, compute FFTs, and run the node transforms from a Python script through the facade in ``uz_dataviewer.api``, which is re-exported at the package top level.

.. note::

   **Importing the package does not import the imgui GUI stack.** ``import uz_dataviewer`` and ``from uz_dataviewer import Client`` use only the Python standard library.
   Accessing the analysis API loads its numerical dependencies.
   Reads, conversions, and analysis also avoid GUI imports.
   GUI entry points must be imported explicitly from ``uz_dataviewer.app``.
   The core is therefore usable on a headless server and ``import`` stays fast.

Controlling an open viewer
==========================

Use ``Client`` when a script should change the running application.
The viewer must already be open.
The default endpoint is ``127.0.0.1:19741``; override it with ``Client("127.0.0.1:19742")`` or ``UZ_DATAVIEWER_ENDPOINT``.
Each viewer instance must have its own endpoint.

.. code-block:: python

   from uz_dataviewer import Client

   with Client() as viewer:
       recording = viewer.load("Log.csv")
       viewer.set_grid(2, 1)
       viewer.add_signal(1, recording, "ia")
       viewer.save_session("analysis.json")

The script runs in its own Python process; the viewer owns the plot and session state.
GUI interactions and Python requests share that state.
Each client call waits for its result or raises an exception; several calls are not a transaction.
After an unrelated session replacement, create a new client and obtain new recording/node/view handles.
Do not reuse handles from the previous session.
See :doc:`uz_dataviewer_usage` for the full client API and Python editor workflow.

The viewer authenticates each request with a random per-instance credential.
Clients discover it automatically from a private per-user directory under the OS temporary directory.
For explicit connection management, ``Client`` also accepts a ``token=`` keyword argument.
Create a new client after restarting the viewer; credentials are never automatically refreshed to retry mutations.

Headless analysis quick start
=============================

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

