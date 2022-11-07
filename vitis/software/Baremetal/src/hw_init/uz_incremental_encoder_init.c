#include "../include/uz_incremental_encoder_init.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_incrementalEncoder_config incre_config_D5_1={
  .base_address=XPAR_UZ_USER_INCREENCODER_V24_IP_0_BASEADDR,
  .ip_core_frequency_Hz=50000000U,
  .line_number_per_turn_mech=256U,
  .OmegaPerOverSample_in_rpm=500.0f,
  .drive_pole_pair=1U
};

static struct uz_incrementalEncoder_config incre_config_D5_2={
  .base_address=XPAR_UZ_USER_INCREENCODER_V24_IP_1_BASEADDR,
  .ip_core_frequency_Hz=50000000U,
  .line_number_per_turn_mech=256U,
  .OmegaPerOverSample_in_rpm=500.0f,
  .drive_pole_pair=1U
};

static struct uz_incrementalEncoder_config incre_config_D5_3={
  .base_address=XPAR_UZ_USER_INCREENCODER_V24_IP_2_BASEADDR,
  .ip_core_frequency_Hz=50000000U,
  .line_number_per_turn_mech=256U,
  .OmegaPerOverSample_in_rpm=500.0f,
  .drive_pole_pair=1U
};


uz_incrementalEncoder_t* initialize_incrementalEncoder_D5_1(void) {
	return(uz_incrementalEncoder_init(incre_config_D5_1));
}

uz_incrementalEncoder_t* initialize_incrementalEncoder_D5_2(void) {
	return(uz_incrementalEncoder_init(incre_config_D5_2));
}

uz_incrementalEncoder_t* initialize_incrementalEncoder_D5_3(void) {
	return(uz_incrementalEncoder_init(incre_config_D5_3));
}

