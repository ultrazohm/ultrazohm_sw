// UltraZohm includes
#include "../include/uz_mlpBgdHls_testbench.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_mlpHls/uz_mlpHls.h"
#include "../IP_Cores/uz_bgdHls/uz_bgdHls.h"

// Reference implementation
#include "../Cranium/src/cranium.h"

// system includes
#include <stddef.h>

// Xilinx includes
#include "xmlp.h"
#include "xbgd.h"
#include "xparameters.h"

// defines
#define TRAINING_SAMPLES 2000U
#define BATCH_SIZE 20U
#define LEARNING_RATE 3.0f
#define NOUTPUT 16U
#define KINPUT 784U

// compiler defines
//#define TEST_TRAINING

static const u32 N = 16; //  Rows of A aka weight Matrix
static const u32 K = N;  //  Cols of A and Rows of Input Vector
static const u32 KInput = KINPUT;
static const u32 NOutput = NOUTPUT;
static const u32 NumberOfHidden = 2;

// input data and classes for training
#ifdef TEST_TRAINING
static const float uz_bgdHls_trainingData[KINPUT * TRAINING_SAMPLES] =
{
#include "uz_mlpBgdHls_trainingData/mnist_data.csv"
		};

static const float uz_mlpHls_trainingClasses[NOUTPUT * TRAINING_SAMPLES] =
{
#include "uz_mlpBgdHls_trainingData/mnist_labels.csv"
		};
#endif

static void mlpProcessSamples(XMlp *instance, float *inputValues, float *layerOutput,
		size_t samples, size_t layerBufferSize, size_t features)
{
	u64 inputAddress = (u64) ((u32) inputValues);
	u64 layerOutputAddress = (u64) ((u32) layerOutput);

	XMlp_Set_input_r(instance, inputAddress);
	XMlp_Set_axiLayerOutput(instance, layerOutputAddress);
	XMlp_Set_loadParameters(instance, (u32) 1);
	XMlp_Set_exportLayers(instance, (u32) 1);
	XMlp_Start(instance);
	while (XMlp_IsIdle(instance) == 0)
		;
	XMlp_Set_loadParameters(instance, (u32) 0);
	for (size_t i = 1; i < samples; i++)
	{
		inputAddress += features * sizeof(float);
		layerOutputAddress += layerBufferSize * sizeof(float);
		XMlp_Set_input_r(instance, inputAddress);
		XMlp_Set_axiLayerOutput(instance, layerOutputAddress);
		XMlp_Start(instance);
		while (XMlp_IsIdle(instance) == 0)
			;
	}
}

