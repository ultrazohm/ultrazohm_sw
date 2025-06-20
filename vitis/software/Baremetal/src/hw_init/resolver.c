#include "../include/resolver.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"



struct uz_incrementalEncoder_config encoder_D5_config_right={
              .base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREMENTAL_ENCODER_D5_3_BASEADDR,
              .ip_core_frequency_Hz=100000000U,
              .line_number_per_turn_mech=5000U,
              .OmegaPerOverSample_in_rpm=500.0f,
              .drive_pole_pair=4U,
              .Encoder_elec_Offset = 0U,
              .counting_direction = 0,
              .Speed_Timeout_ms = 10U //10ms
};

struct uz_incrementalEncoder_config encoder_D5_config_left={
              .base_address=XPAR_UZ_DIGITAL_ADAPTER_D5_ADAPTER_INCREMENTAL_ENCODER_D5_1_BASEADDR,
              .ip_core_frequency_Hz=100000000U,
              .line_number_per_turn_mech=5000U,
              .OmegaPerOverSample_in_rpm=500.0f,
              .drive_pole_pair=4U,
              .Encoder_elec_Offset = 0U,
              .counting_direction = 0,
              .Speed_Timeout_ms = 10U //10ms
};


uz_incrementalEncoder_t* initialize_encoder_right(void){
	return (uz_incrementalEncoder_init(encoder_D5_config_right));
}

uz_incrementalEncoder_t* initialize_encoder_left(void){
	return (uz_incrementalEncoder_init(encoder_D5_config_left));
}
