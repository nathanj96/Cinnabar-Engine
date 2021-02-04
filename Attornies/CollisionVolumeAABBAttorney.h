#ifndef COLLISION_VOLUME_AABB_ATTORNEY
#define COLLISION_VOLUME_AABB_ATTORNEY

#include "CollidableGroup.h"
#include "CollisionVolumeAABB.h"

class CollisionVolumeAABBAttorney
{
	friend class CollidableGroup;
private:
	static void updatePartitionAABB(CollisionVolumeAABB* vol, CollidableGroup* colGroup)
	{
		vol->updatePartitionAABB(colGroup);
	}
};

#endif COLLISION_VOLUME_AABB_ATTORNEY