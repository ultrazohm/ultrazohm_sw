"""Offline JavaScope iq step analysis. Requires numpy and matplotlib.

Metrics use raw samples over the entire HOLD interval (not just the plot window).
Threshold crossings are linearly interpolated; settling is sample-resolved.
IAE uses trapezoidal integration from the step through the last HOLD sample.
"""
import argparse
from pathlib import Path
import re
import csv
import warnings

import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

# Select the log here when running without a command-line filename.
# Paths are relative to this script, independent of the working directory.
DEFAULT_LOG_FILE = Path(__file__).resolve().parent / "javascope/Log_2026-11-04_20-03-07.csv"

PLOT_START_MS, PLOT_END_MS = -2.0, 15.0
NOISE_WINDOW_MS = 20.0
FILTER_WINDOW_MS = 0.5
FILTER_TRANSIENT_GUARD_MS = 10.0
SETTLING_CONFIRM_MS = 2.0
COMPARISON_START_MS, COMPARISON_END_MS = -1.0, 10.0

EXPECTED_MEASUREMENTS = 5  # Diagnostic only; gains and reference levels come from data.
REQUIRED = ["time", "iq_ref_dut", "iq_dut", "experiment_active", "experiment_id",
            "iq_step_state", "iq_step_measurement_id", "iq_step_kp_active"]
OPTIONAL = ["vq_ref_dut", "dut_speed_rpm", "dut_violation", "experiment_sample",
            "experiment_status", "iq_step_reference"]


REPORT_SIGNALS = ["vd_ref_dut", "dut_v_dc_v"]  # Reporting only; not used for segmentation.

def warn(message):
    warnings.warn(message, UserWarning, stacklevel=2)


def load_log(path):
    with path.open(encoding="utf-8-sig", newline="") as stream:
        reader = csv.reader(stream, delimiter=";")
        header = next(reader, [])
        names = [re.sub(r"^CH\d+\s*=\s*\d+\)", "", c.strip(), flags=re.I).strip().lower()
                 for c in header]
        nonempty = [n for n in names if n]
        if len(nonempty) != len(set(nonempty)):
            raise ValueError("Duplicate semantic signal names in CSV header.")
        missing = sorted(set(REQUIRED) - set(names))
        if missing:
            raise ValueError("Missing required signals: " + ", ".join(missing))
        columns = {n: i for i, n in enumerate(names) if n in REQUIRED + OPTIONAL + REPORT_SIGNALS}
        rows = []
        for line, row in enumerate(reader, start=2):
            if not row:
                continue
            try:
                rows.append([float(row[i]) for i in columns.values()])
            except (ValueError, IndexError) as exc:
                raise ValueError(f"Invalid/missing numerical value on CSV line {line}.") from exc
    if len(rows) < 3:
        raise ValueError("At least three data rows are required.")
    values = np.asarray(rows)
    data = {name: values[:, i] for i, name in enumerate(columns)}
    t = data["time"]
    if len(t) < 3 or not np.isfinite(t).all() or not (np.diff(t) > 0).all():
        raise ValueError("Timestamps must be finite and strictly increasing (at least 3 samples).")
    metadata = [c for c in REQUIRED if c.startswith("experiment_") or c.startswith("iq_step_")]
    if not np.isfinite(np.column_stack([data[c] for c in metadata])).all():
        raise ValueError("Invalid numerical experiment metadata; cannot segment reliably.")
    for c in ["experiment_active", "experiment_id", "iq_step_state", "iq_step_measurement_id"]:
        if not np.equal(data[c], np.floor(data[c])).all():
            raise ValueError(f"Non-integer metadata in {c}.")
    return data


