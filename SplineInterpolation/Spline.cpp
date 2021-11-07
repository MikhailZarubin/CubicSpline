#include "Spline.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
	std::string valueToString(long double value)
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
	long double calculateCoeffP(const std::vector<long double>& alphaContainer,	const std::vector<long double>& bettaContainer,
		const std::vector<long double>& gammaContainer, std::vector<long double>& answer, std::vector<long double>::size_type currentIndex);
	long double calculateCoeffQ(const std::vector<long double>& alphaContainer,	const std::vector<long double>& bettaContainer,
		const std::vector<long double>& gammaContainer, const std::vector<long double>& lambdaContainer, const std::vector<long double>& containerCoeffP,
		std::vector<long double>& answer, std::vector<long double>::size_type currentIndex);
}


Spline::Spline(const std::string& expressionStr, const std::string& secondDerivativeStr, const std::initializer_list<long double>& pointList) :
	expression(expressionStr),
	pointContainer(pointList),
	coeffContainer(pointContainer.size())
{
	std::sort(pointContainer.begin(), pointContainer.end());
	long double leftBorder = *pointContainer.begin();
	long double rightBorder = *(--pointContainer.end());

	Function secondDerivative(secondDerivativeStr);
	long double firstCoef = secondDerivative.getValue(leftBorder);
	long double lastCoef = secondDerivative.getValue(rightBorder);
	coeffContainer[0] = firstCoef;
	coeffContainer[coeffContainer.size() - 1] = lastCoef;
}

long double Spline::calculateCoeffA(int numberInterval) const
{
	return expression.getValue(pointContainer[numberInterval]);
}

long double Spline::calculateCoeffB(int numberInterval) const
{
	long double lastPoint = pointContainer[numberInterval - 1];
	long double currentPoint = pointContainer[numberInterval];

	long double currentIntervalLenght = currentPoint - lastPoint;

	long double lastIntervalValue = expression.getValue(lastPoint);
	long double intervalValue = expression.getValue(currentPoint);

	return (intervalValue - lastIntervalValue) / currentIntervalLenght +
		coeffContainer[numberInterval] * currentIntervalLenght / 3 +
		coeffContainer[numberInterval - 1] * currentIntervalLenght / 6;
}

void Spline::fillCoeffContainer()
{
	std::vector<long double>::size_type sizeContainers = coeffContainer.size() - 2;

	std::vector<long double> alphaContainer(sizeContainers);
	std::vector<long double> bettaContainer(sizeContainers);
	std::vector<long double> gammaContainer(sizeContainers);
	std::vector<long double> lambdaContainer(sizeContainers);

	for (std::vector<long double>::size_type i = 0; i < sizeContainers; i++)
	{
		long double lastIntervalValue = expression.getValue(pointContainer[i]);
		long double currentIntervalValue = expression.getValue(pointContainer[i + 1]);
		long double nextIntervalValue = expression.getValue(pointContainer[i + 2]);

		long double currentIntervalLenght = pointContainer[i + 1] - pointContainer[i];
		long double nextIntervalLenght = pointContainer[i + 2] - pointContainer[i + 1];

		alphaContainer[i] = currentIntervalLenght;
		bettaContainer[i] = -2 * (currentIntervalLenght + nextIntervalLenght);
		gammaContainer[i] = nextIntervalLenght;
		lambdaContainer[i] = 6 * (nextIntervalValue - currentIntervalValue) / nextIntervalLenght - (currentIntervalValue - lastIntervalValue) / currentIntervalLenght;
	}
	alphaContainer[0] = 0;
	lambdaContainer[0] -= alphaContainer[0] * coeffContainer[0];
	lambdaContainer[sizeContainers - 1] -= gammaContainer[sizeContainers - 1] * coeffContainer[sizeContainers + 1];
	gammaContainer[sizeContainers - 1] = 0;

	std::vector<long double> containerCoeffP(sizeContainers - 1);
	RunThroughMethodFunctions::calculateCoeffP(alphaContainer, bettaContainer, gammaContainer, containerCoeffP, sizeContainers - 2);

	std::vector<long double> containerCoeffQ(sizeContainers - 1);
	RunThroughMethodFunctions::calculateCoeffQ(alphaContainer, bettaContainer, gammaContainer, lambdaContainer, containerCoeffP, containerCoeffQ, sizeContainers - 2);

	coeffContainer[sizeContainers] = (alphaContainer[sizeContainers - 1] * containerCoeffQ[sizeContainers - 2] - lambdaContainer[sizeContainers - 1]) /
		(bettaContainer[sizeContainers - 1] - alphaContainer[sizeContainers - 1] * containerCoeffP[sizeContainers - 2]);

	for (std::vector<long double>::size_type i = sizeContainers - 1; i > 0; i--)
		coeffContainer[i] = containerCoeffP[i - 1] * coeffContainer[i + 1] + containerCoeffQ[i - 1];
}

long double RunThroughMethodFunctions::calculateCoeffP(const std::vector<long double>& alphaContainer,
	const std::vector<long double>& bettaContainer, const std::vector<long double>& gammaContainer, std::vector<long double>& answer,
	std::vector<long double>::size_type currentIndex)
{
	if (currentIndex == 0) 
	{
		answer[0] = gammaContainer[0] / bettaContainer[0];
		return answer[0];
	}
	else
	{
		answer[currentIndex] = gammaContainer[currentIndex] /
			(bettaContainer[currentIndex] - alphaContainer[currentIndex] * calculateCoeffP(alphaContainer, bettaContainer, gammaContainer, answer, currentIndex - 1));
		return answer[currentIndex];
	}
}

long double RunThroughMethodFunctions::calculateCoeffQ(const std::vector<long double>& alphaContainer,
	const std::vector<long double>& bettaContainer, const std::vector<long double>& gammaContainer, 
	const std::vector<long double>& lambdaContainer, const std::vector<long double>& containerCoeffP,
	std::vector<long double>& answer, std::vector<long double>::size_type currentIndex)
{
	if (currentIndex == 0)
	{
		answer[0] = -lambdaContainer[0] / bettaContainer[0];
		return answer[0];
	}
	else
	{
		answer[currentIndex] = (alphaContainer[currentIndex] *
			calculateCoeffQ(alphaContainer, bettaContainer, gammaContainer, lambdaContainer, containerCoeffP, answer, currentIndex - 1) -
			gammaContainer[currentIndex]) / (bettaContainer[currentIndex] - containerCoeffP[currentIndex - 1] * alphaContainer[currentIndex]);
		return answer[currentIndex];
	}
}

long double Spline::calculateCoeffC(int numberInterval) const
{
	return coeffContainer[numberInterval];
}

long double Spline::calculateCoeffD(int numberInterval) const
{
	long double lastCoeff = coeffContainer[numberInterval - 1];
	long double currentCoeff = coeffContainer[numberInterval];

	long double currentIntervalLenght = pointContainer[numberInterval] - pointContainer[numberInterval - 1];

	return (currentCoeff - lastCoeff) / currentIntervalLenght;
}

std::vector<Function>Spline::startInterpolation()
{
	std::vector<Function> functionsContainer(pointContainer.size() - 1, Function());
	fillCoeffContainer();

	for (std::vector<long double>::size_type i = 0; i < functionsContainer.size(); i++)
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