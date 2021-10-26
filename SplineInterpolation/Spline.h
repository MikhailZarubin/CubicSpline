#pragma once

#include <vector>

using std::vector;
using intPair = std::pair<int, int>;

class Spline
{
	vector<intPair> pointContainer;
public:
	Spline(std::initializer_list<intPair> pointList) :pointContainer{ pointList } {};
};