def detect_steps(data):
    selected = (data["experiment_active"] == 1) & (data["experiment_id"] == 1)
    ids = data["iq_step_measurement_id"]
    changes = np.r_[0, np.flatnonzero((np.diff(selected) != 0) | (np.diff(ids) != 0))+1, len(ids)]
    steps, seen = [], set()
    columns = REQUIRED + [c for c in OPTIONAL if c in data]
    for start, end in zip(changes[:-1], changes[1:]):
        if not selected[start]:
            continue
        block = {c: data[c][start:end] for c in columns}
        mid = int(ids[start])
        if mid in seen:
            raise ValueError(f"Measurement ID {mid} occurs in separate blocks/runs; analyze one sequence per CSV.")
        seen.add(mid)
        try:
            if mid < 1 or not np.isfinite(np.column_stack(list(block.values()))).all():
                raise ValueError("invalid ID or non-finite samples")
            kp = block["iq_step_kp_active"]
            if not np.allclose(kp, kp[0], rtol=1e-5, atol=1e-6) or kp[0] < 0:
                raise ValueError("gain is inconsistent or negative")
            phases = block["iq_step_state"]
            order = phases[np.r_[True, np.diff(phases) != 0]].tolist()
            if order not in ([1, 2, 3], [1, 2, 3, 4]):
                raise ValueError(f"incomplete/unexpected phase sequence {order}")
            baseline, hold, recovery = [{c: v[phases == phase] for c, v in block.items()} for phase in (1, 2, 3)]
            if len(baseline["time"]) < 2 or len(hold["time"]) < 3 or len(recovery["time"]) < 2:
                raise ValueError("too few baseline/HOLD/recovery samples")
            if end >= len(ids):
                raise ValueError("recording ends before measurement completion is observable")
            if order[-1] == 3 and data["iq_step_state"][end] not in (1, 5):
                raise ValueError("recovery did not finish normally")
            if "experiment_status" in block and not (block["experiment_status"] == 1).all():
                raise ValueError("non-RUNNING status during measurement")
            if "experiment_sample" in block and not (np.diff(block["experiment_sample"]) == 1).all():
                raise ValueError("experiment sample counter has gaps or resets")
            intervals = np.diff(block["time"])
            if np.max(intervals) > 1.5 * np.median(intervals):
                raise ValueError("timestamp gap inside measurement")
            initial, final = baseline["iq_ref_dut"][-1], hold["iq_ref_dut"][0]
            if final <= initial:
                raise ValueError("expected a positive reference step")
            for region, level in [(baseline, initial), (hold, final), (recovery, initial)]:
                if not np.allclose(region["iq_ref_dut"], level, rtol=1e-6, atol=1e-6):
                    raise ValueError("reference is not constant within its phase")
            edge = start + int(np.flatnonzero(phases == 2)[0])
            if data["iq_ref_dut"][edge] <= data["iq_ref_dut"][edge-1]:
                raise ValueError("no rising reference edge at HOLD entry")
            if "iq_step_reference" in block and not np.allclose(block["iq_ref_dut"], block["iq_step_reference"], atol=1e-5):
                warn(f"Measurement {mid}: controller reference differs from experiment request (possible limiting).")
            violation = bool((block["dut_violation"] != 0).any()) if "dut_violation" in block else None
            if violation:
                warn(f"Measurement {mid}: DUT VIOLATION ASSERTED; results are fault-affected.")
            steps.append(dict(id=mid, kp=float(kp[0]), initial=float(initial), final=float(final),
                              t0=float(data["time"][edge]), hold=hold, block=block, violation=violation))
        except ValueError as exc:
            warn(f"Measurement {mid} INVALID, skipped: {exc}.")
    missing = sorted(set(range(1, EXPECTED_MEASUREMENTS+1)) - seen)
    if missing:
        warn(f"Missing measurement IDs: {missing}.")
    if len(steps) != EXPECTED_MEASUREMENTS:
        warn(f"Found {len(steps)} valid complete steps; expected {EXPECTED_MEASUREMENTS}.")
    if not steps:
        raise ValueError("No valid complete step intervals found.")
    return sorted(steps, key=lambda s: s["id"])


def calculate_metrics(step):
    hold = step["hold"]
    t = hold["time"] - step["t0"]
    y = hold["iq_dut"]
    amplitude = step["final"] - step["initial"]

    def crossing(level):
        hits = np.flatnonzero(y >= level)
        if not len(hits):
            return np.nan
        k = hits[0]
        if k == 0:
            return np.nan  # Crossing occurred before the observed response window.
        return t[k-1] + (level-y[k-1]) / (y[k]-y[k-1]) * (t[k]-t[k-1])

    rise = crossing(step["initial"] + .9*amplitude) - crossing(step["initial"] + .1*amplitude)
    outside = np.flatnonzero(abs(y-step["final"]) > .02*amplitude)
    settled = not len(outside) or outside[-1] < len(y)-1
    settling = (t[outside[-1]+1] if len(outside) else 0.0) if settled else np.nan
    if not np.isfinite(rise):
        warn(f"Measurement {step['id']}: 10/90% crossing unavailable; rise time is NaN.")
    if not settled:
        warn(f"Measurement {step['id']}: did not settle during HOLD (valid poor response).")
    error = abs(hold["iq_ref_dut"]-y)
    # Explicit trapezoidal rule works with both older and newer NumPy versions.
    iae = np.sum(.5*(error[:-1]+error[1:])*np.diff(t))*1000
    return dict(measurement_id=step["id"], kp_v_per_a=step["kp"],
                initial_reference_a=step["initial"], final_reference_a=step["final"],
                step_amplitude_a=amplitude, step_time_s=step["t0"],
                rise_time_ms=rise*1000, peak_current_a=float(y.max()),
                overshoot_percent=max(0.0, (y.max()-step["final"])/amplitude*100),
                settling_time_ms=settling*1000, settled=settled, iae_a_ms=iae,
                mean_speed_rpm=float(hold["dut_speed_rpm"].mean()) if "dut_speed_rpm" in hold else np.nan,
                max_abs_vq_v=float(abs(hold["vq_ref_dut"]).max()) if "vq_ref_dut" in hold else np.nan,
                dut_violation=step["violation"], hold_samples=len(hold["time"]), evaluated_duration_ms=t[-1]*1000)


def plot_responses(steps, output_dir):
    with plt.rc_context({"font.size": 11, "axes.labelsize": 12, "legend.fontsize": 10,
                         "pdf.fonttype": 42, "ps.fonttype": 42}):
        fig, ax = plt.subplots(figsize=(8, 4.8), layout="constrained")
        for step in steps:
            block = step["block"]
            relative = (block["time"]-step["t0"])*1000
            # Stop at the end of HOLD; never draw the following falling step.
            keep = (relative >= PLOT_START_MS) & (relative <= PLOT_END_MS) & (block["iq_step_state"] <= 2)
            ax.plot(relative[keep], block["iq_dut"][keep], lw=1.5,
                    label=f"Kp = {step['kp']:g} V/A (ID {step['id']})")
        for level in sorted({s["final"] for s in steps}):
            ax.axhline(level, color="0.3", ls="--", lw=1, label=f"Reference = {level:g} A")
        ax.set(xlim=(PLOT_START_MS, PLOT_END_MS), xlabel="Time relative to reference step / ms",
               ylabel="q-axis current / A", title="DUT q-axis current step responses")
        ax.margins(y=.12)
        ax.grid(alpha=.2)
        ax.legend(loc="best", ncol=2)
        fig.savefig(output_dir / "step_responses.pdf")
        fig.savefig(output_dir / "step_responses.png", dpi=300)
        plt.close(fig)



