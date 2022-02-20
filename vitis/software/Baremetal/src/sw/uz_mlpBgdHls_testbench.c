// UltraZohm includes
#include "../include/uz_mlpBgdHls_testbench.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_mlpHls/uz_mlpHls.h"
#include "../IP_Cores/uz_bgdHls/uz_bgdHls.h"

// Reference implementation
#include "../Cranium/src/cranium.h"

// system includes
#include <stddef.h>
#include <stdbool.h>

// Xilinx includes
#include "xparameters.h"

// defines
#define TRAINING_SAMPLES 2000U
#define BATCH_SIZE 20U
#define LEARNING_RATE 3.0f
#define NUMBER_OUTPUTS 16U
#define NUMBER_INPUTS 784U
#define NUMBER_HIDDEN 2U
#define NUMBER_NEURONS 16U
#define PAR_ENTRIES 16U

// reference implementation
#define HIDDEN_ACTIVATION sigmoid
#define OUTPUT_ACTIVATION linear

// compiler defines
//#define TEST_TRAINING

// input data and classes for training
#ifdef TEST_TRAINING
static float uz_bgdHls_trainingData[NUMBER_INPUTS * TRAINING_SAMPLES] =
{
#include "uz_mlpBgdHls_trainingData/mnist_data.csv"
		};

static float uz_bgdHls_trainingClasses[NUMBER_OUTPUTS * TRAINING_SAMPLES] =
{
#include "uz_mlpBgdHls_trainingData/mnist_labels.csv"
		};
#endif

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

static void uz_mlpHlsTestbench(Network *referenceImpl, uz_mlpHls_t *testInstance)
{
	float *inputBuffer = (float *) ((u32) uz_mlpHls_getInputAddress(testInstance));
	float *outputBuffer = (float *) ((u32) uz_mlpHls_getOutputAddress(testInstance));
	Matrix *inputCran = createMatrix(1, uz_mlpHls_getNumberInputs(testInstance), inputBuffer);
	float *resultReference;
	while (1)
	{

		for (unsigned int i = 0; i < uz_mlpHls_getNumberInputs(testInstance); i++)
		{
			inputBuffer[i] = ((float) (rand() % 100)) / 100.0;
		}

		forwardPass(referenceImpl, inputCran);
		resultReference = getOuput(referenceImpl)->data;

		uz_mlpHls_start(testInstance);

		while (uz_mlpHls_isIdle(testInstance) == false)
		{
			;
		}

		// check results

		const float precision = 1e-3;
		for (unsigned int i = 0; i < uz_mlpHls_getNumberOutputs(testInstance); i++)
		{
			float error = fabs(resultReference[i] - outputBuffer[i]);
			if (error > precision)
				uz_printf("Error at output entry %d", i);
			//uz_assert(error < precision);
		}
	}
	destroyNetwork(referenceImpl);
}

#ifdef TEST_TRAINING

static void mlpProcessBatch(uz_mlpHls_t *mlpInstance, uz_bgdHls_t *bgdInstance)
{
	u64 inputAddress = uz_mlpHls_getInputAddress(mlpInstance);
	u64 layerOutputAddress = uz_mlpHls_getLayerOutputAddress(mlpInstance);

	uz_mlpHls_setLoadParameters(mlpInstance, true);
	uz_mlpHls_setExportLayers(mlpInstance, true);
	uz_mlpHls_start(mlpInstance);
	while (uz_mlpHls_isIdle(mlpInstance) == false)
		;
	uz_mlpHls_setLoadParameters(mlpInstance, false);
	for (size_t i = 1; i < uz_bgdHls_getBatchSize(bgdInstance); i++)
	{
		inputAddress += uz_mlpHls_getNumberInputs(mlpInstance) * sizeof(float);
		layerOutputAddress += uz_mlpHls_getLayerBufferSize(mlpInstance) * sizeof(float);
		uz_mlpHls_setInputAddress(mlpInstance, inputAddress);
		uz_mlpHls_setLayerOutputAddress(mlpInstance, layerOutputAddress);
		uz_mlpHls_start(mlpInstance);
		while (uz_mlpHls_isIdle(mlpInstance) == false)
			;
	}
}

