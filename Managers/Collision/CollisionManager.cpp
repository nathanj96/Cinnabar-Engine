#include "CollisionManager.h"
#include "CollidableGroup.h"

#include "CollisionTestCommandBase.h"
#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"
#include <list>

//for debug
#include "Visualizer.h"
#include "Colors.h"

CollisionManager::CTypeID CollisionManager::TypeIDNextNumber = 0;

CollisionManager::CollisionManager() : colGroupCollection(MAX_COLLISION_GROUP, nullptr)
{
};

void CollisionManager::UpdateGroupAABBs()
{
	//can't do while not nullptr because the scene might not have any collidables with id 0 but might have some with id 1.
	//then might have none with ids 2 or 3 but some with id 4, et al.
	for (unsigned int i = 0; i < colGroupCollection.size(); i++)
	{
		if (colGroupCollection[i] != nullptr)
		{
			colGroupCollection[i]->UpdateAABB();
		}
	}
}

void CollisionManager::SetGroupForTypeID(CollisionManager::CTypeID ind)
{
	if (colGroupCollection[ind] == nullptr)
	{
		colGroupCollection[ind] = new CollidableGroup();
	}
}

CollidableGroup* CollisionManager::GetColGroup(CollisionManager::CTypeID id)
{
	return colGroupCollection[id];
}

CollisionManager::~CollisionManager()
{
	for (int i = 0; i < MAX_COLLISION_GROUP; i++)
	{
		delete colGroupCollection[i];
		colGroupCollection[i] = nullptr;
	}
	for (CollisionTestCommands::iterator it = colTestCommands.begin(); it != colTestCommands.end(); it++)
	{
		delete (*it);
	}
}

void CollisionManager::ProcessCommands()
{
	for (CollisionTestCommands::iterator it = colTestCommands.begin(); it != colTestCommands.end(); it++)
	{
		(*it)->Execute();
	}
}

void CollisionManager::ProcessCollision()
{
	//update group partitioning parameters before doing collision tests
	UpdateGroupAABBs();
	ProcessCommands();
}