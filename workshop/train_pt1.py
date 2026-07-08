import torch as th
from stable_baselines3 import DQN
from stable_baselines3.common.env_checker import check_env

from csv_logger import CsvStepWriter, EpisodeCsvLogger, get_q_values
from env_pt1 import PT1Env
from export_to_uz_nn import export_to_uz_nn


GAIN = 1.0
TIME_CONSTANT = 0.2
CONTROL_FREQUENCY = 100.0
EPISODE_SECONDS = 2.0
REFERENCE = 0.0
# Set both to None to train with the fixed REFERENCE value.
TRAIN_REFERENCE_LOW = -1.0
TRAIN_REFERENCE_HIGH = 1.0
INITIAL_STATE_LOW = 0.0
INITIAL_STATE_HIGH = 0.0
DISCRETE_ACTIONS = [-1.0, 0.0, 1.0]
TRAINING_EPISODES = 1000
# 1 logs every episode; 10 logs episodes 1, 11, 21, ...
TRAIN_LOG_EVERY_N_EPISODES = 1
STEPS_PER_EPISODE = round(EPISODE_SECONDS * CONTROL_FREQUENCY)
TOTAL_TIMESTEPS = TRAINING_EPISODES * STEPS_PER_EPISODE
MODEL_PATH = "dqn_pt1"
LOG_DIR = "workshop/logs"
EXPORT_DIR = "workshop/exported_paras"


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
)
check_env(env, warn=True)

HIDDEN_LAYERS = [32, 32]
ACTIVATION_FN = th.nn.ReLU
POLICY_KWARGS = {
    "net_arch": HIDDEN_LAYERS,
    "activation_fn": ACTIVATION_FN,
}

model = DQN("MlpPolicy", env, verbose=1, policy_kwargs=POLICY_KWARGS, seed=0)
training_logger = EpisodeCsvLogger(
    LOG_DIR,
    log_every_n_episodes=TRAIN_LOG_EVERY_N_EPISODES,
)

model.learn(
    total_timesteps=TOTAL_TIMESTEPS,
    log_interval=4,
    callback=training_logger,
)

model.save(MODEL_PATH)
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
        action, _ = model.predict(current_obs, deterministic=True)
        action_index = int(action)
        q_values = get_q_values(model, current_obs)

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
