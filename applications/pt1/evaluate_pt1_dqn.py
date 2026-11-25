"""Evaluate a trained network.pt locally; no UltraZohm connection is opened."""

import argparse
import csv
from pathlib import Path

import numpy as np
import torch

from train_pt1_dqn import make_network

REFERENCES = (-1.0, 0.0, 0.5, 0.1, 0.2, 1.0)


@torch.inference_mode()
def evaluate(network, references=REFERENCES):
    """Greedy PT1 rollout: gain 1, tau 2 ms, 10 kHz, 500 steps/episode."""
    network.eval()
    fraction = np.float32(-np.expm1(np.float32(-0.05)))
    for episode, reference in enumerate(references, 1):
        reference = np.float32(reference)
        y = np.float32(0)
        for step in range(500):
            obs = torch.from_numpy(np.array([y, reference], dtype=np.float32))
            q = network(obs)
            if not torch.isfinite(q).all():
                raise ValueError("Network produced non-finite Q values")
            action_index = int(q.argmax())  # first-index tie breaking, as on R5
            action = np.float32(action_index - 1)
            next_y = y + fraction * (action - y)
            error = reference - next_y
            yield {
                "time": ((episode - 1) * 500 + step) / 10000,
                "episode": episode, "episode_k": step,
                "y": float(y), "reference": float(reference),
                "action_index": action_index, "action_value": float(action),
                "reward": float(-error * error), "next_y": float(next_y),
                "done": int(step == 499),
                "q_action_minus_1": float(q[0]), "q_action_0": float(q[1]),
                "q_action_plus_1": float(q[2]),
            }
            y = next_y


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("checkpoint", type=Path, help="network.pt saved by the trainer")
    parser.add_argument("--output", type=Path, help="new CSV file; default: beside checkpoint")
    args = parser.parse_args()
    torch.set_num_threads(1)
    network = make_network()
    network.load_state_dict(torch.load(args.checkpoint, map_location="cpu", weights_only=True))
    rows = list(evaluate(network))
    output = args.output or args.checkpoint.with_name("host_evaluation.csv")
    with output.open("x", newline="") as stream:
        writer = csv.DictWriter(stream, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)
    for episode, reference in enumerate(REFERENCES, 1):
        samples = rows[(episode - 1) * 500:episode * 500]
        reward = sum(row["reward"] for row in samples)
        print(f"episode={episode} reference={reference:g} return={reward:.4f} "
              f"RMSE={np.sqrt(-reward / 500):.4f} final_y={samples[-1]['next_y']:.4f}")
    print(f"Saved {len(rows)} greedy evaluation steps to {output}")


if __name__ == "__main__":
    main()
