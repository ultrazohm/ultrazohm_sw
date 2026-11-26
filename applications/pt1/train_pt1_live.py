"""Build/program UltraZohm, train PT1 DQN, and display each round in DataViewer.

Run in the checkout's development environment (CLI and DataViewer must match
this checkout). Vitis/XSCT, JTAG and the board Ethernet connection are required.
The launcher owns one acquisition service; close other board clients first.
"""

import argparse
import copy
import importlib.util
import json
import random
import socket
import subprocess
import sys
import time
from collections import deque
from contextlib import closing, contextmanager
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
PLOTS = (
    ("y", "reference", "next_y"),
    ("action_value", "action_index"),
    ("reward",),
    ("epsilon",),
    ("episode", "episode_k"),
    ("nn_update_received", "nn_update_expected"),
)


def wait_until(check, description, timeout=30):
    """Poll until a check returns a truthy value, or raise on timeout."""
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        result = check()
        if result:
            return result
        time.sleep(0.05)
    raise TimeoutError(f"Timed out waiting for {description}")


def require_free_endpoint(endpoint):
    """Fail early if another process owns a requested local endpoint."""
    host, port = endpoint.rsplit(":", 1)
    with socket.socket() as probe:
        try:
            probe.bind((host, int(port)))
        except OSError as error:
            raise RuntimeError(
                f"Endpoint {endpoint} is busy; close its owner or choose another port"
            ) from error


def wait_for_viewer(factory, endpoint, process, log_path, timeout=60):
    """Probe read-only status with fresh credentials until the GUI is ready."""
    last_error = None

    def ready():
        nonlocal last_error
        if process.poll() is not None:
            raise RuntimeError(f"DataViewer exited; see {log_path}")
        # Client caches discovered credentials, including a missing token. Never
        # reuse a client that probed before the GUI published its credentials.
        with factory(endpoint, timeout=1) as probe:
            try:
                probe.status()
                return True
            except (OSError, EOFError) as error:
                last_error = error
            except RuntimeError as error:
                if getattr(error, "code", None) != "unauthorized":
                    raise
                last_error = error
        return False

    try:
        wait_until(ready, "DataViewer startup", timeout)
    except TimeoutError as error:
        raise TimeoutError(
            f"DataViewer startup failed at {endpoint}; last error: {last_error!r}. "
            f"See {log_path}"
        ) from error


def configure_viewer(viewer, channels):
    """Configure the live plots once, without altering them between rounds."""
    viewer.live_follow(True)
    view = viewer.live_view()
    required = {f"JSO_pt1_{name}" for name in channels}
    required.update({"JSO_nn_update_received", "JSO_nn_update_expected"})

    def ready():
        runs = viewer.list_runs(view=view)
        return next((r for r in runs if required <= set(r["signals"])), None)

    run = wait_until(ready, "live training channels")["handle"]
    viewer.set_grid(3, 2, view=view)
    for plot, names in enumerate(PLOTS, 1):
        viewer.clear_plot(plot, view=view)
        for name in names:
            signal = (
                f"JSO_{name}" if name.startswith("nn_update_") else f"JSO_pt1_{name}"
            )
            viewer.add_signal(plot, run, signal, view=view)
    viewer.live_time_depth(15.0)
    viewer.live_follow(True)


def completed_recording(client):
    """Return finalized recording metadata, propagating recording failures."""
    state = client.status()["logging"]["fast"]
    if state["phase"] == "failed":
        raise RuntimeError(f"Recording failed: {state}")
    return state if state["phase"] == "complete" else None


@contextmanager
def continuous_recording(uz, output):
    """Keep one native recording open for uploads, training and evaluation."""
    uz.start_logging()
    try:
        number = max(r["recording"] for r in uz.recordings() if r["stream"] == "fast")

        def ready():
            try:
                info = uz.data_info(recording=number)
            except RuntimeError as error:
                if str(error) != "recording is initializing":
                    raise
                return None
            return info if info["stop"] is not None else None

        wait_until(ready, "continuous recording startup")
        handle = uz.status()["logging"]["fast"]["handle"]
        recording = {"number": number, "handle": handle}
        (output / "recording.json").write_text(json.dumps(recording, indent=2) + "\n")
        yield recording
    finally:
        try:
            uz.stop()
        finally:
            uz.stop_logging()
            wait_until(lambda: completed_recording(uz), "recording finalization", 60)


