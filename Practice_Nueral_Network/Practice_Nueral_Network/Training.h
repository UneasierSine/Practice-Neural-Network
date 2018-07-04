#pragma once
class Training
{
	public:
		Training();
		~Training();

		double costFunctionError(double predictedVal, double actualVal);
};

