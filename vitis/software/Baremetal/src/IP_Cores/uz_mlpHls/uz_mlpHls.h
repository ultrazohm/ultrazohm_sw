#ifndef UZ_MLPHLS_H
#define UZ_MLPHLS_H

// includes
#include "xil_types.h"
#include "xmlp.h"
#include "xparameters.h"

// defines

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

typedef struct uz_mlpHls_t uz_mlpHls_t;

// function declarations
uz_mlpHls_t *uz_mlpInit(struct uz_mlpHls_config_t config);
XMlp *uz_mlpHls_getXilInstance(uz_mlpHls_t *instance);

#endif
