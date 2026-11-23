import numpy as np

class ReplayBuffer:
    def __init__(self, 
                 capacity, 
                 dim_observation, 
                 dim_action, 
                 np_rng):
        
        self.capacity = capacity
        self.ptr = 0
        self.size = 0

        self.dones = np.zeros((capacity, 1), dtype=np.float32)
        self.observations = np.zeros((capacity, dim_observation), dtype=np.float32)
        self.actions = np.zeros((capacity, dim_action), dtype=np.float32)
        self.rewards = np.zeros((capacity, 1), dtype=np.float32)

        self.rng = np_rng

    def add(self, done, observation, action, reward):
        self.dones[self.ptr] = done
        self.observations[self.ptr] = np.asarray(observation)
        self.actions[self.ptr] = np.asarray(action)
        self.rewards[self.ptr] = reward

        self.ptr = (self.ptr + 1) % self.capacity
        self.size = min(self.size + 1, self.capacity)

    def add_batch(self, dones, observations, actions, rewards):
        dones = np.asarray(dones)
        observations = np.asarray(observations)
        actions = np.asarray(actions)
        rewards = np.asarray(rewards)

        if dones.ndim == 1:
            dones = dones[:, None]

        if observations.ndim == 1:
            observations = observations[:, None]

        if actions.ndim == 1:
            actions = actions[:, None]

        if rewards.ndim == 1:
            rewards = rewards[:, None]

        batch_size = len(rewards)

        idx = (np.arange(batch_size) + self.ptr) % self.capacity

        self.dones[idx] = dones
        self.observations[idx] = observations
        self.actions[idx] = actions
        self.rewards[idx] = rewards

        self.ptr = (self.ptr + batch_size) % self.capacity
        self.size = min(self.size + batch_size, self.capacity)

    def sample(self, batch_size):
        idx = self.rng.choice(self.size-1, size=batch_size, replace=False, shuffle=False)

        return (
            
            self.observations[idx],
            self.actions[idx],
            self.rewards[idx],
            self.observations[idx+1],
            self.dones[idx+1]
            )

    def __len__(self):
        return self.size