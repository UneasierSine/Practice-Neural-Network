#pragma once
class NeuronConnection
{
	int beginLayer = 0;
	int endLayer = 0;
	int beginIndex = 0;
	int endIndex = 0;

	long double weight = 0.0;
	long double input = 0.0;
	long double output = 0.0;

	public:
		NeuronConnection(int layer1, int layer2, int index1, int index2);
		~NeuronConnection();

		long double getInput();
		long double getOutput();
		long double getWeight();

		int getBeginIndex();
		int getEndIndex();

		void setInput(long double param);
		void setOutput(long double param);
		void setWeight(long double param);
};

