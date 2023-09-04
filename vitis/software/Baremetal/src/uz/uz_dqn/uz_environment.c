#include "../uz_global_configuration.h"
#if UZ_DQN_ENV_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include <stdio.h>
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_dqn.h"
#include "uz_environment.h"

static uint32_t instance_counterenv = 0U;
static uz_dqn_environment_t instancesenv[UZ_DQN_ENV_MAX_INSTANCES] = {0};
static uz_dqn_environment_t* uz_dqn_environment_allocation(void);

static uz_dqn_environment_t* uz_dqn_environment_allocation(void){
    uz_assert(instance_counterenv < UZ_DQN_BUFFER_MAX_INSTANCES);
    uz_dqn_experience_replay_t* self = &instancesenv[instance_counterenv];
    uz_assert_false(self->is_ready);
    instance_counterenv++;
    self->is_ready = true;
    return (self);
}

uz_dqn_environment_t *uz_dqn_environment_init(struct uz_dqn_environment_config envconf){
    uz_dqn_environment_t *self = uz_dqn_environment_allocation();
    self->length = envconf.bitlength;
    self->bitarray = &envconf.bitarray;
    if (envconf.maxsteps == 0){
        self->max_steps = self->bitlength;
    }
    else{
            self->max_steps = envconf.maxsteps;
        }
    return (self);
}

uz_dqn_environment_reset(uz_dqn_environment_t *self,MTRand *seedRand){
// creates a new target bitset
for(uint32_t j=0; j<self->bitlength;j++){
    self->bitarray[i]=genRand_zero_one(seedRand);
}
}

// class BitFlip(gym.Env):

//     def __init__(self, bit_length=16, max_steps=None, mean_zero=False):
//         super(BitFlip, self).__init__()
//         if bit_length < 1:
//             raise ValueError('bit_length must be >= 1, found {}'.format(bit_length))
//         self.bit_length = bit_length
//         self.mean_zero = mean_zero

//         if max_steps is None:
//             # default to bit_length
//             self.max_steps = bit_length
//         elif max_steps == 0:
//             self.max_steps = None
//         else:
//             self.max_steps = max_steps

//         # spaces documentation: https://gym.openai.com/docs/
//         self.action_space = spaces.Discrete(bit_length)
//         self.observation_space = spaces.Dict({
//             'state': spaces.Box(low=0, high=1, shape=(bit_length, )),
//             'goal': spaces.Box(low=0, high=1, shape=(bit_length, )),
//         })

//         self.reset()

//     def _terminate(self):
//         return (self.state == self.goal).all() or self.steps >= self.max_steps

//     def _reward(self):
//         return -1 if (self.state != self.goal).any() else 0

//     def _step(self, action):
//         # action is an int in the range [0, self.bit_length)
//         self.state[action] = int(not self.state[action])
//         self.steps += 1

//         return (self._get_obs(), self._reward(), self._terminate(), {})

//     def _reset(self):
//         self.steps = 0

//         self.state = np.array([random.choice([1, 0]) for _ in range(self.bit_length)])

//         # make sure goal is not the initial state
//         self.goal = self.state
//         while (self.goal == self.state).all():
//             self.goal = np.array([random.choice([1, 0]) for _ in range(self.bit_length)])

//         return self._get_obs()

//     def _mean_zero(self, x):
//         if self.mean_zero:
//             return (x - 0.5) / 0.5
//         else:
//             return x


//     def _get_obs(self):
//         return {
//             'state': self._mean_zero(self.state),
//             'goal': self._mean_zero(self.goal),
//         }

//     def _render(self, mode='human', close=False):
//         pass

#endif