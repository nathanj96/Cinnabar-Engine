#include "GameUpdatableManager.h"
#include "GameUpdatableAttorney.h"

void GameUpdatableManager::Register(GameUpdatable* up)
{
	GameUpdatableAttorney::Registration::setUpdateObjRef(up, updateList.insert(updateList.end(), up));
}

void GameUpdatableManager::Deregister(GameUpdatable* up)
{
	updateList.erase(up->getUpdateObjRef());
}

void GameUpdatableManager::processElements()
{
	std::list<GameUpdatable*>::iterator it;
	for (it = updateList.begin(); it != updateList.end(); it++)
	{
		GameUpdatableAttorney::GameLoop::GameUpdate(*it);
	}
}