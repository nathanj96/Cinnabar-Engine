#ifndef COLLISION_DISPATCH_BASE
#define COLLISION_DISPATCH_BASE

class Collidable;

class CollisionDispatchBase
{
public:
	CollisionDispatchBase() = default;
	CollisionDispatchBase(const CollisionDispatchBase&) = default;
	CollisionDispatchBase& operator=(const CollisionDispatchBase&) = default;
	virtual ~CollisionDispatchBase() = default;

	virtual void ProcessCallbacks(Collidable* c1, Collidable* c2) = 0;
};

#endif COLLISION_DISPATCH_BASE