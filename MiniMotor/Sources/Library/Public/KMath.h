// SunvyNeverExist Copyright please don't steal work that isn't yours

#pragma once

#include "Core.h"

namespace Lite
{
	struct KMath
	{
		static const double Pi();
		static double DegreeToRad(const double angle);
		static double RadToDegree(const double angle);

		static double Cos(double value);
		static double Sin(double value);

		static double Sqrt(double value);
		static double Pow(double value);
	};
}

