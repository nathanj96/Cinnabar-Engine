#ifndef COLLISION_DISPATCH
#define COLLISION_DISPATCH

#include "CollisionDispatchBase.h"

template <typename C1, typename C2> class CollisionDispatch : public CollisionDispatchBase
{
public:
	CollisionDispatch<C1, C2>() = default;
	CollisionDispatch<C1, C2>(const CollisionDispatch<C1, C2>&) = default;
	CollisionDispatch<C1, C2>& operator= (const CollisionDispatch<C1, C2>&) = default;
	~CollisionDispatch<C1, C2>() = default;

	virtual void ProcessCallbacks(Collidable* c1, Collidable* c2) override
	{
		C1* pDerCol1 = static_cast<C1*>(c1);
		C2* pDerCol2 = static_cast<C2*>(c2);

		pDerCol1->Collision(pDerCol2);
		pDerCol2->Collision(pDerCol1);
	}
};

#endif COLLISION_DISPATCH