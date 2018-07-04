#include "stdafx.h"
#include "Training.h"


Training::Training()
{
}


Training::~Training()
{
}

double Training::costFunctionError(double predictedVal, double actualVal)
{
	double error = (actualVal - predictedVal) * (actualVal - predictedVal);
	return error;
}