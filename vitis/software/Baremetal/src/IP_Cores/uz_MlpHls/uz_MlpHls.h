#ifndef UZ_MLPHLS_H
#define UZ_MLPHLS_H

// includes
#include "xil_types.h"
#include "xmlp.h"

// defines
#define MLP_HLS_PARAMETER_BASE_ADDRESS 0x20100U
#define MLP_HLS_PARAMETER_MEMORY_OFFSET_PL 0xFFE00000U

// typedefs
typedef struct uz_mlpHls_t uz_mlpHls_t;

// structs
struct uz_mlpHls_config_t
{
	u16 deviceId;

	u64 weightMemoryAddress;
	u64 biasMemoryAddress;
	u64 inputAddress;
	u64 outputAddress;
	u64 layerOutputAddress;

	u32 numberNeurons;
	u32 numberHiddenLayers;
	u32 numberInputs;
	u32 numberOutputs;
	u32 loadParameters;
	u32 exportLayers;

	u32 parEntries;
};

// function declarations
void uz_MlpHlsTestbench(void);

#endif
