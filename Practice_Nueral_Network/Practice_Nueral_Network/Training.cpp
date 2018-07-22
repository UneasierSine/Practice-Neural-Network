#include "stdafx.h"
#include "Training.h"


Training::Training()
{
}


Training::~Training()
{
}

long double Training::costFunctionError(long double predictedVal, long double actualVal)
{
	long double error = (actualVal - predictedVal);
	return error;
}

long double Training::weightGradient(Neuron &start, Neuron &end)
{
	return start.getOutput() * end.getError();
}

void Training::errorOutputGradient(Neuron &neuron, long double actual, long double predicted)
{
	neuron.setError( actual - predicted );
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
	for (NeuronConnection &connecc : connections)
	{
		long double prevSetError = layer[connecc.getBeginIndex()].getError();
		long double activationGradient = 1.0;
		if (layerPlusOne[connecc.getEndIndex()].getInput() <= 0.0) activationGradient = 0.00001;
		cout << "Activation Gradient " << activationGradient << " Gradient: " << connecc.getWeight() * layerPlusOne[connecc.getEndIndex()].getError() << endl;
		layer[connecc.getBeginIndex()].setError(prevSetError + (connecc.getWeight() * layerPlusOne[connecc.getEndIndex()].getError() * activationGradient));
	}
}

void Training::modifyWeights(vector<Neuron> &beginLayer, vector<Neuron> &endLayer, vector<NeuronConnection> &connections)
{
	long double learning_rate = 0.00001;

	for (NeuronConnection &connecc : connections)
	{
		long double prevWeight = connecc.getWeight();
		long double gradient = beginLayer[connecc.getBeginIndex()].getOutput() * endLayer[connecc.getEndIndex()].getError();
		connecc.setWeight( -1.0 * learning_rate * gradient + prevWeight);
	}
}

void Training::modifyLastWeights(vector<Neuron> &beginLayer, Neuron &outputNeuron, vector<NeuronConnection> &connections)
{
	long double learning_rate = 0.001;

	for (NeuronConnection connecc : connections)
	{
		long double prevWeight = connecc.getWeight();
		long double gradient = beginLayer[connecc.getBeginIndex()].getOutput() * outputNeuron.getError();
		connecc.setWeight(-1.0 * learning_rate * gradient + prevWeight);
	}
}

void Training::modifyFirstWeights(Neuron &inputNeuron, vector<Neuron> &endLayer, vector<NeuronConnection> &connections)
{
	long double learning_rate = 0.001;

	for (NeuronConnection connecc : connections)
	{
		long double prevWeight = connecc.getWeight();
		long double gradient = inputNeuron.getOutput() * endLayer[connecc.getEndIndex()].getError();
		connecc.setWeight(-1.0 * learning_rate * gradient + prevWeight);
	}
}