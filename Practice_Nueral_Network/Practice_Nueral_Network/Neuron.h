#pragma once
class Neuron
{
	double input = 0.0;
	double output = 0.0;

	int layerNumber = 0;
	int neuronIndex = 0;

	bool isInput = false;
	bool isOutput = false;

	double error = 0.0;

	public:
		Neuron(int layer, int rank);
		~Neuron();

		double getInput();
		double getOutput();
		double getError();

		void setInput(double param);
		void setOnput(double param);
		void setError(double param);
};

