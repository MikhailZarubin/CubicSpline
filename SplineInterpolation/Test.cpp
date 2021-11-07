#include "Function.h"
#include "Spline.h"

#include <iostream>

int main()
{
	Spline spline("t^3", "6*t", { -2, 0, 3, 5 });
	auto result = spline.startInterpolation();
	return 0;
}