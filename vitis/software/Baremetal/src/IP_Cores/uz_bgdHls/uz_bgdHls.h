#pragma once

// includes
#include "xil_types.h"
#include <stdbool.h>

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
	u32 layerBufferSize;
	bool loadParameters;
	u32 batchSize;
	u32 batchBufferSize;
	float learningRate;

	u32 parEntries;
};

// typedefs
typedef struct uz_bgdHls_t uz_bgdHls_t;

// function declarations
uz_bgdHls_t *uz_bgdHls_init(struct uz_bgdHls_config_t config);

// set functions
void uz_bgdHls_setMlpResultsAddress(uz_bgdHls_t *instance, u64 address);
void uz_bgdHls_setClassesAddress(uz_bgdHls_t *instance, u64 address);
void uz_bgdHls_setWeightInputAddress(uz_bgdHls_t *instance, u64 address);
void uz_bgdHls_setBiasInputAddress(uz_bgdHls_t *instance, u64 address);
void uz_bgdHls_setWeightOutputAddress(uz_bgdHls_t *instance, u64 address);
void uz_bgdHls_setBiasOutputAddress(uz_bgdHls_t *instance, u64 address);
void uz_bgdHls_setNumberInputs(uz_bgdHls_t *instance, u32 value);
void uz_bgdHls_setNumberOutputs(uz_bgdHls_t *instance, u32 value);
void uz_bgdHls_setNumberHiddenLayers(uz_bgdHls_t *instance, u32 value);
void uz_bgdHls_setNumberNeurons(uz_bgdHls_t *instance, u32 value);
void uz_bgdHls_setLoadParameters(uz_bgdHls_t *instance, bool value);
void uz_bgdHls_setBatchSize(uz_bgdHls_t *instance, u32 value);
void uz_bgdHls_setLearningRate(uz_bgdHls_t *instance, float value);

// get functions
u64 uz_bgdHls_getMlpResultsAddress(uz_bgdHls_t *instance);
u64 uz_bgdHls_getClassesAddress(uz_bgdHls_t *instance);
u64 uz_bgdHls_getWeightInputAddress(uz_bgdHls_t *instance);
u64 uz_bgdHls_getBiasInputAddress(uz_bgdHls_t *instance);
u64 uz_bgdHls_getWeightOutputAddress(uz_bgdHls_t *instance);
u64 uz_bgdHls_getBiasOutputAddress(uz_bgdHls_t *instance);
u32 uz_bgdHls_getNumberInputs(uz_bgdHls_t *instance);
u32 uz_bgdHls_getNumberOutputs(uz_bgdHls_t *instance);
u32 uz_bgdHls_getNumberHiddenLayers(uz_bgdHls_t *instance);
u32 uz_bgdHls_getNumberNeurons(uz_bgdHls_t *instance);
bool uz_bgdHls_getLoadParameters(uz_bgdHls_t *instance);
u32 uz_bgdHls_getBatchSize(uz_bgdHls_t *instance);
float uz_bgdHls_getLearningRate(uz_bgdHls_t *instance);
u32 uz_bgdHls_getLayerBufferSize(uz_bgdHls_t *instance);
u32 uz_bgdHls_getBatchBufferSize(uz_bgdHls_t *instance);

// control functions
void uz_bgdHls_start(uz_bgdHls_t *instance);
bool uz_bgdHls_isIdle(uz_bgdHls_t *instance);
bool uz_bgdHls_isReady(uz_bgdHls_t *instance);
bool uz_bgdHls_isDone(uz_bgdHls_t *instance);
