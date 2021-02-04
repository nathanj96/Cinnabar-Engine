#include "KeyboardEventManager.h"
#include "SingleKeyEventManager.h"

void KeyboardEventManager::RegisterKeyPress(Inputable* in, AZUL_KEY k)
{
	//see if a manager for the provided key already exists
	SingleKeyMgrMap::iterator it = singleKeyMgrs.find(k);
	if (it != singleKeyMgrs.end())
	{
		(*it).second->RegisterKeyPress(in);
	}
	else
	{
		SingleKeyEventManager* newKeyMgr = new SingleKeyEventManager(k);
		singleKeyMgrs.insert(std::pair<AZUL_KEY, SingleKeyEventManager*>(k, newKeyMgr));
		newKeyMgr->RegisterKeyPress(in);
	}
}

void KeyboardEventManager::RegisterKeyRelease(Inputable* in, AZUL_KEY k)
{
	//see if a manager for the provided key already exists
	SingleKeyMgrMap::iterator it = singleKeyMgrs.find(k);
	if (it != singleKeyMgrs.end())
	{
		(*it).second->RegisterKeyRelease(in);
	}
	else
	{
		SingleKeyEventManager* newKeyMgr = new SingleKeyEventManager(k);
		newKeyMgr->RegisterKeyRelease(in);
	}
}

void KeyboardEventManager::DeregisterKeyPress(Inputable* in, AZUL_KEY k)
{
	//if something is registered to a key, that key's event manager should already exist
	SingleKeyMgrMap::iterator it = singleKeyMgrs.find(k);
	assert(it != singleKeyMgrs.end());
	(*it).second->DeregisterKeyPress(in);
}

void KeyboardEventManager::DeregisterKeyRelease(Inputable* in, AZUL_KEY k)
{
	//if something is registered to a key, that key's event manager should already exist
	SingleKeyMgrMap::iterator it = singleKeyMgrs.find(k);
	assert(it != singleKeyMgrs.end());
	(*it).second->DeregisterKeyRelease(in);
}

void KeyboardEventManager::ProcessKeyEvents()
{
	//check for key press + release of every registered key
	SingleKeyMgrMap::iterator it;
	for (it = singleKeyMgrs.begin(); it != singleKeyMgrs.end(); it++)
	{
		(*it).second->ProcessKeyEvent();
	}
}

KeyboardEventManager::~KeyboardEventManager()
{
	while (!singleKeyMgrs.empty())
	{
		SingleKeyMgrMap::iterator it = singleKeyMgrs.begin();
		delete (*it).second;
		singleKeyMgrs.erase(it);
	}
}
