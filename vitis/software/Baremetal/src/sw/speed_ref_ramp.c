#include "../include/speed_ref_ramp.h"

struct uz_ramp_config config_speed_ref_ramp_prime_mover = {
      .maximum_slope_per_second = 1000.0f,
      .sample_time_seconds = 0.0001f,
      .initial_value = 0.0f
   };

uz_ramp_t* initialize_speed_ref_ramp_prime_mover(void) {
	return uz_ramp_init(config_speed_ref_ramp_prime_mover);
}

