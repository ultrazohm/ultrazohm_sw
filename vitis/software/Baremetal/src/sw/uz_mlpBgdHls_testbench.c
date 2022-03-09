// UltraZohm includes
#include "../include/uz_mlpBgdHls_testbench.h"
#include "../uz/uz_HAL.h"
#include "../IP_Cores/uz_mlpHls/uz_mlpHls.h"
#include "../IP_Cores/uz_bgdHls/uz_bgdHls.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"

// Reference implementation
#include "../Cranium/src/cranium.h"

// system includes
#include <stddef.h>
#include <stdbool.h>

// Xilinx includes
#include "xparameters.h"

// defines
#define BATCH_SIZE 16U
#define LEARNING_RATE 0.5f
#define NUMBER_OUTPUTS 4U
#define NUMBER_INPUTS 4U
#define NUMBER_HIDDEN 2U
#define NUMBER_NEURONS 4U
#define PAR_ENTRIES 4U
#define EPOCHS 1

// reference implementation
#define HIDDEN_ACTIVATION sigmoid
#define OUTPUT_ACTIVATION linear

// input data and classes for training
#ifdef TEST_TRAINING
//static float uz_bgdHls_trainingData[NUMBER_INPUTS * TRAINING_SAMPLES] =
//{
//#include "uz_mlpBgdHls_trainingData/mnist_data.csv"
//		};
//
//static float uz_bgdHls_trainingClasses[NUMBER_OUTPUTS * TRAINING_SAMPLES] =
//{
//#include "uz_mlpBgdHls_trainingData/mnist_labels.csv"
//		};
#endif

static void initMlpWithReference(Network *net, uz_mlpHls_t *testInstanceMlp)
{
	float *weightPointer = (float *) ((u32) uz_mlpHls_getWeightAddress(testInstanceMlp));
	float *biasPointer = (float *) ((u32) uz_mlpHls_getBiasAddress(testInstanceMlp));
	const u32 numberNeurons = uz_mlpHls_getNumberNeurons(testInstanceMlp);
	const u32 numberInputs = uz_mlpHls_getNumberInputs(testInstanceMlp);
	size_t newRows, newCols;

	newRows = net->connections[0]->weights->cols;
	newCols = net->connections[0]->weights->rows;
	Matrix *inputTransp = createMatrixZeroes(newRows, newCols);
	transposeInto(net->connections[0]->weights, inputTransp);
	for (size_t i = 0; i < newCols * newRows; i++)
	{
		weightPointer[i] = inputTransp->data[i];
	}
	destroyMatrix(inputTransp);
	weightPointer += numberNeurons * numberInputs;

	for (size_t i = 0; i < net->numConnections - 1; i++)
	{
		if (i < net->numConnections - 2)
		{
			newRows = net->connections[i + 1]->weights->cols;
			newCols = net->connections[i + 1]->weights->rows;
			Matrix *weightTransp = createMatrixZeroes(newRows, newCols);
			transposeInto(net->connections[i + 1]->weights, weightTransp);
			for (size_t j = 0; j < newRows * newCols; j++)
			{
				weightPointer[j] = weightTransp->data[j];
			}
			destroyMatrix(weightTransp);
			weightPointer += numberNeurons * numberNeurons;
		}

		newRows = net->connections[i]->bias->cols * net->connections[i]->bias->rows;
		for (size_t j = 0; j < newRows; j++)
		{
			biasPointer[j] = net->connections[i]->bias->data[j];
		}
		biasPointer += numberNeurons;
	}

	newRows = net->connections[net->numConnections - 1]->weights->cols;
	newCols = net->connections[net->numConnections - 1]->weights->rows;
	Matrix *outputTransp = createMatrixZeroes(newRows, newCols);
	transposeInto(net->connections[net->numConnections - 1]->weights, outputTransp);

	for (size_t i = 0; i < newRows * newCols; i++)
	{
		weightPointer[i] = outputTransp->data[i];
	}

	destroyMatrix(outputTransp);

	newRows = net->connections[net->numConnections - 1]->bias->cols
			* net->connections[net->numConnections - 1]->bias->rows;
	for (size_t i = 0; i < newRows; i++)
	{
		biasPointer[i] = net->connections[net->numConnections - 1]->bias->data[i];
	}
}

