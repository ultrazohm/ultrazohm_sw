import csv
from pathlib import Path

import numpy as np
import torch
from stable_baselines3.common.callbacks import BaseCallback


FIELDNAMES = [
    "time",
    "episode",
    "episode_k",
    "y",
    "reference",
    "error",
    "action_index",
    "action_value",
    "reward",
    "q_action_minus_1",
    "q_action_0",
    "q_action_plus_1",
    "greedy_action_index",
    "greedy_action_value",
    "exploration_rate",
    "terminated",
    "truncated",
    "done",
]


def get_q_values(model, obs):
    with torch.no_grad():
        obs_tensor = model.policy.obs_to_tensor(obs)[0]
        return model.q_net(obs_tensor).cpu().numpy()[0]


class CsvStepWriter:
    def __init__(self, log_dir, action_values, file_name):
        self.log_dir = Path(log_dir)
        self.log_dir.mkdir(parents=True, exist_ok=True)
        self.action_values = np.asarray(action_values, dtype=np.float32)
        self.path = self.log_dir / file_name
        self.file = None
        self.writer = None

    def open(self):
        self.file = self.path.open("w", newline="")
        self.writer = csv.DictWriter(self.file, fieldnames=FIELDNAMES)
        self.writer.writeheader()

    def close(self):
        if self.file is not None:
            self.file.close()
            self.file = None
            self.writer = None

    def write_step(
        self,
        time,
        episode,
        episode_k,
        obs,
        action_index,
        action_value,
        reward,
        q_values,
        exploration_rate,
        terminated,
        truncated,
        done,
    ):
        y = float(obs[0])
        reference = float(obs[1])
        error = reference - y
        greedy_action_index = int(np.argmax(q_values))

        self.writer.writerow(
            {
                "time": int(time),
                "episode": int(episode),
                "episode_k": int(episode_k),
                "y": y,
                "reference": reference,
                "error": error,
                "action_index": int(action_index),
                "action_value": float(action_value),
                "reward": float(reward),
                "q_action_minus_1": float(q_values[0]),
                "q_action_0": float(q_values[1]),
                "q_action_plus_1": float(q_values[2]),
                "greedy_action_index": greedy_action_index,
                "greedy_action_value": float(self.action_values[greedy_action_index]),
                "exploration_rate": float(exploration_rate),
                "terminated": float(terminated),
                "truncated": float(truncated),
                "done": float(done),
            }
        )


class EpisodeCsvLogger(BaseCallback):
    def __init__(self, log_dir, action_values, file_name="training_log.csv"):
        super().__init__()
        self.csv = CsvStepWriter(log_dir, action_values, file_name)
        self.episode = 1

    def _on_training_start(self):
        self.csv.open()

    def _on_step(self):
        observations = self.model._last_obs
        actions = np.asarray(self.locals["actions"]).reshape(-1)
        rewards = np.asarray(self.locals["rewards"]).reshape(-1)
        dones = np.asarray(self.locals["dones"]).reshape(-1)
        infos = self.locals["infos"]

        for env_index, info in enumerate(infos):
            obs = observations[env_index]
            action_index = int(actions[env_index])
            done = bool(dones[env_index])

            self.csv.write_step(
                time=self.num_timesteps - 1,
                episode=self.episode,
                episode_k=info["step"] - 1,
                obs=obs,
                action_index=action_index,
                action_value=info["u"],
                reward=rewards[env_index],
                q_values=get_q_values(self.model, obs),
                exploration_rate=self.model.exploration_rate,
                terminated=info["terminated"],
                truncated=info["truncated"],
                done=done,
            )

            if done:
                self.episode += 1

        return True

    def _on_training_end(self):
        self.csv.close()
