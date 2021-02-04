#ifndef COLLISION_TEST_PAIR_COMMAND
#define COLLISION_TEST_PAIR_COMMAND

class CollisionDispatchBase;
class CollidableGroup;

#include "CollisionTestCommandBase.h"

class CollisionTestPairCommand : public CollisionTestCommandBase
{
private:
	CollisionDispatchBase* ptrDispatch;
	CollidableGroup* ptrGrp1;
	CollidableGroup* ptrGrp2;
public:
	CollisionTestPairCommand() = delete;
	CollisionTestPairCommand(const CollisionTestPairCommand&) = delete;
	CollisionTestPairCommand& operator=(const CollisionTestPairCommand&) = delete;
	~CollisionTestPairCommand();

	CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd);

	virtual void Execute() override;
};

#endif COLLISION_TEST_PAIR_COMMAND