static void uz_mlpHlsTestbench(Network *referenceImpl, uz_mlpHls_t *testInstance)
{
	float *cranData = (float *) malloc(uz_mlpHls_getNumberInputs(testInstance) * sizeof(float));
	Matrix *inputCran = createMatrix(1, uz_mlpHls_getNumberInputs(testInstance), cranData);
	float *inputBuffer = (float *) ((u32) uz_mlpHls_getInputAddress(testInstance));
	float *outputBuffer = (float *) ((u32) uz_mlpHls_getOutputAddress(testInstance));

	bool repeat = false;
	bool exportLayers = true;
	bool loadParameters = true;
	while (repeat)
	{
		uz_mlpHls_setExportLayers(testInstance, exportLayers);
		uz_mlpHls_setLoadParameters(testInstance, loadParameters);
		float *resultReference;
		float swExecutionTime, hwExecutionTime;
		for (size_t i = 0; i < uz_mlpHls_getNumberInputs(testInstance); i++)
		{
			inputBuffer[i] = ((float) (rand() % 100)) / 100.0;
			cranData[i] = inputBuffer[i];
		}

		uz_SystemTime_ISR_Tic();
		forwardPass(referenceImpl, inputCran);
		uz_SystemTime_ISR_Toc();
		uz_SystemTime_ISR_Tic();
		swExecutionTime = uz_SystemTime_GetIsrExectionTimeInUs();
		resultReference = getOuput(referenceImpl)->data;

		uz_SystemTime_ISR_Tic();
		uz_mlpHls_start(testInstance);
		while (uz_mlpHls_isIdle(testInstance) == false)
		{
			;
		}
		uz_SystemTime_ISR_Toc();
		uz_SystemTime_ISR_Tic();
		hwExecutionTime = uz_SystemTime_GetIsrExectionTimeInUs();

		// check results
		const float precision = 1e-3;
		for (size_t i = 0; i < uz_mlpHls_getNumberOutputs(testInstance); i++)
		{
			float error = fabs(resultReference[i] - outputBuffer[i]);
			if (error > precision)
				uz_printf("Error at output entry %d", i);
			uz_assert(error < precision);
		}
	}

	destroyMatrix(inputCran);
}

static void mlpProcessBatch(uz_mlpHls_t *mlpInstance, uz_bgdHls_t *bgdInstance)
{
	u64 inputAddress = uz_mlpHls_getInputAddress(mlpInstance);
	u64 layerOutputAddress = uz_mlpHls_getLayerOutputAddress(mlpInstance);
	const u64 origLayerOutputAddress = layerOutputAddress;

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
	uz_mlpHls_setLayerOutputAddress(mlpInstance, origLayerOutputAddress);
}

static bool uz_mlpBgdHls_xorArray(float * inputValues, size_t size)
{
	bool return_value = true;
	size_t numberOnes = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (inputValues[i] != 0)
			numberOnes++;
	}
	if (numberOnes == 1)
		return_value = true;
	else
		return_value = false;

	return return_value;
}

static void createXorTrainingData(uz_bgdHls_t *testInstanceBgd)
{
	const u32 numberInputs = uz_bgdHls_getNumberInputs(testInstanceBgd);
	const u32 numberOutputs = uz_bgdHls_getNumberOutputs(testInstanceBgd);
	const u32 numberTrainingSamples = 1 << numberInputs;
	uz_assert(numberTrainingSamples <= uz_bgdHls_getNumberTrainingSamples(testInstanceBgd));
	uz_bgdHls_setNumberTrainingSamples(testInstanceBgd, numberTrainingSamples);
	float *trainingData = (float *) ((u32) uz_bgdHls_getTrainingDataAddress(testInstanceBgd));
	float *classes = (float *) ((u32) uz_bgdHls_getClassesDataAddress(testInstanceBgd));

	// create truth table
	for (size_t i = 0; i < numberInputs; i++)
	{
		size_t range = numberTrainingSamples / (1 << (i + 1));
		float value = 1;
		for (size_t j = 0; j < numberTrainingSamples; j++)
		{
			if ((j % range) == 0)
				value = value != 0 ? 0 : 1;
			trainingData[j * numberInputs + i] = value;
		}
	}

	// xor truth table
	for (size_t i = 0; i < numberTrainingSamples; i++)
	{
		if (uz_mlpBgdHls_xorArray(&trainingData[i * numberInputs], numberInputs))
		{
			classes[i * numberOutputs] = 1;
			classes[i * numberOutputs + 1] = 0;
		}
		else
		{
			classes[i * numberOutputs] = 0;
			classes[i * numberOutputs + 1] = 1;
		}
		for (size_t j = 2; j < numberOutputs; j++)
		{
			classes[i * numberOutputs + j] = 0;
		}
	}
}

static u32 uz_mlpHls_predict(uz_mlpHls_t *testInstanceMlp)
{
	float *outputBuffer = (float*) ((u32) uz_mlpHls_getOutputAddress(testInstanceMlp));
	u32 max = 0;
	for (u32 i = 0; i < uz_mlpHls_getNumberOutputs(testInstanceMlp); i++)
	{
		if (outputBuffer[i] > outputBuffer[max])
			max = i;
	}
	return max;
}

