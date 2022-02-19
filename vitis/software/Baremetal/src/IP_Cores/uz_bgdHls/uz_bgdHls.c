#include "xparameters.h"
#if XPAR_XBGD_NUM_INSTANCES > 0
#include "../../uz/uz_global_configuration.h"
#include "uz_bgdHls.h"
#include "../../uz/uz_HAL.h"

// xilinx
#include "xstatus.h"
#include "xbgd.h"

#define UZ_BGDHLS_PL_ADDRESS(R5_ADDRESS) ((R5_ADDRESS) + (UZ_MEMORY_OFFSET_PL))
#define UZ_BGDHLS_R5_ADDRESS(PL_ADDRESS) ((PL_ADDRESS) - (UZ_MEMORY_OFFSET_PL))

struct uz_bgdHls_t
{
	XBgd xilInstance;
	struct uz_bgdHls_config_t config;
};

static size_t instance_counter = 0U;
static uz_bgdHls_t instances[XPAR_XBGD_NUM_INSTANCES] =
{ 0 };

static uz_bgdHls_t *uz_bgdHls_allocation(void);

static uz_bgdHls_t *uz_bgdHls_allocation(void)
{
	uz_assert(instance_counter < XPAR_XBGD_NUM_INSTANCES);
	uz_bgdHls_t *self = &instances[instance_counter];
	instance_counter++;
	return (self);
}

static void uz_bgdHls_updateBufferSizes(struct uz_bgdHls_config_t *config)
{
	uz_assert_not_NULL(config);
	config->layerBufferSize = config->numberInputs
			+ config->numberHiddenLayers * config->numberNeurons + config->numberOutputs;
	config->batchBufferSize = config->layerBufferSize * config->batchSize;
}

uz_bgdHls_t *uz_bgdHls_init(struct uz_bgdHls_config_t config)
{
	uz_assert_not_zero(config.parEntries);
	XBgd xilInstance;
	uz_assert(XBgd_Initialize(&xilInstance, config.deviceId) == XST_SUCCESS);

	uz_bgdHls_t *instance = uz_bgdHls_allocation();
	instance->xilInstance = xilInstance;
	instance->config = config;

	uz_bgdHls_setMlpResultsAddress(instance, config.mlpResultsMemoryAddress);
	uz_bgdHls_setClassesAddress(instance, config.classesMemoryAddress);
	uz_bgdHls_setWeightInputAddress(instance, config.weightInputMemoryAddress);
	uz_bgdHls_setBiasInputAddress(instance, config.biasInputMemoryAddress);
	uz_bgdHls_setWeightOutputAddress(instance, config.weightOutputMemoryAddress);
	uz_bgdHls_setBiasOutputAddress(instance, config.biasOutputMemoryAddress);

	uz_bgdHls_setNumberInputs(instance, config.numberInputs);
	uz_bgdHls_setNumberOutputs(instance, config.numberOutputs);
	uz_bgdHls_setNumberHiddenLayers(instance, config.numberHiddenLayers);
	uz_bgdHls_setNumberNeurons(instance, config.numberNeurons);
	uz_bgdHls_setLoadParameters(instance, config.loadParameters);
	uz_bgdHls_setBatchSize(instance, config.batchSize);
	uz_bgdHls_setLearningRate(instance, config.learningRate);

	return instance;
}

void uz_bgdHls_setMlpResultsAddress(uz_bgdHls_t *instance, u64 address)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(address);
	u64 hwAddress = UZ_BGDHLS_PL_ADDRESS(address);
	instance->config.mlpResultsMemoryAddress = hwAddress;
	XBgd_Set_axiMlpResultsInput(&instance->xilInstance, hwAddress);
}

void uz_bgdHls_setClassesAddress(uz_bgdHls_t *instance, u64 address)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(address);
	u64 hwAddress = UZ_BGDHLS_PL_ADDRESS(address);
	instance->config.classesMemoryAddress = hwAddress;
	XBgd_Set_axiClassesInput(&instance->xilInstance, hwAddress);
}

void uz_bgdHls_setWeightInputAddress(uz_bgdHls_t *instance, u64 address)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(address);
	u64 hwAddress = UZ_BGDHLS_PL_ADDRESS(address);
	instance->config.weightInputMemoryAddress = hwAddress;
	XBgd_Set_axiWeightInput(&instance->xilInstance, hwAddress);
}

void uz_bgdHls_setBiasInputAddress(uz_bgdHls_t *instance, u64 address)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(address);
	u64 hwAddress = UZ_BGDHLS_PL_ADDRESS(address);
	instance->config.biasInputMemoryAddress = hwAddress;
	XBgd_Set_axiBiasInput(&instance->xilInstance, hwAddress);
}

