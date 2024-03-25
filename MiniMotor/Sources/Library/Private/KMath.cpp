#include "KMath.h"

#include <cmath>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Lite
{
    const double KMath::Pi()
    {
        return M_PI;
    }

    double KMath::DegreeToRad(const double angle)
    {
        return angle * Pi() / 180.0;
    }

    double KMath::RadToDegree(const double angle)
    {
        return angle * 180.0 / Pi();
    }

    double KMath::Cos(double value)
    {
        return std::cos(value);
    }

    double KMath::Sin(double value)
    {
        return std::sin(value);
    }

    double KMath::Sqrt(double value)
    {
        return std::sqrt(value);
    }

    double KMath::Pow(double value)
    {
        return value * value;
    }
}
