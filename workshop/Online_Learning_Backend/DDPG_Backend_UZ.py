import numpy as np
import jax
import jax.numpy as jnp
from flax import nnx
from functools import partial
import optax
from tqdm import tqdm
import time
from Replay_Buffer_DSAR import ReplayBuffer
import threading
import subprocess
import ultrazohm_cli as uz


result = subprocess.run(
    [
        "ultrazohm_cli",
        "create-json-from-javascope-h",
        "--repo", ".",
        "--output", "my-mapping.json",
    ],
    check=True,
    capture_output=True,
    text=True,
)
print("Creating channel mapping from momentary UZ build")
print(result.stdout)

class CommunicationProtocolError(Exception):
    """Raised when a communication partner violates the communication protocol."""
    pass

def identity_activation(x):
    return x

class MLP(nnx.Module):
  def __init__(self, 
               dim_in: int, 
               dim_mid: int, 
               dim_out: int, 
               n_layers: int,
               hidden_activation=None,
               output_activation=None,
               *, 
               rngs: nnx.Rngs):

    self.din = dim_in
    self.dout = dim_out
    self.dmid = dim_mid
    self.rngs = rngs

    kernel_init = nnx.initializers.orthogonal()

    self.hidden_activation = hidden_activation or identity_activation
    self.output_activation = output_activation or identity_activation

    self.layers = nnx.List()
    if n_layers == 1:
       self.layers.append(nnx.Linear(self.din, self.dout, rngs=self.rngs))
    elif n_layers >= 2:
        self.layers.append(nnx.Linear(self.din, self.dmid, rngs=self.rngs))
        for i in range(n_layers-2):
           self.layers.append(nnx.Linear(self.dmid, self.dmid, rngs=self.rngs))
        self.layers.append(nnx.Linear(self.dmid, self.dout, rngs=self.rngs))

  def __call__(self, x: jax.Array):
    for _layer in self.layers[:-1]:
        x = self.hidden_activation(_layer(x))
    x = self.output_activation(self.layers[-1](x))

    return x

  def clone(self):
    graphdef, state = nnx.split(self)
    state = jax.tree.map(lambda x: x.copy(), state)
    return nnx.merge(graphdef, state)


def soft_update(source, target, tau):
    target_state = nnx.state(target, nnx.Param)
    source_state = nnx.state(source, nnx.Param)

    new_state = jax.tree.map(
        lambda t, s: (1.0 - tau) * t + tau * s,
        target_state,
        source_state,
    )

    nnx.update(target, new_state)


def lr_scheduler(lr_interval, progress):
    if progress < 0 or progress > 1:
        progress = 0
    return (1-progress) * lr_interval[0] + progress * lr_interval[1]


@partial(nnx.jit, static_argnames=("discount_factor", "target_update_parameter"))
def train_on_batch(critic, 
                   target_critic, 
                   critic_optimizer,

                   actor, 
                   target_actor, 
                   actor_optimizer,

                   experience_tuple,
                   discount_factor, 
                   target_update_parameter
                   ):

    obs = experience_tuple[0]
    actions = experience_tuple[1]
    rewards = experience_tuple[2]
    next_obs = experience_tuple[3]
    dones = experience_tuple[4]

    for _obs, _actions, _rewards, _next_obs, _dones in zip(obs, actions, rewards, next_obs, dones):

        def critic_loss_fn(critic):

            # Compute TD Loss
            q_next = target_critic(jnp.concatenate([_next_obs, target_actor(_next_obs)], axis=-1))
            q_next = jax.lax.stop_gradient(q_next)
            q_now = critic(jnp.concatenate([_obs, _actions], axis=-1))
            td_loss = ((q_now - _rewards - ( 1 - _dones) * discount_factor * q_next) ** 2).mean()

            return td_loss

        critic_loss, grads = nnx.value_and_grad(critic_loss_fn)(critic)
        critic_optimizer.update(critic, grads)

        def actor_loss_fn(actor):

            # Compute Actor Loss
            a = actor(_obs)
            q_now = critic(jnp.concatenate([_obs, a], axis=-1))
            actor_loss = -q_now.mean()

            # Penalize large output
            output_loss = 10 * jnp.maximum(jnp.abs(a)-1.0, 0.0).mean()  ### MAGIC NUMBERS

            return actor_loss + output_loss
            
        actor_loss, grads = nnx.value_and_grad(actor_loss_fn)(actor)
        actor_optimizer.update(actor, grads)

        soft_update(critic, target_critic, target_update_parameter)
        soft_update(actor, target_actor, target_update_parameter)

    actor_params = jax.tree.leaves(nnx.state(actor, nnx.Param))
    flattened_actor_params = jnp.concatenate([sublist.ravel() for sublist in actor_params], dtype=jnp.float32)

    return actor_loss, critic_loss, flattened_actor_params

