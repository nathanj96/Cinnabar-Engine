#include "CollisionVolumeBoundingBoxBase.h"

const Vect& CollisionVolumeBoundingBoxBase::getHalfDiagLocal() const
{
	return halfDiagLocal;
}

float CollisionVolumeBoundingBoxBase::getScaleFactorSquared() const
{
	return scaleFactorSquared;
}

const Vect& CollisionVolumeBoundingBoxBase::getCenterWorld() const
{
	return centerWorld;
}

const Matrix& CollisionVolumeBoundingBoxBase::getWorld() const
{
	return worldTrans;
}