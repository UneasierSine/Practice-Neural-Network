#pragma once
class NeuronConnection
{
	int beginLayer = 0;
	int endLayer = 0;
	int beginIndex = 0;
	int endIndex = 0;

	double weight = 0.0;
	double input = 0.0;
	double output = 0.0;

	public:
		NeuronConnection(int layer1, int layer2, int index1, int index2);
		~NeuronConnection();

		double getInput();
		double getOutput();
		double getWeight();

		int getBeginIndex();
		int getEndIndex();

		void setInput(double param);
		void setOutput(double param);
		void setWeight(double param);

		double calculatedOutput();
};