def export_plot_data(steps, output_dir, start_ms=PLOT_START_MS, end_ms=PLOT_END_MS,
                     filename="step_plot_data.csv", column_names=None):
    """Plot-only resampling; never bridge acquisition gaps or phase boundaries."""
    periods = [np.median(np.diff(s["block"]["time"]))*1000 for s in steps]
    spacing = float(np.round(np.median(periods), 9))
    if spacing <= 0:
        raise ValueError("Cannot derive a positive plot sampling interval.")
    grid = np.arange(np.ceil(start_ms/spacing), np.floor(end_ms/spacing)+1)*spacing
    grid = np.round(grid, 9)  # Include an exact zero for the reference discontinuity.
    if not all(np.isclose(s["initial"], steps[0]["initial"]) and
               np.isclose(s["final"], steps[0]["final"]) for s in steps):
        raise ValueError("A shared reference column requires identical reference levels across steps.")
    stems = ["iq_kp_" + f"{s['kp']:g}".replace(".", "p").replace("-", "m").replace("+", "") for s in steps]
    names = [n + f"_id_{s['id']}" if stems.count(n)>1 else n for n, s in zip(stems, steps)]
    if column_names is not None:
        names = column_names
    curves = []
    for step in steps:
        block = step["block"]
        use = block["iq_step_state"] <= 2
        t = np.round((block["time"][use]-step["t0"])*1000, 9)
        y, phase = block["iq_dut"][use], block["iq_step_state"][use]
        gaps = np.diff(t) > 1.5*np.median(np.diff(t))
        if "experiment_sample" in block:
            gaps |= np.diff(block["experiment_sample"][use]) != 1
        cuts = np.r_[0, np.flatnonzero(gaps | (np.diff(phase) != 0))+1, len(t)]
        curve = np.full(grid.shape, np.nan)
        for a, b in zip(cuts[:-1], cuts[1:]):
            inside = (grid >= t[a]) & (grid <= t[b-1])
            curve[inside] = np.interp(grid[inside], t[a:b], y[a:b])
        if np.isnan(curve).any():
            warn(f"Measurement {step['id']}: uncovered plot samples exported as nan.")
        curves.append(curve)
    # The reference is a level change, not a linearly interpolated ramp.
    reference = np.where(grid < 0, steps[0]["initial"], steps[0]["final"])
    reference[np.all(np.isnan(curves), axis=0)] = np.nan
    np.savetxt(output_dir / filename, np.column_stack([grid, *curves, reference]),
               delimiter=",", header=",".join(["time_ms", *names, "iq_ref"]), comments="", fmt="%.12g")
    return names, spacing


def report_voltage(steps, data, vdc):
    """HOLD-window command utilization; prefer measured DC link over --vdc."""
    if not all("vq_ref_dut" in step["hold"] for step in steps):
        return "Voltage-command data are unavailable; utilization is not evaluated."
    q = np.concatenate([step["hold"]["vq_ref_dut"] for step in steps])
    times = np.concatenate([step["hold"]["time"] for step in steps])
    indices = np.searchsorted(data["time"], times) if data is not None else None
    vector = data is not None and "vd_ref_dut" in data
    if vector and not np.isfinite(data["vd_ref_dut"][indices]).all():
        warn("Invalid d-axis voltage data; report uses q-axis utilization only.")
        vector = False
    magnitude = np.hypot(data["vd_ref_dut"][indices], q) if vector else abs(q)
    text = rf"Maximum recorded $|u_q^\star|$ during HOLD is {max(abs(q)):.2f}\,V. "
    if vector:
        text += rf"The maximum command-vector magnitude $\sqrt{{(u_d^\star)^2+(u_q^\star)^2}}$ is {max(magnitude):.2f}\,V. "
    recorded = data is not None and "dut_v_dc_v" in data
    if recorded:
        link = data["dut_v_dc_v"][indices]
        if not np.isfinite(link).all() or np.any(link <= 0):
            return text + "Recorded DC-link values are invalid; utilization is omitted."
        if np.ptp(link) <= max(.05, abs(np.mean(link))*.001):
            text += rf"Recorded DC-link voltage is approximately {np.mean(link):.2f}\,V. "
        else:
            text += rf"Recorded DC-link voltage ranges from {min(link):.2f} to {max(link):.2f}\,V. "
        text += r"Utilization uses the simultaneous recorded $U_{\mathrm{dc}}/\sqrt{3}$. "
    elif vdc is not None:
        link = vdc
        text += (rf"Using externally supplied $U_{{\mathrm{{dc}}}}={vdc:g}$\,V "
                 rf"(not recorded), the nominal linear-SVPWM bound is {vdc/np.sqrt(3):.2f}\,V. ")
    else:
        return text + "No DC-link voltage was recorded or supplied; utilization is not calculated."
    utilization = float(np.max(magnitude/(link/np.sqrt(3)))*100)
    if vector:
        text += rf"Maximum vector utilization is {utilization:.1f}\,\%. "
        text += ("The recorded command magnitude remains below this bound. " if utilization < 99.9 else
                 "The command magnitude reaches or exceeds this bound; limiting must be considered. ")
        text += "This compares voltage commands, not measured terminal voltage."
    else:
        text += (rf"Maximum q-axis utilization is {utilization:.1f}\,\%, an indicator only: "
                 "the SVPWM bound applies to the full vector, so this cannot establish unsaturated operation.")
    return text


