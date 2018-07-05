#include "stdafx.h"
#include "FeedForward.h"


FeedForward::FeedForward()
{
}


FeedForward::~FeedForward()
{
}

void FeedForward::weightedSumFirstLayer(vector<NeuronConnection> connections, Neuron input, vector<Neuron> output)
{
	int counter = 0;
	for (NeuronConnection connect : connections)
	{
		output[counter].setInput(connect.getWeight() * input.getOutput());
		counter++;
	}
}

void FeedForward::weightedSumInput(vector<NeuronConnection> connections, vector<Neuron> input, vector<Neuron> output)
{
	static double sum[4] = { 0.0, 0.0, 0.0, 0.0 };
	int counter = 0;
	for (NeuronConnection connect : connections)
	{
		sum[counter] += connect.getWeight() * input[counter].getOutput();
		if (counter == 3)
		{
			counter = 0;
		}
		else
		{
			counter++;
		}
	}
	cout << sum[0] << " " << sum[1] << " " << sum[2] << " " << sum[3] << endl;
	output[0].setInput(sum[0]);
	output[1].setInput(sum[1]);
	output[2].setInput(sum[2]);
	output[3].setInput(sum[3]);
}

void FeedForward::lastWeightedSumInput(vector<NeuronConnection> toOutput, vector<Neuron> input, Neuron output)
{
	static double sum = 0.0;
	int counter = 0;
	for (NeuronConnection outs : toOutput)
	{
		sum += outs.getWeight() * input[counter].getOutput();
		counter++;
	}
	output.setInput(sum);
}