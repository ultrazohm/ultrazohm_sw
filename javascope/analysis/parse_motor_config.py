"""
Parser for motor_config.h — extract the active MOTOR_* #define values.

Usage (as a library):
    from parse_motor_config import load_motor_config
    cfg = load_motor_config('path/to/motor_config.h')
    print(cfg['Rs_Ohm'], cfg['Lm_H'])

Usage (standalone — prints parsed values):
    python parse_motor_config.py [motor_config.h]

The parser:
  1. Resolves MOTOR_CONFIG_SELECT to an integer via the named constants.
  2. Finds the matching #if block.
  3. Extracts all #define MOTOR_* within that block.
  4. Returns a dict keyed by the short name (Rs_Ohm, Rr_Ohm, Lm_H, …).

Derived quantities added automatically:
  Ls_H, Lr_H, sigma, sigma_Ls_H, tau_r_s

If motor_config.h path is not provided, the function searches upward from the
script location for the canonical path:
    vitis/software/Baremetal/src/include/motor_config.h
"""

import os
import re
import sys

# ---- default search path (relative to this script) -------------------------
_SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
_CANONICAL_REL = os.path.join('..', '..', 'vitis', 'software',
                               'Baremetal', 'src', 'include', 'motor_config.h')
_DEFAULT_PATH = os.path.normpath(os.path.join(_SCRIPT_DIR, _CANONICAL_REL))


def _find_motor_config():
    """Return the default motor_config.h path, raising FileNotFoundError if absent."""
    if os.path.isfile(_DEFAULT_PATH):
        return _DEFAULT_PATH
    raise FileNotFoundError(
        f"motor_config.h not found at default location:\n  {_DEFAULT_PATH}\n"
        "Pass the path explicitly with --motor-config <path>.")


# ---- line-level helpers -----------------------------------------------------

_DEFINE_RE = re.compile(r'^\s*#define\s+(\w+)\s+(.+)')


def _strip_comments(s):
    """Strip /* ... */ and // ... from a C token string."""
    # Block comment
    s = re.sub(r'/\*.*?\*/', '', s, flags=re.DOTALL)
    # Line comment
    s = re.sub(r'//.*', '', s)
    return s.strip()


def _parse_float(s):
    """Parse a C float literal like '2.1f', '8.5e-3f', '1.0e-5f'."""
    s = _strip_comments(s).rstrip('f').rstrip('F').rstrip('u').rstrip('U').strip('()')
    return float(s)


def _parse_int(s):
    s = _strip_comments(s).rstrip('u').rstrip('U')
    return int(s, 0)


# ---- main parser ------------------------------------------------------------

