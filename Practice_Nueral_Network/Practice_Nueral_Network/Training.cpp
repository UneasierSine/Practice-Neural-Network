#include "stdafx.h"
#include "Training.h"


Training::Training()
{
}


Training::~Training()
{
}

double Training::costFunctionError(double predictedVal, double actualVal)
{
	double error = (actualVal - predictedVal);
	return error;
}

double Training::weightGradient(Neuron &start, Neuron &end)
{
	return start.getOutput() * end.getError();
}

double Training::neuronOutputError(NeuronConnection &connection, Neuron &end)
{
	return connection.getWeight() * end.getError();
}