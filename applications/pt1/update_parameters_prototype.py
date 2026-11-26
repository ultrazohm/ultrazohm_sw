"""Upload PT1 neural-network weights and biases and report the upload time.

Example:
    python applications/pt1/update_parameters_prototype.py dqn
The board must run UZ_PT1_REPLAY=1 firmware. Close other device clients first.
"""

import argparse
import csv
import json
import math
import struct
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
EXAMPLES = ROOT / "vitis/software/Baremetal/src/uz/uz_exported_actor/examples"
FEEDBACK = ("active", "received", "error", "target", "expected")


def read_parameters_from_csv(directory):
    """Read layerN_weights.csv and layerN_bias.csv in exporter storage order."""
    directory = Path(directory)
    layers = []
    number = 1
    while (directory / f"layer{number}_weights.csv").is_file():
        parameters = {}
        for kind in ("weights", "bias"):
            with (directory / f"layer{number}_{kind}.csv").open(newline="") as source:
                values = [
                    float(value)
                    for row in csv.reader(source)
                    for value in row
                    if value.strip()
                ]
            # Validate representability before stopping the controller.
            values = [
                struct.unpack("<f", struct.pack("<f", value))[0] for value in values
            ]
            if not values or not all(math.isfinite(value) for value in values):
                raise ValueError(
                    f"Layer {number} {kind} must contain finite float32 values"
                )
            parameters[kind] = values
        layers.append(parameters)
        number += 1
    if not layers:
        raise ValueError(f"No layer1_weights.csv found in {directory}")
    return layers


def network_info(target):
    """Dimensions of this checkout's compiled PT1 target."""
    manifest = json.loads((EXAMPLES / f"pt1_{target}/manifest.json").read_text())
    return {
        "target": target,
        "layers": [
            {
                "inputs": layer["weights"]["shape"][0],
                "neurons": layer["weights"]["shape"][1],
            }
            for layer in manifest["layers"]
        ],
    }


def feedback(uz):
    info = uz.data_info()
    if info["start"] is None or info["stop"] == info["start"]:
        return None
    row = uz.tail(1, channels=[f"JSO_nn_update_{name}" for name in FEEDBACK]).row(
        0, named=True
    )
    state = {name: row[f"JSO_nn_update_{name}"] for name in FEEDBACK}
    # The live buffer can still contain samples from before a channel assignment.
    if any(value is None or not math.isfinite(value) for value in state.values()):
        return None
    return state


def wait_feedback(uz, predicate, timeout):
    deadline = time.monotonic() + timeout
    last = None
    while time.monotonic() < deadline:
        status = uz.status()
        if not status["state"]["connected"]:
            raise RuntimeError("Device disconnected during parameter upload")
        last = feedback(uz)
        if last is not None:
            if last["error"] != 0:
                raise RuntimeError(f"Firmware rejected parameter update: {last}")
            if predicate(last):
                return last
        time.sleep(0.02)
    raise TimeoutError(f"Timed out waiting for parameter update feedback: {last}")


def validate_parameters(parameters, info):
    """Check the complete set against the target before sending Stop."""
    target = info["target"]
    if target not in ("dqn", "ddpg") or info != network_info(target):
        raise ValueError("info must match the compiled PT1 target dimensions")
    if len(parameters) != len(info["layers"]):
        raise ValueError("Incorrect number of layers")
    total = 0
    for layer, shape in zip(parameters, info["layers"], strict=True):
        for kind, count in (
            ("weights", shape["inputs"] * shape["neurons"]),
            ("bias", shape["neurons"]),
        ):
            if len(layer[kind]) != count:
                raise ValueError(f"Expected {count} {kind} entries in layer {shape}")
            for value in layer[kind]:
                if not math.isfinite(struct.unpack("<f", struct.pack("<f", value))[0]):
                    raise ValueError("Parameters must be finite float32 values")
            total += count
    return total


def parameter_fields(parameters):
    """Yield the four ordered fields for each parameter in firmware order."""
    for layer_index, layer in enumerate(parameters):
        for kind_id, kind in enumerate(("weights", "bias")):
            for index, value in enumerate(layer[kind]):
                yield (
                    ("NN-Layer", layer_index),
                    ("NN-Type", kind_id),
                    ("NN-Index", index),
                    ("NN-Value", value),
                )


