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

void Neuron::activationFunction(double in)
{
	//Perform ReLU activation
	output = fmin(0.0, in);
}

double Neuron::getInput()
{
	return input;
}

double Neuron::getOutput()
{
	return output;
}

void Neuron::setInput(double param)
{
	input = param;
}

void Neuron::setOnput(double param)
{
	output = param;
}