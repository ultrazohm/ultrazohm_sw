from pathlib import Path
import re

import matplotlib


def use_headless_backend():
    try:
        from IPython import get_ipython

        ipython_shell = get_ipython()
        if ipython_shell is not None and hasattr(ipython_shell, "kernel"):
            return False
    except Exception:
        pass

    return True


if use_headless_backend():
    matplotlib.use("Agg")

import matplotlib.pyplot as plt


SIGNAL_NAME_OVERRIDES = [
    "ILA",
    "Interrupt_2L_max_min",
    "Interrupt_2L_min",
    "Interrupt_2L_max",
    "Interrupt_3L_start_center",
    "Interrupt_3L_start",
    "Interrupt_3L_center",
    "mux_axi_ip_1_interrupt_out_adc",
    "mux_axi_ip_2_select_out",
    "trigger_conversions_2",
    "delay_cycles",
    "delay_trigger_0_pulse_pending",
    "axi2tcm_write_done",
    "d4_out",
]

TIME_FACTORS_TO_NS = {
    "s": 1e9,
    "ms": 1e6,
    "us": 1e3,
    "ns": 1.0,
    "ps": 1e-3,
    "fs": 1e-6,
}


def find_data_file():
    candidate_paths = []
    if "__file__" in globals():
        candidate_paths.append(Path(__file__).with_name("iladata.vcd"))

    candidate_paths.extend(
        [
            Path("iladata.vcd"),
            Path("guide/rpu_software/interrupts/iladata.vcd"),
            Path("source/guide/rpu_software/interrupts/iladata.vcd"),
        ]
    )

    for base_path in [Path.cwd(), *Path.cwd().parents]:
        candidate_paths.append(base_path / "docs/source/guide/rpu_software/interrupts/iladata.vcd")
        candidate_paths.append(base_path / "source/guide/rpu_software/interrupts/iladata.vcd")

    for candidate in candidate_paths:
        resolved_candidate = candidate.resolve()
        if resolved_candidate.exists():
            return resolved_candidate

    raise FileNotFoundError("Could not locate iladata.vcd for the interrupts ILA plot")


DATA_FILE = find_data_file()


def parse_probe_name(reference_name):
    probe_name = reference_name.rsplit("/", maxsplit=1)[-1]
    match = re.match(r"(?P<name>[^\[]+)(?:\[(?P<msb>\d+):(?P<lsb>\d+)\])?$", probe_name)
    if not match:
        return {
            "name": probe_name,
            "display_name": probe_name,
            "width": 1,
        }

    name = match.group("name")
    msb = match.group("msb")
    lsb = match.group("lsb")
    if msb is None or lsb is None:
        return {
            "name": name,
            "display_name": name,
            "width": 1,
        }

    width = abs(int(msb) - int(lsb)) + 1
    return {
        "name": name,
        "display_name": probe_name,
        "width": width,
    }


def resolve_display_name(default_name, signal_index):
    if signal_index >= len(SIGNAL_NAME_OVERRIDES):
        return default_name

    override_name = SIGNAL_NAME_OVERRIDES[signal_index]
    if override_name is None:
        return default_name

    override_name = str(override_name).strip()
    if not override_name:
        return default_name

    return override_name


def parse_var_definition(line, signal_index):
    parts = line.split()
    width = int(parts[2])
    identifier = parts[3]
    reference_name = " ".join(parts[4:-1])
    signal = parse_probe_name(reference_name)
    signal["width"] = width
    signal["display_name"] = resolve_display_name(signal["display_name"], signal_index)
    signal["identifier"] = identifier
    signal["radix"] = "HEX" if width > 1 else "BINARY"
    return signal


def parse_timescale_to_ns(timescale_line):
    match = re.search(r"(?P<magnitude>\d+)\s*(?P<unit>fs|ps|ns|us|ms|s)", timescale_line)
    if not match:
        return 1.0

    magnitude = int(match.group("magnitude"))
    unit = match.group("unit")
    return magnitude * TIME_FACTORS_TO_NS[unit]


def normalize_vcd_bits(bit_string):
    return "".join("0" if character.lower() in {"x", "z"} else character for character in bit_string.strip())


def parse_value_change(line, current_values):
    if line[0] in "01xXzZ":
        current_values[line[1:]] = 1 if line[0] == "1" else 0
        return

    if line[0] in "bB":
        bit_string, identifier = line[1:].split(maxsplit=1)
        current_values[identifier] = int(normalize_vcd_bits(bit_string), 2)


