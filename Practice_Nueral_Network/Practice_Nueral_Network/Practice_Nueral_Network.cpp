// We will attempt to make a neural network.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <vector>

#include "Neuron.h"
#include "NeuronConnection.h"
#include "Training.h"
#include "FeedForward.h"

using namespace std;

int main()
{
#pragma region File_Init

	//Initialize connection weights output file
	ofstream weightsFile;
	weightsFile.open("Connection_Weights.csv");
	if (weightsFile.fail())
	{
		cout << "There was an error when opening the weights output file." << endl;
		return 1;
	}

	//Initialize cost function output file
	ofstream costFile;
	costFile.open("Cost_Function.csv");
	if (costFile.fail())
	{
		cout << "There was an error opening the cost function file." << endl;
		return 1;
	}
	
	//Initialize input file for the input neuron values
	ifstream inputFile;
	inputFile.open("Input.csv");
	if (inputFile.fail())
	{
		cout << "There was an error when opening the input file." << endl;
		return 1;
	}

#pragma endregion File_Init

	//Initialize arrays for input, output, and weights
	int input[500];
	int output[500];
	string::size_type sz;
	
	//Assign the array of inputs and outputs based on the file input
	for (int a = 0; a < 500; a++)
	{
		string line;
		inputFile >> line;
		input [a] = stoi(line.substr(0, line.find_first_of(',')), &sz);
		output [a] = stoi(line.substr(line.find_first_of(',') + 1), &sz);
	}

	FeedForward fdFwd = FeedForward();
	Training tg = Training();

#pragma region Create_Neurons

	//Create the neurons
	Neuron inputNeuron = Neuron(0, 0);

	vector<Neuron> hiddenLayerOne;
	for (int i = 0; i < 4; i++)
	{
		hiddenLayerOne.push_back(Neuron(1, i));
	}
	vector<Neuron> hiddenLayerTwo;
	for (int i = 0; i < 4; i++)
	{
		hiddenLayerTwo.push_back(Neuron(2, i));
	}
	vector<Neuron> hiddenLayerThree;
	for (int i = 0; i < 4; i++)
	{
		hiddenLayerThree.push_back(Neuron(3, i));
	}

	Neuron outputNeuron = Neuron(4, 0);

#pragma endregion Create_Neurons

#pragma region Neuron_Connections

	//Create the neuron connections and output the randomized weights
	weightsFile << "Initial Weights" << endl;
	weightsFile << "Begin Layer,Begin Index,End Layer,End Index,Weight" << endl;

	vector<NeuronConnection> iToOne;
	for (int i = 0; i < hiddenLayerOne.size(); i++)
	{
		iToOne.push_back(NeuronConnection(0, 1, 0, i));
		weightsFile << "0,0,1," << i << "," << iToOne.back().getWeight() << endl;
	}

	vector<NeuronConnection> oneToTwo;
	for (int n = 0; n < hiddenLayerOne.size(); n++)
	{
		for (int i = 0; i < hiddenLayerTwo.size(); i++)
		{
			oneToTwo.push_back(NeuronConnection(1, 2, n, i));
			weightsFile << "1," << n << ",2," << i << "," << oneToTwo.back().getWeight() << endl;
		}
	}

	vector<NeuronConnection> twoToThree;
	for (int n = 0; n < hiddenLayerTwo.size(); n++)
	{
		for (int i = 0; i < hiddenLayerThree.size(); i++)
		{
			twoToThree.push_back(NeuronConnection(2, 3, n, i));
			weightsFile << "2," << n << ",3," << i << "," << twoToThree.back().getWeight() << endl;
		}
	}

	vector<NeuronConnection> threeToOut;
	for (int n = 0; n < hiddenLayerThree.size(); n++)
	{
		threeToOut.push_back(NeuronConnection(3, 4, n, 0));
		weightsFile << "3," << n << ",4,0," << threeToOut.back().getWeight() << endl;
	}

#pragma endregion Neuron_Connections

	//Run feedforward operation and collect errors
	costFile << "Pre-Optimization" << endl;
	costFile << "Input Number,Real,Predicted,Error" << endl;
	int outputInc = 1;

	vector<double> errors;

	for (int in : input)
	{
		inputNeuron.setInput((double)in);
		fdFwd.weightedSumFirstLayer(iToOne, inputNeuron, hiddenLayerOne);
		fdFwd.weightedSumInput(oneToTwo, hiddenLayerOne, hiddenLayerTwo);
		fdFwd.weightedSumInput(twoToThree, hiddenLayerTwo, hiddenLayerThree);
		fdFwd.lastWeightedSumInput(threeToOut, hiddenLayerThree, outputNeuron);

		errors.push_back(outputNeuron.getOutput());

		costFile << outputInc << "," << output[outputInc - 1] << "," << outputNeuron.getOutput() << "," << errors.back() << endl;
		outputInc++;
	}

	//Allow to check the console output.
	int yeetOut = 0;
	while (yeetOut < 5000000000)
	{
		yeetOut++;
	}
	
    return 0;
}