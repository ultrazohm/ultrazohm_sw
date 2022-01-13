#include "../../Cranium/src/cranium.h"
#include "xmultilayerperceptrondecoupled.h"
#include "xparameters.h"
#include "xil_types.h"
#include <stdlib.h>
#include <math.h>
#include "uz_MlpHls.h"
#include "../../uz/uz_HAL.h"

//static const u32 PARAMETER_MEMORY = 0x20100U;
//static const u32 PARAMETER_MEMORY_OFFSET_PL = 0xFFE00000U;

static const unsigned N = 32; //  Rows of A aka weight Matrix
static const unsigned K = N;  //  Cols of A and Rows of Input Vector

static const unsigned int KInput = 8;
static const unsigned int NOutput = 8;
static const unsigned int NumberOfHidden = 3;

//static const u32 weightOffset = (N * KInput + (NumberOfHidden - 1) * N * K
//		+ NOutput * K) * sizeof(float);
//static const u32 biasOffset = (NumberOfHidden * N + NOutput) * sizeof(float);
//static const u32 inputOffset = KInput * sizeof(float);
//
//static float *weightMemory = (float *) PARAMETER_MEMORY;
//static float *biasMemory = (float *) (PARAMETER_MEMORY + weightOffset);
//static float *inputBuffer = (float *) (PARAMETER_MEMORY + weightOffset
//		+ biasOffset);
//static float *outputBuffer = (float *) (PARAMETER_MEMORY + weightOffset
//		+ biasOffset + inputOffset);

void extractCraniumWeights(float *hiddenWeightMemory, float *inputWeightMemory,
		float *outputWeightMemory, float *hiddenBiasMemory,
		float *outputBiasMemory, Network *net);

