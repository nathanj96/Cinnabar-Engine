#ifndef COLLIDABLE_ATTORNEY
#define COLLIDABLE_ATTORNEY

class RegisterCollidableCommand;
class DeregisterCollidableCommand;
class CollidableGroup;
template <typename C1, typename C2> class CollisionDispatch;

#include "Collidable.h"

class CollidableAttorney
{
public:
	class Registration
	{
		friend class RegisterCollidableCommand;
		friend class DeregisterCollidableCommand;
		friend class CollidableGroup;
	private:
		static void RegisterCollidable(Collidable* col)
		{
			col->RegisterCollidable();
		}
		static void DeregisterCollidable(Collidable* col)
		{
			col->DeregisterCollidable();
		}
		static void setCollidableObjRef(Collidable* col, CollidableGroup::CollidableCollectionRef newRef)
		{
			col->setCollidableObjRef(newRef);
		}
	};
};

#endif COLLIDABLE_ATTORNEY