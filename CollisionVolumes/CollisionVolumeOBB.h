#ifndef COLLISION_VOLUME_OBB
#define COLLISION_VOLUME_OBB

#include "CollisionVolumeBoundingBoxBase.h"

class CollisionVolumeOBB : public CollisionVolumeBoundingBoxBase
{
private:
	Vect minLocal;
	Vect maxLocal;
public:
	CollisionVolumeOBB() = delete;
	CollisionVolumeOBB(const CollisionVolumeOBB&) = default;
	CollisionVolumeOBB& operator=(const CollisionVolumeOBB&) = default;
	~CollisionVolumeOBB() = default;

	CollisionVolumeOBB(Model* mod);

	virtual void ComputeData(Model* mod, const Matrix& mat) override;
	virtual void DebugView(const Vect& col) const override;

	virtual bool IntersectAccept(const CollisionVolumeBase& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const override;

	//for visualizer
	const Vect& getMinLocal() const;
	const Vect& getMaxLocal() const;
};

#endif COLLISION_VOLUME_OBB