static float **createCraniumInputArray(float *values, size_t rows, size_t cols)
{
	float **craniumInput = (float **) malloc(rows * sizeof(float *));

	for (size_t i = 0; i < rows; i++)
	{
		craniumInput[i] = &values[i * cols];
	}

	return craniumInput;
}

static void uz_bgdHlsTestbench(Network *referenceImpl, uz_mlpHls_t *testInstanceMlp,
		uz_bgdHls_t *testInstanceBgd)
{
	const u32 batchSize = uz_bgdHls_getBatchSize(testInstanceBgd);
	const u32 numberInputs = uz_mlpHls_getNumberInputs(testInstanceMlp);
	const u32 numberOutputs = uz_mlpHls_getNumberOutputs(testInstanceMlp);

	uz_assert(TRAINING_SAMPLES % batchSize == 0);
	uz_assert(
			uz_mlpHls_getNumberInputs(testInstanceMlp)
					== uz_bgdHls_getNumberInputs(testInstanceBgd));
	uz_assert(
			uz_mlpHls_getNumberOutputs(testInstanceMlp)
					== uz_bgdHls_getNumberOutputs(testInstanceBgd));
	uz_assert(
			uz_mlpHls_getNumberNeurons(testInstanceMlp)
					== uz_bgdHls_getNumberNeurons(testInstanceBgd));
	uz_assert(
			uz_mlpHls_getNumberHiddenLayers(testInstanceMlp)
					== uz_bgdHls_getNumberHiddenLayers(testInstanceBgd));

	u32 maxIter = TRAINING_SAMPLES / batchSize;
	float **craniumInput = createCraniumInputArray(uz_bgdHls_trainingData, TRAINING_SAMPLES,
			numberInputs);
	float **craniumClasses = createCraniumInputArray(uz_bgdHls_trainingClasses, TRAINING_SAMPLES,
			numberOutputs);

	DataSet *cranTrainingData = createDataSet(TRAINING_SAMPLES, numberInputs, craniumInput);
	DataSet *cranTrainingClasses = createDataSet(TRAINING_SAMPLES, numberOutputs, craniumClasses);

	ParameterSet params;
	params.network = referenceImpl;
	params.data = cranTrainingData;
	params.classes = cranTrainingClasses;
	params.lossFunction = MEAN_SQUARED_ERROR;
	params.batchSize = batchSize;
	params.learningRate = uz_bgdHls_getLearningRate(testInstanceBgd);
	params.searchTime = 0;
	params.regularizationStrength = 0;
	params.momentumFactor = 0;
	params.maxIters = TRAINING_SAMPLES;
	params.shuffle = 0;
	params.verbose = 0;
	optimize(params);

	float cranAccuracy = accuracy(referenceImpl, cranTrainingData, cranTrainingClasses);
	uz_printf("Accuracy of Cranium optimization %f \n", cranAccuracy);

	uz_bgdHls_setLoadParameters(testInstanceBgd, true);
	for (size_t iter = 0; iter < maxIter; iter++)
	{
		u64 inputValues = (u64) ((u32) &uz_bgdHls_trainingData[iter * batchSize * numberInputs]);
		uz_mlpHls_setInputAddress(testInstanceMlp, inputValues);
		mlpProcessBatch(testInstanceMlp, testInstanceBgd);

		uz_bgdHls_start(testInstanceBgd);
		while (uz_bgdHls_isIdle(testInstanceBgd) == false)
			;
		if (iter == 0)
		{
			uz_bgdHls_setLoadParameters(testInstanceBgd, false);
		}
	}
}

#endif

