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
		double weightGradient(Neuron &start, Neuron &end);
		void errorOutputGradient(Neuron &neuron, double error);
		void neuronOutputError(Neuron &target, NeuronConnection &connection, Neuron &end);
};

