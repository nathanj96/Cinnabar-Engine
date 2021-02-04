//additional file for god cam functions
#include "Camera.h"

void Camera::TranslateLeftRight(float delta)
{
	vPos += vRight * delta;
}

void Camera::TranslateForwardBack(float delta)
{
	vPos -= vDir * delta;
}

void Camera::RotateLeftRight(float angle)
{
	Matrix Rot = Matrix(ROT_Y, angle);
	vDir = vDir * Rot;
	vUp = vUp * Rot;
	setOrientAndPosition(vUp, vPos - vDir, vPos);
}

void Camera::RotateUpDown(float angle)
{
	Matrix Rot = Matrix(ROT_AXIS_ANGLE, vRight, angle);
	vDir = vDir * Rot;
	vUp = vUp * Rot;
	setOrientAndPosition(vUp, vPos - vDir, vPos);
}