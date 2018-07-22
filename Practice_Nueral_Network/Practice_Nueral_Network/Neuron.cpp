#include "stdafx.h"
#include "Neuron.h"
#include <iostream>
#include <math.h>

using namespace std;

Neuron::Neuron(int layer, int rank)
{
	layerNumber = layer;
	neuronIndex = rank;

	if (layerNumber == 0)
	{
		isInput = true;
	}
	else if (layerNumber == 4)
	{
		isOutput = true;
	}
	else if (layerNumber > 4)
	{
		cout << "Layer index is greater than 4" << endl;
	}
	else if (layerNumber < 0)
	{
		cout << "Layer index is less than 0" << endl;
	}
	else
	{
		isInput = false;
		isOutput = false;
	}
}

Neuron::~Neuron()
{
}

long double Neuron::getInput()
{
	return input;
}

long double Neuron::getOutput()
{
	return output;
}

long double Neuron::getError()
{
	return error;
}

void Neuron::setInput(long double param)
{
	input = param;
	if (input > 0) output = input;
	if (input <= 0) output = 0.00001 * input;
}

void Neuron::setOutput(long double param)
{
	output = param;
}

void Neuron::setError(long double param)
{
	error = param;
}