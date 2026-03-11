"""
Utility for loading UltraZohm JavaScope CSV logs.

Usage:
    from load_log import load_log
    data, fs = load_log("../Log_2026-03-05_11-06-56.csv")
    id_err = data['id'] - data['id_cmd']

The returned dict maps short signal names to numpy-like plain lists.
The channel-to-name mapping is detected automatically from the CSV header.
"""

import csv
import os
import sys
import math

# Alias table for cases where the firmware signal name differs from the analysis
# script's expected name.  Extend only when a rename is necessary.
_NAME_ALIASES = {
    "Theta_el":     "theta_el",
    "Speed_rpm":    "Speed_rpm",   # kept as-is; listed for clarity
}


def _parse_header(fieldnames):
    """Return dict mapping short_name -> column_key for the CSV fieldnames.

    Column format produced by the JavaScope GUI:
        "CH<n>=<jso_enum_number>)<signal_name>"
    e.g. "CH4=12)id"  or  "CH10=29)omega_s_rad_s"

    The signal name is read directly from the header so the loader is
    automatically compatible with any future JSO enum renumbering, as long
    as the signal names in the firmware stay the same.
    """
    col_map = {}
    for col in (fieldnames or []):
        if col == 'time':
            col_map['time'] = 'time'
            continue
        # Must contain "=" (CH<n>=<num>)<name>) and ")" (separator before name)
        if '=' not in col or ')' not in col:
            continue
        after_eq = col.split('=', 1)[1]          # "<num>)<name>"
        parts = after_eq.split(')', 1)
        if len(parts) < 2 or not parts[1]:
            continue
        name = parts[1].strip()                   # signal name from firmware
        name = _NAME_ALIASES.get(name, name)      # apply alias if needed
        col_map[name] = col
    return col_map


def _safe_float(v):
    try:
        return float(v.replace(',', '.'))
    except Exception:
        return None


def load_log(path):
    """
    Load a JavaScope CSV file.

    Returns
    -------
    data : dict[str, list[float]]
        Signal arrays keyed by short name (see _JSO_NAMES).
        Always contains 'time'.
    fs : float
        Estimated sample rate in Hz.
    """
    path = os.path.abspath(path)
    data_raw = {}
    col_map = {}

    with open(path, newline='', encoding='utf-8') as fh:
        reader = csv.DictReader(fh, delimiter=';')
        col_map = _parse_header(reader.fieldnames)
        for short in col_map:
            data_raw[short] = []

        for row in reader:
            for short, col in col_map.items():
                v = _safe_float(row.get(col, ''))
                if v is not None:
                    data_raw[short].append(v)

    # Trim all arrays to the shortest (handles partial trailing rows)
    n = min(len(v) for v in data_raw.values()) if data_raw else 0
    data = {k: v[:n] for k, v in data_raw.items()}

    t = data.get('time', [])
    fs = (n - 1) / (t[-1] - t[0]) if n > 1 and (t[-1] - t[0]) > 0 else 0.0

    return data, fs


# --------------------------------------------------------------------------- #
# Basic statistics helpers
# --------------------------------------------------------------------------- #

def mean(arr):
    return sum(arr) / len(arr)


def std(arr):
    mu = mean(arr)
    return math.sqrt(sum((x - mu) ** 2 for x in arr) / len(arr))


def rms(arr):
    return math.sqrt(sum(x ** 2 for x in arr) / len(arr))


def autocorr(arr, lag=1):
    n = len(arr)
    mu = mean(arr)
    c0 = sum((x - mu) ** 2 for x in arr) / n
    if c0 == 0:
        return 0.0
    cl = sum((arr[i] - mu) * (arr[i + lag] - mu) for i in range(n - lag)) / (n - lag)
    return cl / c0


def crosscorr(x, y, lag=0):
    n = len(x)
    mx, my = mean(x), mean(y)
    sx, sy = std(x), std(y)
    if sx * sy == 0 or n <= lag:
        return 0.0
    c = sum((x[i] - mx) * (y[i + lag] - my) for i in range(n - lag)) / (n - lag)
    return c / (sx * sy)


def dft_amp(arr, freq, fs):
    """Single-bin DFT amplitude (two-sided peak) at given frequency."""
    n = len(arr)
    mu = mean(arr)
    re = sum((arr[i] - mu) * math.cos(2 * math.pi * freq * i / fs) for i in range(n)) / n
    im = sum((arr[i] - mu) * math.sin(2 * math.pi * freq * i / fs) for i in range(n)) / n
    return 2 * math.sqrt(re ** 2 + im ** 2)


def stats_summary(arr):
    """Return (mean, std, min, max)."""
    return mean(arr), std(arr), min(arr), max(arr)


if __name__ == '__main__':
    path = sys.argv[1] if len(sys.argv) > 1 else None
    if path is None:
        print("Usage: python load_log.py <path_to_csv>")
        sys.exit(1)
    d, fs = load_log(path)
    print(f"Loaded: {os.path.basename(path)}")
    t = d.get('time', [])
    if len(t) < 2:
        print("  WARNING: empty or single-sample log")
    else:
        print(f"  {len(t)} samples,  {t[-1]-t[0]:.2f} s,  fs={fs:.0f} Hz")
    print(f"  Channels: {sorted(d.keys())}")
