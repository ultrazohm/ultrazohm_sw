"""Offline closed-loop iq sweep analysis; requires only numpy and matplotlib.

Fit x = a*sin(w*t) + b*cos(w*t) + c, with sine phasor a + j*b.
H = output phasor / recorded input phasor; no delay correction is applied.
Residuals include ripple, harmonics and unmodelled dynamics as well as noise.
Metrics retain acquisition order; Bode data are sorted by frequency.

Example (from the repository root):
  python analyze_iq_sweep.py javascope/Log_2026-11-05_16-10-54.csv --output results --vdc 48

One run per file. Missing channels, invalid numbers or ambiguous segmentation
are errors; questionable fits remain in the exports with quality_status warnings.
Measured periods use the time span plus one sample interval, so boundaries have
one-sample resolution. The first three points define the low-frequency mean only
if their spread is <=0.5 dB and none has a quality warning. Bandwidth is interpolated
in dB versus log frequency, never extrapolated. Final-point/flagged support makes
it provisional. Sparse frequency points can hide features and phase wraps;
unwrapping cannot resolve arbitrary additional delays between measured points.
Voltage utilization describes commands, not measured terminal voltages.
The generated two-page PGFPlots report is compiled automatically when pdflatex
is available on PATH; otherwise the LaTeX source and analysis outputs remain usable.
"""
import argparse
import csv
from pathlib import Path
import re
import shutil
import subprocess

import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

# Defaults for running directly from an editor; CLI arguments override these.
ROOT = Path(__file__).resolve().parent
DEFAULT_LOG_FILE = ROOT / "javascope/Log_2026-11-05_16-10-54.csv"
DEFAULT_OUTPUT_DIR = ROOT / "results"

# Diagnostic thresholds, not controller limits. Warnings do not discard fits.
MIN_SAMPLES = 20
MIN_PERIODS = 3.0
MIN_SAMPLES_PER_PERIOD = 10.0
MIN_INPUT_AMPLITUDE_A = 0.01
MAX_FIT_CONDITION = 1e6
MAX_INPUT_RESIDUAL_RELATIVE = 0.05
MAX_OUTPUT_RESIDUAL_RELATIVE = 0.20
LOW_GAIN_SPREAD_DB = 0.5  # Lowest three points must form a consistent plateau.
REQUIRED = ["time", "iq_ref_dut", "iq_dut", "experiment_active", "experiment_id",
            "iq_sweep_state", "iq_sweep_frequency_id", "iq_sweep_frequency_hz",
            "iq_sweep_measurement_active"]
OPTIONAL = ["dut_speed_rpm", "vq_ref_dut", "vd_ref_dut", "dut_violation",
            "experiment_status", "experiment_sample", "iq_sweep_reference",
            "iq_sweep_phase_rad", "dut_v_dc_v"]


def load_log(path):
    with Path(path).open(encoding="utf-8-sig", newline="") as stream:
        reader = csv.reader(stream, delimiter=";")
        names = [re.sub(r"^CH\d+\s*=\s*\d+\)", "", n.strip(), flags=re.I).lower()
                 for n in next(reader, [])]
        nonempty = [n for n in names if n]
        if len(nonempty) != len(set(nonempty)):
            raise ValueError("Duplicate semantic channel names.")
        missing = set(REQUIRED) - set(names)
        if missing:
            raise ValueError("Missing required signals: " + ", ".join(sorted(missing)))
        columns = {n: i for i, n in enumerate(names) if n in REQUIRED + OPTIONAL}
        rows = []
        for line, row in enumerate(reader, 2):
            if not row or not any(v.strip() for v in row):
                continue
            try:
                rows.append([float(row[i]) for i in columns.values()])
            except (ValueError, IndexError) as exc:
                raise ValueError(f"Invalid/missing numerical value on line {line}.") from exc
    if len(rows) < 3:
        raise ValueError("At least three data samples are required.")
    values = np.asarray(rows)
    for j, name in enumerate(columns):
        if not np.isfinite(values[:, j]).all():
            raise ValueError(f"Non-finite numerical values in {name}.")
    data = {n: values[:, j] for j, n in enumerate(columns)}
    if not (np.diff(data["time"]) > 0).all():
        raise ValueError("Timestamps must be strictly increasing.")
    for name in ["experiment_active", "experiment_id", "iq_sweep_state",
                 "iq_sweep_frequency_id", "iq_sweep_measurement_active",
                 "experiment_status", "experiment_sample", "dut_violation"]:
        if name in data and not (data[name] == np.floor(data[name])).all():
            raise ValueError(f"Non-integer metadata in {name}.")
    for name in ["experiment_active", "iq_sweep_measurement_active"]:
        if not np.isin(data[name], [0, 1]).all():
            raise ValueError(f"{name} must be 0 or 1.")
    return data


