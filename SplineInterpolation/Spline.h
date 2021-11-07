#pragma once

#include "Function.h"
#include <initializer_list>
#include <vector>


class Spline
{
	Function expression;
	std::vector<long double> pointContainer;
	std::vector<long double> coeffContainer;

	long double calculateCoeffA(int numberInterval) const;
	long double calculateCoeffB(int numberInterval) const;
	long double calculateCoeffC(int numberInterval) const;
	long double calculateCoeffD(int numberInterval) const;

	void fillCoeffContainer();
public:
	Spline() = default;
	Spline(const std::string& expressionStr, const std::string& secondDerivativeStr, const std::initializer_list<long double>& pointList);
	~Spline() = default;
	std::vector<Function> startInterpolation();
};

