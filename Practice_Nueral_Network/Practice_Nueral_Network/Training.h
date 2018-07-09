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
		void errorOutputGradient(Neuron &neuron, double actual, double predicted);
		void errorsLastHidden(vector<Neuron> &layerLast, Neuron &output, vector<NeuronConnection> &connections);
		void errorsHidden(vector<Neuron> &layer, vector<Neuron> &layerPlusOne, vector<NeuronConnection> &connections);
		void modifyWeights(vector<Neuron> &beginLayer, vector<Neuron> &endLayer, vector<NeuronConnection> &connections);
		void modifyLastWeights(vector<Neuron> &beginLayer, Neuron &outputNeuron, vector<NeuronConnection> &connections);
		void modifyFirstWeights(Neuron &inputNeuron, vector<Neuron> &endLayer, vector<NeuronConnection> &connections);
};

