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
	double error = (actualVal - predictedVal) * (actualVal - predictedVal);
	return error;
}

double Training::weightGradient(Neuron &start, Neuron &end)
{
	return start.getOutput() * end.getError();
}

void Training::neuronOutputError();

void Training::neuronOutputError(Neuron &target, NeuronConnection &connection, Neuron &end)
{
	double activationGradient = 1.0;
	if (target.getInput() <= 0.0) activationGradient = 0.0;
	target.setError(connection.getWeight() * end.getError() * activationGradient);
}