def _recv_all_into(connection, buffer):
    view = memoryview(buffer)

    received = 0
    while received < len(buffer):
        nbytes = connection.recv_into(view[received:])
        if nbytes == 0:
            return None
        received += nbytes

    return received


class DDPG_Agent:
    def __init__(self, 
                 
                 discount_factor,
                 batch_size,
                 replay_buffer_size,
                 observation_dim,
                 action_dim,
                 target_update_parameter,
                 
                 actor, 
                 actor_optimizer,
                 actor_learning_rate_interval,
                 critic,
                 critic_optimizer,
                 critic_learning_rate_interval,

                 client_IP,
                 UZ_mapping_filename,
                 port,
                 captured_channels,
                 assign_channels_from_nb,

                 progress_bar=False,
                 randomizer_seed=None,
                 rollout_size=None):


        if randomizer_seed is None:
            numpy_rng = np.random.default_rng()
        else:
            numpy_rng = np.random.default_rng(randomizer_seed)

        self.discount_factor = discount_factor
        self.batch_size = batch_size

        self.observation_dim = observation_dim
        self.action_dim = action_dim
        self.target_update_parameter = target_update_parameter

        self.training_completion_idx = 0
        self.done_idx = self.training_completion_idx + 1
        self.observation_idx = self.done_idx + 1
        self.action_idx = self.observation_idx + self.observation_dim
        self.reward_idx = self.action_idx + self.action_dim
        self.experience_size = self.reward_idx + 1

        self.experience_message_size_bytes = 4 * self.experience_size
        self.experience_bytes_recv_buffer = bytearray(self.experience_message_size_bytes)

        self.replay_buffer = ReplayBuffer(capacity=replay_buffer_size, 
                                          dim_observation=self.observation_dim, 
                                          dim_action=self.action_dim, 
                                          np_rng=numpy_rng)

        print("Initialize optimizers")
        self.actor = actor
        self.target_actor = self.actor.clone()
        self.actor_learning_rate_interval = actor_learning_rate_interval
        tx_actor = optax.inject_hyperparams(actor_optimizer)(learning_rate=self.actor_learning_rate_interval[0])
        self.actor_optimizer = nnx.Optimizer(actor, tx_actor, wrt=nnx.Param)
        self.actor_optimizer.opt_state.hyperparams["learning_rate"] = jnp.asarray(lr_scheduler(self.actor_learning_rate_interval, np.float32(0.0)))

        self.critic = critic
        self.target_critic = self.critic.clone()
        self.critic_learning_rate_interval = critic_learning_rate_interval
        tx_critic = optax.inject_hyperparams(critic_optimizer)(learning_rate=self.critic_learning_rate_interval[0])
        self.critic_optimizer = nnx.Optimizer(critic, tx_critic, wrt=nnx.Param)
        self.critic_optimizer.opt_state.hyperparams["learning_rate"] = jnp.asarray(lr_scheduler(self.critic_learning_rate_interval, np.float32(0.0)))
        time.sleep(0.1)

        if rollout_size is None:
            self.rollout_size = 1
        else:
            self.rollout_size = rollout_size
        self.nb_warmup_steps = self.batch_size * self.rollout_size

        self.actor_params = jax.tree.leaves(nnx.state(self.actor, nnx.Param))
        self.flattened_actor_params = np.concatenate([sublist.ravel() for sublist in self.actor_params], dtype=np.float64)
        print(f"Actor has {len(self.flattened_actor_params)} parameters")
        self.actor_structure = np.array([sublist.size for sublist in self.actor_params]).reshape(-1, 2).sum(axis=1)
        self.actor_weight_idx_layer = np.cumsum(np.insert(self.actor_structure, 0, 0))

        print("Compiling backward pass...")
        compile_time = time.time()

        # Compile for single batch
        train_on_batch.lower(critic = self.critic, 
                             target_critic = self.target_critic, 
                             critic_optimizer = self.critic_optimizer,

                             actor = self.actor, 
                             target_actor = self.target_actor, 
                             actor_optimizer = self.actor_optimizer,

                             discount_factor = self.discount_factor, 
                             target_update_parameter = self.target_update_parameter,
                             experience_tuple = tuple(np.random.uniform(
                                size=[1, self.batch_size, object_size]
                                ).astype(np.float32)
                                for object_size in [
                                    self.observation_dim, 
                                    self.action_dim, 
                                    1, 
                                    self.observation_dim, 
                                    1
                            ])
                            ).compile()

        # Compile for full rollout
        train_on_batch.lower(critic = self.critic, 
                             target_critic = self.target_critic, 
                             critic_optimizer = self.critic_optimizer,
    
                             actor = self.actor, 
                             target_actor = self.target_actor, 
                             actor_optimizer = self.actor_optimizer,

                             discount_factor = self.discount_factor, 
                             target_update_parameter = self.target_update_parameter,
                             experience_tuple = tuple(np.random.uniform(
                                 size=[self.rollout_size, self.batch_size, object_size]
                                 ).astype(np.float32)
                                 for object_size in [
                                     self.observation_dim, 
                                     self.action_dim, 
                                     1, 
                                     self.observation_dim, 
                                     1
                                ])
                             ).compile()
        
        compile_time = time.time()-compile_time
        print(f"Compiled after {int(compile_time)} seconds")

        self.client_IP = client_IP
        print("Init connection to UZ client")
        self.acquirer = uz.Acquisition(channel_mapping=UZ_mapping_filename)
        self.acquirer.__enter__()
        self.uz_client = uz.Client()
        self.uz_client.connect(self.client_IP, port)
        print("UZ connection established")
        time.sleep(0.1)

        self.captured_channels = captured_channels
        for ch_idx, ch_name in enumerate(captured_channels):
            self.uz_client.set_observable(ch_name, assign_channels_from_nb + ch_idx)

        print("Sending initial weights")
        self._set_actor_weights()
        # STATUS) 1: normal, receiving; 0: client expects one more weights; -1: client is shutting down

        time.sleep(0.1)
    
        self.client_alive = True
        self.training_completion = 0.0
        self.reading_cursor = None

        self.progress_bar = progress_bar

        self.update_counter = 0

    def launch(self):

        print("Starting")

        self.receiver_thread = threading.Thread(
            target=self.while_client_alive,
            args=(self._read_training_data, )
            )
        self.receiver_thread.start()

        self.training_thread = threading.Thread(
            target=self.while_client_alive,
            args=(self._train, )
            )
        self.training_thread.start()    

        self.sender_thread = threading.Thread(
            target=self.while_client_alive,
            args=(self._set_actor_weights, )
            )
        self.sender_thread.start()

        print("NULL")

        if self.progress_bar:
            self.progress_bar = tqdm(total=100)
            while self.client_alive:
                self.progress_bar.n = int(self.training_completion * 100)
                self.progress_bar.refresh()
                time.sleep(0.5)
            self.progress_bar.close()

        print("A")

        self.training_thread.join()
        self.sender_thread.join()

        print("B")

        print(f"A total of {self.update_counter} training updates have been performed.")


    def _train(self):

        if self.replay_buffer.size-1 >= self.batch_size:

            self.critic_optimizer.opt_state.hyperparams["learning_rate"] = jnp.asarray(lr_scheduler(self.critic_learning_rate_interval, self.training_completion))
            self.actor_optimizer.opt_state.hyperparams["learning_rate"] = jnp.asarray(lr_scheduler(self.actor_learning_rate_interval, self.training_completion))

            if self.replay_buffer.size-1 >= self.nb_warmup_steps:
                experience_minibatch = self.replay_buffer.sample([self.rollout_size, self.batch_size])
                self.update_counter += self.rollout_size

            else:
                experience_minibatch = self.replay_buffer.sample([1, self.batch_size])
                self.update_counter += 1
        
            actor_loss, critic_loss, self.flattened_actor_params = train_on_batch(
                critic=self.critic, 
                target_critic=self.target_critic, 
                critic_optimizer=self.critic_optimizer,

                actor=self.actor, 
                target_actor=self.target_actor, 
                actor_optimizer=self.actor_optimizer,

                target_update_parameter=self.target_update_parameter,
                discount_factor=self.discount_factor,
                experience_tuple=experience_minibatch
                )
            
        else:
            time.sleep(0.1)


    def _read_training_data(self):
        page = self.uz_client.read_since(self.reading_cursor,
                             channels=self.captured_channels,
                             limit=10_000)
        self.reading_cursor = page.cursor

        experience = page.data[*self.captured_channels].to_numpy()

        experience = page.data.to_numpy()
        print(experience[-1][1])

        ### DATA FORMAT
        # training_completion (scalar in [0, 1])    
        # done (scalar)
        # observations (vectorial)
        # actions (vectorial)
        # reward (scalar)
        ### length = observation_dim + action_dim + 3

        #self.training_completion = np.clip(experience[0], 0.0, 1.0)

        # self.replay_buffer.add(
        #            experience_floats[self.done_idx],
        #            experience_floats[self.observation_idx:self.action_idx], 
        #            experience_floats[self.action_idx:self.reward_idx], 
        #            experience_floats[self.reward_idx]
        #        )


    def _set_actor_weights(self):

        for _layer_idx in range(len(self.actor_structure)):
            layer_params = self.flattened_actor_params[self.actor_weight_idx_layer[_layer_idx]:self.actor_weight_idx_layer[_layer_idx+1]]
            for _param_idx in range(self.actor_structure[_layer_idx]):

                self.uz_client.set_variable("layer_idx", _layer_idx)
                self.uz_client.set_variable("param_idx", _param_idx)
                self.uz_client.set_variable("param_value", layer_params[_param_idx])

                self.uz_client.set_variable("allow_update", 1)
                time.sleep(5e-6)
                self.uz_client.set_variable("allow_update", 0)
                    

    def while_client_alive(self, loop_fcn):
        while self.client_alive:
            loop_fcn()


    def save_weights_to_CSV(self):
        params = nnx.state(self, nnx.Param)

        leaves, treedef = jax.tree.flatten(params)

        idx = 0
        new_leaves = []

        for leaf in leaves:
            n = leaf.size

            new_values = jnp.asarray(
                flat_weights[idx:idx + n]
            ).reshape(leaf.shape)

            new_leaves.append(new_values)
            idx += n

        if idx != len(flat_weights):
            raise ValueError(f"Expected {idx} weights, got {len(flat_weights)}")

        new_params = jax.tree.unflatten(treedef, new_leaves)

        nnx.update(self, new_params)


    def close(self):

        print("Stopping training")
        print("Setting final weights")

        try:
            self._set_actor_weights()
            print("Final weights have been set")

            time.sleep(0.1)
            
            print("Controlled shutdown of connection")

        except (ConnectionResetError, BrokenPipeError):
            print("Client is already offline")


        finally:    
            self.client_alive = False
            time.sleep(0.1)

            ### shutdown the uz_client somewhat gracefully ?

            self.uz_client.stop()
            self.acquirer.__exit__()

            print("Connection was closed")

            print("Saving weights")
            self.actor_params = jax.tree.leaves(nnx.state(self.actor, nnx.Param))
            for i, actor_weight in enumerate(self.actor_params):

                layer_idx = i // 2 + 1

                if len(actor_weight.shape) == 1: # is bias
                    print("This is a bias:", actor_weight.shape)
                    filename = f"layer{layer_idx}_bias.csv"

                elif len(actor_weight.shape) == 2: # is weight matrix
                    print("This is a weight matrix:", actor_weight.shape)
                    filename = f"layer{layer_idx}_weights.csv"

                values = np.asarray(actor_weight, dtype=np.float32).reshape(1, -1)
                np.savetxt(filename, values, delimiter=",", fmt="%.10g")

            
  