static float uz_bgdHls_accuracy(uz_mlpHls_t *testInstanceMlp, uz_bgdHls_t *testInstanceBgd)
{
	const u32 numberOutputs = uz_mlpHls_getNumberOutputs(testInstanceMlp);
	const u32 numberInputs = uz_mlpHls_getNumberInputs(testInstanceMlp);
	const u32 numberTrainingSamples = uz_bgdHls_getNumberTrainingSamples(testInstanceBgd);

	u64 inputAddress = uz_bgdHls_getTrainingDataAddress(testInstanceBgd);
	const float *classes = (float *) ((u32) uz_bgdHls_getClassesDataAddress(testInstanceBgd));
	u32 prediction;
	float numCorrect = 0;
	uz_mlpHls_setLoadParameters(testInstanceMlp, true);
	uz_mlpHls_setExportLayers(testInstanceMlp, false);
	uz_mlpHls_start(testInstanceMlp);
	while (uz_mlpHls_isIdle(testInstanceMlp) == false)
		;
	uz_mlpHls_setLoadParameters(testInstanceMlp, false);
	prediction = uz_mlpHls_predict(testInstanceMlp);
	if (classes[prediction] == 1)
		numCorrect++;
	for (size_t i = 1; i < numberTrainingSamples; i++)
	{
		inputAddress += numberInputs * sizeof(float);
		uz_mlpHls_setInputAddress(testInstanceMlp, inputAddress);
		uz_mlpHls_start(testInstanceMlp);
		while (uz_mlpHls_isIdle(testInstanceMlp) == false)
			;
		prediction = uz_mlpHls_predict(testInstanceMlp);

		if (classes[i * numberOutputs + prediction] == 1)
			numCorrect++;
	}

	return (numCorrect / ((float) numberTrainingSamples));
}

static void uz_bgdHlsTestbench(Network *referenceImpl, uz_mlpHls_t *testInstanceMlp,
		uz_bgdHls_t *testInstanceBgd)
{
	createXorTrainingData(testInstanceBgd);
	const u32 batchSize = uz_bgdHls_getBatchSize(testInstanceBgd);
	const u32 numberInputs = uz_mlpHls_getNumberInputs(testInstanceMlp);
	const u32 numberOutputs = uz_mlpHls_getNumberOutputs(testInstanceMlp);
	const u32 numberTrainingSamples = uz_bgdHls_getNumberTrainingSamples(testInstanceBgd);
	const u64 trainingDataBaseAddress = uz_bgdHls_getTrainingDataAddress(testInstanceBgd);
	const u64 classesBaseAddress = uz_bgdHls_getClassesDataAddress(testInstanceBgd);

	u32 batches = numberTrainingSamples / batchSize;
	float **craniumTrainingData = (float **) malloc(numberTrainingSamples * sizeof(float *));
	float **craniumClassesData = (float **) malloc(numberTrainingSamples * sizeof(float *));
	float *trainingDataFloat = (float *) ((u32) trainingDataBaseAddress);
	float *classesFloat = (float *) ((u32) classesBaseAddress);
	// copy training data because cranium will free the allocated memory
	// when calling the function destroyDataSet(...)
	for (size_t i = 0; i < numberTrainingSamples; i++)
	{
		craniumTrainingData[i] = (float *) malloc(numberInputs * sizeof(float));
		for (size_t j = 0; j < numberInputs; j++)
		{
			craniumTrainingData[i][j] = trainingDataFloat[i * numberInputs + j];
		}
		craniumClassesData[i] = (float *) malloc(numberOutputs * sizeof(float));
		for (size_t j = 0; j < numberOutputs; j++)
		{
			craniumClassesData[i][j] = classesFloat[i * numberOutputs + j];
		}
	}

	DataSet *cranTrainingData = createDataSet(numberTrainingSamples, numberInputs,
			craniumTrainingData);
	DataSet *cranTrainingClasses = createDataSet(numberTrainingSamples, numberOutputs,
			craniumClassesData);

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
	params.maxIters = (int) (EPOCHS * batches);
	params.shuffle = 0;
	params.verbose = 0;

	bool repeat = true;
	bool loadParameters = true;
	float swExecutionTime, hwExecutionTime;
	while (repeat)
	{
		uz_bgdHls_setLoadParameters(testInstanceBgd, loadParameters);
		uz_SystemTime_ISR_Tic();
		optimize(params);
		uz_SystemTime_ISR_Toc();
		uz_SystemTime_ISR_Tic();
		swExecutionTime = uz_SystemTime_GetIsrExectionTimeInUs();

		float cranAccuracy = accuracy(referenceImpl, cranTrainingData, cranTrainingClasses);
		uz_printf("Accuracy of Cranium optimization %f \n", cranAccuracy);

		float uzBgdAccuracy;
		for (size_t epoch = 0; epoch < EPOCHS; epoch++)
		{
			u64 inputValues = trainingDataBaseAddress;
			u64 classes = classesBaseAddress;
			for (size_t iter = 0; iter < batches; iter++)
			{
				uz_mlpHls_setInputAddress(testInstanceMlp, inputValues);
				uz_bgdHls_setClassesAddress(testInstanceBgd, classes);
				mlpProcessBatch(testInstanceMlp, testInstanceBgd);
				uz_SystemTime_ISR_Tic();
				uz_bgdHls_start(testInstanceBgd);
				while (uz_bgdHls_isIdle(testInstanceBgd) == false)
					;
				uz_SystemTime_ISR_Toc();
				uz_SystemTime_ISR_Tic();
				hwExecutionTime = uz_SystemTime_GetIsrExectionTimeInUs();
//				if (iter == 0)
//				{
//					uz_bgdHls_setLoadParameters(testInstanceBgd, false);
//				}

				classes += batchSize * numberOutputs * sizeof(float);
				inputValues += batchSize * numberInputs * sizeof(float);
			}

			uz_mlpHls_setInputAddress(testInstanceMlp, trainingDataBaseAddress);
			uz_bgdHls_setClassesAddress(testInstanceBgd, classesBaseAddress);
			uzBgdAccuracy = uz_bgdHls_accuracy(testInstanceMlp, testInstanceBgd);
			uz_printf("Accuracy of UZ BGD optimization in epoch %d is %f \n", epoch, uzBgdAccuracy);
		}

		uzBgdAccuracy = uz_bgdHls_accuracy(testInstanceMlp, testInstanceBgd);
		uz_printf("Accuracy of UZ BGD optimization %f \n", uzBgdAccuracy);
	}

	destroyDataSet(cranTrainingClasses);
	destroyDataSet(cranTrainingData);

}

