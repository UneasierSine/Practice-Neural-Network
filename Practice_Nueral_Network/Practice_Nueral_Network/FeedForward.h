#pragma once
#include <vector>
#include "NeuronConnection.h"
#include "Neuron.h"
#include <iostream>

using namespace std;

class FeedForward
{
	public:
		FeedForward();
		~FeedForward();

		void weightedSumFirstLayer(vector<NeuronConnection> &connections, Neuron &input, vector<Neuron> &output);
		void weightedSumInput(vector<NeuronConnection> &connections, vector<Neuron> &input, vector<Neuron> &output);
		void lastWeightedSumInput(vector<NeuronConnection> &toOutput, vector<Neuron> &input, Neuron &output);
};

