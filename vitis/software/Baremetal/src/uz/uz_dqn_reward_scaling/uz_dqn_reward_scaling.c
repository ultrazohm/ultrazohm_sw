/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2023 Tobias Schindler
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#include "../uz_HAL.h"
#include "uz_dqn_reward_scaling.h"
#include "../uz_nn/uz_nn_activation_functions.h"

#include <math.h>

static float uz_dqn_reward_scaling_linear(float data, float min_before, float max_before, float min_new, float max_new);

// Assumes that the best value for x is 0 (= no error) and +- values are bad
float uz_dqn_scaling_log(float x, float x_bad_performance)
{
    x = fabsf(x);
    x_bad_performance = fabsf(x_bad_performance);
    float bounds = logf(19.0f);
    x = uz_dqn_reward_scaling_linear(x, x_bad_performance, 0.0f, -bounds, bounds);
    float result = uz_nn_activation_function_sigmoid_logistic(x);
    return result;
}

static float uz_dqn_reward_scaling_linear(float data, float min_before, float max_before, float min_new, float max_new)
{

    float temp = (data - min_before) / (max_before - min_before);
    float new_data = (min_new - temp * (min_new - max_new));
    return new_data;
}

// Code for uz_dqn_reward_scaling_linear taken from fusion_tvc/transforms.py
// Paper: https://www.nature.com/articles/s41586-021-04301-9
// #Copyright 2021 DeepMind Technologies Limited.
// #
// #Licensed under the Apache License, Version 2.0(the "License");
// #you may not use this file except in compliance with the License.
// #You may obtain a copy of the License at
// #
// #http: // www.apache.org/licenses/LICENSE-2.0
// #
// #Unless required by applicable law or agreed to in writing, software
// #distributed under the License is distributed on an "AS-IS" BASIS,
// #WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// #See the License for the specific language governing permissions and
// #limitations under the License.
// ""
//     "Transforms from actual/target to rewards."
//     ""
// #Constants to set the sharpness / slope of the sigmoid.
// #Defaults were chosen such that the good / bad have 0.95 and 0.05 reward:
// #https: // www.wolframalpha.com/input/?i=plot+1%2F%281%2Be%5E%28-+%28-ln%2819%29+-+%28x-1%29*%282*ln%2819%29%29%29%29%29+from+x%3D0+to+2
//   high: float = math.log(19)  # +2.9444389791664403
//   low: float = -math.log(19)  # -2.9444389791664403
//
//   def __call__(self, errors: List[float]) -> List[float]:
//     return [logistic(scale(err, self.bad, self.good, self.low, self.high))
//             for err in errors]