def load_motor_config(path=None):
    """
    Parse motor_config.h and return a dict of the active machine's parameters.

    Keys (always present):
        Rs_Ohm, Rr_Ohm, Lm_H, Lsigma_s_H, Lsigma_r_H, PolePairs,
        J_kgm2, Psi_rated_Vs, I_max_A,
        Vdc_max_V, Iphase_max_A, Speed_max_rpm,
        Current_Kp_scale, Current_Ki_scale,
        Speed_Kp, Speed_Ki, Resonant_gain_scale,
        KF_Q_i, KF_Q_psi, KF_R_i

    Derived keys (added automatically):
        Ls_H, Lr_H, sigma, sigma_Ls_H, tau_r_s
    """
    if path is None:
        path = _find_motor_config()

    with open(path, encoding='utf-8') as f:
        lines = f.readlines()

    # --- Pass 1: collect all top-level #define values (outside any #if) ------
    # We do a simple forward scan; we stop paying attention once we're inside
    # a #if block and restart when we hit #endif at depth 0.
    top_defines = {}   # name → raw value string
    depth = 0
    for line in lines:
        stripped = line.strip()
        if stripped.startswith('#if') or stripped.startswith('#ifdef') or stripped.startswith('#ifndef'):
            depth += 1
            continue
        if stripped.startswith('#endif'):
            depth -= 1
            continue
        if depth == 0:
            m = _DEFINE_RE.match(line)
            if m:
                top_defines[m.group(1)] = m.group(2).strip()

    # --- Resolve MOTOR_CONFIG_SELECT → integer --------------------------------
    sel_raw = top_defines.get('MOTOR_CONFIG_SELECT', '')
    # It may be a numeric literal or a name like MOTOR_CONFIG_LINDNER_3KW
    if sel_raw in top_defines:
        sel_value = _parse_int(top_defines[sel_raw])
    else:
        try:
            sel_value = _parse_int(sel_raw)
        except ValueError:
            raise ValueError(
                f"Cannot resolve MOTOR_CONFIG_SELECT = '{sel_raw}' in {path}")

    # Find which MOTOR_CONFIG_<NAME> matches sel_value
    active_name = None
    for k, v in top_defines.items():
        if k.startswith('MOTOR_CONFIG_') and k != 'MOTOR_CONFIG_SELECT':
            try:
                if _parse_int(v) == sel_value:
                    active_name = k
                    break
            except (ValueError, TypeError):
                pass

    if active_name is None:
        raise ValueError(
            f"No MOTOR_CONFIG_<NAME> constant equals {sel_value} in {path}")

    # --- Pass 2: find the matching #if block and extract its #defines ---------
    # Supports both:
    #   #if (MOTOR_CONFIG_SELECT == MOTOR_CONFIG_LINDNER_3KW)
    #   #if MOTOR_CONFIG_SELECT == MOTOR_CONFIG_LINDNER_3KW
    block_defines = {}
    in_block = False
    block_depth = 0
    for line in lines:
        stripped = line.strip()
        if not in_block:
            # Check if this is the opening line of our target block
            if stripped.startswith('#if') and active_name in stripped and 'MOTOR_CONFIG_SELECT' in stripped:
                in_block = True
                block_depth = 1
                continue
        else:
            if stripped.startswith('#if') or stripped.startswith('#ifdef') or stripped.startswith('#ifndef'):
                block_depth += 1
                continue
            if stripped.startswith('#endif'):
                block_depth -= 1
                if block_depth == 0:
                    break
                continue
            if block_depth == 1:
                m = _DEFINE_RE.match(line)
                if m:
                    block_defines[m.group(1)] = m.group(2).strip()

    if not block_defines:
        raise ValueError(
            f"Could not find #if block for {active_name} in {path}")

    # --- Extract and type-convert the MOTOR_* parameters ---------------------
    def _get(suffix, converter=_parse_float, default=None):
        key = f'MOTOR_{suffix}'
        if key not in block_defines:
            if default is not None:
                return default
            raise KeyError(f"{key} not found in active block of {path}")
        return converter(block_defines[key])

    cfg = {
        'Rs_Ohm':            _get('Rs_Ohm'),
        'Rr_Ohm':            _get('Rr_Ohm'),
        'Lm_H':              _get('Lm_H'),
        'Lsigma_s_H':        _get('Lsigma_s_H'),
        'Lsigma_r_H':        _get('Lsigma_r_H', default=_get('Lsigma_s_H')),
        'PolePairs':         _get('PolePairs'),
        'J_kgm2':            _get('J_kgm2'),
        'Psi_rated_Vs':      _get('Psi_rated_Vs'),
        'I_max_A':           _get('I_max_A'),
        'Vdc_max_V':         _get('Vdc_max_V'),
        'Iphase_max_A':      _get('Iphase_max_A'),
        'Speed_max_rpm':     _get('Speed_max_rpm'),
        'Current_Kp_scale':  _get('Current_Kp_scale'),
        'Current_Ki_scale':  _get('Current_Ki_scale'),
        'Speed_Kp':          _get('Speed_Kp'),
        'Speed_Ki':          _get('Speed_Ki'),
        'Resonant_gain_scale': _get('Resonant_gain_scale'),
        'KF_Q_i':            _get('KF_Q_i'),
        'KF_Q_psi':          _get('KF_Q_psi'),
        'KF_R_i':            _get('KF_R_i'),
        '_active_config':    active_name,
        '_source':           os.path.abspath(path),
    }

    # --- Derived quantities --------------------------------------------------
    ls = cfg['Lm_H'] + cfg['Lsigma_s_H']
    lr = cfg['Lm_H'] + cfg['Lsigma_r_H']
    sig = 1.0 - cfg['Lm_H']**2 / (ls * lr)
    cfg['Ls_H']       = ls
    cfg['Lr_H']       = lr
    cfg['sigma']      = sig
    cfg['sigma_Ls_H'] = sig * ls
    cfg['tau_r_s']    = lr / cfg['Rr_Ohm']

    return cfg


# ---- CLI --------------------------------------------------------------------

def main():
    path = sys.argv[1] if len(sys.argv) > 1 else None
    try:
        cfg = load_motor_config(path)
    except (FileNotFoundError, ValueError, KeyError) as e:
        print(f"ERROR: {e}", file=sys.stderr)
        sys.exit(1)

    print(f"Source: {cfg['_source']}")
    print(f"Active config: {cfg['_active_config']}\n")
    skip = {'_active_config', '_source'}
    for k, v in cfg.items():
        if k in skip:
            continue
        if isinstance(v, float):
            print(f"  {k:25s} = {v:.6g}")
        else:
            print(f"  {k:25s} = {v}")


if __name__ == '__main__':
    main()
