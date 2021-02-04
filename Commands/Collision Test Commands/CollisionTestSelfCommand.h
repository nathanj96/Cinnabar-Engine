#ifndef COLLISION_TEST_SELF_COMMAND
#define COLLISION_TEST_SELF_COMMAND

class CollisionDispatchBase;
class CollidableGroup;

#include "CollisionTestCommandBase.h"

class CollisionTestSelfCommand : public CollisionTestCommandBase
{
private:
	CollisionDispatchBase* ptrDispatch;
	CollidableGroup* ptrGrp;
public:
	CollisionTestSelfCommand() = delete;
	CollisionTestSelfCommand(const CollisionTestSelfCommand&) = delete;
	CollisionTestSelfCommand& operator=(const CollisionTestSelfCommand&) = delete;
	~CollisionTestSelfCommand();

	CollisionTestSelfCommand(CollidableGroup* g, CollisionDispatchBase* pd);

	virtual void Execute() override;
};

#endif COLLISION_TEST_SELF_COMMAND