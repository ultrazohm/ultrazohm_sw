#include "../IP_Cores/uz_incrementalEncoder/uz_incrementalEncoder.h"
#include "../include/incremental.h"
#include "xparameters.h"

struct uz_incrementalEncoder_config incre_config_d5_1={
  .base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREENCODER_V24_IP_0_BASEADDR,
  .ip_core_frequency_Hz=50000000U,
  .line_number_per_turn_mech=5000U,
  .OmegaPerOverSample_in_rpm=500.0f,
  .drive_pole_pair=4U
};

struct uz_incrementalEncoder_config incre_config_d5_2={
  .base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREENCODER_V24_IP_1_BASEADDR,
  .ip_core_frequency_Hz=50000000U,
  .line_number_per_turn_mech=5000U,
  .OmegaPerOverSample_in_rpm=500.0f,
  .drive_pole_pair=4U
};

struct uz_incrementalEncoder_config incre_config_d5_3={
  .base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREENCODER_V24_IP_2_BASEADDR,
  .ip_core_frequency_Hz=50000000U,
  .line_number_per_turn_mech=5000U,
  .OmegaPerOverSample_in_rpm=500.0f,
  .drive_pole_pair=4U
};

uz_incrementalEncoder_t* uz_incremental_encoder_d5_1_init(void) {
	return(uz_incrementalEncoder_init(incre_config_d5_1));
}

uz_incrementalEncoder_t* uz_incremental_encoder_d5_2_init(void) {
	return(uz_incrementalEncoder_init(incre_config_d5_2));
}

uz_incrementalEncoder_t* uz_incremental_encoder_d5_3_init(void) {
	return(uz_incrementalEncoder_init(incre_config_d5_3));
}