void uz_bgdHls_setWeightOutputAddress(uz_bgdHls_t *instance, u64 address)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(address);
	u64 hwAddress = UZ_BGDHLS_PL_ADDRESS(address);
	instance->config.weightOutputMemoryAddress = hwAddress;
	XBgd_Set_axiWeightOutput(&instance->xilInstance, hwAddress);
}

void uz_bgdHls_setBiasOutputAddress(uz_bgdHls_t *instance, u64 address)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(address);
	u64 hwAddress = UZ_BGDHLS_PL_ADDRESS(address);
	instance->config.biasOutputMemoryAddress = hwAddress;
	XBgd_Set_axiBiasOutput(&instance->xilInstance, hwAddress);
}

void uz_bgdHls_setNumberInputs(uz_bgdHls_t *instance, u32 value)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(value);
	uz_assert(value % instance->config.parEntries == 0);
	instance->config.numberInputs = value;
	XBgd_Set_numberInputs(&instance->xilInstance, value);
	uz_bgdHls_updateBufferSizes(&instance->config);
}

void uz_bgdHls_setNumberOutputs(uz_bgdHls_t *instance, u32 value)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(value);
	uz_assert(value % instance->config.parEntries == 0);
	instance->config.numberOutputs = value;
	XBgd_Set_numberOutputs(&instance->xilInstance, value);
	uz_bgdHls_updateBufferSizes(&instance->config);
}

void uz_bgdHls_setNumberHiddenLayers(uz_bgdHls_t *instance, u32 value)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(value);
	instance->config.numberHiddenLayers = value;
	XBgd_Set_numberLayers(&instance->xilInstance, value);
	uz_bgdHls_updateBufferSizes(&instance->config);
}

void uz_bgdHls_setNumberNeurons(uz_bgdHls_t *instance, u32 value)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(value);
	uz_assert(value % instance->config.parEntries == 0);
	instance->config.numberNeurons = value;
	XBgd_Set_numberNeurons(&instance->xilInstance, value);
	uz_bgdHls_updateBufferSizes(&instance->config);
}

void uz_bgdHls_setLoadParameters(uz_bgdHls_t *instance, bool value)
{
	uz_assert_not_NULL(instance);
	instance->config.loadParameters = value;
	if (value)
		XBgd_Set_loadParameters(&instance->xilInstance, (u32) 1);
	else
		XBgd_Set_loadParameters(&instance->xilInstance, (u32) 0);
}

void uz_bgdHls_setBatchSize(uz_bgdHls_t *instance, u32 value)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(value);
	instance->config.batchSize = value;
	XBgd_Set_batchSize(&instance->xilInstance, value);
	uz_bgdHls_updateBufferSizes(&instance->config);
}

void uz_bgdHls_setLearningRate(uz_bgdHls_t *instance, float value)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(value);
	instance->config.learningRate = value;
	// this cast is necessary see Xilinx UG1399 p. 208
	XBgd_Set_learningRate(&instance->xilInstance, *((u32*) &instance->config.learningRate));
}

u64 uz_bgdHls_getMlpResultsAddress(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return UZ_BGDHLS_R5_ADDRESS(instance->config.mlpResultsMemoryAddress);
}

u64 uz_bgdHls_getClassesAddress(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return UZ_BGDHLS_R5_ADDRESS(instance->config.classesMemoryAddress);
}

u64 uz_bgdHls_getWeightInputAddress(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return UZ_BGDHLS_R5_ADDRESS(instance->config.weightInputMemoryAddress);
}

u64 uz_bgdHls_getBiasInputAddress(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return UZ_BGDHLS_R5_ADDRESS(instance->config.biasInputMemoryAddress);
}

u64 uz_bgdHls_getWeightOutputAddress(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return UZ_BGDHLS_R5_ADDRESS(instance->config.weightOutputMemoryAddress);
}

u64 uz_bgdHls_getBiasOutputAddress(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return UZ_BGDHLS_R5_ADDRESS(instance->config.biasOutputMemoryAddress);
}

u32 uz_bgdHls_getNumberInputs(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.numberInputs;
}

u32 uz_bgdHls_getNumberOutputs(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.numberOutputs;
}

u32 uz_bgdHls_getNumberHiddenLayers(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.numberHiddenLayers;
}

u32 uz_bgdHls_getNumberNeurons(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.numberNeurons;
}

bool uz_bgdHls_getLoadParameters(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.loadParameters;
}

u32 uz_bgdHls_getBatchSize(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.batchSize;
}

float uz_bgdHls_getLearningRate(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.learningRate;
}

u32 uz_bgdHls_getLayerBufferSize(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.layerBufferSize;
}

u32 uz_bgdHls_getBatchBufferSize(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.batchBufferSize;
}

#endif
