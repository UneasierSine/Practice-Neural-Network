#pragma once
class Neuron
{
	long double input = 0.0;
	long double output = 0.0;

	int layerNumber = 0;
	int neuronIndex = 0;

	bool isInput = false;
	bool isOutput = false;

	long double error = 0.0;

	public:
		Neuron(int layer, int rank);
		~Neuron();

		long double getInput();
		long double getOutput();
		long double getError();

		void setInput(long double param);
		void setOutput(long double param);
		void setError(long double param);
};

