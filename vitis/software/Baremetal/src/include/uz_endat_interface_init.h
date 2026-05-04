#pragma once

#include "../globalData.h"
#include "../IP_Cores/uz_endat_interface/uz_endat_interface.h"

uz_endat_interface_t *endat_encoder_init_endat_d4_1(void);
void update_endat_encoder_on_D4(DS_Data *const data);