def read_capture(path):
    signals = []
    current_values = {}
    timestamps = []
    snapshots = []
    current_time = None
    in_data_section = False
    timescale_to_ns = 1.0
    collect_timescale = False
    timescale_lines = []

    with path.open(encoding="utf-8") as vcd_file:
        for raw_line in vcd_file:
            line = raw_line.strip()
            if not line:
                continue

            if collect_timescale:
                if line == "$end":
                    timescale_to_ns = parse_timescale_to_ns(" ".join(timescale_lines))
                    collect_timescale = False
                else:
                    timescale_lines.append(line)
                continue

            if not in_data_section:
                if line == "$timescale":
                    collect_timescale = True
                    timescale_lines = []
                    continue

                if line.startswith("$var "):
                    signals.append(parse_var_definition(line, len(signals)))
                    continue

                if line == "$enddefinitions $end":
                    in_data_section = True
                continue

            if line.startswith("#"):
                if current_time is not None:
                    timestamps.append(current_time)
                    snapshots.append(current_values.copy())
                current_time = int(line[1:])
                continue

            if line.startswith("$"):
                continue

            parse_value_change(line, current_values)

    if current_time is not None:
        timestamps.append(current_time)
        snapshots.append(current_values.copy())

    if not timestamps:
        raise ValueError("No signal transitions were found in iladata.vcd")

    normalized_timestamps = [(timestamp - timestamps[0]) * timescale_to_ns for timestamp in timestamps]
    series = []
    for signal in signals:
        series.append(
            {
                "name": signal["name"],
                "display_name": signal["display_name"],
                "width": signal["width"],
                "radix": signal["radix"],
                "values": [snapshot.get(signal["identifier"], 0) for snapshot in snapshots],
            }
        )

    return normalized_timestamps, series


def style_axis(ax, samples, row_count):
    x_start = samples[0]
    x_end = samples[-1]
    if x_end == x_start:
        x_end = x_start + 1.0
    ax.set_xlim(x_start, x_end)
    ax.set_ylim(-0.4, row_count + 0.6)
    ax.set_yticks([])
    ax.grid(axis="x", color="#d9d9d9", linewidth=0.8)
    ax.spines[["left", "right", "top"]].set_visible(False)


def format_binary(value, width):
    return format(value, f"0{width}b")


def format_value(value, width, radix):
    if radix == "HEX":
        hex_digits = max(1, (width + 3) // 4)
        return format(value, f"0{hex_digits}X")

    if radix == "BINARY":
        return format_binary(value, width)

    if radix == "SIGNED":
        sign_bit = 1 << (width - 1)
        signed_value = value - (1 << width) if value & sign_bit else value
        return str(signed_value)

    return str(value)


def build_segments(samples, values):
    if not samples:
        return []

    segments = []
    start_index = 0
    for index in range(1, len(values)):
        if values[index] != values[index - 1]:
            segments.append((start_index, index - 1, values[index - 1]))
            start_index = index
    segments.append((start_index, len(values) - 1, values[-1]))
    return segments


def plot_single_bit_trace(ax, samples, values, row_index, label, color):
    baseline = row_index
    amplitude = 0.72
    x_span = max(samples[-1] - samples[0], 1.0)
    waveform = [baseline + amplitude * (1 if value else 0) for value in values]
    ax.step(samples, waveform, where="post", color=color, linewidth=1.6)
    ax.text(
        samples[0] - 0.01 * x_span,
        baseline + amplitude / 2,
        label,
        ha="right",
        va="center",
        fontsize=9,
        color="#222222",
    )


def plot_bus_trace(ax, samples, values, row_index, label, color, width, radix):
    baseline = row_index
    upper = baseline + 0.68
    lower = baseline + 0.12
    center = (upper + lower) / 2.0
    x_span = max(samples[-1] - samples[0], 1.0)
    label_threshold = max(x_span * 0.05, 0.2)
    segments = build_segments(samples, values)

    ax.text(
        samples[0] - 0.01 * x_span,
        center,
        label,
        ha="right",
        va="center",
        fontsize=9,
        color="#222222",
    )

    for segment_index, (start_index, end_index, value) in enumerate(segments):
        x_start = samples[start_index]
        x_end = samples[end_index]
        if end_index < len(samples) - 1:
            x_end = samples[end_index + 1]

        ax.hlines([upper, lower], x_start, x_end, colors=color, linewidth=1.2)

        span = x_end - x_start
        state_text = format_value(value, width, radix)
        if span >= label_threshold:
            ax.text(
                x_start + span / 2.0,
                center,
                state_text,
                ha="center",
                va="center",
                fontsize=8,
                color=color,
                bbox={"facecolor": "white", "edgecolor": "none", "pad": 0.6, "alpha": 0.85},
            )

        if segment_index == len(segments) - 1:
            continue

        transition_sample = samples[end_index + 1]
        previous_sample = samples[end_index]
        half_width = max((transition_sample - previous_sample) * 0.35, x_span * 0.004)
        left_x = max(x_start, transition_sample - half_width)
        right_x = transition_sample + half_width
        ax.plot([left_x, right_x], [upper, lower], color=color, linewidth=1.0)
        ax.plot([left_x, right_x], [lower, upper], color=color, linewidth=1.0)


def plot_trace(ax, samples, signal, row_index, color):
    if signal["width"] == 1:
        plot_single_bit_trace(ax, samples, signal["values"], row_index, signal["display_name"], color)
        return

    plot_bus_trace(
        ax,
        samples,
        signal["values"],
        row_index,
        signal["display_name"],
        color,
        signal["width"],
        signal["radix"],
    )


def create_figure():
    samples, series = read_capture(DATA_FILE)

    fig, ax = plt.subplots(figsize=(14, 10), layout="constrained")
    fig.supxlabel("Time [ns]")

    style_axis(ax, samples, len(series))
    color_cycle = plt.rcParams["axes.prop_cycle"].by_key()["color"]
    for row_index, signal in enumerate(reversed(series)):
        plot_trace(ax, samples, signal, row_index, color_cycle[row_index % len(color_cycle)])

    return fig, ax


fig, ax = create_figure()

if __name__ == "__main__":
    plt.show()