#ifndef COLLISION_VOLUME_BASE
#define COLLISION_VOLUME_BASE

class Model;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

#include "Matrix.h"
#include "Vect.h"

class CollisionVolumeBase
{
public:
	CollisionVolumeBase() = default;
	CollisionVolumeBase(const CollisionVolumeBase&) = default;
	CollisionVolumeBase& operator=(const CollisionVolumeBase&) = default;
	virtual ~CollisionVolumeBase() = default;

	virtual void ComputeData(Model* mod, const Matrix& mat) = 0;
	virtual void DebugView(const Vect& col) const = 0;

	virtual bool IntersectAccept(const CollisionVolumeBase& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const = 0;
};

#endif COLLISION_VOLUME_BASE