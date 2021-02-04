#ifndef COLLISION_TEST_TERRAIN_COMMAND
#define COLLISION_TEST_TERRAIN_COMMAND

class CollidableGroup;

#include "CollisionTestCommandBase.h"

class CollisionTestTerrainCommand : public CollisionTestCommandBase
{
private:
	CollidableGroup* ptrGrp;
	//terrain is retrieved from scene terrain manager
public:
	CollisionTestTerrainCommand() = delete;
	CollisionTestTerrainCommand(const CollisionTestTerrainCommand&) = delete;
	CollisionTestTerrainCommand& operator=(const CollisionTestTerrainCommand&) = delete;
	~CollisionTestTerrainCommand() = default;

	CollisionTestTerrainCommand(CollidableGroup* g);

	virtual void Execute() override;
};

#endif COLLISION_TEST_TERRAIN_COMMAND