int uz_mlpBgdHls_testbench()
{
	srand((unsigned int) 2);

	const u32 weightOffset =
			((NUMBER_INPUTS + (NUMBER_HIDDEN - 1) * NUMBER_NEURONS + NUMBER_OUTPUTS)
					* NUMBER_NEURONS) * sizeof(float);
	const u32 biasOffset = (NUMBER_HIDDEN * NUMBER_NEURONS + NUMBER_OUTPUTS) * sizeof(float);
	const u32 inputOffset = NUMBER_INPUTS * sizeof(float);
	const u32 outputOffset = NUMBER_OUTPUTS * sizeof(float);

	struct uz_mlpHls_config_t mlpConfig =
	{
			.weightMemoryAddress = (u64) MLP_HLS_PARAMETER_BASE_ADDRESS,
			.biasMemoryAddress = (u64) (MLP_HLS_PARAMETER_BASE_ADDRESS + weightOffset),
			.inputAddress = (u64) (MLP_HLS_PARAMETER_BASE_ADDRESS + weightOffset + biasOffset),
			.outputAddress = (u64) (MLP_HLS_PARAMETER_BASE_ADDRESS + weightOffset + biasOffset
					+ inputOffset),
			.layerOutputAddress = (u64) (MLP_HLS_PARAMETER_BASE_ADDRESS + weightOffset + biasOffset
					+ inputOffset + outputOffset),
			.deviceId = XPAR_MLP_MLP_DEVICE_ID,
			.loadParameters = true,
			.exportLayers = true,
			.numberHiddenLayers = NUMBER_HIDDEN,
			.numberInputs = NUMBER_INPUTS,
			.numberOutputs = NUMBER_OUTPUTS,
			.numberNeurons = NUMBER_NEURONS,
			.parEntries = PAR_ENTRIES };
	uz_mlpHls_t *testInstanceMlp = uz_mlpHls_init(mlpConfig);

	const u32 numberHiddenLayers = uz_mlpHls_getNumberHiddenLayers(testInstanceMlp);
	const u32 numberNeurons = uz_mlpHls_getNumberNeurons(testInstanceMlp);
	const u32 numberInputs = uz_mlpHls_getNumberInputs(testInstanceMlp);
	const u32 numberOutputs = uz_mlpHls_getNumberOutputs(testInstanceMlp);

	Activation hiddenActivation[numberHiddenLayers];
	size_t hiddenSize[numberHiddenLayers];
	for (size_t i = 0; i < numberHiddenLayers; i++)
	{
		hiddenActivation[i] = HIDDEN_ACTIVATION;
		hiddenSize[i] = uz_mlpHls_getNumberNeurons(testInstanceMlp);
	}

	Network *net = createNetwork(numberInputs, numberHiddenLayers, hiddenSize, hiddenActivation,
			numberOutputs, OUTPUT_ACTIVATION);

	float *weightMemory = (float *) ((u32) uz_mlpHls_getWeightAddress(testInstanceMlp));
	float *biasMemory = (float *) ((u32) uz_mlpHls_getBiasAddress(testInstanceMlp));

	extractCraniumWeights(&weightMemory[numberNeurons * numberInputs], weightMemory,
			&weightMemory[numberNeurons * (numberInputs + (numberHiddenLayers - 1) * numberNeurons)],
			biasMemory, &biasMemory[numberHiddenLayers * numberNeurons], net);

	uz_mlpHlsTestbench(net, testInstanceMlp);

#ifdef TEST_TRAINING
	struct uz_bgdHls_config_t bgdConfig =
	{
			.mlpResultsMemoryAddress = uz_mlpHls_getLayerOutputAddress(testInstanceMlp),
			.classesMemoryAddress = (u64) ((u32) uz_bgdHls_trainingClasses),
			.weightInputMemoryAddress = uz_mlpHls_getWeightAddress(testInstanceMlp),
			.biasInputMemoryAddress = uz_mlpHls_getBiasAddress(testInstanceMlp),
			.weightOutputMemoryAddress = uz_mlpHls_getWeightAddress(testInstanceMlp),
			.biasOutputMemoryAddress = uz_mlpHls_getBiasAddress(testInstanceMlp),
			.numberInputs = uz_mlpHls_getNumberInputs(testInstanceMlp),
			.numberOutputs = uz_mlpHls_getNumberOutputs(testInstanceMlp),
			.numberHiddenLayers = uz_mlpHls_getNumberHiddenLayers(testInstanceMlp),
			.numberNeurons = uz_mlpHls_getNumberNeurons(testInstanceMlp),
			.loadParameters = true,
			.batchSize = BATCH_SIZE,
			.learningRate = LEARNING_RATE,
			.parEntries = uz_mlpHls_getParEntries(testInstanceMlp),
			.deviceId = XPAR_MLP_BGD_DEVICE_ID };

	uz_bgdHls_t *testInstanceBgd = uz_bgdHls_init(bgdConfig);
	uz_bgdHlsTestbench(net, testInstanceMlp, testInstanceBgd);
#endif

	return UZ_SUCCESS;
}