def write_report(steps, metrics, names, spacing, source, output_dir, data=None, vdc=None):
    """Fill report markers without changing numerical analysis or exported CSVs."""
    def escape(text):
        specials = {"": r"\textbackslash{}", "_": r"\_", "%": r"\%", "&": r"\&",
                    "#": r"\#", "$": r"\$", "{": r"\{", "}": r"\}", "~": r"\textasciitilde{}", "^": r"\textasciicircum{}"}
        return "".join(specials.get(c, c) for c in str(text))

    first = steps[0]
    gains = ", ".join(f"{s['kp']:g}" for s in steps)
    setup = (rf"The recorded reference changes from {first['initial']:g} to {first['final']:g}\,A "
             rf"(amplitude {first['final']-first['initial']:g}\,A). "
             rf"The {len(steps)} evaluated gains are {gains}\,V/A. ")
    if all("dut_speed_rpm" in step["hold"] for step in steps):
        speeds = np.concatenate([step["hold"]["dut_speed_rpm"] for step in steps])
        lo, hi, mean = speeds.min(), speeds.max(), speeds.mean()
        tolerance = max(0.5, abs(mean)*0.001)  # rpm: 0.5 absolute or 0.1% relative.
        if hi-lo <= tolerance or f"{lo:.0f}" == f"{hi:.0f}":
            setup += rf"The recorded motor speed was approximately {mean:.0f}\,rpm. "
        else:
            setup += rf"The recorded motor speed ranged from {lo:.0f} to {hi:.0f}\,rpm. "
    dt = np.concatenate([np.diff(s["block"]["time"]) for s in steps])
    if np.allclose(dt, np.median(dt), rtol=.001, atol=1e-9):
        setup += rf"Timestamp spacing is {spacing:g}\,ms, corresponding to a logging rate of {1000/spacing:g}\,Hz."
    else:
        setup += "Logging intervals are nonuniform; no single logging rate is assigned."
    best_over = min(metrics, key=lambda m: m["overshoot_percent"])
    discussion = (rf"The smallest overshoot is {best_over['overshoot_percent']:.2f}\,\% "
                  rf"at $K_p={best_over['kp_v_per_a']:g}$\,V/A. ")
    for field, label, unit in [("settling_time_ms", "shortest settling time", "ms"),
                               ("iae_a_ms", "lowest IAE", r"A\,ms")]:
        valid = [m for m in metrics if np.isfinite(m[field])]
        if valid:
            best = min(valid, key=lambda m: m[field])
            discussion += rf"The {label} is {best[field]:.2f}\,{unit} at $K_p={best['kp_v_per_a']:g}$\,V/A. "
    rise = [m for m in metrics if np.isfinite(m["rise_time_ms"])]
    if rise:
        slow = max(rise, key=lambda m: m["rise_time_ms"])
        discussion += rf"The slowest rise occurs at $K_p={slow['kp_v_per_a']:g}$\,V/A ({slow['rise_time_ms']:.3f}\,ms). "
    nominal = next((m for m in metrics if np.isclose(m["kp_v_per_a"], 8.8)), None)
    higher = [m for m in metrics if m["kp_v_per_a"] > 8.81]
    if nominal and higher and all(m["rise_time_ms"] < nominal["rise_time_ms"] and
                                  m["overshoot_percent"] > nominal["overshoot_percent"] for m in higher):
        discussion += "Every tested gain above the nominal value reduces rise time but increases overshoot. "
    # A simple raw-sample ringing indicator, not frequency or causal identification.
    excursions = []
    for step in steps:
        y = step["hold"]["iq_dut"]
        amplitude = step["final"]-step["initial"]
        reached = np.flatnonzero(y >= step["initial"]+.9*amplitude)
        if len(reached):
            error = y[reached[0]:]-step["final"]
            signs = np.sign(error[abs(error) > .02*amplitude])
            excursions.append((int(np.count_nonzero(np.diff(signs))), step["kp"]))
    if excursions and max(excursions)[0] >= 2:
        count, kp = max(excursions)
        discussion += (rf"Alternating post-rise excursions beyond the $\pm2\%$ band indicate ringing; "
                       rf"the largest count is {count} side changes at $K_p={kp:g}$\,V/A. ")
    faults = [str(step["id"]) for step in steps if step["violation"]]
    if faults:
        discussion += r"\textbf{DUT violations affect IDs " + ", ".join(faults) + ".} "
    discussion += ("These trade-offs apply to the tested operating point, not a universal optimum. "
                   "Neither rise time nor the nominal 800 Hz design target establishes a measured closed-loop bandwidth. "
                   "The waveform alone does not identify the cause of ringing.")
    voltage = report_voltage(steps, data, vdc)
    colors = ["uzblue", "uzorange", "uzgreen", "uzred", "uzpurple"]
    plots = []
    for i, (s, name) in enumerate(zip(steps, names)):
        plots.append(r"\addplot[very thick,solid," + colors[i % len(colors)] +
                     r"] table[x=time_ms,y=" + name + r",col sep=comma]{step_plot_data.csv};" + "\n" +
                     rf"\addlegendentry{{$K_p={s['kp']:g}$\,V/A}}")
    template = Path(__file__).with_name("step_report.tex").read_text(encoding="utf-8")
    replacements = {"% GENERATED_SETUP": setup, "% GENERATED_PLOTS": "\n".join(plots),
                    "% GENERATED_DISCUSSION": discussion, "% GENERATED_VOLTAGE": voltage,
                    "% GENERATED_SOURCE": r"\texttt{" + escape(source.name) + "}",
                    "% GENERATED_AXIS": f"xmin={PLOT_START_MS:g}, xmax={PLOT_END_MS:g},"}
    for marker, value in replacements.items():
        template = template.replace(marker, value)
    (output_dir / "step_report.tex").write_text(template, encoding="utf-8")