def detect_frequency_points(data):
    active = (data["experiment_id"] == 2) & (data["experiment_active"] == 1)
    measure = data["iq_sweep_measurement_active"] == 1
    state, ids = data["iq_sweep_state"], data["iq_sweep_frequency_id"]
    if np.any(measure & (~active | (state != 3))) or np.any(active & (state == 3) & ~measure):
        raise ValueError("Measurement flag disagrees with sweep ID/active/state metadata.")
    if "experiment_status" in data and np.any(active & (data["experiment_status"] != 1)):
        raise ValueError("Active sweep has non-running experiment status.")
    if np.count_nonzero(np.diff(np.r_[False, active].astype(int)) == 1) > 1:
        raise ValueError("Multiple sweep runs: analyze one sequence per CSV.")
    edges = np.r_[0, np.flatnonzero(np.diff(measure) | (np.diff(ids) != 0)) + 1, len(ids)]
    points, seen = [], set()
    for start, end in zip(edges[:-1], edges[1:]):
        if not measure[start]:
            continue
        fid = int(ids[start])
        if fid < 1 or fid in seen:
            raise ValueError(f"Invalid or duplicated frequency ID {fid}.")
        seen.add(fid)
        block = {k: v[start:end] for k, v in data.items()}
        f = block["iq_sweep_frequency_hz"]
        if f[0] <= 0 or not np.allclose(f, f[0], rtol=1e-6, atol=1e-6):
            raise ValueError(f"Frequency ID {fid}: inconsistent/nonpositive frequency.")
        notes = []
        if fid != len(points) + 1:
            notes.append("missing_or_out_of_order_frequency_ID")
        before = start > 0 and active[start-1] and ids[start-1] == fid and state[start-1] == 2
        after = end < len(ids) and active[end] and ids[end] == fid and state[end] == 4
        if not (before and after):
            notes.append("incomplete_measurement_window")
        points.append((block, notes))
    if not points:
        raise ValueError("No active ID-2 sweep measurement windows found.")
    active_ids = set(ids[active & (state == 2)].astype(int))
    missing = active_ids - seen
    if missing:
        points[-1][1].append("missing_measurement_IDs_" + "_".join(map(str, sorted(missing))))
    frequencies = [p[0]["iq_sweep_frequency_hz"][0] for p in points]
    if len(set(frequencies)) != len(frequencies):
        raise ValueError("Duplicate excitation frequencies; cannot form a unique Bode curve.")
    if not np.all(np.diff(frequencies) > 0):
        points[-1][1].append("nonascending_frequency_order")
    return points


def fit_sinusoid(time, signal, frequency):
    angle = 2 * np.pi * frequency * (time - time[0])
    design = np.column_stack((np.sin(angle), np.cos(angle), np.ones(len(time))))
    coef, _, rank, singular = np.linalg.lstsq(design, signal, rcond=None)
    condition = singular[0] / singular[-1] if singular[-1] > 0 else np.inf
    if rank < 3:
        raise ValueError("rank-deficient sinusoidal fit")
    return complex(coef[0], coef[1]), coef[2], np.sqrt(np.mean((signal-design@coef)**2)), condition


