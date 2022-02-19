#ifndef UZ_MLPHLS_H
#define UZ_MLPHLS_H

// includes
#include "xil_types.h"
#include <stdbool.h>

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
	u32 layerBufferSize;
	bool loadParameters;
	bool exportLayers;

	u32 parEntries;
};

typedef struct uz_mlpHls_t uz_mlpHls_t;

// function declarations
uz_mlpHls_t *uz_mlpHls_init(struct uz_mlpHls_config_t config);

// set functions
void uz_mlpHls_setWeightAddress(uz_mlpHls_t *instance, u64 address);
void uz_mlpHls_setBiasAddress(uz_mlpHls_t *instance, u64 address);
void uz_mlpHls_setInputAddress(uz_mlpHls_t *instance, u64 address);
void uz_mlpHls_setOutputAddress(uz_mlpHls_t *instance, u64 address);
void uz_mlpHls_setLayerOutputAddress(uz_mlpHls_t *instance, u64 address);
void uz_mlpHls_setNumberNeurons(uz_mlpHls_t *instance, u32 value);
void uz_mlpHls_setNumberHiddenLayers(uz_mlpHls_t *instance, u32 value);
void uz_mlpHls_setNumberInputs(uz_mlpHls_t *instance, u32 value);
void uz_mlpHls_setNumberOutputs(uz_mlpHls_t *instance, u32 value);
void uz_mlpHls_setLoadParameters(uz_mlpHls_t *instance, bool value);
void uz_mlpHls_setExportLayers(uz_mlpHls_t *instance, bool value);

// get functions
u64 uz_mlpHls_getWeightAddress(uz_mlpHls_t *instance);
u64 uz_mlpHls_getBiasAddress(uz_mlpHls_t *instance);
u64 uz_mlpHls_getInputAddress(uz_mlpHls_t *instance);
u64 uz_mlpHls_getOutputAddress(uz_mlpHls_t *instance);
u64 uz_mlpHls_getLayerOutputAddress(uz_mlpHls_t *instance);
u32 uz_mlpHls_getNumberNeurons(uz_mlpHls_t *instance);
u32 uz_mlpHls_getNumberHiddenLayers(uz_mlpHls_t *instance);
u32 uz_mlpHls_getNumberInputs(uz_mlpHls_t *instance);
u32 uz_mlpHls_getNumberOutputs(uz_mlpHls_t *instance);
bool uz_mlpHls_getLoadParameter(uz_mlpHls_t *instance);
bool uz_mlpHls_getExportLayers(uz_mlpHls_t *instance);
u32 uz_mlpHls_getParEntries(uz_mlpHls_t *instance);
u32 uz_mlpHls_getLayerBufferSize(uz_mlpHls_t *instance);
u16 uz_mlpHls_getDeviceId(uz_mlpHls_t *instance);

#endif
