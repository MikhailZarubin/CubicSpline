#include "Spline.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
	std::string valueToString(double value)
	{
		std::string answer;

		std::ostringstream oStream;
		oStream << value;

		std::istringstream iStream(oStream.str());
		iStream >> answer;

		return answer;
	}
}

namespace RunThroughMethodFunctions
{
	double calculateCoeffP(const std::vector<double>& alphaContainer,	const std::vector<double>& bettaContainer,
		const std::vector<double>& gammaContainer, std::vector<double>& answer, std::vector<double>::size_type currentIndex);
	double calculateCoeffQ(const std::vector<double>& alphaContainer,	const std::vector<double>& bettaContainer,
		const std::vector<double>& gammaContainer, const std::vector<double>& lambdaContainer, const std::vector<double>& containerCoeffP,
		std::vector<double>& answer, std::vector<double>::size_type currentIndex);
}


Spline::Spline(const std::string& expressionStr, const std::string& secondDerivativeStr, const std::vector<double>& pointList) :
	expression(expressionStr),
	pointContainer(pointList),
	coeffContainer(pointContainer.size())
{
	std::sort(pointContainer.begin(), pointContainer.end());
	double leftBorder = *pointContainer.begin();
	double rightBorder = *(--pointContainer.end());

	Function secondDerivative(secondDerivativeStr);
	double firstCoef = secondDerivative.getValue(leftBorder);
	double lastCoef = secondDerivative.getValue(rightBorder);
	coeffContainer[0] = firstCoef;
	coeffContainer[coeffContainer.size() - 1] = lastCoef;
}

double Spline::calculateCoeffA(int numberInterval) const
{
	return expression.getValue(pointContainer[numberInterval]);
}

double Spline::calculateCoeffB(int numberInterval) const
{
	double lastPoint = pointContainer[numberInterval - 1];
	double currentPoint = pointContainer[numberInterval];

	double currentIntervalLenght = currentPoint - lastPoint;

	double lastIntervalValue = expression.getValue(lastPoint);
	double intervalValue = expression.getValue(currentPoint);

	return (intervalValue - lastIntervalValue) / currentIntervalLenght +
		coeffContainer[numberInterval] * currentIntervalLenght / 3 +
		coeffContainer[numberInterval - 1] * currentIntervalLenght / 6;
}

// https://pro-prof.com/forums/topic/sweep-method-for-solving-systems-of-linear-algebraic-equations
void Spline::fillCoeffContainer()
{
	std::vector<double>::size_type sizeContainers = coeffContainer.size() - 2;

	std::vector<double> alphaContainer(sizeContainers);
	std::vector<double> bettaContainer(sizeContainers);
	std::vector<double> gammaContainer(sizeContainers);
	std::vector<double> lambdaContainer(sizeContainers);

	for (std::vector<double>::size_type i = 0; i < sizeContainers; i++)
	{
		double lastIntervalValue = expression.getValue(pointContainer[i]);
		double currentIntervalValue = expression.getValue(pointContainer[i + 1]);
		double nextIntervalValue = expression.getValue(pointContainer[i + 2]);

		double currentIntervalLenght = pointContainer[i + 1] - pointContainer[i];
		double nextIntervalLenght = pointContainer[i + 2] - pointContainer[i + 1];

		alphaContainer[i] = currentIntervalLenght;
		bettaContainer[i] = 2 * (currentIntervalLenght + nextIntervalLenght);
		gammaContainer[i] = nextIntervalLenght;
		lambdaContainer[i] = 6 * ((nextIntervalValue - currentIntervalValue) / nextIntervalLenght - (currentIntervalValue - lastIntervalValue) / currentIntervalLenght);
	}
	lambdaContainer[0] -= alphaContainer[0] * coeffContainer[0];
	lambdaContainer[sizeContainers - 1] -= gammaContainer[sizeContainers - 1] * coeffContainer[sizeContainers + 1];

	std::vector<double> containerCoeffP(sizeContainers);
	RunThroughMethodFunctions::calculateCoeffP(alphaContainer, bettaContainer, gammaContainer, containerCoeffP, sizeContainers - 1);

	std::vector<double> containerCoeffQ(sizeContainers);
	RunThroughMethodFunctions::calculateCoeffQ(alphaContainer, bettaContainer, gammaContainer, lambdaContainer, containerCoeffP, containerCoeffQ, sizeContainers - 1);

	coeffContainer[sizeContainers] = containerCoeffQ[sizeContainers - 1]; 

	for (std::vector<double>::size_type i = sizeContainers - 1; i > 0; i--)
		coeffContainer[i] = containerCoeffP[i - 1] * coeffContainer[i + 1] + containerCoeffQ[i - 1];
}

