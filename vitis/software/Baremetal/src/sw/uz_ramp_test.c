/******************************************************************************
* Copyright 2026
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

#include "../include/uz_ramp_test.h"

static struct uz_ramp_config ramp_test_config = {
	.maximum_slope_per_second = 100.0f,
	.sample_time_seconds = 0.0f,
	.initial_value = 0.0f
};

uz_ramp_t *initialize_uz_ramp_test(float sample_time_seconds)
{
	ramp_test_config.sample_time_seconds = sample_time_seconds;
	return (uz_ramp_init(ramp_test_config));
}

void update_uz_ramp_test(DS_Data *data)
{
	data->av.ramp_test_output = uz_ramp_step(data->objects.ramp_test, data->av.ramp_test_input);
}
