#include "UpdatableManager.h"
#include "UpdatableAttorney.h"
#include "DebugOut.h"

void UpdatableManager::Register(Updatable* up)
{
	//insert an element into the list, then save its iterator inside the element for constant time removal later
	UpdatableAttorney::Registration::setUpdateObjRef(up, updateList.insert(updateList.end(), up));
	//DebugMsg::out("Updatable registered\n");
}

void UpdatableManager::Deregister(Updatable* up)
{
	updateList.erase(up->getUpdateObjRef());
	//DebugMsg::out("Updatable deregistered\n");
}

void UpdatableManager::processElements()
{
	std::list<Updatable*>::iterator it;
	for (it = updateList.begin(); it != updateList.end(); it++)
	{
		UpdatableAttorney::GameLoop::Update(*it);
	}
}