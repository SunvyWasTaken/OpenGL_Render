// SunvyNeverExist Copyright please don't steal work that isn't yours

#pragma once

#include "Core.h"

#include "Rotator.h"
#include "Vector.h"

#include "KMath.h"

using FVector = Lite::Vector<double>;

namespace Lite
{
	template <typename T>
	struct Quaternion;

	template <typename T>
	struct Rotator
	{
		Rotator(T value = 0) : Pitch(value), Yaw(value), Roll(value) {}
		Rotator(T pitch, T yaw, T roll) : Pitch(pitch), Yaw(yaw), Roll(roll) {}

		T Pitch;
		T Yaw;
		T Roll;

		Vector<T> GetForward() const;

	};

	template <typename T>
	struct Quaternion
	{
		T X, Y, Z, W;
	};


	template<typename T>
	Vector<T> Rotator<T>::GetForward() const
	{
		const double RRoll = KMath::DegreeToRad(Roll);
		const double RPitch = KMath::DegreeToRad(Pitch);
		const double RYaw = KMath::DegreeToRad(Yaw);

		double Rx[3][3] = {
			{1.0, 0.0, 0.0},
			{0.0, KMath::Cos(RRoll), -1 * KMath::Sin(RRoll)},
			{0.0, KMath::Sin(RRoll), KMath::Cos(RRoll)}
		};

		double Ry[3][3] = {
			{KMath::Cos(RPitch), 0.0, KMath::Sin(RPitch)},
			{0.0, 1.0, 0.0},
			{-1 * KMath::Sin(RPitch), 0.0, KMath::Cos(RPitch)}
		};

		double Rz[3][3] = {
			{KMath::Cos(RYaw), -1 * KMath::Sin(RYaw), 0.0},
			{KMath::Sin(RYaw), KMath::Cos(RYaw), 0.0},
			{0.0, 0.0, 1.0}
		};

		double R[3][3] = Rz * Ry * Rx;

		FVector ForwardVector = R[0][0];

		return ForwardVector;
	}
}