static void extractCraniumWeights(float *hiddenWeightMemory, float *inputWeightMemory,
		float *outputWeightMemory, float *hiddenBiasMemory, float *outputBiasMemory, Network *net)
{
	size_t newRows, newCols;
	newRows = net->connections[0]->weights->cols;
	newCols = net->connections[0]->weights->rows;
	Matrix *inputTransp = createMatrixZeroes(newRows, newCols);
	transposeInto(net->connections[0]->weights, inputTransp);
	for (unsigned int i = 0; i < newCols * newRows; i++)
	{
		inputWeightMemory[i] = inputTransp->data[i];
	}

	destroyMatrix(inputTransp);

	for (unsigned int i = 0; i < net->numConnections - 1; i++)
	{
		if (i < net->numConnections - 2)
		{
			newRows = net->connections[i + 1]->weights->cols;
			newCols = net->connections[i + 1]->weights->rows;
			Matrix *weightTransp = createMatrixZeroes(newRows, newCols);
			transposeInto(net->connections[i + 1]->weights, weightTransp);
			for (unsigned int j = 0; j < newRows * newCols; j++)
			{
				hiddenWeightMemory[i * newRows * newCols + j] = weightTransp->data[j];
			}
			destroyMatrix(weightTransp);
		}

		newRows = net->connections[i]->bias->cols * net->connections[i]->bias->rows;
		for (unsigned int j = 0; j < newRows; j++)
		{
			hiddenBiasMemory[i * newRows + j] = net->connections[i]->bias->data[j];
		}
	}

	newRows = net->connections[net->numConnections - 1]->weights->cols;
	newCols = net->connections[net->numConnections - 1]->weights->rows;
	Matrix *outputTransp = createMatrixZeroes(newRows, newCols);
	transposeInto(net->connections[net->numConnections - 1]->weights, outputTransp);

	for (unsigned int i = 0; i < newRows * newCols; i++)
	{
		outputWeightMemory[i] = outputTransp->data[i];
	}

	destroyMatrix(outputTransp);

	newRows = net->connections[net->numConnections - 1]->bias->cols
			* net->connections[net->numConnections - 1]->bias->rows;
	for (unsigned int i = 0; i < newRows; i++)
	{
		outputBiasMemory[i] = net->connections[net->numConnections - 1]->bias->data[i];
	}
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

static void uz_mlpHlsTestbench(Network *referenceImpl, uz_mlpHls_t *testInstance,
		float *inputBuffer, float *outputBuffer)
{
	Matrix *inputCran = createMatrix(1, KInput, inputBuffer);
	float *resultReference;
	while (1)
	{

		for (unsigned int i = 0; i < KInput; i++)
		{
			inputBuffer[i] = ((float) (rand() % 100)) / 100.0;
		}

		forwardPass(referenceImpl, inputCran);
		resultReference = getOuput(referenceImpl)->data;

		XMlp_Start(uz_mlpHls_getXilInstance(testInstance));

		while (XMlp_IsIdle(uz_mlpHls_getXilInstance(testInstance)) == 0)
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
	destroyNetwork(referenceImpl);
}

static void uz_bgdHlsTestbench(Network *referenceImpl, uz_mlpHls_t *testInstanceMlp,
		uz_bgdHls_t *testInstanceBgd)
{

}

int uz_mlpBgdHls_testbench(bool testMlp, bool testBgd)
{
	srand((unsigned int) 2);

	const u32 ParameterBaseAddress = MLP_HLS_PARAMETER_BASE_ADDRESS;
	const u32 weightOffset = (N * KInput + (NumberOfHidden - 1) * N * K + NOutput * K)
			* sizeof(float);
	const u32 biasOffset = (NumberOfHidden * N + NOutput) * sizeof(float);
	const u32 inputOffset = KInput * sizeof(float);
	const u32 outputOffset = NOutput * sizeof(float);
	const u32 layerBufferSize = (KInput + NumberOfHidden * N + NOutput);

	float *weightMemory = (float *) ParameterBaseAddress;
	float *biasMemory = (float *) (ParameterBaseAddress + weightOffset);
	float *inputBuffer = (float *) (ParameterBaseAddress + weightOffset + biasOffset);
	float *outputBuffer = (float *) (ParameterBaseAddress + weightOffset + biasOffset + inputOffset);
	float *layerBuffer = (float *) (ParameterBaseAddress + weightOffset + biasOffset + inputOffset
			+ outputOffset);
	Network *net = configureCranium();

	extractCraniumWeights(&weightMemory[N * KInput], weightMemory,
			&weightMemory[N * KInput + (NumberOfHidden - 1) * N * K], biasMemory,
			&biasMemory[NumberOfHidden * N], net);

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

#ifdef TEST_TRAINING
	struct uz_bgdHls_config_t bgdConfig =
	{
			.mlpResultsMemoryAddress = mlpConfig.layerOutputAddress,
			.classesMemoryAddress = (u64) ((u32) uz_mlpHls_trainingClasses),
			.weightInputMemoryAddress = mlpConfig.weightMemoryAddress,
			.biasInputMemoryAddress = mlpConfig.biasMemoryAddress,
			.weightOutputMemoryAddress = mlpConfig.weightMemoryAddress,
			.biasOutputMemoryAddress = mlpConfig.biasMemoryAddress,
			.numberInputs = mlpConfig.numberInputs,
			.numberOutputs = mlpConfig.numberOutputs,
			.numberHiddenLayers = mlpConfig.numberHiddenLayers,
			.numberNeurons = mlpConfig.numberNeurons,
			.loadParameters = mlpConfig.loadParameters,
			.batchSize = BATCH_SIZE,
			.learningRate = LEARNING_RATE,
			.parEntries = mlpConfig.parEntries,
			.deviceId = XPAR_MLP_BGD_DEVICE_ID };
	// uz_bgdHls_t *testInstanceBgd = uz_bgdInit(bgdConfig);
#endif

	uz_mlpHls_t *testInstanceMlp = uz_mlpInit(mlpConfig);
	if (testMlp)
		uz_mlpHlsTestbench(net, testInstanceMlp, inputBuffer, outputBuffer);

	return UZ_SUCCESS;
}
