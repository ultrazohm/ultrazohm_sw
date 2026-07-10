from pathlib import Path

import numpy as np
import torch as th
import random
from datetime import datetime
seed=random.seed(datetime.now().timestamp())

from stable_baselines3 import DQN
from stable_baselines3.common.env_checker import check_env

from csv_logger import CsvStepWriter, EpisodeCsvLogger, get_q_values
from env_pt1 import PT1Env
from export_to_uz_nn import export_to_uz_nn


GAIN = 1.0
TIME_CONSTANT = 0.002
CONTROL_FREQUENCY = 10000.0
EPISODE_SECONDS = 0.05

# Set TRAIN_REFERENCE_LOW and TRAIN_REFERENCE_HIGH to None to train with the fixed REFERENCE value.
REFERENCE = 0.0
TRAIN_REFERENCE_LOW = -1.0
TRAIN_REFERENCE_HIGH = 1.0

INITIAL_STATE_LOW = 0.0
INITIAL_STATE_HIGH = 0.0
DISCRETE_ACTIONS = [-1.0, 0.0, 1.0]


def squared_error_reward(
    *,
    y: float,
    reference: float,
    error: float,
    u: float,
    step: int,
) -> float:
    return -error * error

REWARD_FUNCTION = squared_error_reward
TRAIN_LOG_EVERY_N_EPISODES = 1
TOTAL_TIMESTEPS = 50_000
LEARNING_RATE = 1e-4
BUFFER_SIZE = 1_000_000
LEARNING_STARTS = 100
BATCH_SIZE = 32
TAU = 1.0
GAMMA = 0.99
TRAIN_FREQ = 1
GRADIENT_STEPS = 1
TARGET_UPDATE_INTERVAL = 10
EXPLORATION_FRACTION = 0.1
EXPLORATION_INITIAL_EPS = 1.0
EXPLORATION_FINAL_EPS = 0.05
TORCH_NUM_THREADS = 1
th.set_num_threads(TORCH_NUM_THREADS)

STEPS_PER_EPISODE = round(EPISODE_SECONDS * CONTROL_FREQUENCY)
TRAINING_EPISODES = (TOTAL_TIMESTEPS + STEPS_PER_EPISODE - 1) // STEPS_PER_EPISODE


BASE_DIR = Path(__file__).resolve().parent
MODEL_PATH = BASE_DIR / "dqn_pt1"
LOG_DIR = BASE_DIR / "logs"
EXPORT_DIR = BASE_DIR / "exported_paras"


env = PT1Env(
    gain=GAIN,
    time_constant=TIME_CONSTANT,
    control_frequency=CONTROL_FREQUENCY,
    episode_seconds=EPISODE_SECONDS,
    reference=REFERENCE,
    reference_low=TRAIN_REFERENCE_LOW,
    reference_high=TRAIN_REFERENCE_HIGH,
    initial_state_low=INITIAL_STATE_LOW,
    initial_state_high=INITIAL_STATE_HIGH,
    action_values=DISCRETE_ACTIONS,
    reward_function=REWARD_FUNCTION,
)
check_env(env, warn=True)

HIDDEN_LAYERS = [32, 32]
ACTIVATION_FN = th.nn.ReLU
POLICY_KWARGS = {
    "net_arch": HIDDEN_LAYERS,
    "activation_fn": ACTIVATION_FN,
}

model = DQN(
    "MlpPolicy",
    env,
    learning_rate=LEARNING_RATE,
    buffer_size=BUFFER_SIZE,
    learning_starts=LEARNING_STARTS,
    batch_size=BATCH_SIZE,
    tau=TAU,
    gamma=GAMMA,
    train_freq=TRAIN_FREQ,
    gradient_steps=GRADIENT_STEPS,
    target_update_interval=TARGET_UPDATE_INTERVAL,
    exploration_fraction=EXPLORATION_FRACTION,
    exploration_initial_eps=EXPLORATION_INITIAL_EPS,
    exploration_final_eps=EXPLORATION_FINAL_EPS,
    verbose=1,
    policy_kwargs=POLICY_KWARGS,
    seed=seed,
)
training_logger = EpisodeCsvLogger(
    LOG_DIR,
    log_every_n_episodes=TRAIN_LOG_EVERY_N_EPISODES,
)

model.learn(
    total_timesteps=TOTAL_TIMESTEPS,
    log_interval=5,
    callback=training_logger,
)

# model.save(MODEL_PATH)
export_to_uz_nn(model, EXPORT_DIR)


EVAL_REFERENCES = [-1.0, 0.0, 0.5, 0.1, 0.2, 1.0]
eval_log = CsvStepWriter(LOG_DIR, env.actions, "eval_log.csv")
eval_log.open()
time = 0

for episode, reference in enumerate(EVAL_REFERENCES, start=1):
    obs, _ = env.reset(options={"reference": reference})
    total_reward = 0.0

    for episode_k in range(STEPS_PER_EPISODE):
        current_obs = obs
        # Greedy action from q-values; equivalent to
        # model.predict(current_obs, deterministic=True) with one forward pass.
        q_values = get_q_values(model, current_obs)
        action_index = int(np.argmax(q_values))

        obs, reward, terminated, truncated, info = env.step(action_index)
        done = terminated or truncated
        total_reward += reward

        eval_log.write_step(
            time=time,
            episode=episode,
            episode_k=episode_k,
            obs=current_obs,
            action_index=action_index,
            action_value=info["u"],
            reward=reward,
            q_values=q_values,
            exploration_rate=0.0,
            terminated=terminated,
            truncated=truncated,
            done=done,
        )
        time += 1

        if done:
            break

    print(
        f"episode={episode}, total_reward={total_reward:.3f}, "
        f"final_y={obs[0]:.4f}, reference={obs[1]:.4f}, "
        f"final_error={info['error']:.4f}"
    )

eval_log.close()
