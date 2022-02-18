#include "uz_mlpHls.h"
#include "../../uz/uz_HAL.h"

// xilinx
#include "xstatus.h"

// IP core drivers
#include "xmlp.h"

struct uz_mlpHls_t
{
	XMlp xilInstance;
	struct uz_mlpHls_config_t config;
};

static size_t instance_counter = 0U;
static uz_mlpHls_t instances[XPAR_XMLP_NUM_INSTANCES] =
{ 0 };

static uz_mlpHls_t *uz_mlpHls_allocation(void);

static uz_mlpHls_t *uz_mlpHls_allocation(void)
{
	uz_assert(instance_counter < XPAR_XMLP_NUM_INSTANCES);
	uz_mlpHls_t *self = &instances[instance_counter];
	instance_counter++;
	return (self);
}

uz_mlpHls_t *uz_mlpInit(struct uz_mlpHls_config_t config)
{
	uz_assert_not_zero(config.weightMemoryAddress);
	uz_assert_not_zero(config.biasMemoryAddress);
	uz_assert_not_zero(config.inputAddress);
	uz_assert_not_zero(config.outputAddress);
	uz_assert_not_zero(config.layerOutputAddress);

	uz_assert(config.numberHiddenLayers > 0);
	uz_assert(config.parEntries > 0);
	uz_assert(config.numberInputs % config.parEntries == 0);
	uz_assert(config.numberInputs > 0);
	uz_assert(config.numberNeurons % config.parEntries == 0);
	uz_assert(config.numberNeurons > 0);
	uz_assert(config.numberOutputs > 0);

	XMlp xilInstance;
	uz_assert(XMlp_Initialize(&xilInstance, config.deviceId) == XST_SUCCESS);

	uz_mlpHls_t *instance = uz_mlpHls_allocation();
	instance->xilInstance = xilInstance;
	instance->config = config;
	XMlp *xilPtr = &instance->xilInstance;

	XMlp_Set_axiWeightInput(xilPtr, config.weightMemoryAddress);
	XMlp_Set_axiBiasInput(xilPtr, config.biasMemoryAddress);
	XMlp_Set_input_r(xilPtr, config.inputAddress);
	XMlp_Set_output_r(xilPtr, config.outputAddress);
	XMlp_Set_axiLayerOutput(xilPtr, config.layerOutputAddress);

	XMlp_Set_loadParameters(xilPtr, config.loadParameters);
	XMlp_Set_exportLayers(xilPtr, config.exportLayers);
	XMlp_Set_numberInputs(xilPtr, config.numberInputs);
	XMlp_Set_numberOutputs(xilPtr, config.numberOutputs);
	XMlp_Set_numberLayers(xilPtr, config.numberHiddenLayers);
	XMlp_Set_numberNeurons(xilPtr, config.numberNeurons);

	return instance;
}

XMlp *uz_mlpHls_getXilInstance(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return &instance->xilInstance;
}
