#ifndef COLLISION_VOLUME_AABB
#define COLLISION_VOLUME_AABB

#include "CollisionVolumeBoundingBoxBase.h"
#include "Vect.h"

class CollidableGroup;
class CollisionGroupAABBAttorney;

class CollisionVolumeAABB : public CollisionVolumeBoundingBoxBase
{
	friend class CollisionVolumeAABBAttorney;
private:
	Vect minCorner;
	Vect maxCorner;

	void updatePartitionAABB(CollidableGroup* colGroup);
public:
	//allow default constructor so collidable groups can have AABBs
	CollisionVolumeAABB() = default;
	CollisionVolumeAABB(const CollisionVolumeAABB&) = default;
	CollisionVolumeAABB& operator=(const CollisionVolumeAABB&) = default;
	~CollisionVolumeAABB() = default;

	CollisionVolumeAABB(Model* mod);

	//Connected with the Visualizer to show all the collision cells of a terrain on screen
	void ComputeDataTerrain(Vect min, Vect max);

	virtual void ComputeData(Model* mod, const Matrix& mat) override;
	//Used for visualizing sound geometry - Min/max is computed within the geometry class, then passed in here to make
	//the AABB
	void ComputeDataSoundGeometry(Vect min, Vect max);

	virtual bool IntersectAccept(const CollisionVolumeBase& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const override;

	virtual void DebugView(const Vect& col) const override;

	Vect getMinCorner() const;
	Vect getMaxCorner() const;
};

#endif COLLISION_VOLUME_AABB