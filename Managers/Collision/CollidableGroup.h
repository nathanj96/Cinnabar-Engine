#ifndef COLLIDABLE_GROUP
#define COLLIDABLE_GROUP

#include <list>
#include "CollisionVolumeAABB.h"

class Collidable;

class CollidableGroup
{
public:
	//getter doesn't work if this is private
	using CollidableCollection = std::list<Collidable*>;
private:
	CollidableCollection collidableCollection;
	//AABB for the group, used for space partitioning
	CollisionVolumeAABB* groupVol;
public:
	CollidableGroup();
	CollidableGroup(const CollidableGroup&) = default;
	CollidableGroup& operator=(const CollidableGroup&) = default;
	~CollidableGroup();

	using CollidableCollectionRef = CollidableCollection::iterator;
	//const CollidableCollectionRef& maybe? Review slides later
	//it's just for setting the list refs - do inside function like usual, maybe
	//change later on
	void Deregister(Collidable* col);
	void Register(Collidable* col);
	const CollidableCollection& GetColliderCollection() const;

	void UpdateAABB();
	//for debug
	const CollisionVolumeAABB& GetGroupAABB() const;
};

#endif COLLIDABLE_GROUP