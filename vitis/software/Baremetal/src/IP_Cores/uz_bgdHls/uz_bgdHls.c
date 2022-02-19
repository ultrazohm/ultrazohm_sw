#include "uz_bgdHls.h"
#include "../../uz/uz_HAL.h"

// xilinx
#include "xstatus.h"

// IP core drivers
#include "xbgd.h"

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

static void uz_bgdHls_updateLayerBufferSize(struct uz_bgdHls_config_t *config)
{
	uz_assert_not_NULL(config);
	config->layerBufferSize = config->numberInputs
			+ config->numberHiddenLayers * config->numberNeurons + config->numberOutputs;
}

uz_bgdHls_t *uz_bgdHls_init(struct uz_bgdHls_config_t config)
{
	uz_assert_not_zero(config.mlpResultsMemoryAddress);
	uz_assert_not_zero(config.classesMemoryAddress);
	uz_assert_not_zero(config.weightInputMemoryAddress);
	uz_assert_not_zero(config.biasInputMemoryAddress);
	uz_assert_not_zero(config.weightOutputMemoryAddress);
	uz_assert_not_zero(config.biasOutputMemoryAddress);

	uz_assert(config.numberHiddenLayers > 0);
	uz_assert(config.parEntries > 0);
	uz_assert(config.numberInputs % config.parEntries == 0);
	uz_assert(config.numberInputs > 0);
	uz_assert(config.numberNeurons % config.parEntries == 0);
	uz_assert(config.numberNeurons > 0);
	uz_assert(config.numberOutputs > 0);
	uz_assert(config.batchSize > 0);
	uz_assert(config.learningRate > 0);

	XBgd xilInstance;
	uz_assert(XBgd_Initialize(&xilInstance, config.deviceId) == XST_SUCCESS);

	uz_bgdHls_t *instance = uz_bgdHls_allocation();
	instance->xilInstance = xilInstance;
	instance->config = config;
	uz_bgdHls_updateLayerBufferSize(&instance->config);
	XBgd *xilPtr = &instance->xilInstance;

	XBgd_Set_axiMlpResultsInput(xilPtr, config.mlpResultsMemoryAddress);
	XBgd_Set_axiClassesInput(xilPtr, config.classesMemoryAddress);
	XBgd_Set_axiWeightInput(xilPtr, config.weightInputMemoryAddress);
	XBgd_Set_axiBiasInput(xilPtr, config.biasInputMemoryAddress);
	XBgd_Set_axiWeightOutput(xilPtr, config.weightOutputMemoryAddress);
	XBgd_Set_axiBiasOutput(xilPtr, config.biasOutputMemoryAddress);

	XBgd_Set_numberInputs(xilPtr, config.numberInputs);
	XBgd_Set_numberOutputs(xilPtr, config.numberOutputs);
	XBgd_Set_numberLayers(xilPtr, config.numberHiddenLayers);
	XBgd_Set_numberNeurons(xilPtr, config.numberNeurons);
	XBgd_Set_loadParameters(xilPtr, config.loadParameters);
	XBgd_Set_batchSize(xilPtr, config.batchSize);
	// this cast is necessary see Xilinx UG1399 p. 208
	XBgd_Set_learningRate(xilPtr, *((u32*) &config.learningRate));

	return instance;
}

XBgd *uz_bgdHls_getXilInstance(uz_bgdHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return &instance->xilInstance;
}
