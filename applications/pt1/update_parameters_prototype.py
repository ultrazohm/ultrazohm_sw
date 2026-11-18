"""Upload PT1 neural-network weights and biases using the released CLI API.

Example:
    python applications/pt1/update_parameters_prototype.py dqn path/to/export
The board must run UZ_PT1_REPLAY=1 firmware. Close other device clients first.
"""

import argparse
import csv
import json
import math
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import time

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
                values = [float(value) for row in csv.reader(source)
                          for value in row if value.strip()]
            # Validate representability before stopping the controller.
            values = [struct.unpack("<f", struct.pack("<f", value))[0] for value in values]
            if not values or not all(math.isfinite(value) for value in values):
                raise ValueError(f"Layer {number} {kind} must contain finite float32 values")
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
        "layers": [{"inputs": layer["weights"]["shape"][0],
                    "neurons": layer["weights"]["shape"][1]}
                   for layer in manifest["layers"]],
    }


def feedback(uz):
    if uz.data_info()["stop"] in (None, 0):
        return None
    row = uz.tail(1, channels=[f"JSO_nn_update_{name}" for name in FEEDBACK]).row(0, named=True)
    return {name: row[f"JSO_nn_update_{name}"] for name in FEEDBACK}


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


def uz_nn_update_weights(uz, parameters, info, *, command_interval=0.002, timeout=5.0):
    """Pause, upload a complete parameter set, finish, and leave control stopped.

    uz is an ultrazohm_cli.Client connected to an acquisition service.
    info contains target ('dqn'/'ddpg') and layers with inputs and neurons.
    Recording must be idle so feedback channel assignments can be changed.
    """
    if not math.isfinite(command_interval) or command_interval < 0.001:
        raise ValueError("command_interval must be at least 0.001 seconds")
    if not math.isfinite(timeout) or timeout <= 0:
        raise ValueError("timeout must be positive")
    target = info["target"]
    if target not in ("dqn", "ddpg") or info != network_info(target):
        raise ValueError("info must match the compiled PT1 target dimensions")
    if len(parameters) != len(info["layers"]):
        raise ValueError("Incorrect number of layers")
    total = 0
    for layer, shape in zip(parameters, info["layers"]):
        for kind, count in (("weights", shape["inputs"] * shape["neurons"]),
                            ("bias", shape["neurons"])):
            if len(layer[kind]) != count:
                raise ValueError(f"Expected {count} {kind} entries in layer {shape}")
            for value in layer[kind]:
                if not math.isfinite(struct.unpack("<f", struct.pack("<f", value))[0]):
                    raise ValueError("Parameters must be finite float32 values")
            total += count

    # These slots follow the fourteen PT1 replay signals.
    for slot, name in enumerate(FEEDBACK, 15):
        uz.set_observable(f"JSO_nn_update_{name}", slot)
    target_id = {"dqn": 1, "ddpg": 2}[target]
    try:
        uz.stop()
        time.sleep(0.1)
        uz.set_variable("NN-Target", target_id)
        time.sleep(0.05)
        uz.button(7)
        # Begin clears any error left by a previous aborted upload.
        deadline = time.monotonic() + timeout
        while True:
            state = feedback(uz)
            if state and state["active"] == 1 and state["received"] == 0 and state["error"] == 0:
                if state["target"] != target_id or state["expected"] != total:
                    raise RuntimeError(f"Board target or parameter count differs: {state}")
                break
            if time.monotonic() >= deadline:
                raise TimeoutError(f"Board did not enter update mode: {state}")
            time.sleep(0.02)

        sent = 0
        for layer_index, layer in enumerate(parameters):
            for kind_id, kind in enumerate(("weights", "bias")):
                for index, value in enumerate(layer[kind]):
                    for name, field in (("NN-Layer", layer_index), ("NN-Type", kind_id),
                                        ("NN-Index", index), ("NN-Value", value)):
                        uz.set_variable(name, field)
                        time.sleep(command_interval)
                    sent += 1
                    if sent % 32 == 0 or sent == total:
                        wait_feedback(uz, lambda state: state["received"] == sent, timeout)
                        print(f"Received {sent}/{total} parameters", flush=True)
        uz.button(8)
        result = wait_feedback(
            uz, lambda state: state["active"] == 0 and state["received"] == total, timeout)
        print("Parameter upload finished; controller remains stopped.", flush=True)
        return result
    except BaseException:
        uz.stop()
        raise


def main():
    import ultrazohm_cli

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("target", choices=("dqn", "ddpg"))
    parser.add_argument("directory", type=Path, help="export directory containing layer CSV files")
    parser.add_argument("--device", default="192.168.1.233:1000")
    parser.add_argument("--endpoint", default="127.0.0.1:19740")
    parser.add_argument("--command-interval", type=float, default=0.002)
    args = parser.parse_args()
    parameters = read_parameters_from_csv(args.directory)
    info = network_info(args.target)
    result = subprocess.run(
        [sys.executable, "-m", "ultrazohm_cli", "channel-mapping", "--repo", str(ROOT)],
        capture_output=True, text=True, check=True)
    with tempfile.TemporaryDirectory(prefix="pt1-upload-") as temporary:
        mapping = Path(temporary) / "mapping.json"
        mapping.write_text(result.stdout, encoding="utf-8")
        with ultrazohm_cli.Acquisition(
            device=args.device, endpoint=args.endpoint, channel_mapping=str(mapping)
        ):
            uz = ultrazohm_cli.Client(args.endpoint)
            try:
                uz_nn_update_weights(uz, parameters, info, command_interval=args.command_interval)
            finally:
                uz.close()


if __name__ == "__main__":
    try:
        main()
    except (OSError, ValueError, RuntimeError, OverflowError, subprocess.CalledProcessError) as error:
        sys.exit(str(error))
    except KeyboardInterrupt:
        sys.exit("Upload interrupted. A complete re-upload or firmware restart is required.")