void uz_MlpHlsTestbench(void) {
	srand((unsigned int) 2);

	XMultilayerperceptrondecoupled testInstance = { .Configuration_BaseAddress =
	XPAR_MULTILAYERPERCEPTRON_1_S_AXI_CONFIGURATION_BASEADDR,
			.Control_BaseAddress =
			XPAR_MULTILAYERPERCEPTRON_1_S_AXI_CONTROL_BASEADDR };

	XMultilayerperceptrondecoupled_Initialize(&testInstance,
	XPAR_MULTILAYERPERCEPTRON_1_DEVICE_ID);

	const u32 PARAMETER_MEMORY = 0x20100U;
	const u32 PARAMETER_MEMORY_OFFSET_PL = 0xFFE00000U;

	const u32 weightOffset = (N * KInput + (NumberOfHidden - 1) * N * K
			+ NOutput * K) * sizeof(float);
	const u32 biasOffset = (NumberOfHidden * N + NOutput) * sizeof(float);
	const u32 inputOffset = KInput * sizeof(float);

	float *weightMemory = (float *) PARAMETER_MEMORY;
	float *biasMemory = (float *) (PARAMETER_MEMORY + weightOffset);
	float *inputBuffer =
			(float *) (PARAMETER_MEMORY + weightOffset + biasOffset);
	float *outputBuffer = (float *) (PARAMETER_MEMORY + weightOffset
			+ biasOffset + inputOffset);

	Activation hiddenActivation[NumberOfHidden];
	size_t hiddenSize[NumberOfHidden];
	Matrix *inputCran = createMatrix(1, KInput, inputBuffer);

	for (unsigned int i = 0; i < NumberOfHidden; i++) {
		hiddenActivation[i] = sigmoid;
		hiddenSize[i] = N;
	}

	Network *net = createNetwork(KInput, NumberOfHidden, hiddenSize,
			hiddenActivation, NOutput, sigmoid);

	extractCraniumWeights(&weightMemory[N * KInput], weightMemory,
			&weightMemory[N * KInput + (NumberOfHidden - 1) * N * K],
			biasMemory, &biasMemory[NumberOfHidden * N], net);

	float *resultReference;
	while (1) {

		for (unsigned int i = 0; i < KInput; i++) {
			inputBuffer[i] = ((float) (rand() % 100)) / 100.0;
		}

		forwardPass(net, inputCran);
		resultReference = getOuput(net)->data;

		u64 address;
		address = (u64) ((u32) weightMemory + PARAMETER_MEMORY_OFFSET_PL);
		XMultilayerperceptrondecoupled_Set_axiWeightInput(&testInstance,
				address);
		address = 0;
		address = XMultilayerperceptrondecoupled_Get_axiWeightInput(
				&testInstance);

		address = (u64) ((u32) biasMemory + PARAMETER_MEMORY_OFFSET_PL);
		XMultilayerperceptrondecoupled_Set_axiBiasInput(&testInstance, address);

		address = (u64) ((u32) inputBuffer + PARAMETER_MEMORY_OFFSET_PL);
		XMultilayerperceptrondecoupled_Set_input_r(&testInstance, address);

		address = (u64) ((u32) outputBuffer + PARAMETER_MEMORY_OFFSET_PL);
		XMultilayerperceptrondecoupled_Set_output_r(&testInstance, address);

		XMultilayerperceptrondecoupled_Set_loadParameters(&testInstance,
				(u32) 1);
		XMultilayerperceptrondecoupled_Set_exportLayers(&testInstance, (u32) 0);
		XMultilayerperceptrondecoupled_Set_numberInputs(&testInstance,
				(u32) KInput);
		XMultilayerperceptrondecoupled_Set_numberOutputs(&testInstance,
				(u32) NOutput);
		XMultilayerperceptrondecoupled_Set_numberLayers(&testInstance,
				(u32) NumberOfHidden);
		XMultilayerperceptrondecoupled_Set_numberNeurons(&testInstance,
				(u32) N);

		XMultilayerperceptrondecoupled_Start(&testInstance);

		while (XMultilayerperceptrondecoupled_IsIdle(&testInstance) == 0) {
			;
		}

		// check results

		const float precision = 1e-3;
		for (unsigned int i = 0; i < NOutput; i++) {
			float error = fabs(resultReference[i] - outputBuffer[i]);
			uz_assert(error < precision);
		}
	}

	destroyNetwork(net);

}

void extractCraniumWeights(float *hiddenWeightMemory, float *inputWeightMemory,
		float *outputWeightMemory, float *hiddenBiasMemory,
		float *outputBiasMemory, Network *net) {

	Matrix *inputTransp = createMatrixZeroes(N, KInput);
	transposeInto(net->connections[0]->weights, inputTransp);
	for (unsigned int i = 0; i < N * KInput; i++) {
		inputWeightMemory[i] = inputTransp->data[i];
	}

	destroyMatrix(inputTransp);

	for (unsigned int i = 0; i < NumberOfHidden; i++) {
		if (i < NumberOfHidden - 1) {
			Matrix *weightTransp = createMatrixZeroes(N, K);
			transposeInto(net->connections[i + 1]->weights, weightTransp);
			for (unsigned int j = 0; j < N * K; j++) {
				hiddenWeightMemory[i * N * K + j] = weightTransp->data[j];
			}
			destroyMatrix(weightTransp);
		}

		for (unsigned int j = 0; j < N; j++) {
			hiddenBiasMemory[i * N + j] = net->connections[i]->bias->data[j];
		}
	}

	Matrix *outputTransp = createMatrixZeroes(NOutput, K);
	transposeInto(net->connections[NumberOfHidden]->weights, outputTransp);

	for (unsigned int i = 0; i < NOutput * K; i++) {
		outputWeightMemory[i] = outputTransp->data[i];
	}

	destroyMatrix(outputTransp);

	for (unsigned int i = 0; i < NOutput; i++) {
		outputBiasMemory[i] = net->connections[NumberOfHidden]->bias->data[i];
	}
}

