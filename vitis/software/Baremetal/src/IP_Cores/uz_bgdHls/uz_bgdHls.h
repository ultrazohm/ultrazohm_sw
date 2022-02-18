#pragma once

// includes
#include "xil_types.h"
#include "xbgd.h"
#include "xparameters.h"

// defines

// structs
struct uz_bgdHls_config_t
{
	u16 deviceId;

	u64 mlpResultsMemoryAddress;
	u64 classesMemoryAddress;
	u64 weightInputMemoryAddress;
	u64 biasInputMemoryAddress;
	u64 weightOutputMemoryAddress;
	u64 biasOutputMemoryAddress;

	u32 numberInputs;
	u32 numberOutputs;
	u32 numberHiddenLayers;
	u32 numberNeurons;
	u32 loadParameters;
	u32 batchSize;
	float learningRate;

	u32 parEntries;
};

// typedefs
typedef struct uz_bgdHls_t uz_bgdHls_t;

// function declarations
uz_bgdHls_t *uz_bgdInit(struct uz_bgdHls_config_t config);
XBgd *uz_bgdHls_getXilInstance(uz_bgdHls_t *instance);
