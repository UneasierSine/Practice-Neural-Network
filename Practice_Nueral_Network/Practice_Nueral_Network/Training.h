#pragma once
#include "Neuron.h"
#include "NeuronConnection.h"
#include <vector>

using namespace std;

class Training
{
	public:
		Training();
		~Training();

		double costFunctionError(double predictedVal, double actualVal);
		double weightGradient(Neuron start, Neuron end);
		double neuronOutputGradient(NeuronConnection connection, Neuron end);

};

