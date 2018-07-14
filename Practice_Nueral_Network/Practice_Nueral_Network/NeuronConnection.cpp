#include "stdafx.h"
#include <random>
#include "NeuronConnection.h"


NeuronConnection::NeuronConnection(int layer1, int layer2, int index1, int index2)
{
	beginLayer = layer1;
	endLayer = layer2;
	
	beginIndex = index1;
	endIndex = index2;

	weight = ((long double)rand()*(2 + 0.1) / (long double)RAND_MAX + 0.1);
}


NeuronConnection::~NeuronConnection()
{
}

long double NeuronConnection::getInput()
{
	return input;
}

long double NeuronConnection::getOutput()
{
	return output;
}

long double NeuronConnection::getWeight()
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

void NeuronConnection::setInput(long double param)
{
	input = param;
}

void NeuronConnection::setOutput(long double param)
{
	output = param;
}

void NeuronConnection::setWeight(long double param)
{
	weight = param;
}