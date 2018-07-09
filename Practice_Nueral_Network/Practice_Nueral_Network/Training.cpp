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

void Training::errorOutputGradient(Neuron &neuron, double actual, double predicted)
{
	neuron.setError( 2 * predicted - 2 * actual );
}

void Training::errorsLastHidden(vector<Neuron> &layerLast, Neuron &output, vector<NeuronConnection> &connections)
{
	for (int i = 0; i < connections.size(); i++)
	{
		layerLast[i].setError( output.getError() * connections[i].getWeight() );
	}
}

void Training::errorsHidden(vector<Neuron> &layer, vector<Neuron> &layerPlusOne, vector<NeuronConnection> &connections)
{
	double sumErrors[10];
	for (NeuronConnection connecc : connections)
	{
		double prevSetError = layer[connecc.getBeginIndex()].getError();
		double activationGradient = 1.0;
		if (layerPlusOne[connecc.getEndIndex()].getInput() <= 0.0) activationGradient = 0.0;

		sumErrors[connecc.getBeginIndex()] += connecc.getWeight() * layerPlusOne[connecc.getEndIndex()].getError() * activationGradient;
	}

	
}

void Training::modifyWeights(vector<Neuron> &beginLayer, vector<Neuron> &endLayer, vector<NeuronConnection> &connections)
{
	double learning_rate = 0.01;

	for (NeuronConnection connecc : connections)
	{
		double prevWeight = connecc.getWeight();
		double gradient = beginLayer[connecc.getBeginIndex()].getOutput() * endLayer[connecc.getEndIndex()].getError();
		connecc.setWeight( -1.0 * learning_rate * gradient + prevWeight);
	}
}

void Training::modifyLastWeights(vector<Neuron> &beginLayer, Neuron &outputNeuron, vector<NeuronConnection> &connections)
{
	double learning_rate = 0.01;

	for (NeuronConnection connecc : connections)
	{
		double prevWeight = connecc.getWeight();
		double gradient = beginLayer[connecc.getBeginIndex()].getOutput() * outputNeuron.getError();
		connecc.setWeight(-1.0 * learning_rate * gradient + prevWeight);
	}
}

void Training::modifyFirstWeights(Neuron &inputNeuron, vector<Neuron> &endLayer, vector<NeuronConnection> &connections)
{
	double learning_rate = 0.01;

	for (NeuronConnection connecc : connections)
	{
		double prevWeight = connecc.getWeight();
		double gradient = inputNeuron.getOutput() * endLayer[connecc.getEndIndex].getError();
		connecc.setWeight(-1.0 * learning_rate * gradient + prevWeight);
	}
}