def stationary_and_settling(step, raw):
    """Additional diagnostics only; original raw metrics are never replaced."""
    hold = step["hold"]
    t = (hold["time"]-step["t0"])*1000
    y, target = hold["iq_dut"], step["final"]
    dt = float(np.median(np.diff(t)))
    if t[-1]-t[0] < NOISE_WINDOW_MS:
        raise ValueError(f"ID {step['id']}: HOLD too short for stationary window.")
    tail = y[t > t[-1]-NOISE_WINDOW_MS+dt*.01]
    width = max(1, int(round(FILTER_WINDOW_MS/dt)))
    if width % 2 == 0:
        width += 1
    block = step["block"]
    use = block["iq_step_state"] <= 2  # Exclude falling reference/recovery.
    bt = (block["time"][use]-step["t0"])*1000
    by = block["iq_dut"][use]
    half = width//2
    filtered = np.convolve(by, np.ones(width)/width, mode="valid")
    ft = bt[half:len(bt)-half] if half else bt
    valid = ft >= 0
    ft, filtered = ft[valid], filtered[valid]
    band = .02*(target-step["initial"])
    outside = np.flatnonzero(abs(filtered-target)>band)
    candidate = ft[outside[-1]+1] if len(outside) and outside[-1]<len(ft)-1 else (0. if not len(outside) else np.nan)
    # Protect early ringing against moving-average attenuation.
    early_bad = np.flatnonzero((t <= FILTER_TRANSIENT_GUARD_MS) & (abs(y-target)>band))
    if np.isfinite(candidate) and len(early_bad):
        candidate = max(candidate, t[min(early_bad[-1]+1,len(t)-1)])
    if np.isfinite(candidate) and ft[-1]-candidate < SETTLING_CONFIRM_MS:
        candidate = np.nan
    raw_supported = bool(np.isfinite(raw["settling_time_ms"]) and
                         t[-1]-raw["settling_time_ms"] >= SETTLING_CONFIRM_MS)
    raw_peak = np.max(y[t<=FILTER_TRANSIENT_GUARD_MS])-target
    filtered_peak = np.max(filtered[ft<=FILTER_TRANSIENT_GUARD_MS])-target
    attenuation = 100*(1-filtered_peak/raw_peak) if raw_peak>band else np.nan
    result = dict(stationary_mean_a=float(np.mean(tail)), stationary_std_a=float(np.std(tail)),
                  stationary_rms_error_a=float(np.sqrt(np.mean((tail-target)**2))),
                  filtered_settling_time_ms=float(candidate), raw_settling_supported=raw_supported,
                  filter_samples=width, effective_filter_ms=width*dt, filtered_observation_end_ms=float(ft[-1]),
                  unguarded_peak_attenuation_percent=float(attenuation))
    return result, ft, filtered


def match_gains(cil, desk):
    pairs, used = [], set()
    for c in cil:
        matches = [d for d in desk if np.isclose(c['kp'],d['kp'],rtol=1e-5,atol=1e-5)]
        if len(matches)>1 or any(np.isclose(c['kp'],p[0]['kp'],rtol=1e-5,atol=1e-5) for p in pairs):
            raise ValueError("Duplicate gains make matching ambiguous; use one measurement per gain.")
        if not matches:
            warn(f"No Deskbench match for CIL gain {c['kp']:g} (ID {c['id']}).")
            continue
        d=matches[0]
        if not np.allclose([c['initial'],c['final']],[d['initial'],d['final']],rtol=1e-5,atol=1e-5):
            raise ValueError(f"Incompatible reference levels at Kp={c['kp']:g}; cannot use a shared reference.")
        used.add(d['id']);pairs.append((c,d))
    for d in desk:
        if d['id'] not in used:warn(f"No CIL match for Deskbench gain {d['kp']:g} (ID {d['id']}).")
    if not pairs:raise ValueError("No matched gains.")
    return pairs