def calculate_frequency_response(point, logging_dt, vdc=None):
    d, initial_notes = point
    notes = list(initial_notes)
    t, f = d["time"], float(d["iq_sweep_frequency_hz"][0])
    dt = float(np.median(np.diff(t))) if len(t) > 1 else logging_dt
    periods = (t[-1]-t[0]+dt) * f  # Sample-cell duration, boundary uncertainty ~one sample.
    row = dict(frequency_id=int(d["iq_sweep_frequency_id"][0]), frequency_hz=f,
               magnitude_db=np.nan, phase_deg=np.nan, phase_wrapped_deg=np.nan)
    for key in ["input_amplitude_a", "output_amplitude_a", "input_offset_a", "output_offset_a",
                "input_residual_rms_a", "output_residual_rms_a", "output_residual_relative"]:
        row[key] = np.nan
    row.update(sample_count=len(t), samples_per_period=1/(dt*f), measured_periods=periods,
               mean_speed_rpm=float(np.mean(d["dut_speed_rpm"])) if "dut_speed_rpm" in d else np.nan,
               max_voltage_command_v=np.nan, voltage_utilization_percent=np.nan,
               voltage_kind="unavailable", dut_violation=np.max(d["dut_violation"]) if "dut_violation" in d else np.nan,
               fit_condition=np.nan)
    if len(t) < MIN_SAMPLES or periods < MIN_PERIODS:
        notes.append("insufficient_samples_or_periods")
    if 1/(dt*f) < MIN_SAMPLES_PER_PERIOD-1e-6:
        notes.append("low_sampling_resolution")
    if 1/(dt*f) <= 2:
        notes.append("at_or_above_Nyquist")
    if np.any(np.abs(np.diff(t)/logging_dt-1) > 0.05):
        notes.append("timestamp_gaps_or_jitter")
    if "experiment_sample" in d and np.any(np.diff(d["experiment_sample"]) != 1):
        notes.append("sample_counter_gaps")
    if row["dut_violation"] > 0:
        notes.append("DUT_violation")
    try:
        if len(t) < 3 or 1/(dt*f) <= 2:
            raise ValueError("insufficient independent samples")
        inp, in_dc, in_rms, condition = fit_sinusoid(t, d["iq_ref_dut"], f)
        out, out_dc, out_rms, _ = fit_sinusoid(t, d["iq_dut"], f)
        row.update(input_amplitude_a=abs(inp), output_amplitude_a=abs(out),
                   input_offset_a=in_dc, output_offset_a=out_dc, input_residual_rms_a=in_rms,
                   output_residual_rms_a=out_rms, output_residual_relative=out_rms/max(abs(out), 1e-15),
                   fit_condition=condition)
        if condition > MAX_FIT_CONDITION:
            notes.append("poor_fit_condition")
        if abs(inp) < MIN_INPUT_AMPLITUDE_A:
            notes.append("small_input_amplitude")
        if in_rms/max(abs(inp), 1e-15) > MAX_INPUT_RESIDUAL_RELATIVE:
            notes.append("nonsinusoidal_reference")
        if row["output_residual_relative"] > MAX_OUTPUT_RESIDUAL_RELATIVE:
            notes.append("large_output_residual")
        if abs(inp) <= 1e-12 or abs(out) <= 1e-12:
            raise ValueError("zero fundamental amplitude")
        response = out / inp
        row.update(magnitude_db=20*np.log10(abs(response)), phase_wrapped_deg=np.degrees(np.angle(response)))
    except (ValueError, np.linalg.LinAlgError) as exc:
        notes.append("invalid_fit: " + str(exc))
    if "vq_ref_dut" in d:
        voltage = np.abs(d["vq_ref_dut"])
        row["voltage_kind"] = "q_axis_only"
        if "vd_ref_dut" in d:
            voltage = np.hypot(d["vd_ref_dut"], d["vq_ref_dut"])
            row["voltage_kind"] = "dq_vector"
        row["max_voltage_command_v"] = np.max(voltage)
        bus = vdc if vdc is not None else d.get("dut_v_dc_v")
        if bus is not None:
            if np.any(np.asarray(bus) <= 0):
                notes.append("invalid_recorded_dc_voltage")
            else:
                row["voltage_utilization_percent"] = 100*np.max(voltage/(np.asarray(bus)/np.sqrt(3)))
                if row["voltage_utilization_percent"] >= 95:
                    notes.append("high_voltage_utilization")
    row["quality_status"] = "; ".join(notes) or "OK"
    return row


def estimate_bandwidth(results):
    ordered = sorted(results, key=lambda r: r["frequency_hz"])
    base = ordered[:3]
    if len(base) < 3 or any(r["quality_status"] != "OK" for r in base):
        return np.nan, np.nan, "Bandwidth unavailable: fewer than three reliable lowest-frequency points."
    gains = [r["magnitude_db"] for r in base]
    if not np.isfinite(gains).all() or np.ptp(gains) > LOW_GAIN_SPREAD_DB:
        return np.nan, np.nan, "Bandwidth unavailable: lowest three points do not form a consistent gain plateau."
    reference = float(np.mean(gains))
    target = reference-3.0
    for i, (a, b) in enumerate(zip(ordered[:-1], ordered[1:])):
        ga, gb = a["magnitude_db"], b["magnitude_db"]
        if np.isfinite([ga, gb]).all() and ga >= target > gb:
            fraction = (target-ga)/(gb-ga)
            frequency = np.exp(np.log(a["frequency_hz"])+fraction*np.log(b["frequency_hz"]/a["frequency_hz"]))
            questionable = any(r["quality_status"] != "OK" for r in ordered[:i+2])
            provisional = questionable or i+2 == len(ordered)
            suffix = " (provisional: final-point support and/or quality warnings)" if provisional else ""
            return reference, frequency, f"Relative -3 dB bandwidth: {frequency:.1f} Hz{suffix}."
    if any(not np.isfinite(r["magnitude_db"]) for r in ordered):
        return reference, np.nan, "Bandwidth unavailable: invalid fits leave gaps in the measured response."
    return reference, np.nan, "-3 dB bandwidth not reached within measured frequency range."


