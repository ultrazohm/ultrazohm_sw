#include "dqTransform.h"

void DQTransformation_Initialize(DS_Data* data){
	//Write down the theta-offset
	Xil_Out32(Trans_123_dq_theta_offset_REG, (uint32_t)(ldexpf(data->mrp.incrementalEncoderOffset, Q20)));	// Shift 20 Bit for fixed-point // Input to the IP-Core
}