def collect_replay(uz, recording):
    """Read only the next replay from the continuously growing recording."""
    import polars as pl

    number = recording["number"]
    start = position = uz.data_info(recording=number)["stop"]
    frames = []
    samples = 0
    deadline = time.monotonic() + 10.0
    try:
        uz.button(4)
        while time.monotonic() < deadline:
            status = uz.status()
            if not status["state"]["connected"]:
                raise RuntimeError("Device disconnected during PT1 replay")
            if status["logging"]["fast"]["phase"] != "recording":
                raise RuntimeError(
                    f"Continuous recording interrupted: {status['logging']['fast']}"
                )
            stop = min(uz.data_info(recording=number)["stop"], position + 10000)
            if stop > position:
                data = uz.read_range(position, stop, recording=number)
                if data.height != stop - position:
                    raise ValueError("Incomplete recording range during PT1 replay")
                position = stop
                active = data.filter(data["JSO_pt1_actor"] == 1)
                frames.append(active)
                samples += active.height
                if samples >= 3000:
                    data = pl.concat(frames).with_columns(
                        (
                            (pl.col("JSO_pt1_episode") - 1) * 500
                            + pl.col("JSO_pt1_episode_k")
                        ).alias("JSO_pt1_time"),
                        (pl.col("JSO_pt1_episode_k") == 499)
                        .cast(pl.Float32)
                        .alias("JSO_pt1_done"),
                    )
                    return data, {
                        "recording": recording["handle"],
                        "start": start,
                        "stop": position,
                    }
            time.sleep(0.02)
        raise TimeoutError(f"PT1 replay captured {samples}/3000 transitions")
    finally:
        uz.stop()


def evaluate_final(uz, output, recording):
    """Evaluate uploaded weights without updating the network or replay buffer."""
    from train_pt1_dqn import transitions

    uz.stop()
    uz.set_variable("DQN-Epsilon", 0.0)
    time.sleep(0.1)
    print("Evaluating final network: six episodes, epsilon=0, no learning", flush=True)
    data, segment = collect_replay(uz, recording)
    transitions(data, 0.0)  # Require all 3,000 intact transitions and zero exploration.
    active = data.filter(data["JSO_pt1_actor"] == 1)
    episodes = []
    for episode in range(1, 7):
        samples = active.filter(active["JSO_pt1_episode"] == episode)
        error = samples["JSO_pt1_reference"] - samples["JSO_pt1_next_y"]
        episodes.append(
            {
                "episode": episode,
                "reference": float(samples["JSO_pt1_reference"][0]),
                "return": float(samples["JSO_pt1_reward"].sum()),
                "rmse": float((error * error).mean() ** 0.5),
                "final_y": float(samples["JSO_pt1_next_y"][-1]),
            }
        )
    summary = {
        "epsilon": 0.0,
        "transitions": active.height,
        **segment,
        "episodes": episodes,
        "return": float(active["JSO_pt1_reward"].sum()),
    }
    (output / "evaluation.json").write_text(json.dumps(summary, indent=2) + "\n")
    print(f"Evaluation: {json.dumps(summary)}", flush=True)
    return summary


def upload_network(uz, network, info):
    """Upload weights without changing live channels or interrupting logging."""
    from train_pt1_dqn import parameters
    from update_parameters_prototype import uz_nn_update_weights

    uz_nn_update_weights(
        uz, parameters(network), info, command_interval=0.0002, assign_feedback=False
    )