def uz_nn_update_weights(
    uz,
    parameters,
    info,
    *,
    command_interval=0.002,
    timeout=5.0,
    assign_feedback=True,
    timings=None,
):
    """Pause, upload a complete parameter set, finish, and leave control stopped.

    uz is an ultrazohm_cli.Client connected to an acquisition service.
    info contains target ('dqn'/'ddpg') and layers with inputs and neurons.
    Recording must be idle when assign_feedback is True. Pass False when all
    feedback channels are already assigned, to preserve a continuous recording.
    If timings is a dict, fill it with host wall-clock seconds by upload phase.
    Validation and feedback channel assignment are outside the measured interval.
    """
    if not math.isfinite(command_interval) or command_interval < 0.0001:
        raise ValueError("command_interval must be at least 0.0001 seconds")
    if not math.isfinite(timeout) or timeout <= 0:
        raise ValueError("timeout must be positive")
    total = validate_parameters(parameters, info)

    # These slots follow the fourteen PT1 replay signals.
    if assign_feedback:
        for slot, name in enumerate(FEEDBACK, 15):
            uz.set_observable(f"JSO_nn_update_{name}", slot)
    target_id = {"dqn": 1, "ddpg": 2}[info["target"]]
    buckets = {}

    def measured(name, function, *args):
        if timings is None:
            return function(*args)
        before = time.perf_counter()
        try:
            return function(*args)
        finally:
            buckets[name] = buckets.get(name, 0.0) + time.perf_counter() - before

    try:
        started = time.perf_counter()
        measured("startup_commands", uz.stop)
        measured("startup_sleeps", time.sleep, 0.1)
        measured("startup_commands", uz.set_variable, "NN-Target", target_id)
        measured("startup_sleeps", time.sleep, 0.05)
        measured("startup_commands", uz.button, 7)
        begin_wait = time.perf_counter()
        # Begin clears any error left by a previous aborted upload.
        deadline = time.monotonic() + timeout
        while True:
            state = feedback(uz)
            if (
                state
                and state["active"] == 1
                and state["received"] == 0
                and state["error"] == 0
            ):
                if state["target"] != target_id or state["expected"] != total:
                    raise RuntimeError(
                        f"Board target or parameter count differs: {state}"
                    )
                break
            if time.monotonic() >= deadline:
                raise TimeoutError(f"Board did not enter update mode: {state}")
            time.sleep(0.02)

        buckets["begin_confirmation"] = time.perf_counter() - begin_wait

        for sent, fields in enumerate(parameter_fields(parameters), 1):
            for name, field in fields:
                measured("parameter_commands", uz.set_variable, name, field)
                measured("parameter_sleeps", time.sleep, command_interval)
            if sent % 32 == 0 or sent == total:
                measured(
                    "receipt_checks",
                    wait_feedback,
                    uz,
                    lambda state, sent=sent: state["received"] == sent,
                    timeout,
                )
                print(f"Received {sent}/{total} parameters", flush=True)
        measured("finish_command", uz.button, 8)
        result = measured(
            "finish_confirmation",
            wait_feedback,
            uz,
            lambda state: state["active"] == 0 and state["received"] == total,
            timeout,
        )
        elapsed = time.perf_counter() - started
        if timings is not None:
            timings.update(buckets)
            timings["other"] = elapsed - sum(buckets.values())
            timings["total"] = elapsed
        print(
            f"Uploaded {total} parameters in {elapsed:.3f} s. "
            "Controller remains stopped.",
            flush=True,
        )
        return result
    except BaseException:
        uz.stop()
        raise


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("target", choices=("dqn", "ddpg"))
    parser.add_argument(
        "directory",
        nargs="?",
        type=Path,
        help=(
            "directory containing layer CSV files "
            "(defaults to the bundled export for the target)"
        ),
    )
    parser.add_argument("--device", default="192.168.1.233:1000")
    parser.add_argument("--endpoint", default="127.0.0.1:19740")
    parser.add_argument("--command-interval", type=float, default=0.002)
    args = parser.parse_args()
    directory = args.directory or EXAMPLES / f"pt1_{args.target}"
    parameters = read_parameters_from_csv(directory)
    info = network_info(args.target)

    from ultrazohm_cli import Acquisition, Client

    with Acquisition(device=args.device, endpoint=args.endpoint, repo=str(ROOT)):
        uz = Client(args.endpoint)
        try:
            uz_nn_update_weights(
                uz, parameters, info, command_interval=args.command_interval
            )
        finally:
            uz.close()


if __name__ == "__main__":
    try:
        main()
    except (
        OSError,
        ValueError,
        RuntimeError,
        OverflowError,
    ) as error:
        sys.exit(str(error))
    except KeyboardInterrupt:
        sys.exit(
            "Upload interrupted. A complete re-upload or firmware restart is required."
        )