##### USER SPECIFICATIONS

# General setup
rng_seed = 0
gamma = 0.9

observation_dim=2
action_dim=1

captured_channels = ["JSO_RL_TRAINING_COMPLETION",
                     "JSO_RL_DONE_FLAG",
                     "JSO_RL_OBS0_PT1STATE", 
                     "JSO_RL_OBS1_PT1REF", 
                     "JSO_RL_ACT0_PT1INPUT",
                     "JSO_RL_REWARD"]

critic_learning_rate_interval = [1e-2, 5e-5] # [start, end]
actor_learning_rate_interval = [1e-2, 5e-5]

batch_size = 32
target_update_parameter = 0.35
replay_buffer_size = int(2 ** 15)


# Define the function approximators
nb_critic_layers = 6
nb_critic_neurons_per_layer = 50

nb_actor_layers = 3
nb_actor_neurons_per_layer = 32

leaky_relu_alpha = 0.0

def Leaky_ReLU(x):
    return jnp.maximum(leaky_relu_alpha * x, x)

def identity_activation(x):
    return x

actor = MLP(dim_in=observation_dim, 
            dim_out=action_dim, 
            dim_mid=nb_actor_neurons_per_layer, 
            n_layers=nb_actor_layers,
            hidden_activation=Leaky_ReLU,
            output_activation=None,
            rngs=nnx.Rngs(rng_seed))

critic = MLP(dim_in=observation_dim+action_dim, 
             dim_out=1, 
             dim_mid=nb_critic_neurons_per_layer, 
             n_layers=nb_actor_layers,
             hidden_activation=Leaky_ReLU,
             output_activation=None,
             rngs=nnx.Rngs(rng_seed))

### Make the agent
ddpg_agent = DDPG_Agent(discount_factor=gamma,
                        batch_size=batch_size,
                        replay_buffer_size=replay_buffer_size,
                        observation_dim=observation_dim,
                        action_dim=action_dim,
                        target_update_parameter=target_update_parameter,
    
                        actor=actor, 
                        actor_optimizer=optax.adam,
                        actor_learning_rate_interval=actor_learning_rate_interval,
                        critic=critic,
                        critic_optimizer=optax.adam,
                        critic_learning_rate_interval=critic_learning_rate_interval,

                        client_IP="192.168.1.233",
                        UZ_mapping_filename="my-mapping.json",
                        port=1_000,
                        captured_channels = captured_channels,
                        assign_channels_from_nb = 4,

                        progress_bar=True,
                        randomizer_seed=rng_seed,
                        rollout_size=16
                        )

try:
    ddpg_agent.launch()

finally:
    ddpg_agent.close()
    

