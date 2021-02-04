#ifndef COLLISION_VOLUME_BOUNDING_BOX_BASE
#define COLLISION_VOLUME_BOUNDING_BOX_BASE

#include "CollisionVolumeBase.h"
#include "Vect.h"

class CollisionVolumeBoundingBoxBase : public CollisionVolumeBase
{
protected:
	//AABBs need this for OBB intersection
	Matrix worldTrans;
	Vect centerWorld;
	Vect halfDiagLocal;
	float scaleFactorSquared;
public:
	CollisionVolumeBoundingBoxBase() = default;
	CollisionVolumeBoundingBoxBase(const CollisionVolumeBoundingBoxBase&) = default;
	CollisionVolumeBoundingBoxBase& operator=(const CollisionVolumeBoundingBoxBase&) = default;
	virtual ~CollisionVolumeBoundingBoxBase() = default;

	const Vect& getHalfDiagLocal() const;
	float getScaleFactorSquared() const;
	const Vect& getCenterWorld() const;
	const Matrix& getWorld() const;
};

#endif COLLISION_VOLUME_BOUNDING_BOX_BASE