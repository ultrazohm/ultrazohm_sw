#include "xparameters.h"
#if XPAR_XMLP_NUM_INSTANCES > 0
#include "../../uz/uz_global_configuration.h"
#include "uz_mlpHls.h"
#include "../../uz/uz_HAL.h"

// xilinx
#include "xstatus.h"
#include "xmlp.h"
#include "xgpio.h"

#define UZ_MLPHLS_PL_ADDRESS(R5_ADDRESS) ((R5_ADDRESS) + (UZ_MEMORY_OFFSET_PL))
#define UZ_MLPHLS_R5_ADDRESS(PL_ADDRESS) ((PL_ADDRESS) - (UZ_MEMORY_OFFSET_PL))

// pins at GPIO
#define UZ_MLPHLS_GPIO_START (1<<0)
#define UZ_MLPHLS_GPIO_DONE (1<<0)
#define UZ_MLPHLS_GPIO_IDLE (1<<1)
#define UZ_MLPHLS_GPIO_READY (1<<2)

struct uz_mlpHls_t
{
	XMlp xilInstance;
	XGpio xilGpioMonitor;
	XGpio xilGpioControl;
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

static void uz_mlpHls_updateLayerBufferSize(struct uz_mlpHls_config_t *config)
{
	uz_assert_not_NULL(config);
	config->layerBufferSize = config->numberInputs
			+ config->numberHiddenLayers * config->numberNeurons + config->numberOutputs;
}

uz_mlpHls_t *uz_mlpHls_init(struct uz_mlpHls_config_t config, XGpio monitor, XGpio control)
{
	uz_assert_not_zero(config.parEntries);
	XMlp xilInstance;
	uz_assert(XMlp_Initialize(&xilInstance, config.deviceId) == XST_SUCCESS);

	uz_mlpHls_t *instance = uz_mlpHls_allocation();
	instance->xilInstance = xilInstance;
	instance->config = config;
	instance->xilGpioMonitor = monitor;
	instance->xilGpioControl = control;

	uz_mlpHls_setWeightAddress(instance, config.weightMemoryAddress);
	uz_mlpHls_setBiasAddress(instance, config.biasMemoryAddress);
	uz_mlpHls_setInputAddress(instance, config.inputAddress);
	uz_mlpHls_setOutputAddress(instance, config.outputAddress);
	uz_mlpHls_setLayerOutputAddress(instance, config.layerOutputAddress);

	uz_mlpHls_setNumberNeurons(instance, config.numberNeurons);
	uz_mlpHls_setNumberHiddenLayers(instance, config.numberHiddenLayers);
	uz_mlpHls_setNumberInputs(instance, config.numberInputs);
	uz_mlpHls_setNumberOutputs(instance, config.numberOutputs);
	uz_mlpHls_setLoadParameters(instance, config.loadParameters);
	uz_mlpHls_setExportLayers(instance, config.exportLayers);

	return instance;
}

void uz_mlpHls_setWeightAddress(uz_mlpHls_t *instance, u64 address)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(address);
	u64 hwAddress = UZ_MLPHLS_PL_ADDRESS(address);
	instance->config.weightMemoryAddress = hwAddress;
	XMlp_Set_axiWeightInput(&instance->xilInstance, hwAddress);
}

void uz_mlpHls_setBiasAddress(uz_mlpHls_t *instance, u64 address)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(address);
	u64 hwAddress = UZ_MLPHLS_PL_ADDRESS(address);
	instance->config.biasMemoryAddress = hwAddress;
	XMlp_Set_axiBiasInput(&instance->xilInstance, hwAddress);
}

void uz_mlpHls_setInputAddress(uz_mlpHls_t *instance, u64 address)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(address);
	u64 hwAddress = UZ_MLPHLS_PL_ADDRESS(address);
	instance->config.inputAddress = hwAddress;
	XMlp_Set_input_r(&instance->xilInstance, hwAddress);
}

void uz_mlpHls_setOutputAddress(uz_mlpHls_t *instance, u64 address)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(address);
	u64 hwAddress = UZ_MLPHLS_PL_ADDRESS(address);
	instance->config.outputAddress = hwAddress;
	XMlp_Set_output_r(&instance->xilInstance, hwAddress);
}

void uz_mlpHls_setLayerOutputAddress(uz_mlpHls_t *instance, u64 address)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(address);
	u64 hwAddress = UZ_MLPHLS_PL_ADDRESS(address);
	instance->config.layerOutputAddress = hwAddress;
	XMlp_Set_axiLayerOutput(&instance->xilInstance, hwAddress);
}

void uz_mlpHls_setNumberNeurons(uz_mlpHls_t *instance, u32 value)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(value);
	uz_assert(value % instance->config.parEntries == 0);
	instance->config.numberNeurons = value;
	XMlp_Set_numberNeurons(&instance->xilInstance, value);
	uz_mlpHls_updateLayerBufferSize(&instance->config);
}

