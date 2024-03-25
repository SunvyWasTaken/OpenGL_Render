// SunvyNeverExist Copyright please don't steal work that isn't yours

#pragma once

#include "Core.h"
#include "Vector.h"
#include "Rotator.h"

namespace Lite
{
	template <typename T>
	struct Transform
	{
		Vector<typename T> Location;
		Rotator<typename T> Rotation;
		Vector<typename T> Scale = {1.0, 1.0, 1.0};
	};
}

using FVector = Lite::Vector<double>;
using FRotator = Lite::Rotator<double>;
using FTransform = Lite::Transform<double>;
