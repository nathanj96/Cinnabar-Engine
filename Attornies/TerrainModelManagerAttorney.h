#ifndef TERRAIN_MODEL_MANAGER_ATTORNEY
#define TERRAIN_MODEL_MANAGER_ATTORNEY

#include "TerrainModelManager.h"

class CinnabarEngine;

class TerrainModelManagerAttorney
{
	friend class CinnabarEngine;
private:
	static void Terminate()
	{
		TerrainModelManager::Terminate();
	}
};

#endif TERRAIN_MODEL_MANAGER_ATTORNEY