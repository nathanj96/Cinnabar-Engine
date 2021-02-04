#ifndef MODEL_MANAGER_ATTORNEY
#define MODEL_MANAGER_ATTORNEY

#include "ModelManager.h"

class CinnabarEngine;

class ModelManagerAttorney
{
	//giving it access to Terminate()
	friend class CinnabarEngine;
private:
	static void Terminate()
	{
		ModelManager::Terminate();
	}
};

#endif MODEL_MANAGER_ATTORNEY