int uz_mlpBgdHls_testbench()
{
	float axiDelay = 0;
	for (size_t i = 0; i < 100; i++)
	{
		uz_SystemTime_ISR_Tic();
		uz_SystemTime_ISR_Toc();
		uz_SystemTime_ISR_Tic();
		axiDelay += uz_SystemTime_GetIsrExectionTimeInUs();
	}

	axiDelay /= 100;

	srand((unsigned int) 2);
	// determine addresses for parameters and init MLP
	const u64 weightOffset =
			((NUMBER_INPUTS + (NUMBER_HIDDEN - 1) * NUMBER_NEURONS + NUMBER_OUTPUTS)
					* NUMBER_NEURONS) * sizeof(float);
	const u64 biasOffset = (NUMBER_HIDDEN * NUMBER_NEURONS + NUMBER_OUTPUTS) * sizeof(float);
	const u64 inputOffset = NUMBER_INPUTS * sizeof(float);
	const u64 outputOffset = NUMBER_OUTPUTS * sizeof(float);

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

	// init reference implementation
	const u32 numberHiddenLayers = uz_mlpHls_getNumberHiddenLayers(testInstanceMlp);
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

	// initialize parameters of HW implementation and start the MLP testbench
	initMlpWithReference(net, testInstanceMlp);
	uz_mlpHlsTestbench(net, testInstanceMlp);

	struct uz_bgdHls_config_t bgdConfig =
	{
			.mlpResultsMemoryAddress = uz_mlpHls_getLayerOutputAddress(testInstanceMlp),
			.classesMemoryAddress = 1, // to avoid assert will be changed later
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
			.deviceId = XPAR_MLP_BGD_DEVICE_ID,
			.numberTrainingSamples = (1 << uz_mlpHls_getNumberInputs(testInstanceMlp)) };

	uz_bgdHls_t *testInstanceBgd = uz_bgdHls_init(bgdConfig);
	u64 trainingData = uz_mlpHls_getLayerOutputAddress(testInstanceMlp)
			+ uz_bgdHls_getBatchBufferSize(testInstanceBgd) * sizeof(float);
	u64 classes = trainingData
			+ uz_bgdHls_getNumberTrainingSamples(testInstanceBgd)
					* uz_mlpHls_getNumberInputs(testInstanceMlp) * sizeof(float);

	uz_bgdHls_setTrainingDataAddress(testInstanceBgd, trainingData);
	uz_bgdHls_setClassesDataAddress(testInstanceBgd, classes);
	uz_bgdHlsTestbench(net, testInstanceMlp, testInstanceBgd);

	// clean up
	destroyNetwork(net);

	return UZ_SUCCESS;
}
