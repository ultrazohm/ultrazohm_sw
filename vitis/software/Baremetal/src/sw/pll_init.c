#include "../include/pll_init.h"


struct uz_pos_to_speed_pll_config_t pll_config = {

              .machine_polepairs=21.0f,

              .kp_pll=628.3185f,

              .ki_pll=98696.0f,

              .sampling_time_in_seconds=0.000025f

};


uz_pos_to_speed_pll_t* pll_0_init(void) {

        return(uz_pos_to_speed_pll_init(pll_config));

}
