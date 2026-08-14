#!/usr/bin/env python3
"""Use uz_dataviewer headlessly, as a library -- no GUI window.

Loads a log, prints a DataFrame head, computes an FFT, and runs a low-pass filter
node, all through the ergonomic facade in :mod:`uz_dataviewer.api`.

    python examples/headless_example.py [path/to/log.csv]

(Defaults to a file under ``testdata/`` if no path is given.)
"""

from __future__ import annotations

import os
import sys

# Allow running from a source checkout without installing.
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "src"))

import numpy as np

import uz_dataviewer as uz


def main(path: str) -> None:
    # 1. Load -- returns a Dataset (shared time axis + named signal arrays).
    data = uz.read(path)
    print(data)
    print("signals:", data.names)
    print(data.to_dataframe().head())

    # 2. FFT of the first signal over the whole record (as a DataFrame).
    name = data.names[0]
    spectrum = uz.fft_frame(data.time, data[name])
    peak = spectrum.loc[spectrum["amplitude"].idxmax()]
    print(f"\nFFT of {name!r}: peak amplitude {peak['amplitude']:.4g} at {peak['frequency']:.2f} Hz")

    # 3. Run a node transform (same calculation the GUI's node graph uses).
    print("available node kinds:", uz.kinds())
    t_out, y_out, info = uz.node(
        "filter", (data.time, data[name]), type="low", cutoff=40.0, taps=201
    )
    print(f"filter node -> {info}; output std {np.std(y_out):.4g}")


if __name__ == "__main__":
    default = os.path.join(os.path.dirname(__file__), "..", "testdata", "9m_rows.csv")
    main(sys.argv[1] if len(sys.argv) > 1 else default)
