// We will attempt to make a neural network.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

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
	weightsFile.open("/Output/Connection_Weights.csv");
	if (weightsFile.fail())
	{
		cout << "There was an error when opening the weights output file." << endl;
		return 1;
	}

	//Initialize cost function output file
	ofstream initialCostFile;
	initialCostFile.open("/Output/Cost_Function.csv");
	if (initialCostFile.fail())
	{
		cout << "There was an error opening the initial cost function file." << endl;
		return 1;
	}

	//Initialize cost function output file
	ofstream finalCostFile;
	finalCostFile.open("/Output/Cost_Function.csv");
	if (finalCostFile.fail())
	{
		cout << "There was an error opening the final cost function file." << endl;
		return 1;
	}

	//Initialize input file for the input neuron values
	ifstream inputFile;
	inputFile.open("/Input/Input.csv");
	if (inputFile.fail())
	{
		cout << "There was an error when opening the input file." << endl;
		return 1;
	}

#pragma endregion

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

	double learning_rate = 0.01;

	int outputInc = 1;
	vector<double> errors;

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

#pragma endregion

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

#pragma endregion 

#pragma region Initial_Feed_Forward
	//Run feedforward operation and collect errors
	initialCostFile << "Pre-Optimization" << endl;
	initialCostFile << "Input Number,Real,Predicted,Error" << endl;
	
	for (int in : input)
	{
		inputNeuron.setInput(in);
		
		fdFwd.weightedSumFirstLayer(iToOne, inputNeuron, hiddenLayerOne);		
		fdFwd.weightedSumInput(oneToTwo, hiddenLayerOne, hiddenLayerTwo);
		fdFwd.weightedSumInput(twoToThree, hiddenLayerTwo, hiddenLayerThree);
		fdFwd.lastWeightedSumInput(threeToOut, hiddenLayerThree, outputNeuron);

		errors.push_back(tg.costFunctionError(outputNeuron.getOutput(), output[outputInc - 1]));
		
		initialCostFile << outputInc << "," << output[outputInc - 1] << "," << outputNeuron.getOutput() << "," << errors.back() << endl;
		outputInc++;
	}
#pragma endregion 

#pragma region Training
	
	//Get the number of training epochs and create output files for them
	string epochUserInput = "";
	cout << "What is the number of epochs that you would like to train with? ";
	cin >> epochUserInput;
	int num_epochs = stoi(epochUserInput, &sz);

	vector<ofstream> epochFiles(num_epochs);
	for (int count = 0; count < epochFiles.size() ; count++)
	{
		string filename = "/Output/Epoch_" + to_string(count + 1) + "_Output.csv";
		epochFiles[count].open(filename);
		if (epochFiles[count].fail())
		{
			cout << "There was an error opening the output file for epoch " + (count + 1);
			return 1;
		}
	}

	for (int count = 0; count < epochFiles.size(); count++)
	{
		//Create file headers
		epochFiles[count] << "Pre-Weight Change,,,,Post-Weight Change" << endl;
		epochFiles[count] << "Input Number,Real,Predicted,Error,Input Number,Real,Predicted,Error";
		
		//Weight changes across each training example
		for (int in : input)
		{
			errors.clear();
			
			//Feed forward 
			inputNeuron.setInput(in);

			fdFwd.weightedSumFirstLayer(iToOne, inputNeuron, hiddenLayerOne);
			fdFwd.weightedSumInput(oneToTwo, hiddenLayerOne, hiddenLayerTwo);
			fdFwd.weightedSumInput(twoToThree, hiddenLayerTwo, hiddenLayerThree);
			fdFwd.lastWeightedSumInput(threeToOut, hiddenLayerThree, outputNeuron);

			errors.push_back(tg.costFunctionError(outputNeuron.getOutput(), output[outputInc - 1]));

			epochFiles[count] << outputInc << "," << output[outputInc - 1] << "," << outputNeuron.getOutput() << "," << errors.back() << ",";
			outputInc++;

			//Output layer error
			outputNeuron.setError(1.0);
			
			//Third hidden layer error and weight change
			for (NeuronConnection connecc : threeToOut)
			{
				hiddenLayerThree[connecc.getBeginIndex()].setError( tg.neuronOutputError( connecc, outputNeuron ) );
				connecc.setWeight( -tg.weightGradient( hiddenLayerThree[connecc.getBeginIndex()], outputNeuron ) * learning_rate + connecc.getWeight() );
			}
			for (NeuronConnection connecc : twoToThree)
			{
				hiddenLayerTwo[connecc.getBeginIndex()].setError( hiddenLayerTwo[connecc.getBeginIndex()].getError() + tg.neuronOutputError( connecc, hiddenLayerThree[connecc.getEndIndex] ) );
				connecc.setWeight( -tg.weightGradient( hiddenLayerTwo[connecc.getBeginIndex()], hiddenLayerThree[connecc.getEndIndex()] ) * learning_rate + connecc.getWeight() );
			}
			for (NeuronConnection connecc : oneToTwo)
			{
				hiddenLayerOne[connecc.getBeginIndex()].setError( hiddenLayerTwo[connecc.getBeginIndex()].getError() + tg.neuronOutputError( connecc, hiddenLayerTwo[connecc.getEndIndex()] ) );
				connecc.setWeight( -tg.weightGradient( hiddenLayerOne[connecc.getBeginIndex()], hiddenLayerTwo[connecc.getEndIndex()] ) * learning_rate + connecc.getWeight() );
			}
			for (NeuronConnection connecc : iToOne)
			{
				connecc.setWeight( -tg.weightGradient( inputNeuron, hiddenLayerOne[connecc.getEndIndex()] ) * learning_rate + connecc.getWeight() );
			}
		}
	}

#pragma endregion

#pragma region Final_Feed_Forward
	//Run feedforward operation and collect errors
	finalCostFile << "Post-Optimization" << endl;
	finalCostFile << "Input Number,Real,Predicted,Error" << endl;

	for (int in : input)
	{
		inputNeuron.setInput(in);

		fdFwd.weightedSumFirstLayer(iToOne, inputNeuron, hiddenLayerOne);
		fdFwd.weightedSumInput(oneToTwo, hiddenLayerOne, hiddenLayerTwo);
		fdFwd.weightedSumInput(twoToThree, hiddenLayerTwo, hiddenLayerThree);
		fdFwd.lastWeightedSumInput(threeToOut, hiddenLayerThree, outputNeuron);

		errors.push_back(tg.costFunctionError(outputNeuron.getOutput(), output[outputInc - 1]));

		initialCostFile << outputInc << "," << output[outputInc - 1] << "," << outputNeuron.getOutput() << "," << errors.back() << endl;
		outputInc++;
	}
#pragma endregion 

	cout << "ALL DONE" << endl;

	//Allow to check the console output.
	Sleep(50000);
	
    return 0;
}