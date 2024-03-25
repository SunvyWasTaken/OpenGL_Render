// SunvyNeverExist Copyright please don't steal work that isn't yours

#pragma once

#include "Core.h"

#include "KMath.h"

namespace Lite
{
	template <typename T>
	struct  Vector
	{
		explicit Vector(T num = 0);
		Vector(T x, T y, T z);

		// TODO do the rest of the math;

		T X;
		T Y;
		T Z;

		// Addition de deux vecteurs
		Vector operator+(const Vector& other) const 
		{
			return Vector(X + other.X, Y + other.Y, Z + other.Z);
		}

		// Soustraction de deux vecteurs
		Vector operator-(const Vector& other) const 
		{
			return Vector(X - other.X, Y - other.Y, Z - other.Z);
		}

		Vector operator*(const Vector& other) const {
			return Vector(X * other.X, Y * other.Y, Z * other.Z);
		}

		// Produit scalaire de deux vecteurs
		float Dot(const Vector& other) const 
		{
			return X * other.X + Y * other.Y + Z * other.Z;
		}

		// Produit vectoriel de deux vecteurs
		Vector Cross(const Vector& other) const
		{
			return Vector(Z * other.Z - Z * other.Y,
				Z * other.X - X * other.Z,
				X * other.Y - Y * other.X);
		}

		// Calcul de la longueur (norme) du vecteur
		float Length() const
		{
			return KMath::Sqrt(X * X + Y * Y + Z * Z);
		}

		// Normalisation du vecteur
		Vector SafeNormalize() const 
		{
			const float len = Length();
			if (len != 0.0f)
				return Vector(X / len, Y / len, Z / len);
			else
				return Vector();
		}
	};
}

#include "../Private/Vector.hxx"