def compare_recordings(cdata, csteps, cmetrics, cpath, dpath, output, vdc):
    ddata=load_log(dpath);dsteps=detect_steps(ddata)
    dmetrics=[calculate_metrics(step) for step in dsteps]
    pairs=match_gains(csteps,dsteps)
    rows, flattened, columns = [], [], []
    diagnostic_fig, dax=plt.subplots(len(pairs),1,figsize=(9,2.2*len(pairs)),squeeze=False,layout="constrained")
    for i,(c,d) in enumerate(pairs):
        row={'kp_v_per_a':c['kp']}
        for label,step,metrics in [('cil',c,cmetrics),('deskbench',d,dmetrics)]:
            raw=next(m for m in metrics if m['measurement_id']==step['id'])
            diag,ft,fy=stationary_and_settling(step,raw)
            row.update({label+'_'+key:value for key,value in {**raw,**diag}.items()})
            name='iq_'+label+'_kp_'+f"{c['kp']:g}".replace('.','p')
            columns.append(name);flattened.append(step)
            t=(step['hold']['time']-step['t0'])*1000
            dax[i,0].plot(t,step['hold']['iq_dut'],alpha=.55,label=label+' raw')
            dax[i,0].plot(ft,fy,ls='--',label=label+' centered average')
        row['rise_time_abs_difference_ms']=abs(row['deskbench_rise_time_ms']-row['cil_rise_time_ms'])
        row['overshoot_difference_pp']=row['deskbench_overshoot_percent']-row['cil_overshoot_percent']
        row['iae_abs_difference_a_ms']=abs(row['deskbench_iae_a_ms']-row['cil_iae_a_ms'])
        rows.append(row)
        dax[i,0].set(xlim=(0,10),ylabel='Current / A',title=f"Kp = {c['kp']:g} V/A")
        dax[i,0].grid(alpha=.2)
    dax[0,0].legend(ncol=2,fontsize=8);dax[-1,0].set_xlabel('Time from reference step / ms')
    diagnostic_fig.savefig(output/'filter_diagnostic.png',dpi=160);plt.close(diagnostic_fig)
    with (output/'step_comparison_metrics.csv').open('w',newline='') as stream:
        writer=csv.DictWriter(stream,fieldnames=rows[0]);writer.writeheader();writer.writerows(rows)
    export_plot_data(flattened,output,COMPARISON_START_MS,COMPARISON_END_MS,
                     'step_comparison_data.csv',columns)
    fig,ax=plt.subplots(figsize=(9,5),layout='constrained')
    colors=['uzblue','uzorange','uzgreen','uzred','uzpurple'];plots=[]
    for i,(c,d) in enumerate(pairs):
        for j,(step,style) in enumerate([(c,'-'),(d,'--')]):
            block=step['block'];t=(block['time']-step['t0'])*1000
            keep=(t>=COMPARISON_START_MS)&(t<=COMPARISON_END_MS)&(block['iq_step_state']<=2)
            ax.plot(t[keep],block['iq_dut'][keep],color=f'C{i%10}',ls=style,lw=1.2,
                    label=f"Kp = {c['kp']:g} V/A" if j==0 else '_nolegend_')
            plots.append(r'\addplot[thick,'+colors[i%5]+(','+'solid' if j==0 else ',dashed')+
                         ('' if j==0 else ',forget plot')+r'] table[x=time_ms,y='+columns[2*i+j]+
                         r',col sep=comma]{step_comparison_data.csv};')
            if j==0:plots.append(rf"\addlegendentry{{$K_p={c['kp']:g}$ V/A}}")
    ref=[pairs[0][0]['initial'],pairs[0][0]['initial'],pairs[0][0]['final'],pairs[0][0]['final']]
    ax.plot([COMPARISON_START_MS,0,0,COMPARISON_END_MS],ref,color='0.3',lw=.8,label='Reference')
    ax.set(xlim=(COMPARISON_START_MS,COMPARISON_END_MS),xlabel='Time from reference step / ms',
           ylabel='q-axis current / A',title='CIL (solid) and Deskbench (dashed)')
    ax.grid(alpha=.2);ax.legend(ncol=3,fontsize=9);ax.margins(y=.1)
    for extension in ['pdf','png']:fig.savefig(output/f'step_comparison.{extension}',dpi=300)
    plt.close(fig)
    write_comparison_report(pairs,rows,plots,cdata,ddata,cpath,dpath,output,vdc)
    for r in rows:
        print(f"Kp={r['kp_v_per_a']:g}: rise CIL/Desk {r['cil_rise_time_ms']:.3f}/{r['deskbench_rise_time_ms']:.3f} ms; "
              f"overshoot {r['cil_overshoot_percent']:.2f}/{r['deskbench_overshoot_percent']:.2f}%; "
              f"filtered settling {r['cil_filtered_settling_time_ms']:.2f}/{r['deskbench_filtered_settling_time_ms']:.2f} ms; "
              f"Desk stationary SD {r['deskbench_stationary_std_a']*1000:.1f} mA")
    print(f"{len(pairs)} gain-matched pairs. Results: {output.resolve()}")


