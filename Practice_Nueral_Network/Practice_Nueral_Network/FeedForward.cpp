#include "stdafx.h"
#include "FeedForward.h"


FeedForward::FeedForward()
{
}


FeedForward::~FeedForward()
{
}

void FeedForward::weightedSumFirstLayer(vector<NeuronConnection> &connections, Neuron &input, vector<Neuron> &output)
{
	for (NeuronConnection connect : connections)
	{
		output[connect.getEndIndex()].setInput(connect.getWeight() * input.getOutput());
		//cout << connect.getEndIndex() << " " << output[connect.getEndIndex()].getOutput() << endl;
	}
}

void FeedForward::weightedSumInput(vector<NeuronConnection> &connections, vector<Neuron> &input, vector<Neuron> &output)
{
	for (NeuronConnection connect : connections)
	{
		output[connect.getEndIndex()].setInput(connect.getWeight() * input[connect.getBeginIndex()].getInput());
		//cout << input[connect.getBeginIndex()].getInput() << " " << connect.getWeight() << " " << output[connect.getEndIndex()].getInput() << endl;
	}
}

void FeedForward::lastWeightedSumInput(vector<NeuronConnection> &toOutput, vector<Neuron> &input, Neuron &output)
{
	static long double sum;
	int counter = 0;
	for (NeuronConnection outs : toOutput)
	{
		output.setInput(outs.getWeight() * input[counter].getOutput());
		//cout << input[counter].getOutput() << " " << output.getInput() << endl;
		counter++;
	}
}