double RunThroughMethodFunctions::calculateCoeffP(const std::vector<double>& alphaContainer,
	const std::vector<double>& bettaContainer, const std::vector<double>& gammaContainer, std::vector<double>& answer,
	std::vector<double>::size_type currentIndex)
{
	if (currentIndex == 0) 
	{
		answer[0] = -1 * gammaContainer[0] / bettaContainer[0];
		return answer[0];
	}
	else
	{
		answer[currentIndex] = -1 * gammaContainer[currentIndex] /
			(bettaContainer[currentIndex] + alphaContainer[currentIndex] * calculateCoeffP(alphaContainer, bettaContainer, gammaContainer, answer, currentIndex - 1));
		return answer[currentIndex];
	}
}

double RunThroughMethodFunctions::calculateCoeffQ(const std::vector<double>& alphaContainer,
	const std::vector<double>& bettaContainer, const std::vector<double>& gammaContainer, 
	const std::vector<double>& lambdaContainer, const std::vector<double>& containerCoeffP,
	std::vector<double>& answer, std::vector<double>::size_type currentIndex)
{
	if (currentIndex == 0)
	{
		answer[0] = lambdaContainer[0] / bettaContainer[0];
		return answer[0];
	}
	else
	{
		answer[currentIndex] = (lambdaContainer[currentIndex] -
			alphaContainer[currentIndex] * calculateCoeffQ(alphaContainer, bettaContainer, gammaContainer, lambdaContainer, containerCoeffP, answer, currentIndex - 1)) /
			(bettaContainer[currentIndex] + containerCoeffP[currentIndex - 1] * alphaContainer[currentIndex]);
		return answer[currentIndex];
	}
}

double Spline::calculateCoeffC(int numberInterval) const
{
	return coeffContainer[numberInterval];
}

double Spline::calculateCoeffD(int numberInterval) const
{
	double lastCoeff = coeffContainer[numberInterval - 1];
	double currentCoeff = coeffContainer[numberInterval];

	double currentIntervalLenght = pointContainer[numberInterval] - pointContainer[numberInterval - 1];

	return (currentCoeff - lastCoeff) / currentIntervalLenght;
}

std::vector<Function>Spline::startInterpolation()
{
	std::vector<Function> functionsContainer(pointContainer.size() - 1, Function());
	fillCoeffContainer();

	for (std::vector<double>::size_type i = 0; i < functionsContainer.size(); i++)
	{
		std::string currentPoint = ::valueToString(pointContainer[i + 1]);
		std::string coeffA = ::valueToString(calculateCoeffA(i + 1));
		std::string coeffB = ::valueToString(calculateCoeffB(i + 1));
		std::string coeffC = ::valueToString(calculateCoeffC(i + 1) / 2);
		std::string coeffD = ::valueToString(calculateCoeffD(i + 1) / 6);

		std::string expression = coeffA + "+" + coeffB + "*(t-" + currentPoint + ")+" + coeffC + "*((t-" + currentPoint + ")^2)+" + coeffD + "*((t-" + currentPoint + ")^3)";

		functionsContainer[i] = Function(expression);
	}

	return functionsContainer;
}