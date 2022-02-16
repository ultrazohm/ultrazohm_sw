#include "../../uz/uz_global_configuration.h"
#include "../../Cranium/src/cranium.h"
#include "uz_MlpHls.h"
#include "uz_MlpHlsPrivate.h"
#include "../../uz/uz_HAL.h"

// xilinx
#include "xparameters.h"
#include "xil_types.h"
#include "xstatus.h"

// IP core drivers
#include "xmlp.h"
#include "xbgd.h"

// system includes
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

struct uz_mlpHls_t
{
	XMlp xilInstance;
	struct uz_mlpHls_config_t config;
};

static const u32 N = 16; //  Rows of A aka weight Matrix
static const u32 K = N;  //  Cols of A and Rows of Input Vector
static const u32 KInput = 16;
static const u32 NOutput = 10;
static const u32 NumberOfHidden = 2;

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

static Network *configureCranium(void)
{
	Activation hiddenActivation[NumberOfHidden];
	size_t hiddenSize[NumberOfHidden];

	for (unsigned int i = 0; i < NumberOfHidden; i++)
	{
		hiddenActivation[i] = sigmoid;
		hiddenSize[i] = N;
	}

	Network *net = createNetwork(KInput, NumberOfHidden, hiddenSize, hiddenActivation, NOutput,
			linear);

	return net;
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

void uz_MlpHlsTestbench(void)
{
	srand((unsigned int) 2);

	const u32 ParameterBaseAddress = MLP_HLS_PARAMETER_BASE_ADDRESS;
	const u32 weightOffset = (N * KInput + (NumberOfHidden - 1) * N * K + NOutput * K)
			* sizeof(float);
	const u32 biasOffset = (NumberOfHidden * N + NOutput) * sizeof(float);
	const u32 inputOffset = KInput * sizeof(float);
	const u32 outputOffset = NOutput * sizeof(float);
	const u32 layerBufferSize = (KInput + NumberOfHidden * N + NOutput);

	Network *net = configureCranium();

	float *weightMemory = (float *) ParameterBaseAddress;
	float *biasMemory = (float *) (ParameterBaseAddress + weightOffset);
	float *inputBuffer = (float *) (ParameterBaseAddress + weightOffset + biasOffset);
	float *outputBuffer = (float *) (ParameterBaseAddress + weightOffset + biasOffset + inputOffset);
	float *layerBuffer = (float *) (ParameterBaseAddress + weightOffset + biasOffset + inputOffset
			+ outputOffset);
	Matrix *inputCran = createMatrix(1, KInput, inputBuffer);

	extractCraniumWeights(&weightMemory[N * KInput], weightMemory,
			&weightMemory[N * KInput + (NumberOfHidden - 1) * N * K], biasMemory,
			&biasMemory[NumberOfHidden * N], net);

	float *resultReference;

	struct uz_mlpHls_config_t mlpConfig =
	{
			.weightMemoryAddress = (u64) ((u32) weightMemory + MLP_HLS_PARAMETER_MEMORY_OFFSET_PL),
			.biasMemoryAddress = (u64) ((u32) biasMemory + MLP_HLS_PARAMETER_MEMORY_OFFSET_PL),
			.inputAddress = (u64) ((u32) inputBuffer + MLP_HLS_PARAMETER_MEMORY_OFFSET_PL),
			.outputAddress = (u64) ((u32) outputBuffer + MLP_HLS_PARAMETER_MEMORY_OFFSET_PL),
			.layerOutputAddress = (u64) ((u32) layerBuffer + MLP_HLS_PARAMETER_MEMORY_OFFSET_PL),
			.deviceId = XPAR_MLP_MLP_DEVICE_ID,
			.loadParameters = 1,
			.exportLayers = 1,
			.numberHiddenLayers = NumberOfHidden,
			.numberInputs = KInput,
			.numberOutputs = NOutput,
			.numberNeurons = N,
			.parEntries = 16 };

	uz_mlpHls_t *testInstance = uz_mlpInit(mlpConfig);
	while (1)
	{

		for (unsigned int i = 0; i < KInput; i++)
		{
			inputBuffer[i] = ((float) (rand() % 100)) / 100.0;
		}

		forwardPass(net, inputCran);
		resultReference = getOuput(net)->data;

		XMlp_Start(&testInstance->xilInstance);

		while (XMlp_IsIdle(&testInstance->xilInstance) == 0)
		{
			;
		}

		// check results

		const float precision = 1e-3;
		for (unsigned int i = 0; i < NOutput; i++)
		{
			float error = fabs(resultReference[i] - outputBuffer[i]);
			if (error > precision)
				uz_printf("Error at output entry %d", i);
			//uz_assert(error < precision);
		}
	}
	destroyNetwork(net);
}

void uz_BgdHlsTestbench(void)
{

}

void uz_mlpBgdHlsTestbench(bool testMlp, bool testBgd)
{
	if (testMlp)
		uz_MlpHlsTestbench();
	if (testBgd)
		uz_BgdHlsTestbench();
}

