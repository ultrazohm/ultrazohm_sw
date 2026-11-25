"""Upload PT1 parameters in confirmed JavaScope bursts."""

import argparse
import json
import math
import socket
import struct
import subprocess
import sys
import time
from contextlib import suppress
from pathlib import Path

from update_parameters_prototype import (
    EXAMPLES,
    FEEDBACK,
    ROOT,
    network_info,
    parameter_fields,
    read_parameters_from_csv,
    validate_parameters,
)

COMMAND = struct.Struct("<If")
PARAMETER_BYTES = 4 * COMMAND.size
FEEDBACK_SLOTS = range(15, 20)
MAX_BURST_PARAMETERS = 48  # 192 of the A53 FIFO's 256 command slots.


class JavaScope:
    """Send raw commands and consume feedback on the same device connection."""

    def __init__(self, connection, mapping, timeout):
        self.connection = connection
        self.timeout = timeout
        samples = mapping["samples_per_packet"]
        channels = mapping["channels"]
        if channels != 20 or not 1 <= samples <= 4096:
            raise ValueError("Unsupported JavaScope frame geometry")
        self.frame = bytearray(4 + (channels + 2) * samples * 4)
        self.slow_ids = struct.Struct(f"<{samples}f")
        self.slow_ids_offset = len(self.frame) - self.slow_ids.size
        self.slow_count = len(mapping["slow_signals"])
        # Status, slow values, then each channel's samples in a contiguous block.
        self.feedback_offsets = [4 * ((slot + 1) * samples) for slot in FEEDBACK_SLOTS]

    def send(self, commands):
        self.connection.settimeout(self.timeout)
        self.connection.sendall(commands)

    def wait(self, predicate, description):
        deadline = time.monotonic() + self.timeout
        state = None
        try:
            while time.monotonic() < deadline:
                remaining = memoryview(self.frame)
                while remaining:
                    seconds = deadline - time.monotonic()
                    if seconds <= 0:
                        raise TimeoutError
                    self.connection.settimeout(seconds)
                    received = self.connection.recv_into(remaining)
                    if not received:
                        raise ConnectionError("Device closed the JavaScope connection")
                    remaining = remaining[received:]
                slow_ids = self.slow_ids.unpack_from(self.frame, self.slow_ids_offset)
                if not all(
                    0 <= index < self.slow_count and index.is_integer()
                    for index in slow_ids
                ):
                    raise RuntimeError("Invalid JavaScope frame or firmware mapping")
                state = {
                    name: struct.unpack_from("<f", self.frame, offset)[0]
                    for name, offset in zip(
                        FEEDBACK, self.feedback_offsets, strict=True
                    )
                }
                if predicate(state):
                    return
        except TimeoutError as error:
            raise TimeoutError(
                f"Timed out waiting for {description}: {state}"
            ) from error
        raise TimeoutError(f"Timed out waiting for {description}: {state}")


def upload(device, mapping, parameters, info, *, burst_size=32, timeout=5.0):
    """Send one burst at a time and wait for each R5 count before advancing."""
    if not 1 <= burst_size <= MAX_BURST_PARAMETERS:
        raise ValueError(f"Burst size must be 1 to {MAX_BURST_PARAMETERS} parameters")
    if not math.isfinite(timeout) or timeout <= 0:
        raise ValueError("Timeout must be positive")
    total = validate_parameters(parameters, info)
    target = {"dqn": 1, "ddpg": 2}[info["target"]]
    commands = mapping["commands"]
    variables = mapping["variables"]
    observables = mapping["observables"]
    stop = COMMAND.pack(commands["Stop"], 0.0)
    begin = b"".join(
        (
            stop,
            *(
                COMMAND.pack(200 + slot, observables[f"JSO_nn_update_{name}"])
                for slot, name in zip(FEEDBACK_SLOTS, FEEDBACK, strict=True)
            ),
            COMMAND.pack(variables["NN-Target"], target),
            COMMAND.pack(commands["My_Button_7"], 0.0),
        )
    )
    finish = COMMAND.pack(commands["My_Button_8"], 0.0)
    payload = b"".join(
        COMMAND.pack(variables[name], value)
        for fields in parameter_fields(parameters)
        for name, value in fields
    )

    def confirmed(state, count, active):
        if state["target"] != target or state["expected"] != total:
            return False
        if state["error"] != 0:
            raise RuntimeError(f"Firmware rejected parameter update: {state}")
        return state["active"] == active and state["received"] == count

    with socket.create_connection(device, timeout=timeout) as connection:
        connection.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        wire = JavaScope(connection, mapping, timeout)
        started = time.monotonic()
        try:
            wire.send(begin)
            # Ignore prior upload feedback until the new Begin has reset the count.
            wire.wait(
                lambda state: state["error"] == 0 and confirmed(state, 0, 1),
                "the R5 to enter update mode",
            )
            for first in range(0, total, burst_size):
                count = min(first + burst_size, total)
                wire.send(payload[first * PARAMETER_BYTES : count * PARAMETER_BYTES])
                wire.wait(
                    lambda state, count=count: confirmed(state, count, 1),
                    f"the R5 to accept {count}/{total} parameters",
                )
            wire.send(finish)
            wire.wait(
                lambda state: confirmed(state, total, 0), "R5 finish confirmation"
            )
        except BaseException:
            # A burst may have partially reached RAM. Abort without replaying it.
            with suppress(OSError):
                wire.send(stop)
            raise
        elapsed = time.monotonic() - started

    print(
        f"Uploaded {total} parameters in {elapsed:.3f} s. Controller remains stopped."
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("target", choices=("dqn", "ddpg"))
    parser.add_argument("directory", nargs="?", type=Path, help="custom CSV export")
    parser.add_argument("--device", default="192.168.1.233:1000", metavar="IP:PORT")
    parser.add_argument(
        "--burst-size",
        type=int,
        default=32,
        metavar="PARAMETERS",
        help=f"parameters per burst (1 to {MAX_BURST_PARAMETERS}, default 32)",
    )
    parser.add_argument("--timeout", type=float, default=5.0, metavar="SECONDS")
    args = parser.parse_args()
    host, separator, port = args.device.rpartition(":")
    if not separator or not host or not port.isdecimal() or not 1 <= int(port) <= 65535:
        parser.error("--device must be IP:PORT")
    directory = args.directory or EXAMPLES / f"pt1_{args.target}"
    parameters = read_parameters_from_csv(directory)
    mapping = subprocess.run(
        [sys.executable, "-m", "ultrazohm_cli", "channel-mapping", "--repo", str(ROOT)],
        capture_output=True,
        text=True,
        check=True,
    )
    upload(
        (host, int(port)),
        json.loads(mapping.stdout),
        parameters,
        network_info(args.target),
        burst_size=args.burst_size,
        timeout=args.timeout,
    )


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as error:
        sys.exit(error.stderr.strip() or str(error))
    except (OSError, KeyError, ValueError, RuntimeError, OverflowError) as error:
        sys.exit(str(error))
    except KeyboardInterrupt:
        sys.exit(
            "Upload interrupted. A complete re-upload or firmware restart is required."
        )
