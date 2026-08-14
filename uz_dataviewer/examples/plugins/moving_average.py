"""Sample node plugin: a moving-average smoother.

Drop this file (or this whole folder) where the viewer looks for plugins:

  * point ``UZ_DATAVIEWER_PLUGINS`` at this directory, or
  * copy it into ``~/.uz_dataviewer/nodes/``

then restart the viewer (or run ``load_plugins(<dir>)`` in the console). A new
``+ movavg`` button appears in the Nodes toolbar.
"""

import numpy as np

from uz_dataviewer.plugins import ParamSpec, transform


@transform(
    "movavg",
    params={"width": "51"},
    inputs=(1, 1),
    ui=[ParamSpec.int("width", "window (samples)")],
)
def moving_average(inputs, params):
    """Centered moving average over ``width`` samples (one input)."""
    time, y = inputs[0]
    width = max(1, int(float(params.get("width", 51))))
    kernel = np.ones(width) / width
    out = np.convolve(np.asarray(y, dtype=float), kernel, mode="same")
    return time, out, f"moving avg, {width} samples"