def run_training(args, uz, viewer, viewer_process):
    """Collect and learn in rounds, then evaluate the final uploaded network."""
    import numpy as np
    import torch
    from train_pt1_dqn import CHANNELS, make_network, parameters, train, transitions
    from update_parameters_prototype import FEEDBACK, network_info

    # Derive redundant time/done fields from episode counters to fit all 19 slots.
    channels = (
        *(name for name in CHANNELS if name not in {"time", "done"}),
        "action_value",
    )
    info = network_info("dqn")
    if [(x["inputs"], x["neurons"]) for x in info["layers"]] != [
        (2, 32),
        (32, 32),
        (32, 3),
    ]:
        raise ValueError("Trainer requires the PT1 2-32-32-3 network")
    torch.set_num_threads(1)
    torch.manual_seed(args.seed)
    rng = random.Random(args.seed)
    network = make_network()
    target = copy.deepcopy(network)
    optimizer = torch.optim.Adam(network.parameters(), lr=1e-4)
    replay = deque(maxlen=100_000)
    updates = 0

    uz.stop()
    for slot, name in enumerate(channels, 1):
        uz.set_observable(f"JSO_pt1_{name}", slot)
    for slot, name in enumerate(FEEDBACK, 15):
        uz.set_observable(f"JSO_nn_update_{name}", slot)
    time.sleep(0.1)
    configure_viewer(viewer, channels)
    with continuous_recording(uz, args.output) as recording:
        for iteration in range(args.rounds):
            if viewer_process.poll() is not None:
                raise RuntimeError("DataViewer closed before training finished")
            epsilon = max(0.05, 1 - 0.95 * iteration / max(1, args.rounds * 0.1))
            print(f"Round {iteration + 1}/{args.rounds}: uploading weights", flush=True)
            upload_network(uz, network, info)
            uz.set_variable("DQN-Epsilon", epsilon)
            time.sleep(0.1)
            data, segment = collect_replay(uz, recording)
            replay.extend(transitions(data, epsilon))
            updates, loss = train(
                network, target, optimizer, replay, rng, args.gradient_steps, updates
            )
            torch.save(network.state_dict(), args.output / "network.pt")
            metrics = {
                "round": iteration + 1,
                "epsilon": epsilon,
                "loss": loss,
                "reward": data.filter(data["JSO_pt1_actor"] == 1)[
                    "JSO_pt1_reward"
                ].sum(),
                "transitions": len(replay),
                **segment,
            }
            with (args.output / "progress.jsonl").open("a", encoding="utf-8") as log:
                log.write(json.dumps(metrics) + "\n")
            print(json.dumps(metrics), flush=True)

        export = args.output / "export"
        export.mkdir()
        for number, layer in enumerate(parameters(network), 1):
            for kind, values in layer.items():
                np.savetxt(
                    export / f"layer{number}_{kind}.csv", [values], delimiter=","
                )
        if viewer_process.poll() is not None:
            raise RuntimeError("DataViewer closed before the final upload")
        upload_network(uz, network, info)
        evaluate_final(uz, args.output, recording)
        print(
            f"Training and evaluation complete; controller stopped. Results: {args.output}",
            flush=True,
        )


