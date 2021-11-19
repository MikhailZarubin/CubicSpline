#include "Spline.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

namespace RunThroughMethodFunctions {
	double calculateCoeffP(const std::vector<double>& alphaContainer,	const std::vector<double>& bettaContainer,
		const std::vector<double>& gammaContainer, std::vector<double>& answer, std::vector<double>::size_type currentIndex);
	double calculateCoeffQ(const std::vector<double>& alphaContainer,	const std::vector<double>& bettaContainer,
		const std::vector<double>& gammaContainer, const std::vector<double>& lambdaContainer, const std::vector<double>& containerCoeffP,
		std::vector<double>& answer, std::vector<double>::size_type currentIndex);
}


std::string convertFunction::valueToString(double value, std::string::size_type accuracy)
{
	std::string answer;

	std::ostringstream oStream;
	oStream << value;

	std::istringstream iStream(oStream.str());
	iStream >> answer;

	if (accuracy > 0)
	{
		string temporaryAnswer;
		std::string::size_type index;

		for (index = 0; index < answer.size(); index++)
		{
			if (answer[index] == '.' || answer[index] == ',')
				break;

			temporaryAnswer += answer[index];
		}

		while (index < answer.size() && accuracy != 0)
		{
			temporaryAnswer += answer[index];
			index++;
			accuracy--;
		}

		answer = temporaryAnswer;
	}

	return answer;
}

Spline::Spline(const std::vector<double>& valueList, const std::vector<double>& pointList) :
	valueContainer(valueList),
	pointContainer(pointList),
	coeffContainer(pointContainer.size())
{
	if (pointContainer.size() != valueContainer.size())
		throw - 1;

	coeffContainer[0] = 0;
	coeffContainer[coeffContainer.size() - 1] = 0;

	//sorting
	for (std::vector<double>::size_type i = 0; i < pointContainer.size(); i++)
	{
		for (std::vector<double>::size_type j = i + 1; j < pointContainer.size(); j++)
		{
			if (pointContainer[j] < pointContainer[i])
			{
				std::swap(pointContainer[i], pointContainer[j]);
				std::swap(valueContainer[i], valueContainer[j]);
			}

			if (pointContainer[j] == pointContainer[i])
				throw - 1;
		}
	}
}

double Spline::calculateCoeffA(int numberInterval) const
{
	return valueContainer[numberInterval];
}

double Spline::calculateCoeffB(int numberInterval) const
{
	double lastPoint = pointContainer[numberInterval - 1];
	double currentPoint = pointContainer[numberInterval];

	double currentIntervalLenght = currentPoint - lastPoint;

	double lastIntervalValue = valueContainer[numberInterval - 1];
	double intervalValue = valueContainer[numberInterval];

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
		double lastIntervalValue = valueContainer[i];
		double currentIntervalValue = valueContainer[i + 1];
		double nextIntervalValue = valueContainer[i + 2];

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

std::vector<std::pair<Function, SplineCoeffs>>Spline::startInterpolation()
{
	std::vector<std::pair<Function, SplineCoeffs>> functionsContainer(pointContainer.size() - 1, { Function(), SplineCoeffs() });
	fillCoeffContainer();

	for (std::vector<double>::size_type i = 0; i < functionsContainer.size(); i++)
	{
		double coeffA = calculateCoeffA(i + 1);
		double coeffB = calculateCoeffB(i + 1);
		double coeffC = calculateCoeffC(i + 1);
		double coeffD = calculateCoeffD(i + 1);

		std::string currentPoint = convertFunction::valueToString(pointContainer[i + 1]);
		std::string coeffAStr = convertFunction::valueToString(coeffA);
		std::string coeffBStr = convertFunction::valueToString(coeffB);
		std::string coeffCStr = convertFunction::valueToString(coeffC / 2);
		std::string coeffDStr = convertFunction::valueToString(coeffD / 6);

		std::string expression = coeffAStr + "+(" + coeffBStr + ")*(t-(" + currentPoint + "))+(" + coeffCStr + ")*((t-(" + currentPoint + "))^2)+(" + coeffDStr + ")*((t-(" + currentPoint + "))^3)";

		functionsContainer[i] = { Function(expression), SplineCoeffs(coeffA, coeffB, coeffC, coeffD) };
	}

	return functionsContainer;
}