#include "stdafx.h"
#include <random>
#include "NeuronConnection.h"


NeuronConnection::NeuronConnection(int layer1, int layer2, int index1, int index2)
{
	beginLayer = layer1;
	endLayer = layer2;
	
	beginIndex = index1;
	endIndex = index2;

	weight = ((double)rand()*(10 + 0.1) / (double)RAND_MAX + 0.1);
}


NeuronConnection::~NeuronConnection()
{
}

double NeuronConnection::getInput()
{
	return input;
}

double NeuronConnection::getOutput()
{
	return output;
}

double NeuronConnection::getWeight()
{
	return weight;
}

int NeuronConnection::getBeginIndex()
{
	return beginIndex;
}

int NeuronConnection::getEndIndex()
{
	return endIndex;
}

void NeuronConnection::setInput(double param)
{
	input = param;
}

void NeuronConnection::setOutput(double param)
{
	output = param;
}

void NeuronConnection::setWeight(double param)
{
	weight = param;
}

double NeuronConnection::calculatedOutput()
{
	return weight * input;
}