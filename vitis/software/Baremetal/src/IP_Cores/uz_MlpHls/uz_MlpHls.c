#include "../../Cranium/src/cranium.h"
#include "xmultilayerperceptrondecoupled.h"
#include "xparameters.h"
#include "xil_types.h"
#include <stdlib.h>
#include <math.h>

static const u32 PARAMETER_MEMORY = 0x20100U;
static const u32 PARAMETER_MEMORY_OFFSET_PL = 0xFFE00000U;

static const unsigned N = 32; //  Rows of A aka weight Matrix
static const unsigned K = N;  //  Cols of A and Rows of Input Vector

static const unsigned int KInput = 8;
static const unsigned int NOutput = 8;
static const unsigned int NumberOfHidden = 4;
static const u32 weightOffset = (N * KInput + (NumberOfHidden - 1) * N * K
		+ NOutput * K) * sizeof(float);
static const u32 biasOffset = (NumberOfHidden * N + NOutput) * sizeof(float);
static const u32 inputOffset = KInput * sizeof(float);

static float *weightMemory = (float *) PARAMETER_MEMORY;
static float *biasMemory = (float *) (PARAMETER_MEMORY + weightOffset);
static float *inputBuffer = (float *) (PARAMETER_MEMORY + weightOffset
		+ biasOffset);
static float *outputBuffer = (float *) (PARAMETER_MEMORY + weightOffset
		+ biasOffset + inputOffset);

void extractCraniumWeights(float *hiddenWeightMemory, float *inputWeightMemory,
		float *outputWeightMemory, float *hiddenBiasMemory,
		float *outputBiasMemory, Network *net);

/**
 * N = Number of rows of input and number of cols of output
 * K = Number of cols of input and number of rows of output
 */
void myTranspose(float *src, float *dst, const int N, const int K) {
	for (int n = 0; n < N; n++) {
		for (int k = 0; k < K; k++) {
			dst[k * N + k] = src[n * N + k];
		}
	}
}

void uz_MlpHlsTestbench(void) {
	srand((unsigned int) 2);

	Activation hiddenActivation[NumberOfHidden];
	size_t hiddenSize[NumberOfHidden];
	float inputData[KInput];
	for (unsigned int i = 0; i < KInput; i++) {
		inputData[i] = ((float) (rand() % 100)) / 100.0;
	}
	Matrix *inputCran = createMatrix(1, KInput, inputData);

	for (unsigned int i = 0; i < NumberOfHidden; i++) {
		hiddenActivation[i] = sigmoid;
		hiddenSize[i] = N;
	}
	Network *net = createNetwork(KInput, NumberOfHidden, hiddenSize,
			hiddenActivation, NOutput, sigmoid);

	forwardPass(net, inputCran);

	float *resultReference = getOuput(net)->data;

	extractCraniumWeights(&weightMemory[N * KInput], weightMemory,
			&weightMemory[N * KInput + (NumberOfHidden - 1) * N * K],
			biasMemory, &biasMemory[NumberOfHidden * N], net);

	XMultilayerperceptrondecoupled testInstance = { .Configuration_BaseAddress =
	XPAR_MULTILAYERPERCEPTRON_1_S_AXI_CONFIGURATION_BASEADDR,
			.Control_BaseAddress =
			XPAR_MULTILAYERPERCEPTRON_1_S_AXI_CONTROL_BASEADDR };

	XMultilayerperceptrondecoupled_Initialize(&testInstance,
	XPAR_MULTILAYERPERCEPTRON_1_DEVICE_ID);

	u64 address = 0;
	address |= (u32) weightMemory + PARAMETER_MEMORY_OFFSET_PL;
	XMultilayerperceptrondecoupled_Set_axiWeightInput(&testInstance, address);

	address = 0;
	address |= (u32) biasMemory + PARAMETER_MEMORY_OFFSET_PL;
	XMultilayerperceptrondecoupled_Set_axiBiasInput(&testInstance, address);

	address = 0;
	address |= (u32) inputBuffer + PARAMETER_MEMORY_OFFSET_PL;
	XMultilayerperceptrondecoupled_Set_input_r(&testInstance, address);

	address = 0;
	address |= (u32) outputBuffer + PARAMETER_MEMORY_OFFSET_PL;
	XMultilayerperceptrondecoupled_Set_output_r(&testInstance, address);

	XMultilayerperceptrondecoupled_Set_loadParameters(&testInstance, (u32) 1);
	XMultilayerperceptrondecoupled_Set_exportLayers(&testInstance, (u32) 0);
	XMultilayerperceptrondecoupled_Set_numberInputs(&testInstance,
			(u32) KInput);
	XMultilayerperceptrondecoupled_Set_numberOutputs(&testInstance,
			(u32) NOutput);
	XMultilayerperceptrondecoupled_Set_numberLayers(&testInstance,
			(u32) NumberOfHidden);
	XMultilayerperceptrondecoupled_Set_numberNeurons(&testInstance, (u32) N);

	XMultilayerperceptrondecoupled_Start(&testInstance);

	while (XMultilayerperceptrondecoupled_IsIdle(&testInstance) == 0) {
		;
	}

	// check results

	const float precision = 1e-3;
	int failure = 0;
	for (unsigned int i = 0; i < NOutput; i++)
	{
		if(fabs(resultReference[i] - outputBuffer[i]) >= precision)
			failure = 1;
	}

	while(failure);

}

void extractCraniumWeights(float *hiddenWeightMemory, float *inputWeightMemory,
		float *outputWeightMemory, float *hiddenBiasMemory,
		float *outputBiasMemory, Network *net) {
	myTranspose(net->connections[0]->weights->data, inputWeightMemory, KInput,
			N);

	for (unsigned int i = 0; i < NumberOfHidden; i++) {
		if (i < NumberOfHidden - 1) {
			for (unsigned int j = 0; j < N * K; j++) {
				myTranspose(net->connections[i + 1]->weights->data,
						&hiddenWeightMemory[i * N * K + j], K, N);
			}
		}

		for (unsigned int j = 0; j < N; j++) {
			hiddenBiasMemory[i * N + j] = net->connections[i]->bias->data[j];
		}
	}

	myTranspose(net->connections[NumberOfHidden]->weights->data,
			outputWeightMemory, K, NOutput);

	for (unsigned int i = 0; i < NOutput; i++) {
		outputBiasMemory[i] = net->connections[NumberOfHidden]->bias->data[i];
	}
}

