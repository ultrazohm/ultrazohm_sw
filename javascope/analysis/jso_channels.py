"""
Parser for the JS_OberservableData enum in javascope.h.

Provides:
  parse_jso_enum(path)        -> {signal_name: jso_number}
  ini_preset(names, jso_map)  -> 'n ; n ; n ...' string for properties.ini

Signal names are derived by stripping the 'JSO_' prefix from enum member names,
which matches exactly the names the JavaScope GUI writes into CSV headers.

Usage (standalone — prints the current enum):
  python jso_channels.py [path/to/javascope.h]
"""

import os
import re
import sys

# ---- default path -----------------------------------------------------------
_SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
_CANONICAL_REL = os.path.join('..', '..', 'vitis', 'software',
                               'Baremetal', 'src', 'include', 'javascope.h')
_DEFAULT_PATH = os.path.normpath(os.path.join(_SCRIPT_DIR, _CANONICAL_REL))


def parse_jso_enum(path=None):
    """
    Parse the JS_OberservableData enum from javascope.h.

    Returns
    -------
    dict mapping signal_name -> jso_number
        Excludes ZEROVALUE and ENDMARKER entries.

    The signal_name is the enum member name with the 'JSO_' prefix stripped.
    It matches the name that appears in JavaScope CSV headers:
        'CH4=12)id'  ->  signal_name 'id'  (JSO_id = 12)
    """
    if path is None:
        path = _DEFAULT_PATH
    if not os.path.isfile(path):
        raise FileNotFoundError(
            f"javascope.h not found at:\n  {path}\n"
            "Pass the path explicitly.")

    with open(path, encoding='utf-8') as f:
        text = f.read()

    # Extract the enum body between 'enum JS_OberservableData {' and '};'
    m = re.search(r'enum\s+JS_OberservableData\s*\{(.+?)\}', text, re.DOTALL)
    if not m:
        raise ValueError(f"enum JS_OberservableData not found in {path}")

    body = m.group(1)

    # Parse members: name [= value] , (ignoring comments)
    # Remove // comments first
    body_no_comments = re.sub(r'//[^\n]*', '', body)
    members_raw = re.findall(r'(\w+)\s*(?:=\s*[\w]+\s*)?,?', body_no_comments)

    # Assign sequential numbers starting from 0 (matching C enum semantics)
    # All members use the default auto-increment here (no member has explicit non-zero value
    # except ZEROVALUE=0, which we handle by starting at 0).
    result = {}
    counter = 0
    for name in members_raw:
        if not name:
            continue
        if name in ('JSO_ZEROVALUE', 'JSO_ENDMARKER'):
            counter += 1
            continue
        if not name.startswith('JSO_'):
            counter += 1
            continue
        signal = name[4:]   # strip 'JSO_' prefix
        result[signal] = counter
        counter += 1

    return result


def ini_preset(signal_names, jso_map, n_channels=20):
    """
    Build a 'preSelectedChannelNumbers' value string for properties.ini.

    Parameters
    ----------
    signal_names : list[str]
        Ordered list of signal names for CH1..CHn.
        Names not found in jso_map are substituted with 0 (ZEROVALUE).
    jso_map : dict[str, int]
        Output of parse_jso_enum().
    n_channels : int
        Total channel count (pad with 0 if fewer names are given).

    Returns
    -------
    str  e.g. '8 ; 9 ; 10 ; 12 ; 13 ; 25 ; ...'
    """
    nums = []
    for name in signal_names[:n_channels]:
        if name in jso_map:
            nums.append(jso_map[name])
        else:
            nums.append(0)   # ZEROVALUE / not assigned
    # Pad
    while len(nums) < n_channels:
        nums.append(0)
    return ' ; '.join(str(n) for n in nums)


def print_ini_section(label, signal_names, jso_map, n_channels=20):
    """Print a ready-to-paste properties.ini block for the given channel set."""
    print(f"\n# --- {label} ---")
    print(f"# Channels: {', '.join(signal_names)}")
    print(f"preSelectedChannelNumbers = {ini_preset(signal_names, jso_map, n_channels)}")
    visible = ['1'] * min(len(signal_names), n_channels) + \
              ['0'] * (n_channels - min(len(signal_names), n_channels))
    print(f"preSelectedChannelVisibility = {' ; '.join(visible[:n_channels])}")


# ---- CLI --------------------------------------------------------------------

def main():
    path = sys.argv[1] if len(sys.argv) > 1 else None
    try:
        jso = parse_jso_enum(path)
    except (FileNotFoundError, ValueError) as e:
        print(f"ERROR: {e}", file=sys.stderr)
        sys.exit(1)

    print(f"JS_OberservableData enum  ({path or _DEFAULT_PATH})\n")
    print(f"  {'JSO_number':>10}   signal_name")
    print(f"  " + "-" * 36)
    for name, num in sorted(jso.items(), key=lambda x: x[1]):
        print(f"  {num:>10}   {name}")

    print(f"\nTotal observable channels: {max(jso.values()) + 1}  (ENDMARKER = {max(jso.values()) + 1})")


if __name__ == '__main__':
    main()
