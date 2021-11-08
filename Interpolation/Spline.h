#pragma once

#include "Function.h"
#include <vector>

namespace convertFunction {
	std::string valueToString(double value);
}


class Spline
{
	Function expression;
	std::vector<double> pointContainer;
	std::vector<double> coeffContainer;

	double calculateCoeffA(int numberInterval) const;
	double calculateCoeffB(int numberInterval) const;
	double calculateCoeffC(int numberInterval) const;
	double calculateCoeffD(int numberInterval) const;

	void fillCoeffContainer();
public:
	Spline() = default;
	Spline(const std::string& expressionStr, const std::string& secondDerivativeStr, const std::vector<double>& pointList);
	~Spline() = default;
	std::vector<Function> startInterpolation();
};

