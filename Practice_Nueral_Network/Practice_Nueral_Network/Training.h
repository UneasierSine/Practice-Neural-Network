#pragma once
#include "Neuron.h"
#include "NeuronConnection.h"
#include <vector>
#include <iostream>

using namespace std;

class Training
{
	public:
		Training();
		~Training();

		long double costFunctionError(long double predictedVal, long double actualVal);
		long double weightGradient(Neuron &start, Neuron &end);
		void errorOutputGradient(Neuron &neuron, long double actual, long double predicted);
		void errorsLastHidden(vector<Neuron> &layerLast, Neuron &output, vector<NeuronConnection> &connections);
		void errorsHidden(vector<Neuron> &layer, vector<Neuron> &layerPlusOne, vector<NeuronConnection> &connections);
		void modifyWeights(vector<Neuron> &beginLayer, vector<Neuron> &endLayer, vector<NeuronConnection> &connections);
		void modifyLastWeights(vector<Neuron> &beginLayer, Neuron &outputNeuron, vector<NeuronConnection> &connections);
		void modifyFirstWeights(Neuron &inputNeuron, vector<Neuron> &endLayer, vector<NeuronConnection> &connections);
};

