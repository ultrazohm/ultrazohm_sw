.. _uz_dataviewer_plugins:

============
Node plugins
============

The Nodes canvas can be extended with nodes that apply a user-defined transformation.
To this end, a Python file is required that turns input signals into an output signal.
Once installed, your node kind works like a builtin node with a toolbar button, param widgets, evaluation, scripting (``node_*``), and save/restore.
Plugins are optional, when no plugin is installed, the app runs unchanged.
For how to use nodes in the GUI see :ref:`uz_dataviewer_nodes`.

Plugins location
================

``uz_dataviewer`` scans these locations in order, and only if they exist:

#. ``UZ_DATAVIEWER_PLUGINS``: one or more directories (``os.pathsep``-separated: ``:`` on Linux/macOS, ``;`` on Windows). Point this at your plugin folder.
#. ``~/.uz_dataviewer/nodes/``: the default user plugin folder.

.. code-block:: bash

   export UZ_DATAVIEWER_PLUGINS=/path/to/my/plugins
   python run.py

You can also load new node kinds at runtime from the console:

.. code-block:: text

   load_plugins("/path/to/my/plugins")     # or load_plugins() for the configured dirs

A missing folder or file is silently skipped.
A plugin that throws an error on import is logged to the console and skipped;
its registrations and module entry are rolled back.
Node kinds cannot replace an existing plugin or builtin registration. Restart the
viewer to load changes to an already registered kind. This keeps cached node
outputs consistent with the implementation that produced them.

Plugin structure
================

A plugin file registers one or more transforms with the ``@transform`` decorator.
The function takes ``inputs`` (a list of ``(time, y)`` NumPy arrays (one per connected input) as well as the node's ``params`` (a ``dict[str, str]``) and returns ``(out_time, out_y, info)``.

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
       start = (width - 1) // 2
       out = np.convolve(np.asarray(y, float), np.ones(width) / width, mode="full")[start:start + len(y)] if len(y) else np.empty(0)
       return time, out, f"moving avg, {width} samples"   # info shows under the node

A working example is located at ``ultrazohm_sw/uz_dataviewer/examples/plugins/moving_average.py``.

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

- Output an ``(out_time, out_y, info)`` tuple. ``out_time`` is the independent axis of the derived signal and must preserve the input domain. Only the built-in FFT changes a time axis to frequency.
  Raise a normal exception with a clear message on bad input — it's caught, shown on the node, and the rest of the graph keeps working.
- The result is materialized as a **derived run** named after the node, so it appears in Navigation and is draggable into plots / FFT / Histogram.
- Keep transforms **pure NumPy** if you want them to also work in the web build. 
  Native plugins can import anything that's installed.
- Scripting & sessions: a graph stores only the node *kind* and its params, never your code, so ``.uzscript``/JSON round-trip unchanged.
  Opening a session whose plugin isn't installed keeps the node as a greyed **"missing plugin"** placeholder (params + links preserved); install the plugin and re-evaluate to restore it.

Transform ownership
-------------------

Plugin API version 2 makes inputs read-only array views. Allocate a separate working array before
mutating samples. Returned arrays are validated, converted to float64 axes and
float32 values, and copied into owned output buffers before publication. Invalid
outputs fail only their node; independent graph branches continue evaluating.
Plugins preserve the independent-axis domain of their inputs.
Registration validates lowercase kind identifiers, callable implementations,
input arity (0–1,024), unique parameter keys, declared widget types, nonempty
unique enum choices, and typed defaults. Invalid declarations roll back the
plugin import. Input arrays must be one-dimensional and paired with equal-length
axes; output diagnostic text must be a string.
