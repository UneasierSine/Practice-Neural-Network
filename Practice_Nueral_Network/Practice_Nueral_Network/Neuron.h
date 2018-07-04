#pragma once
class Neuron
{
	double input = 0.0;
	double output = 0.0;

	int layerNumber = 0;
	int neuronIndex = 0;

	bool isInput = false;
	bool isOutput = false;

	public:
		Neuron(int layer, int rank);
		~Neuron();

		void activationFunction(double in);

		double getInput();
		double getOutput();

		void setInput(double param);
		void setOnput(double param);
};

