.. _uz_dataviewer_plugins:

============
Node plugins
============

The Nodes canvas can be extended with your own **transform nodes** — a plain Python file that turns input signals into an output signal.
Once installed, your node kind works exactly like a builtin: a toolbar button, param widgets, evaluation, scripting (``node_*``), and save/restore.
Plugins are entirely optional; with none installed the app runs unchanged.

For how to use nodes in the GUI see :ref:`uz_dataviewer_nodes`; for the engine internals see :ref:`the node graph section <uz_dataviewer_node_graph>`.

Where plugins live
==================

The viewer scans these locations in order, and only if they exist:

#. **``UZ_DATAVIEWER_PLUGINS``** — one or more directories (``os.pathsep``-separated: ``:`` on Linux/macOS, ``;`` on Windows). Point this at your plugin folder.
#. **``~/.uz_dataviewer/nodes/``** — the default user plugin folder.

.. code-block:: bash

   export UZ_DATAVIEWER_PLUGINS=/path/to/my/plugins
   python run.py

You can also load a folder at runtime from the console (no restart):

.. code-block:: text

   load_plugins("/path/to/my/plugins")     # or load_plugins() for the configured dirs

A missing folder or file is silently skipped; a plugin that throws on import is logged to the console and skipped — it never blocks startup.

The contract
============

A plugin file registers one or more transforms with the ``@transform`` decorator.
The function takes ``inputs`` (a list of ``(time, y)`` NumPy arrays, one per connected input) and the node's ``params`` (a ``dict[str, str]``), and returns ``(out_time, out_y, info)``:

.. code-block:: python

   import numpy as np
   from uz_dataviewer.plugins import transform, ParamSpec

   @transform(
       "movavg",                       # the node kind (unique; the toolbar button label)
       params={"width": "51"},         # default params (values are strings)
       inputs=(1, 1),                  # (min, max) number of inputs
       ui=[ParamSpec.int("width", "window (samples)")],   # widgets the canvas draws
   )
   def moving_average(inputs, params):
       time, y = inputs[0]
       width = max(1, int(float(params.get("width", 51))))
       out = np.convolve(np.asarray(y, float), np.ones(width) / width, mode="same")
       return time, out, f"moving avg, {width} samples"   # info shows under the node

That is the whole API. A working copy is in ``examples/plugins/moving_average.py``.

``@transform(...)`` arguments
-----------------------------

.. list-table::
   :header-rows: 1
   :widths: 25 75

   * - arg
     - meaning
   * - ``kind`` (1st, positional)
     - unique node-kind id; must not be ``source`` or clash with a builtin (``fft``/``math``/``filter``/``shift``)
   * - ``params``
     - default parameters as a ``{str: str}`` dict
   * - ``inputs``
     - ``(min, max)`` input arity — e.g. ``(1, 1)`` one input, ``(2, 2)`` two, ``(1, 2)`` one-or-two
   * - ``ui``
     - list of ``ParamSpec`` describing the editable params (see below)
   * - ``unit``
     - optional unit string for the derived signal (default ``""``)

``ParamSpec`` widgets
---------------------

``ParamSpec.float(key, label)``, ``.int(key, label)``, ``.bool(key, label)``, ``.enum(key, options, label)``, ``.str(key, label)``.
Each renders a widget that writes back to ``params[key]``; read it in your function with ``params.get(key, default)``.
``params`` values are always strings — coerce with ``float()`` / ``int()``.

Rules & tips
============

- **Output an ``(out_time, out_y, info)`` tuple.** ``out_time`` is the x-axis of the derived signal (for a spectrum-like node it can be frequency).
  Raise a normal exception with a clear message on bad input — it's caught, shown on the node, and the rest of the graph keeps working.
- The result is materialized as a **derived run** named after the node, so it appears in Navigation and is draggable into plots / FFT / Histogram.
- Keep transforms **pure NumPy** if you want them to also work in the web build. 
  Native plugins can import anything that's installed.
- **Scripting & sessions:** a graph stores only the node *kind* and its params, never your code, so ``.uzscript``/JSON round-trip unchanged.
  Opening a session whose plugin isn't installed keeps the node as a greyed **"missing plugin"** placeholder (params + links preserved); install the plugin and re-evaluate to restore it.

Security
========

A plugin is code you deliberately installed (same trust level as ``pip install``).
A saved **session never contains code** — only kind names and params — so opening someone else's graph stays data-only.
To run without any plugins, just leave the folders empty / ``UZ_DATAVIEWER_PLUGINS`` unset.
