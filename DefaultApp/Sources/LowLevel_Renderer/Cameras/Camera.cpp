#include "Camera.h"

Math::Mat4<float> Camera::getMatrixView() const
{
	// Obtenez la matrice de transformation de la camera
	Math::Mat4<float> cameraMatrix = transform.getMatrix();

	// Calculez une matrice de translation pour ramener la camera a l'origine du monde
	Math::Point3D<float> inversePos = { -transform.position.x, -transform.position.y, -transform.position.z };
	Math::Mat4<float> translateToOrigin = Math::Mat4<float>::translate(inversePos);

	// Appliquez d'abord la translation, puis la transformation de la camera, puis inversez la translation
	return translateToOrigin * cameraMatrix * translateToOrigin;
}

