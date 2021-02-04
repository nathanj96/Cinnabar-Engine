//Manager attached to each Scene to control the terrain currently active in it

#ifndef TERRAIN_MANAGER
#define TERRAIN_MANAGER

class TerrainModel;

class TerrainManager
{
private:
	TerrainModel* currTerrain;
public:
	TerrainManager() = default;
	TerrainManager(const TerrainManager&) = default;
	TerrainManager& operator=(const TerrainManager&) = default;
	~TerrainManager() = default;

	TerrainModel* getCurrentTerrain() const;
	void setCurrentTerrain(TerrainModel* newTerr);
	//since terrain models are loaded before the first scene is initialized, trying to have
	//the terrain handle its own drawing will cause errors. Handle it in the manager instead
	void renderCurrentTerrain();
};

#endif TERRAIN_MANAGER