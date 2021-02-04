#ifndef COLLISION_VOLUME_BSPHERE
#define COLLISION_VOLUME_BSPHERE

#include "CollisionVolumeBase.h"
#include "CollisionVolumeAABB.h"
#include "Vect.h"

class CollisionVolumeBSphere : public CollisionVolumeBase
{
private:
	Vect center;
	float radius;
public:
	CollisionVolumeBSphere() = default;
	CollisionVolumeBSphere(const CollisionVolumeBSphere&) = default;
	CollisionVolumeBSphere& operator=(const CollisionVolumeBSphere&) = default;
	~CollisionVolumeBSphere() = default;

	virtual void ComputeData(Model* mod, const Matrix& mat) override;

	virtual void DebugView(const Vect& col) const override;

	virtual bool IntersectAccept(const CollisionVolumeBase& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const override;

	float GetRadius() const;
	const Vect& GetCenter() const;
};

#endif COLLISION_VOLUME_BSPHERE