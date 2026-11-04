#include "../include/prime_mover_speed_pll.h"

uz_pos_to_speed_pll_t* initialize_prime_mover_speed_pll(float sample_time_s)
{
    // Parallel estimator only: damping 1, nominal frequency 200 Hz.
    // Use the public API unchanged, including its existing startup behavior.
    struct uz_pos_to_speed_pll_config_t config = {
        .machine_polepairs = 4.0f,
        .kp_pll = 2513.2741f,
        .ki_pll = 1579136.7f,
        .sampling_time_in_seconds = sample_time_s
    };
    return uz_pos_to_speed_pll_init(config);
}