def parse_args(argv=None):
    """Parse launcher options and validate them before touching hardware."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--device", default="192.168.1.233:1000")
    parser.add_argument("--endpoint", default="127.0.0.1:19740")
    parser.add_argument("--viewer-endpoint", default="127.0.0.1:19741")
    parser.add_argument(
        "--xsct", help="Vitis XSCT executable; otherwise CLI preferences/PATH"
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=ROOT
        / "artifacts"
        / ("pt1-live-" + datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%S.%fZ")),
    )
    parser.add_argument("--rounds", type=int, default=20)
    parser.add_argument("--gradient-steps", type=int, default=3000)
    parser.add_argument("--seed", type=int, default=1)
    parser.add_argument(
        "--exit-after-training",
        action="store_true",
        help="close viewer/service after training",
    )
    args = parser.parse_args(argv)
    if args.rounds < 1 or args.gradient_steps < 1:
        parser.error("rounds and gradient-steps must be positive")
    if args.endpoint == args.viewer_endpoint:
        parser.error("acquisition and viewer endpoints must differ")

    return args


def check_dependencies():
    """Keep --help usable without optional training and GUI dependencies."""

    missing = [
        name
        for name in (
            "ultrazohm_cli",
            "ultrazohm_dataviewer",
            "torch",
            "numpy",
            "polars",
        )
        if importlib.util.find_spec(name) is None
    ]
    if missing:
        raise SystemExit(
            f"Missing packages in {sys.executable}: {', '.join(missing)}\n"
            "Build and enter the checkout development environment:\n"
            "  ./uz_developer build linux_wheels\n"
            "  ./uz_developer shell\n"
            '  uv pip install --python "$(command -v python)" -r applications/pt1/requirements.txt\n'
            "Then run this script again. The development shell uses a separate\n"
            "cached environment by default, not the repository .venv.\n"
        )

    # Fail before programming if learner dependencies are missing.
    import train_pt1_dqn  # noqa: F401


def attach_viewer(viewer, endpoint):
    """Wait for repository preparation before attaching to acquisition."""
    from ultrazohm_dataviewer import ViewerError

    def attach():
        try:
            return viewer.live_attach(endpoint)
        except ViewerError as error:
            # Only this pre-dispatch rejection is safe to retry.
            if "root directory preparation" not in str(error):
                raise
            return None

    wait_until(attach, "viewer repository preparation", 60)


@contextmanager
def open_viewer(args, viewer_args):
    """Own the viewer process and connection, including startup-failure cleanup."""
    from ultrazohm_dataviewer import Client

    log_path = args.output / "dataviewer.log"
    with log_path.open("w", encoding="utf-8") as log:
        process = subprocess.Popen(
            [sys.executable, "-u", "-m", "ultrazohm_dataviewer", *viewer_args],
            cwd=ROOT,
            stdout=log,
            stderr=subprocess.STDOUT,
        )
        try:
            wait_for_viewer(Client, args.viewer_endpoint, process, log_path)
            with Client(args.viewer_endpoint, timeout=30) as viewer:
                attach_viewer(viewer, args.endpoint)
                yield viewer, process
        finally:
            if process.poll() is None:
                process.terminate()
                try:
                    process.wait(timeout=5)
                except subprocess.TimeoutExpired:
                    process.kill()
                    process.wait()


def main(argv=None):
    """Prepare the run, program the board, and manage the live training session."""
    args = parse_args(argv)
    check_dependencies()

    from ultrazohm_cli import Acquisition, Client
    from ultrazohm_dataviewer.cli import parser as viewer_parser

    viewer_args = [
        "--endpoint",
        args.viewer_endpoint,
        "gui",
        "--live",
        "--live-repo",
        str(ROOT),
    ]
    # Reject an older installed viewer before building/programming the board.
    viewer_parser().parse_args(viewer_args)

    require_free_endpoint(args.endpoint)
    require_free_endpoint(args.viewer_endpoint)
    args.output = args.output.resolve()
    args.output.mkdir(parents=True, exist_ok=False)
    (args.output / "settings.json").write_text(
        json.dumps(vars(args), default=str, indent=2)
    )
    profile = args.output / "profile.json"
    profile.write_text(
        json.dumps(
            {
                "schema_version": 1,
                "name": "pt1-training-live",
                "sample_period_us": 100,
                "initial_channels": {},
            }
        )
    )
    # Flash owns the first board connection. Acquisition stops the device and
    # finalizes recordings on every exit, including failed startup or training.
    with Acquisition(
        repo=str(ROOT),
        endpoint=args.endpoint,
        xsct=args.xsct,
        profile=str(profile),
        output=str(args.output / "acquisition"),
    ), closing(Client(args.endpoint)) as uz:
        print("Building and programming UltraZohm through CLI flash…", flush=True)
        subprocess.run(
            [
                sys.executable,
                "-m",
                "ultrazohm_cli",
                "--endpoint",
                args.endpoint,
                "flash",
                "--device",
                args.device,
            ],
            check=True,
            cwd=ROOT,
        )
        with open_viewer(args, viewer_args) as (viewer, process):
            run_training(args, uz, viewer, process)
            if not args.exit_after_training:
                print(
                    "Close DataViewer or press Ctrl-C here to stop the service.",
                    flush=True,
                )
                while process.poll() is None:
                    time.sleep(0.2)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print(
            "Interrupted; acquisition cleanup requested device Stop.", file=sys.stderr
        )
        sys.exit(130)
