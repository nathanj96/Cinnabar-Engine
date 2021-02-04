#include "CollidableGroup.h"
#include "Collidable.h"
#include "DebugOut.h"
#include "CollidableAttorney.h"
#include "CollisionVolumeAABBAttorney.h"

#include <string>
using namespace std;

CollidableGroup::CollidableGroup()
{
	groupVol = new CollisionVolumeAABB();
}

void CollidableGroup::UpdateAABB()
{
	CollisionVolumeAABBAttorney::updatePartitionAABB(groupVol, this);
}

void CollidableGroup::Register(Collidable* col)
{
	//collidableCollection.push_back(col);
	CollidableAttorney::Registration::setCollidableObjRef(col, collidableCollection.insert(collidableCollection.end(), col));
	//debug - comment out when not needed
	std::string disp = col->colName + " registered" + '\n';
	const char* dispCstr = disp.c_str();
	DebugMsg::out(const_cast<char*>(dispCstr));
	DebugMsg::out("Number now registered: %d\n", collidableCollection.size());
}

const CollisionVolumeAABB& CollidableGroup::GetGroupAABB() const
{
	return *groupVol;
}

void CollidableGroup::Deregister(Collidable* col)
{
	//collidableCollection.remove(col);
	collidableCollection.erase(col->getRef());
	//debug - comment out when not needed
	std::string disp = col->colName + " deregistered" + '\n';
	const char* dispCstr = disp.c_str();
	DebugMsg::out(const_cast<char*>(dispCstr));
	DebugMsg::out("Number now registered: %d\n", collidableCollection.size());
}

const CollidableGroup::CollidableCollection& CollidableGroup::GetColliderCollection() const
{
	return collidableCollection;
}

CollidableGroup::~CollidableGroup()
{
	delete groupVol;
	groupVol = nullptr;
}