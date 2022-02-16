#ifndef UZ_MLPHLSPRIVATE_H
#define UZ_MLPHLSPRIVATE_H

#include "../../Cranium/src/cranium.h"
#include <stddef.h>
#include "xmlp.h"
#include "uz_MlpHls.h"

void extractCraniumWeights(float *hiddenWeightMemory, float *inputWeightMemory,
		float *outputWeightMemory, float *hiddenBiasMemory,
		float *outputBiasMemory, Network *net)
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
				hiddenWeightMemory[i * newRows * newCols + j] =
						weightTransp->data[j];
			}
			destroyMatrix(weightTransp);
		}

		newRows = net->connections[i]->bias->cols
				* net->connections[i]->bias->rows;
		for (unsigned int j = 0; j < newRows; j++)
		{
			hiddenBiasMemory[i * newRows + j] =
					net->connections[i]->bias->data[j];
		}
	}

	newRows = net->connections[net->numConnections - 1]->weights->cols;
	newCols = net->connections[net->numConnections - 1]->weights->rows;
	Matrix *outputTransp = createMatrixZeroes(newRows, newCols);
	transposeInto(net->connections[net->numConnections - 1]->weights,
			outputTransp);

	for (unsigned int i = 0; i < newRows * newCols; i++)
	{
		outputWeightMemory[i] = outputTransp->data[i];
	}

	destroyMatrix(outputTransp);

	newRows = net->connections[net->numConnections - 1]->bias->cols
			* net->connections[net->numConnections - 1]->bias->rows;
	for (unsigned int i = 0; i < newRows; i++)
	{
		outputBiasMemory[i] =
				net->connections[net->numConnections - 1]->bias->data[i];
	}
}

void mlpProcessSamples(XMlp *instance, float *inputValues, float *layerOutput,
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

#endif