def write_comparison_report(pairs,rows,plots,cdata,ddata,cpath,dpath,output,vdc):
    def escape(s):
        return ''.join({'_':r'\_','%':r'\%','&':r'\&','#':r'\#','$':r'\$'}.get(c,c) for c in s)
    setup=rf"{len(pairs)} gains were matched by recorded $K_p$: "+', '.join(f"{c['kp']:g}" for c,d in pairs)+r" V/A. "
    setup+=rf"The reference changes from {pairs[0][0]['initial']:g} to {pairs[0][0]['final']:g} A. "
    for label,steps in [('CIL',[c for c,d in pairs]),('Deskbench',[d for c,d in pairs])]:
        speeds=[np.mean(s['hold']['dut_speed_rpm']) for s in steps if 'dut_speed_rpm' in s['hold']]
        if speeds:
            value=f'{np.mean(speeds):.1f}' if np.ptp(speeds)<.1 else f'{min(speeds):.1f}--{max(speeds):.1f}'
            setup+=rf"{label} mean HOLD speeds: {value}\,rpm. "
        dt=np.concatenate([np.diff(s['block']['time']) for s in steps])
        if np.allclose(dt,np.median(dt),rtol=.001,atol=1e-9):setup+=rf"{label} logging: {1/np.median(dt)/1000:g}\,kHz. "
    setup+='Operating conditions are similar but not identical; speed differences may influence the comparison.'
    diffs=[r['rise_time_abs_difference_ms'] for r in rows]
    discussion=rf"Absolute rise-time differences span {min(diffs):.3f}--{max(diffs):.3f}\,ms. "
    over=[r['overshoot_difference_pp'] for r in rows]
    discussion+=rf"Deskbench-minus-CIL overshoot differences span {min(over):.2f}--{max(over):.2f} percentage points. "
    best=min(rows,key=lambda r:r['deskbench_iae_a_ms'])
    best_over=min(rows,key=lambda r:r['deskbench_overshoot_percent'])
    discussion+=rf"Deskbench IAE is lowest at $K_p={best['kp_v_per_a']:g}$ V/A; overshoot is lowest at $K_p={best_over['kp_v_per_a']:g}$ V/A. "
    if min(over)<0<max(over):
        discussion+='The direction of the overshoot deviation changes with gain. '
    high=sorted([r for r in rows if r['kp_v_per_a']>=8.79],key=lambda r:r['kp_v_per_a'])
    if len(high)>=3 and all(np.all(np.diff([r[label+'_overshoot_percent'] for r in high])>0)
                           for label in ['cil','deskbench']):
        discussion+='Both datasets show increasing overshoot above the nominal gain. '
    # Describe ringing only when repeated raw excursions exceed the stationary variation.
    ringing=[]
    for c,d in pairs:
        for label,step in [('cil',c),('deskbench',d)]:
            row=next(r for r in rows if np.isclose(r['kp_v_per_a'],c['kp']))
            y=step['hold']['iq_dut'];t=(step['hold']['time']-step['t0'])*1000
            error=y[t<=5]-step['final']
            threshold=max(.02*(step['final']-step['initial']),3*row[label+'_stationary_std_a'])
            signs=np.sign(error[abs(error)>threshold])
            if np.count_nonzero(np.diff(signs))>=3:ringing.append(label)
    if 'cil' in ringing and 'deskbench' in ringing:
        discussion+='Repeated early excursions confirm ringing in both datasets. '
    sd=[r['deskbench_stationary_std_a']*1000 for r in rows]
    csd=[r['cil_stationary_std_a']*1000 for r in rows]
    if min(sd)>max(csd):discussion+='Deskbench stationary variation is greater throughout. '
    discussion+=('Thus CIL captures aspects of the transient response but not the full physical waveform. '
                 'The speed mismatch may influence differences; these data do not isolate parameter, inverter or sensor causes. '
                 'No universal optimum or measured closed-loop bandwidth follows from this test.')
    if any(c['violation'] or d['violation'] for c,d in pairs):
        discussion+=r' \textbf{Logged DUT violations affect this comparison.}'
    cil_sd='approximately zero (below 0.01 mA)' if max(csd)<.01 else f'{min(csd):.2g}--{max(csd):.2g} mA'
    desk_sd=f'{np.mean(sd):.0f}' if round(min(sd))==round(max(sd)) else f'{min(sd):.0f}--{max(sd):.0f}'
    method=rf"Stationary current standard deviation: CIL {cil_sd}; Deskbench {desk_sd}\,mA, evaluated over the final {NOISE_WINDOW_MS:g}\,ms of HOLD. "
    method+='This variation may include sensor noise, current ripple and control-induced oscillations; its contributions are not independently identified.'
    exceeds=[r['deskbench_stationary_std_a'] > .02*r['deskbench_step_amplitude_a'] for r in rows]
    if all(exceeds):
        method+=r' Conventional $\pm2\%$ settling time is not reported for the physical Deskbench because stationary current variation exceeds the corresponding tolerance band.'
    elif any(exceeds):
        gains=', '.join(f"{r['kp_v_per_a']:g}" for r,e in zip(rows,exceeds) if e)
        method+=rf' Stationary variation exceeds the $\pm2\%$ band at $K_p={gains}$ V/A; settling comparisons require caution.'
    method+=' Raw and filtered settling metrics remain in the CSV for traceability.'
    # Reuse the existing voltage assessment and condense its presentation only.
    assessments=[report_voltage([p[i] for p in pairs],data,vdc) for i,data in enumerate([cdata,ddata])]
    utilization=[re.search(r'Maximum (vector|q-axis) utilization is ([0-9.]+)',v) for v in assessments]
    if all(utilization):
        kind='voltage-vector' if all(m[1]=='vector' for m in utilization) else 'available voltage-command'
        voltage=rf"Maximum commanded {kind} utilization was {utilization[0][2]}\,\% in CIL and {utilization[1][2]}\,\% on the Deskbench"
        if all('not recorded' in v for v in assessments):
            voltage+=rf", relative to the nominal linear-SVPWM limit of {vdc/np.sqrt(3):.2f}\,V at an externally supplied DC-link voltage of {vdc:g}\,V. "
        else:
            voltage+=r', using each recording\textquotesingle s recorded or explicitly supplied $U_{\mathrm{dc}}/\sqrt{3}$. '
        voltage+='These are commands, not measured terminal voltages; other limiting mechanisms are not excluded.'
        if any(float(m[2])>=99.9 for m in utilization):voltage+=' The nominal bound is reached in at least one recording.'
        if kind!='voltage-vector':voltage+=' Where only the q-axis component is available, utilization is an indicator rather than a full-vector assessment.'
    else:
        voltage=' '.join(label+': '+v for label,v in zip(['CIL','Deskbench'],assessments))
    # Shared limits are based on both raw datasets over the requested plot window.
    values=[np.array([pairs[0][0]['initial'],pairs[0][0]['final']])]
    panels=[[],[]];colors=['uzblue','uzorange','uzgreen','uzred','uzpurple']
    for i,(c,d) in enumerate(pairs):
        for j,step in enumerate((c,d)):
            block=step['block'];t=(block['time']-step['t0'])*1000
            use=(t>=COMPARISON_START_MS)&(t<=COMPARISON_END_MS)&(block['iq_step_state']<=2)
            values.append(block['iq_dut'][use])
            column='iq_'+('cil' if j==0 else 'deskbench')+'_kp_'+f"{c['kp']:g}".replace('.','p')
            panels[j].append(r'\addplot[thick,solid,'+colors[i%5]+r'] table[x=time_ms,y='+column+r',col sep=comma]{step_comparison_data.csv};')
            if j==1:panels[j].append(rf"\addlegendentry{{$K_p={c['kp']:g}$ V/A}}")
    values=np.concatenate(values);lo,hi=np.nanmin(values),np.nanmax(values)
    margin=max((hi-lo)*.08,.01);lo-=margin;hi+=margin
    from matplotlib.ticker import MaxNLocator
    ticks=MaxNLocator(nbins=5).tick_values(lo,hi)
    yticks=','.join(f'{v:g}' for v in ticks if lo<=v<=hi)
    template=Path(__file__).with_name('step_report.tex').read_text()
    replacements={'% COMPARISON_MODE':r'\comparisontrue','% COMP_SETUP':setup,'% COMP_CIL_PLOTS':'\n'.join(panels[0]),'% COMP_DESK_PLOTS':'\n'.join(panels[1]),
                  '% COMP_AXIS':f'xmin={COMPARISON_START_MS:g},xmax={COMPARISON_END_MS:g},ymin={lo:.8g},ymax={hi:.8g},ytick={{{yticks}}},',
                  '% COMP_DISCUSSION':discussion,'% COMP_METHOD':method,'% COMP_VOLTAGE':voltage,
                  '% COMP_SOURCES':r'CIL: \texttt{'+escape(cpath.name)+r'}.\\ Deskbench: \texttt{'+escape(dpath.name)+'}.'}
    for k,v in replacements.items():template=template.replace(k,v)
    template=template.replace('pdftitle={Experimental Evaluation of PMSM q-Axis Current Control}',
                              'pdftitle={Experimental Validation of PMSM q-Axis Current Control}')
    (output/'step_report.tex').write_text(template)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("log", type=Path, nargs="?", default=DEFAULT_LOG_FILE,
                        help="JavaScope CSV; overrides DEFAULT_LOG_FILE near the top of this script")
    parser.add_argument("--output", type=Path)
    parser.add_argument("--deskbench", type=Path, help="Compare this physical Deskbench log with the positional CIL log")
    parser.add_argument("--vdc", type=float, help="Externally supplied DC-link voltage in V; recorded voltage takes precedence")
    args = parser.parse_args()
    try:
        if args.vdc is not None and (not np.isfinite(args.vdc) or args.vdc <= 0):
            raise ValueError("--vdc must be a finite positive voltage.")
        data = load_log(args.log)
        steps = detect_steps(data)
        metrics = [calculate_metrics(s) for s in steps]
        output = args.output or args.log.parent / (args.log.stem + "_results")
        output.mkdir(parents=True, exist_ok=True)
        if args.deskbench:
            compare_recordings(data, steps, metrics, args.log, args.deskbench, output, args.vdc)
            return
        with (output / "step_metrics.csv").open("w", newline="") as stream:
            writer = csv.DictWriter(stream, fieldnames=list(metrics[0]))
            writer.writeheader()
            writer.writerows(metrics)
        plot_responses(steps, output)
        names, spacing = export_plot_data(steps, output)
        write_report(steps, metrics, names, spacing, args.log, output, data, args.vdc)
    except (ValueError, OSError) as exc:
        parser.exit(1, f"Error: {exc}\n")
    fields = ["measurement_id", "kp_v_per_a", "rise_time_ms", "peak_current_a",
              "overshoot_percent", "settling_time_ms", "iae_a_ms"]
    print("  ".join(fields))
    for row in metrics:
        print("  ".join(f"{row[c]:.3f}" for c in fields))
    print(f"\n{len(steps)} complete steps. Outputs: {output.resolve()}")


if __name__ == "__main__":
    main()
