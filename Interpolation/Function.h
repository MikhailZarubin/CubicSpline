#pragma once

#include "Calculator.h"

#include <set>

using std::set;
using std::pair;

using doublePair = pair<long double, long double>;

class Function
{
protected:
	string functionExpression;
public:
	Function() = default;
	Function(const string& expression) : functionExpression(expression) {};
	~Function() = default;
	void replaceExpression(const string& newExpression);
	long double getValue(long double point) const;
	string getExpression() const;
};
