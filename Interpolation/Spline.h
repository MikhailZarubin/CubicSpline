#pragma once

#include "Function.h"
#include <vector>

namespace convertFunction {
	std::string valueToString(double valuem, std::string::size_type accuracy = 0);
}


struct SplineCoeffs
{
	double aCoeff, bCoeff, cCoeff, dCoeff;

	SplineCoeffs(double a = 0, double b = 0, double c = 0, double d = 0) :aCoeff(a), bCoeff(b), cCoeff(c), dCoeff(d) {};
};

class Spline
{
	std::vector<double> valueContainer;
	std::vector<double> pointContainer;
	std::vector<double> coeffContainer;

	double calculateCoeffA(int numberInterval) const;
	double calculateCoeffB(int numberInterval) const;
	double calculateCoeffC(int numberInterval) const;
	double calculateCoeffD(int numberInterval) const;

	void fillCoeffContainer();
public:
	Spline() = default;
	Spline(const std::vector<double>& valueList, const std::vector<double>& pointList);
	~Spline() = default;
	std::vector<std::pair<Function, SplineCoeffs>> startInterpolation();
};

