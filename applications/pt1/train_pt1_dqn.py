"""Minimal host DQN learner; the PT1 actor and plant run exclusively on R5.

Uses the workshop's network, reward, Adam learning rate and DQN target.
Collection and uploads are deliberately separated: no partially updated actor.
"""

import argparse
from collections import deque
import copy
import json
from pathlib import Path
import random
import subprocess
import sys
import time

import numpy as np
import torch
from torch import nn

from pt1_recording import ROOT, wait_for_replay
from update_parameters_prototype import network_info, uz_nn_update_weights

CHANNELS = ("actor", "time", "episode", "episode_k", "y", "reference",
            "action_index", "reward", "next_y", "done", "epsilon",
            "isr_0", "isr_1", "isr_2", "isr_3")


def make_network():
    return nn.Sequential(nn.Linear(2, 32), nn.ReLU(), nn.Linear(32, 32),
                         nn.ReLU(), nn.Linear(32, 3))


def parameters(network):
    # uz_nn stores [input, neuron], PyTorch Linear stores [neuron, input].
    return [{"weights": layer.weight.detach().numpy().T.flatten().tolist(),
             "bias": layer.bias.detach().numpy().tolist()}
            for layer in network if isinstance(layer, nn.Linear)]


def transitions(data, epsilon):
    """Require one intact batch; never silently train on missing/repeated ticks."""
    rows = data.filter(data["JSO_pt1_actor"] == 1).select(
        [f"JSO_pt1_{name}" for name in CHANNELS]).to_numpy()
    if rows.shape != (3000, len(CHANNELS)) or not np.isfinite(rows).all():
        raise ValueError("Expected 3,000 finite DQN transitions; check logging and ISR rate")
    col = {name: rows[:, i] for i, name in enumerate(CHANNELS)}
    for name, expected in (("time", np.arange(3000)),
                           ("episode", np.arange(3000) // 500 + 1),
                           ("episode_k", np.arange(3000) % 500),
                           ("done", (np.arange(3000) % 500 == 499).astype(float))):
        if not np.array_equal(col[name], expected):
            raise ValueError(f"Invalid {name}: missing, duplicate or reordered samples")
    counter = np.zeros(3000, dtype=np.uint64)
    for i in range(4):
        limb = col[f"isr_{i}"]
        if not np.all((limb >= 0) & (limb <= 65535) & (limb == np.floor(limb))):
            raise ValueError("Invalid ISR counter limb")
        counter |= limb.astype(np.uint64) << (16 * i)
    if not np.all(np.diff(counter) == 1):
        raise ValueError("ISR counter gap: collection must log every ISR")
    if not np.all(col["epsilon"] == np.float32(epsilon)):
        raise ValueError("Firmware did not accept DQN-Epsilon")
    actions = col["action_index"]
    if not np.all(np.isin(actions, [0, 1, 2])):
        raise ValueError("Invalid DQN action index")
    within_episode = col["done"][:-1] == 0
    if not np.array_equal(col["next_y"][:-1][within_episode], col["y"][1:][within_episode]):
        raise ValueError("Next observation does not match the next ISR")
    obs = np.column_stack((col["y"], col["reference"])).astype(np.float32)
    next_obs = np.column_stack((col["next_y"], col["reference"])).astype(np.float32)
    # These are time-limit truncations (as in workshop/env_pt1.py), not terminal
    # plant states. Bootstrap from the logged final observation, never the reset.
    return list(zip(obs, actions.astype(np.int64), col["reward"].astype(np.float32), next_obs))


def train(network, target, optimizer, replay, rng, steps, updates):
    population = list(replay)
    for _ in range(steps):
        obs, action, reward, next_obs = map(np.asarray, zip(*rng.sample(population, 32)))
        with torch.no_grad():
            expected = torch.from_numpy(reward) + 0.99 * target(torch.from_numpy(next_obs)).max(1).values
        predicted = network(torch.from_numpy(obs)).gather(1, torch.from_numpy(action)[:, None]).squeeze(1)
        loss = nn.functional.smooth_l1_loss(predicted, expected)
        optimizer.zero_grad()
        loss.backward()
        nn.utils.clip_grad_norm_(network.parameters(), 10.0)
        optimizer.step()
        updates += 1
        if updates % 10 == 0:
            target.load_state_dict(network.state_dict())
    return updates, float(loss.detach())


def main():
    from ultrazohm_cli import Acquisition, Client

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, required=True, help="new run directory")
    parser.add_argument("--device", default="192.168.1.233:1000")
    parser.add_argument("--endpoint", default="127.0.0.1:19740")
    parser.add_argument("--rounds", type=int, default=20)
    parser.add_argument("--gradient-steps", type=int, default=3000)
    parser.add_argument("--seed", type=int, default=1)
    args = parser.parse_args()
    if args.rounds < 1 or args.gradient_steps < 1:
        parser.error("rounds and gradient-steps must be positive")
    torch.set_num_threads(1)
    torch.manual_seed(args.seed)
    rng = random.Random(args.seed)
    network = make_network()
    target = copy.deepcopy(network)
    optimizer = torch.optim.Adam(network.parameters(), lr=1e-4)
    replay = deque(maxlen=100_000)
    info = network_info("dqn")
    if [(x["inputs"], x["neurons"]) for x in info["layers"]] != [(2, 32), (32, 32), (32, 3)]:
        raise ValueError("This trainer requires the workshop 2-32-32-3 network")
    contract = subprocess.run(
        [sys.executable, "-m", "ultrazohm_cli", "channel-mapping", "--repo", str(ROOT)],
        check=True, capture_output=True, text=True).stdout
    mapping_data = json.loads(contract)
    for name in CHANNELS:
        if f"JSO_pt1_{name}" not in mapping_data["observables"]:
            raise ValueError(f"Missing firmware channel: {name}")
    args.output.mkdir(parents=True, exist_ok=False)
    mapping = args.output.resolve() / "channel_mapping.json"
    mapping.write_text(contract)
    (args.output / "settings.json").write_text(json.dumps(vars(args), default=str, indent=2))
    profile = args.output.resolve() / "profile.json"
    profile.write_text(json.dumps({"schema_version": 1, "name": "pt1-training",
                                   "sample_period_us": 100, "initial_channels": {}}))
    updates = 0
    for iteration in range(args.rounds):
        epsilon = max(0.05, 1.0 - 0.95 * iteration / max(1, args.rounds * 0.1))
        destination = args.output.resolve() / f"round-{iteration:04d}"
        with Acquisition(device=args.device, endpoint=args.endpoint,
                         channel_mapping=str(mapping), profile=str(profile), output=str(destination)) as acquisition:
            uz = Client(args.endpoint)
            try:
                uz_nn_update_weights(uz, parameters(network), info)
                for slot, name in enumerate(CHANNELS, 1):
                    uz.set_observable(f"JSO_pt1_{name}", slot)
                uz.set_variable("DQN-Epsilon", epsilon)
                time.sleep(0.1)
                uz.start_logging()
                uz.button(4)
                wait_for_replay(uz, 1, 10.0)
                uz.stop_logging()
            finally:
                uz.close()
        data = acquisition.read_recording()
        replay.extend(transitions(data, epsilon))
        updates, loss = train(network, target, optimizer, replay, rng, args.gradient_steps, updates)
        torch.save(network.state_dict(), args.output / "network.pt")
        print(f"round={iteration} transitions={len(replay)} epsilon={epsilon:.3f} "
              f"reward={data.filter(data['JSO_pt1_actor'] == 1)['JSO_pt1_reward'].sum():.3f} "
              f"loss={loss:.6f}", flush=True)
    # Export a directly reusable upload, and deploy the final trained actor.
    export = args.output / "export"
    export.mkdir()
    for number, layer in enumerate(parameters(network), 1):
        for kind, values in layer.items():
            np.savetxt(export / f"layer{number}_{kind}.csv", [values], delimiter=",")
    with Acquisition(device=args.device, endpoint=args.endpoint, channel_mapping=str(mapping)):
        uz = Client(args.endpoint)
        try:
            uz_nn_update_weights(uz, parameters(network), info)
            uz.set_variable("DQN-Epsilon", 0.0)
            time.sleep(0.1)
        finally:
            uz.close()
    print(f"Trained actor uploaded and stopped. CSV parameters: {export}")


if __name__ == "__main__":
    main()