void uz_mlpHls_setNumberHiddenLayers(uz_mlpHls_t *instance, u32 value)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(value);
	instance->config.numberHiddenLayers = value;
	XMlp_Set_numberLayers(&instance->xilInstance, value);
	uz_mlpHls_updateLayerBufferSize(&instance->config);
}

void uz_mlpHls_setNumberInputs(uz_mlpHls_t *instance, u32 value)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(value);
	uz_assert(value % instance->config.parEntries == 0);
	instance->config.numberInputs = value;
	XMlp_Set_numberInputs(&instance->xilInstance, value);
	uz_mlpHls_updateLayerBufferSize(&instance->config);
}

void uz_mlpHls_setNumberOutputs(uz_mlpHls_t *instance, u32 value)
{
	uz_assert_not_NULL(instance);
	uz_assert_not_zero(value);
	instance->config.numberOutputs = value;
	XMlp_Set_numberOutputs(&instance->xilInstance, value);
	uz_mlpHls_updateLayerBufferSize(&instance->config);
}

void uz_mlpHls_setLoadParameters(uz_mlpHls_t *instance, bool value)
{
	uz_assert_not_NULL(instance);
	instance->config.loadParameters = value;
	if (value)
		XMlp_Set_loadParameters(&instance->xilInstance, (u32) 1);
	else
		XMlp_Set_loadParameters(&instance->xilInstance, (u32) 0);
}

void uz_mlpHls_setExportLayers(uz_mlpHls_t *instance, bool value)
{
	uz_assert_not_NULL(instance);
	instance->config.exportLayers = value;
	if (value)
		XMlp_Set_exportLayers(&instance->xilInstance, (u32) 1);
	else
		XMlp_Set_exportLayers(&instance->xilInstance, (u32) 0);
}

u64 uz_mlpHls_getWeightAddress(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return UZ_MLPHLS_R5_ADDRESS(instance->config.weightMemoryAddress);
}

u64 uz_mlpHls_getBiasAddress(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return UZ_MLPHLS_R5_ADDRESS(instance->config.biasMemoryAddress);
}

u64 uz_mlpHls_getInputAddress(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return UZ_MLPHLS_R5_ADDRESS(instance->config.inputAddress);
}

u64 uz_mlpHls_getOutputAddress(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return UZ_MLPHLS_R5_ADDRESS(instance->config.outputAddress);
}

u64 uz_mlpHls_getLayerOutputAddress(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return UZ_MLPHLS_R5_ADDRESS(instance->config.layerOutputAddress);
}

u32 uz_mlpHls_getNumberNeurons(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.numberNeurons;
}

u32 uz_mlpHls_getNumberHiddenLayers(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.numberHiddenLayers;
}

u32 uz_mlpHls_getNumberInputs(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.numberInputs;
}

u32 uz_mlpHls_getNumberOutputs(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.numberOutputs;
}

bool uz_mlpHls_getLoadParameter(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.loadParameters;
}

bool uz_mlpHls_getExportLayers(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.exportLayers;
}

u32 uz_mlpHls_getParEntries(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.parEntries;
}

u32 uz_mlpHls_getLayerBufferSize(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.layerBufferSize;
}

u16 uz_mlpHls_getDeviceId(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	return instance->config.deviceId;
}

void uz_mlpHls_start(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	//XMlp_Start(&instance->xilInstance);
	XGpio_DiscreteSet(&instance->xilGpioControl, 1, UZ_MLPHLS_GPIO_START);
	XGpio_DiscreteClear(&instance->xilGpioControl, 1, UZ_MLPHLS_GPIO_START);
}

bool uz_mlpHls_isIdle(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	bool return_value;
//	if(XMlp_IsIdle(&instance->xilInstance) != 0)
//		return_value = true;
//	else
//		return_value = false;

	if(XGpio_DiscreteRead(&instance->xilGpioMonitor, 1) & UZ_MLPHLS_GPIO_IDLE)
		return_value = true;
	else
		return_value = false;

	return return_value;
}

bool uz_mlpHls_isReady(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	bool return_value;
//	if(XMlp_IsReady(&instance->xilInstance) != 0)
//		return_value = true;
//	else
//		return_value = false;

	if(XGpio_DiscreteRead(&instance->xilGpioMonitor, 1) & UZ_MLPHLS_GPIO_READY)
		return_value = true;
	else
		return_value = false;

	return return_value;
}

bool uz_mlpHls_isDone(uz_mlpHls_t *instance)
{
	uz_assert_not_NULL(instance);
	bool return_value;
//	if(XMlp_IsDone(&instance->xilInstance) != 0)
//		return_value = true;
//	else
//		return_value = false;

	if(XGpio_DiscreteRead(&instance->xilGpioMonitor, 1) & UZ_MLPHLS_GPIO_DONE)
		return_value = true;
	else
		return_value = false;

	return return_value;
}

#endif