def export_results(results, output_dir):
    for filename, rows, fields in [
        ("iq_sweep_metrics.csv", results, list(results[0])),
        ("iq_sweep_bode.csv", sorted(results, key=lambda r: r["frequency_hz"]),
         ["frequency_hz", "magnitude_db", "phase_deg", "phase_wrapped_deg"])]:
        with (output_dir/filename).open("w", newline="", encoding="utf-8") as stream:
            writer = csv.DictWriter(stream, fields, extrasaction="ignore")
            writer.writeheader()
            writer.writerows(rows)


def plot_bode(results, output_dir, reference, bandwidth, message):
    rows = sorted(results, key=lambda r: r["frequency_hz"])
    f = [r["frequency_hz"] for r in rows]
    plt.rcParams.update({"font.family": "serif", "font.size": 10, "pdf.fonttype": 42})
    fig, axes = plt.subplots(2, 1, sharex=True, figsize=(6.8, 5.3), constrained_layout=True)
    for ax, key, label in zip(axes, ["magnitude_db", "phase_deg"], ["Magnitude / dB", "Phase / °"]):
        ax.semilogx(f, [r[key] for r in rows], "o-", color="#17618d", ms=4, lw=1.3)
        ax.set_ylabel(label)
        ax.grid(True, which="major", alpha=0.35)
        ax.grid(True, which="minor", alpha=0.13)
        flagged = [r for r in rows if r["quality_status"] != "OK"]
        if flagged:
            ax.plot([r["frequency_hz"] for r in flagged], [r[key] for r in flagged],
                    "o", mfc="none", mec="#b65a00", ms=7, label="Quality warning")
    if np.isfinite(reference):
        axes[0].axhline(reference, color="0.5", ls=":", lw=1, label="Low-frequency mean")
        axes[0].axhline(reference-3, color="0.35", ls="--", lw=1, label="Relative −3 dB")
    if np.isfinite(bandwidth):
        qualifier = " (provisional)" if "provisional" in message else ""
        axes[0].plot(bandwidth, reference-3, "x", color="#b65a00", ms=8,
                     label=f"Bandwidth {bandwidth/1000:.2f} kHz{qualifier}")
    handles, _ = axes[0].get_legend_handles_labels()
    if handles:
        axes[0].legend(fontsize=8, loc="best")
    axes[1].set_xlabel("Frequency / Hz")
    for extension in ["pdf", "png"]:
        fig.savefig(output_dir/f"iq_sweep_bode.{extension}", dpi=300)
    plt.close(fig)



def latex_escape(text):
    replacements = {"\\": r"\textbackslash{}", "_": r"\_", "%": r"\%", "&": r"\&",
                    "#": r"\#", "$": r"\$", "{": r"\{", "}": r"\}", "~": r"\textasciitilde{}",
                    "^": r"\textasciicircum{}"}
    return "".join(replacements.get(c, c) for c in str(text))


