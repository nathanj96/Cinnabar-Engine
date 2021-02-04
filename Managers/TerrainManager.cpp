#include "TerrainManager.h"
#include "TerrainModel.h"

TerrainModel* TerrainManager::getCurrentTerrain() const
{
	return currTerrain;
}

void TerrainManager::setCurrentTerrain(TerrainModel* newTerrain)
{
	currTerrain = newTerrain;
}

void TerrainManager::renderCurrentTerrain()
{
 	currTerrain->TerrainRender();
}
