#ifndef COLLISION_TEST_COMMAND_BASE
#define COLLISION_TEST_COMMAND_BASE

class CollisionTestCommandBase
{
public:
	CollisionTestCommandBase() = default;
	CollisionTestCommandBase(const CollisionTestCommandBase&) = default;
	CollisionTestCommandBase& operator=(const CollisionTestCommandBase&) = default;
	virtual void Execute() = 0;

	virtual ~CollisionTestCommandBase()
	{
	};
};

#endif COLLISION_TEST_COMMAND_BASE