def generate_report(results, output_dir, source, dt, vdc, data, reference, bandwidth, message):
    """Present existing results; bandwidth and quality decisions are not recomputed."""
    valid = sorted([r for r in results if np.isfinite(r["magnitude_db"])], key=lambda r: r["frequency_hz"])
    if not valid:
        raise ValueError("Cannot generate a report without fitted frequency points.")
    first, last = valid[0], valid[-1]
    peak = max(valid, key=lambda r: r["magnitude_db"])
    def values(key):
        return np.array([r[key] for r in valid if np.isfinite(r[key])])
    def mean(key):
        a = values(key)
        return f"{np.mean(a):.3g}" if len(a) else "unavailable"
    def span(key, scale=1):
        a = values(key)*scale
        return f"{min(a):.2f}--{max(a):.2f}" if len(a) else "unavailable"
    frequency_range = f"{first['frequency_hz']:g}--{last['frequency_hz']:g}"
    flagged = [r for r in results if r["quality_status"] != "OK"]
    low_sampling = [r for r in results if "low_sampling_resolution" in r["quality_status"]]
    sampling = (f"Sampling-resolution flags affect {len(low_sampling)} points at " +
                ", ".join(f"{r['frequency_hz']:g}" for r in low_sampling) + r"\,Hz. "
                if low_sampling else "No point carries a sampling-resolution flag. ")
    other = sorted({w.strip() for r in flagged for w in r["quality_status"].split(";")
                    if w.strip() != "low_sampling_resolution"})
    if other:
        sampling += "Other flags: " + latex_escape(", ".join(other)) + ". "
    violation = values("dut_violation")
    violations = ("No DUT violations were recorded in the measurement windows." if len(violation) and not np.any(violation)
                  else "DUT violations occur in the measurement windows." if len(violation)
                  else "DUT violation status was not recorded.")
    voltage = values("voltage_utilization_percent")
    voltage_text = (f"Maximum {latex_escape(valid[0]['voltage_kind'].replace('_', ' '))} command utilization is "
                    f"{max(voltage):.2f}\\% of $U_{{DC}}/\\sqrt{{3}}$. " if len(voltage)
                    else "Voltage utilization is unavailable without both voltage commands and a DC-link value. ")
    voltage_text += "These are commands, not measured terminal voltages; this metric does not exclude other limiting mechanisms."
    bus = (f"{vdc:g} V (supplied nominal value)" if vdc is not None else
           f"{np.mean(data['dut_v_dc_v']):.3g} V (recorded mean)" if "dut_v_dc_v" in data else "not supplied or recorded")
    provisional = "provisional" in message
    # Summarize the high-frequency diagnostic region without changing any fit or flag.
    high = valid[-5:]
    residual = [r['output_residual_relative']*100 for r in high]
    conditioning = [r['fit_condition'] for r in valid]
    fit_text = ("The sinusoidal least-squares fits remain numerically well-conditioned. "
                if np.isfinite(conditioning).all() and max(conditioning) < 10 else
                "Fit conditioning requires inspection; numerical reliability is not assumed. ")
    fit_text += (f"Output residual RMS over {high[0]['frequency_hz']:g}--{high[-1]['frequency_hz']:g}\\,Hz "
                 f"is {min(residual):.1f}--{max(residual):.1f}\\% of fitted amplitude. ")
    crossing_note = ""
    if np.isfinite(bandwidth) and provisional:
        upper = int(np.searchsorted([r['frequency_hz'] for r in valid], bandwidth))
        bracket = valid[max(0, upper-1):upper+1]
        crossing_note = ("The bandwidth remains provisional because its crossing depends on quality-flagged measurements. "
                         if any(r['quality_status'] != 'OK' for r in bracket) else
                         "The bandwidth remains provisional because of final-point support or preceding quality warnings. ")
    bw_label = ("Provisional closed-loop $-3$ dB bandwidth estimate" if provisional
                else "Closed-loop $-3$ dB bandwidth estimate")
    if np.isfinite(bandwidth):
        # Interpolation for descriptive phase only; the bandwidth is passed unchanged.
        phase = np.interp(np.log(bandwidth), np.log([r['frequency_hz'] for r in valid]),
                          [r['phase_deg'] for r in valid])
        bw_text = f"{bw_label}: {bandwidth/1000:.3f}\\,kHz."
        phase_text = f"{phase:.1f} degrees (log-frequency interpolation)"
        bw_discussion = (f"The relative $-3$ dB crossing is estimated at {bandwidth/1000:.3f}\\,kHz. " +
                         ("It remains provisional because the crossing has final-point support and/or quality warnings. "
                          if provisional else "The crossing is bracketed by measured points without quality flags. "))
    else:
        bw_text = ("$-3$ dB bandwidth not reached within the measured frequency range."
                   if "not reached" in message else latex_escape(message))
        phase_text = "unavailable (no supported bandwidth crossing)"
        bw_discussion = bw_text + " No extrapolation is used. "
    gain_text = f"{reference:.3f} dB" if np.isfinite(reference) else "unavailable"
    trend = ("Phase lag increases overall across the measured range. " if last['phase_deg'] < first['phase_deg']
             else "Phase does not show an overall increase in lag across the measured range. ")
    peaking = (f"An intermediate-frequency magnitude maximum of {peak['magnitude_db']:.2f}\\,dB occurs at "
               f"{peak['frequency_hz']:g}\\,Hz. " if peak not in (first, last)
               else f"The largest measured magnitude is {peak['magnitude_db']:.2f}\\,dB at the range boundary. ")
    rolloff = ("The response rolls off toward the highest measured frequency. " if last['magnitude_db'] < peak['magnitude_db']
               else "No decline from the maximum is resolved at the upper frequency boundary. ")
    discussion = (f"The low-frequency gain reference is {gain_text}, describing tracking around the measured operating point. " +
                  peaking + trend + rolloff + bw_discussion +
                  "This reference-tracking measure differs from the contextual nominal 800 Hz design bandwidth and from "
                  "open-loop gain crossover. The result alone neither disproves the design target nor establishes a physical "
                  "cause for peaking or lag. Sampling resolution and channel timing constrain interpretation of the "
                  "high-frequency points; quality flags warrant caution rather than automatic rejection. These measurements "
                  "do not establish controller instability or a quantified phase uncertainty.")
    references = ""
    if np.isfinite(reference):
        for level, style in [(reference, "dashed"), (reference-3, "densely dashed")]:
            references += (rf"\addplot[gray,{style},thin,forget plot] coordinates "
                           rf"{{({first['frequency_hz']},{level}) ({last['frequency_hz']},{level})}};" + "\n")
    if np.isfinite(bandwidth):
        references += (rf"\addplot[only marks,mark=x,mark size=3pt,brown,forget plot] coordinates "
                       rf"{{({bandwidth},{reference-3})}};" + "\n")
    def warning_marks(key):
        # Read values from metrics CSV; only the flagged row indices are generated.
        indices = [i for i, r in enumerate(results) if r['quality_status'] != 'OK']
        if not indices:
            return ""
        predicate = "".join(rf"\ifnum\coordindex={i}\relax\else " for i in indices)
        predicate += r"\def\pgfmathresult{nan}" + r"\fi"*len(indices)
        return (rf"\addplot[only marks,mark=o,mark size=3pt,brown,forget plot,x filter/.code={{{predicate}}}] "
                rf"table[x=frequency_hz,y={key},col sep=comma]"
                r"{iq_sweep_metrics.csv};")
    text = r"""\documentclass[a4paper,10pt]{article}
\usepackage[margin=20mm]{geometry}
\usepackage[T1]{fontenc}
\usepackage{lmodern,amsmath,booktabs,siunitx,pgfplots,pgfplotstable}
\usepackage[hidelinks]{hyperref}
\usepgfplotslibrary{groupplots}
\pgfplotsset{compat=1.18}
\setlength{\parindent}{0pt}\setlength{\parskip}{5pt}
\setlength{\emergencystretch}{2em}
\begin{document}
\begin{center}
{\Large\bfseries Experimental Frequency Response of PMSM\\q-Axis Current Control}\par
\smallskip
{\normalsize Closed-Loop Reference Tracking on the Physical Deskbench}
\end{center}
\section*{1. Objective and experimental setup}
The physical Deskbench PMSM operates in current-control mode with a parallel PI
q-axis controller. The prime mover maintains the approximate speed operating point.
UltraZohm applies an automated sinusoidal reference sweep; JavaScope records the
reference and current. Proportional and integral gains remain constant by experiment
configuration; unrecorded gain values are not inferred. The measured transfer is
$H(j\omega)=I_q(j\omega)/I_{q,\mathrm{ref}}(j\omega)$.
\begin{center}\begin{tabular}{ll}\toprule
Reference offset / excitation amplitude & @OFFSET@ A / @AMPLITUDE@ A\\
Mean speed / logging rate & @SPEED@ rpm / @RATE@ kHz\\
Measured range / fitted points & @RANGE@ Hz / @COUNT@\\
DC-link voltage & @BUS@\\\bottomrule
\end{tabular}\end{center}
\begin{center}\begin{tikzpicture}
\begin{groupplot}[group style={group size=1 by 2,vertical sep=0.65cm},
width=.94\linewidth,height=7.1cm,xmode=log,xmin=@XMIN@,xmax=@XMAX@,
grid=both,major grid style={gray!22},minor grid style={gray!10},
tick label style={font=\small},label style={font=\normalsize},
unbounded coords=jump,enlarge y limits=0.15]
\nextgroupplot[ylabel={Magnitude / dB},xticklabels=\empty]
\addplot[blue!65!black,solid,mark=*,mark size=1.7pt] table[x=frequency_hz,y=magnitude_db,col sep=comma]{iq_sweep_bode.csv};
@REFERENCES@
@MAGWARN@
\nextgroupplot[ylabel={Phase / $^\circ$},xlabel={Frequency / Hz}]
\addplot[blue!65!black,solid,mark=*,mark size=1.7pt] table[x=frequency_hz,y=phase_deg,col sep=comma]{iq_sweep_bode.csv};
@PHASEWARN@
\end{groupplot}\end{tikzpicture}\end{center}
{\small\textbf{Figure 1.} Closed-loop reference tracking from sinusoidal fits.
Solid lines connect measured points; phase is unwrapped. Outlined circles denote
quality-flagged points, not necessarily invalid data. Dashed lines show the
low-frequency reference and its relative $-3$ dB threshold when available;
an $\times$ marks a supported crossing. @BWTEXT@}
\newpage
\section*{2. Quantitative evaluation}
\begin{tabular}{@{}p{.47\linewidth}p{.49\linewidth}@{}}\toprule
Measured range / fitted points & @RANGE@ Hz / @COUNT@\\
Low-frequency gain reference & @GAIN@\\
Maximum measured magnitude & @PEAK@ dB at @PEAKF@ Hz\\
@BWLABEL@ & @BWVALUE@\\
Phase at estimated bandwidth & @PHASEBW@\\
Maximum voltage-command utilization & @UTIL@\\\bottomrule
\end{tabular}

\section*{3. Measurement quality and limitations}
Logging at @RATE@ kHz is constrained by the current ISR-coupled architecture,
not a fundamental UltraZohm hardware limit. With supplied ISR execution above
$50\,\mu$s and no independent logger, 20 kHz acquisition requires optimization
or architectural changes.

@SAMPLING@ @FITTEXT@ @CROSSINGNOTE@
The table lists the final recorded frequency points.
\begin{center}\small
\pgfplotstabletypeset[col sep=comma,
row predicate/.code={\ifnum\pgfplotstablerow<@TABLESTART@\relax\pgfplotstableuserowfalse\fi},
columns={frequency_hz,samples_per_period,output_residual_relative,fit_condition},
columns/frequency_hz/.style={column name={Frequency / Hz},fixed,precision=0},
columns/samples_per_period/.style={column name={Samples / period},fixed,precision=2},
columns/output_residual_relative/.style={column name={Residual / amplitude},fixed,precision=3},
columns/fit_condition/.style={column name={Fit condition},fixed,precision=2},
every head row/.style={before row=\toprule,after row=\midrule},
every last row/.style={after row=\bottomrule}]{iq_sweep_metrics.csv}
\end{center}
Input residual RMS is at most \num{@INRES@} A; windows span @PERIODS@ periods.
@VIOLATIONS@ Output residuals include possible ripple, noise, harmonics and
other dynamics. Good fit conditioning does not ensure temporal resolution:
sparse sampling increases phase sensitivity to channel timing and unmodelled
sampling effects, without alone invalidating the fit. Voltage utilization refers
to commands, not measured terminal voltages, and does not exclude other limiting.

\section*{4. Scientific interpretation}
@DISCUSSION@

\section*{5. Reproducibility}
Source: \texttt{@SOURCE@}. Measurement type: physical Deskbench (supplied context).
Operating-point values above are equal-weight means over fitted frequency points.
Settling intervals are excluded using sweep metadata. Independent least-squares
fits of \texttt{iq\_ref\_dut} and \texttt{iq\_dut} use
$a\sin(2\pi ft)+b\cos(2\pi ft)+c$ at the recorded frequency; the ratio of fitted
phasors $a+jb$ gives magnitude and output-relative phase, followed by unwrapping.
The low-frequency reference is the mean of the lowest three points, requiring
no quality warnings and a gain spread of at most @GAINSPREAD@ dB. Bandwidth uses
dB interpolation against log frequency, without extrapolation. Plots read \texttt{iq\_sweep\_bode.csv};
the diagnostic table reads \texttt{iq\_sweep\_metrics.csv}, both by relative path.
\end{document}
"""
    replacements = dict(OFFSET=mean('input_offset_a'), AMPLITUDE=mean('input_amplitude_a'),
                        SPEED=mean('mean_speed_rpm'), RATE=f"{1/dt/1000:.3g}", RANGE=frequency_range,
                        COUNT=f"{len(valid)} of {len(results)}", BUS=latex_escape(bus),
                        XMIN=f"{first['frequency_hz']/1.1:.8g}", XMAX=f"{last['frequency_hz']*1.1:.8g}",
                        REFERENCES=references, MAGWARN=warning_marks('magnitude_db'), PHASEWARN=warning_marks('phase_deg'),
                        BWTEXT=bw_text, GAIN=gain_text, PEAK=f"{peak['magnitude_db']:.3f}", PEAKF=f"{peak['frequency_hz']:g}",
                        BWLABEL=bw_label, BWVALUE=f"{bandwidth/1000:.3f} kHz" if np.isfinite(bandwidth) else bw_text,
                        PHASEBW=phase_text, UTIL=f"{max(voltage):.2f}\\%" if len(voltage) else "unavailable",
                        SAMPLING=sampling, FITTEXT=fit_text, CROSSINGNOTE=crossing_note,
                        TABLESTART=str(max(0,len(results)-5)),
                        RESIDUAL=span('output_residual_relative',100), AMPRANGE=span('input_amplitude_a'),
                        INRES=f"{max(values('input_residual_rms_a')):.2g}", PERIODS=span('measured_periods'),
                        VIOLATIONS=violations, VOLTAGE=voltage_text, DISCUSSION=discussion,
                        SOURCE=latex_escape(source.name), GAINSPREAD=f"{LOW_GAIN_SPREAD_DB:g}")
    for key, value in replacements.items():
        text = text.replace('@'+key+'@', value)
    (output_dir/'iq_sweep_report.tex').write_text(text, encoding='utf-8')
    compiler = shutil.which('pdflatex')
    if compiler is None:
        print('Report source generated; PDF not compiled: pdflatex is not available on PATH.')
        return
    for _ in range(2):
        run = subprocess.run([compiler, '-interaction=nonstopmode', '-halt-on-error',
                              '-no-shell-escape', 'iq_sweep_report.tex'], cwd=output_dir,
                             capture_output=True, text=True, errors='replace', timeout=60)
        if run.returncode:
            raise ValueError('Report compilation failed; see iq_sweep_report.log in the output directory.')
    print('LaTeX report compiled: ' + str((output_dir/'iq_sweep_report.pdf').resolve()))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("log", nargs="?", type=Path, default=DEFAULT_LOG_FILE)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT_DIR)
    parser.add_argument("--vdc", type=float, help="Nominal DC-link voltage / V (otherwise use recorded value if available)")
    args = parser.parse_args()
    if args.vdc is not None and (not np.isfinite(args.vdc) or args.vdc <= 0):
        parser.error("--vdc must be finite and positive.")
    try:
        data = load_log(args.log)
        dt = float(np.median(np.diff(data["time"])))
        results = [calculate_frequency_response(p, dt, args.vdc) for p in detect_frequency_points(data)]
        valid = sorted([r for r in results if np.isfinite(r["magnitude_db"])], key=lambda r: r["frequency_hz"])
        for row, phase in zip(valid, np.degrees(np.unwrap(np.radians([r["phase_wrapped_deg"] for r in valid])))):
            row["phase_deg"] = phase
        reference, bandwidth, message = estimate_bandwidth(results)
        args.output.mkdir(parents=True, exist_ok=True)
        export_results(results, args.output)
        plot_bode(results, args.output, reference, bandwidth, message)
        generate_report(results, args.output, args.log, dt, args.vdc, data, reference, bandwidth, message)
    except (OSError, ValueError, subprocess.TimeoutExpired) as exc:
        parser.exit(2, f"Error: {exc}\n")
    print(f"{len(valid)}/{len(results)} fitted points; {min(r['frequency_hz'] for r in results):g}-"
          f"{max(r['frequency_hz'] for r in results):g} Hz; logging rate ~ {1/dt:.1f} Hz")
    for key, label in [("mean_speed_rpm", "Mean speed / rpm"), ("input_offset_a", "Reference offset / A"),
                       ("input_amplitude_a", "Excitation amplitude / A")]:
        values = [r[key] for r in results if np.isfinite(r[key])]
        if values:
            print(f"{label}: {np.mean(values):.4g} (equal point weighting)")
    utilization = [r["voltage_utilization_percent"] for r in results if np.isfinite(r["voltage_utilization_percent"])]
    if utilization:
        print(f"Maximum voltage-command utilization: {max(utilization):.2f}% ({results[0]['voltage_kind']}, relative to Vdc/sqrt(3))")
    else:
        print("Voltage utilization unavailable: voltage commands or DC-link voltage not provided.")
    print(message)
    print("Frequency / Hz | Magnitude / dB | Phase / deg | Output residual / amplitude | Quality")
    for r in results:
        print(f"{r['frequency_hz']:14g} | {r['magnitude_db']:14.3f} | {r['phase_deg']:11.2f} | "
              f"{r['output_residual_relative']:27.3%} | {r['quality_status']}")
    print(f"Outputs: {args.output.resolve()}")
    print("Voltage commands are not measured terminal voltages; low utilization does not exclude other limiting.")


if __name__ == "__main__":
    main()
