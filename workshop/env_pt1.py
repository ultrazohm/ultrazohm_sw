import gymnasium as gym
import numpy as np
from gymnasium import spaces


class PT1Env(gym.Env):
    """Minimal PT1 control environment for discrete or continuous control.

    Plant:
        dy/dt = (gain * u - y) / time_constant

    The discrete update is the exact zero-order-hold solution for constant
    input over one control period.
    """

    metadata = {"render_modes": ["ansi"]}
    actions = np.array([-1.0, 0.0, 1.0], dtype=np.float32)

    def __init__(
        self,
        gain: float = 1.0,
        time_constant: float = 0.2,
        control_frequency: float = 50.0,
        episode_seconds: float = 2.0,
        reference: float = 0.0,
        reference_low: float | None = None,
        reference_high: float | None = None,
        initial_state_low: float = -1.0,
        initial_state_high: float = 1.0,
        action_values=None,
        action_range: tuple[float, float] | None = None,
    ):
        super().__init__()

        if time_constant <= 0.0:
            raise ValueError("time_constant must be > 0")
        if control_frequency <= 0.0:
            raise ValueError("control_frequency must be > 0")
        if episode_seconds <= 0.0:
            raise ValueError("episode_seconds must be > 0")
        if (reference_low is None) != (reference_high is None):
            raise ValueError(
                "reference_low and reference_high must both be set or both be None"
            )
        if reference_low is not None and reference_low > reference_high:
            raise ValueError("reference_low must be <= reference_high")
        if initial_state_low > initial_state_high:
            raise ValueError("initial_state_low must be <= initial_state_high")
        if action_values is not None and action_range is not None:
            raise ValueError("Set either action_values or action_range, not both")

        self.gain = float(gain)
        self.time_constant = float(time_constant)
        self.control_frequency = float(control_frequency)
        self.dt = 1.0 / self.control_frequency
        self.alpha = float(np.exp(-self.dt / self.time_constant))
        self.max_steps = max(1, int(round(episode_seconds * self.control_frequency)))
        self.reference_default = float(reference)
        self.reference = self.reference_default
        self.reference_low = None if reference_low is None else float(reference_low)
        self.reference_high = None if reference_high is None else float(reference_high)
        self.initial_state_low = float(initial_state_low)
        self.initial_state_high = float(initial_state_high)

        self._configure_actions(action_values, action_range)

        signal_limit = max(
            abs(self.gain * self.action_low),
            abs(self.gain * self.action_high),
            abs(self.reference_default),
            abs(self.reference_low) if self.reference_low is not None else 0.0,
            abs(self.reference_high) if self.reference_high is not None else 0.0,
            abs(self.initial_state_low),
            abs(self.initial_state_high),
            1.0,
        )
        self.observation_space = spaces.Box(
            low=np.array([-signal_limit, -signal_limit], dtype=np.float32),
            high=np.array([signal_limit, signal_limit], dtype=np.float32),
            dtype=np.float32,
        )

        self.y = 0.0
        self.step_count = 0

    def _configure_actions(self, action_values, action_range):
        if action_range is not None:
            action_low, action_high = action_range
            if action_low >= action_high:
                raise ValueError("action_range low must be < high")

            self.continuous_actions = True
            self.actions = None
            self.action_low = float(action_low)
            self.action_high = float(action_high)
            self.action_space = spaces.Box(
                low=np.array([self.action_low], dtype=np.float32),
                high=np.array([self.action_high], dtype=np.float32),
                dtype=np.float32,
            )
            return

        action_values = self.actions if action_values is None else action_values
        actions = np.asarray(action_values, dtype=np.float32).reshape(-1)
        if actions.size == 0:
            raise ValueError("action_values must contain at least one action")

        self.continuous_actions = False
        self.actions = actions
        self.action_low = float(np.min(actions))
        self.action_high = float(np.max(actions))
        self.action_space = spaces.Discrete(len(self.actions))

    def _get_obs(self):
        return np.array([self.y, self.reference], dtype=np.float32)

    def reset(self, seed=None, options=None):
        super().reset(seed=seed)

        options = options or {}
        if "reference" in options:
            self.reference = float(options["reference"])
        elif self.reference_low is not None:
            self.reference = float(
                self.np_random.uniform(self.reference_low, self.reference_high)
            )
        else:
            self.reference = self.reference_default

        self.y = float(
            self.np_random.uniform(self.initial_state_low, self.initial_state_high)
        )
        self.step_count = 0
        return self._get_obs(), {"reference": self.reference}

    def step(self, action):
        if self.continuous_actions:
            action_array = np.asarray(action, dtype=np.float32).reshape(-1)
            if action_array.size != 1:
                raise ValueError("PT1Env expects one scalar continuous action")

            u = float(np.clip(action_array[0], self.action_low, self.action_high))
        else:
            action_index = int(action)
            u = float(self.actions[action_index])

        return self._step_with_input(u)

    def _step_with_input(self, u):
        self.y = self.alpha * self.y + (1.0 - self.alpha) * self.gain * u
        self.step_count += 1

        error = self.reference - self.y
        reward = -error * error
        terminated = False
        truncated = self.step_count >= self.max_steps
        info = {
            "u": u,
            "y": self.y,
            "reference": self.reference,
            "error": error,
            "step": self.step_count,
            "terminated": terminated,
            "truncated": truncated,
        }

        return self._get_obs(), float(reward), terminated, truncated, info

    def render(self):
        return f"step={self.step_count}, y={self.y:.4f}, ref={self.reference:.4f}"

