"""Shared acquisition setup for the separate PT1 DQN and DDPG scripts."""

import argparse
from datetime import datetime, timezone
from importlib.metadata import version
import json
from pathlib import Path
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[2]
CHANNELS = (
    "actor", "time", "episode", "episode_k", "y", "reference", "error",
    "action_value", "reward", "action_index", "q_action_minus_1",
    "q_action_0", "q_action_plus_1", "done",
)


def wait_for_replay(client, actor_id, timeout, recording=1):
    """Read recording history so a short replay cannot be missed between polls."""
    deadline = time.monotonic() + timeout
    cursor = None
    samples = 0
    while time.monotonic() < deadline:
        status = client.status()
        if not status["state"]["connected"]:
            raise RuntimeError("Device disconnected during PT1 replay")
        phase = status["logging"]["fast"]["phase"]
        if phase == "failed":
            raise RuntimeError(f"Recording failed: {status['logging']['fast']}")
        try:
            page = client.read_since(cursor, recording=recording, limit=10000)
        except RuntimeError as error:
            # start_logging installs the recording route before its background
            # writer has initialized readable history. Its phase can already be
            # "recording" here. Retry only this transient error, within deadline.
            if str(error) != "recording is initializing":
                raise
            time.sleep(0.02)
            continue
        cursor = page.cursor
        active = page.data.filter(page.data["JSO_pt1_actor"] == actor_id)
        samples += active.height
        if samples >= 3000:
            # Retain a short idle tail and allow the firmware to finish its last tick.
            time.sleep(0.05)
            return
        time.sleep(0.02)
    raise TimeoutError(
        f"PT1 actor {actor_id}: captured {samples}/3000 samples within {timeout:g}s. "
        "Check UZ_PT1_REPLAY=1, the deployed firmware, and the 10 kHz ISR."
    )


def run_actor(actor, number, args, mapping, profile, output):
    from ultrazohm_cli import Acquisition, Client

    actor_id = number - 3
    destination = output / "recording"
    print(f"Running PT1 {actor.upper()}; recording to {destination}", flush=True)
    with Acquisition(
        device=args.device, endpoint=args.endpoint, output=str(destination),
        channel_mapping=str(mapping), profile=str(profile), format="csv",
    ) as acquisition:
        client = Client(args.endpoint)
        try:
            client.stop()
            # Initial observable assignments and Stop have no device acknowledgment.
            # Allow their responses to appear before recording the replay.
            time.sleep(0.1)
            client.start_logging()
            client.button(number)
            wait_for_replay(client, actor_id, args.timeout)
            client.stop_logging()
        finally:
            # Acquisition's context manager sends Stop and waits for finalization,
            # including when recording, command execution, or a read fails.
            client.close()

    data = acquisition.read_recording()
    # Keep a semicolon capture alongside the native Parquet/CSV recordings.
    capture = destination / f"pt1_{actor}_capture.csv"
    data.write_csv(capture, separator=";")
    print(f"Recorded {capture}", flush=True)


def main(actor):
    parser = argparse.ArgumentParser(description=f"Record a PT1 {actor.upper()} replay on UltraZohm.")
    parser.add_argument("--device", default="192.168.1.233:1000")
    parser.add_argument("--endpoint", default="127.0.0.1:19740")
    parser.add_argument("--output", type=Path,
                        help="new output directory (default: artifacts/pt1-hardware/<actor>-<UTC timestamp>)")
    parser.add_argument("--timeout", type=float, default=10.0)
    args = parser.parse_args()
    if args.timeout <= 0:
        parser.error("--timeout must be positive")

    # Use the installed release's CLI to interpret this checkout's current headers.
    result = subprocess.run(
        [sys.executable, "-m", "ultrazohm_cli", "channel-mapping", "--repo", str(ROOT)],
        check=True, capture_output=True, text=True,
    )
    contract = json.loads(result.stdout)
    for name in CHANNELS:
        if f"JSO_pt1_{name}" not in contract["observables"]:
            raise ValueError(f"Firmware mapping is missing JSO_pt1_{name}")

    timestamp = datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%S.%fZ")
    output = (args.output or ROOT / "artifacts/pt1-hardware" / f"{actor}-{timestamp}").resolve()
    output.mkdir(parents=True, exist_ok=False)
    mapping = output / "channel_mapping.json"
    mapping.write_text(json.dumps(contract, indent=2) + "\n", encoding="utf-8")
    profile = output / "pt1_profile.json"
    profile.write_text(json.dumps({
        "schema_version": 1, "name": "pt1-hardware", "sample_period_us": 100,
        "initial_channels": {
            str(slot): f"JSO_pt1_{name}" for slot, name in enumerate(CHANNELS, 1)
        },
    }, indent=2) + "\n", encoding="utf-8")
    print(f"Using installed ultrazohm_cli {version('ultrazohm_cli')}", flush=True)
    print(f"Session files: {output}", flush=True)

    run_actor(actor, {"dqn": 4, "ddpg": 5}[actor], args, mapping, profile, output)


def run(actor):
    try:
        main(actor)
    except (OSError, RuntimeError, ValueError, subprocess.CalledProcessError) as error:
        sys.exit(str(error))
    except KeyboardInterrupt:
        sys.exit("Interrupted; acquisition cleanup requested device Stop.")
