//Terrains are treated as their own object/associated manager because of their complicated setup. This manager controls the loading and unloading
//of the assets necessary to make them work

#ifndef TERRAIN_MODEL_MANAGER
#define TERRAIN_MODEL_MANAGER

#include <unordered_map>

#include <string>
using namespace std;

class TerrainModel;
class ShaderObject;
class Texture;

class TerrainModelManagerAttorney;

class TerrainModelManager
{
	friend class TerrainModelManagerAttorney;
private:
	using MapKey = std::string;
	using TerrainMap = std::unordered_map <MapKey, TerrainModel*>;
	using KeyTerrainPair = std::pair<MapKey, TerrainModel*>;

	std::string defaultPath;
	TerrainMap terrMap;

	//Singleton setup
	static TerrainModelManager* terrainModelManagerInstance;

	TerrainModelManager();
	TerrainModelManager(const TerrainModelManager&) = delete;
	TerrainModelManager& operator=(const TerrainModelManager&) = delete;
	~TerrainModelManager() = default;

	static TerrainModelManager& Instance()
	{
		if (!terrainModelManagerInstance)
			terrainModelManagerInstance = new TerrainModelManager;

		return *terrainModelManagerInstance;
	}

	static void Terminate();
	//On game exit, unload all models
	static void unloadTerrains();
public:

	/**********************************************************************************************//**
	 * \fn	static TerrainModel* TerrainModelManager::getTerrain(MapKey key);
	 * \ingroup TERRAINMODELMANAGER
	 * \brief	Retrieves the terrain with the given key
	 *
	 * \param 	key	The key associated with the terrain model when it was loaded.
	 *
	 * \returns	The TerrainModel with the given key. Throws an error if no such model was found.
	 **************************************************************************************************/

	static TerrainModel* getTerrain(MapKey key);
	//note: since the terrain will be loaded with a shader and texture applied to it at the same time, these shaders and textures must have been loaded already

	/**********************************************************************************************//**
	 * \fn	static void TerrainModelManager::loadTerrain(MapKey key, const char* heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV, ShaderObject* shd, Texture* tx);
	 * \ingroup TERRAINMODELMANAGER
	 * \brief	Function used to load terrains into Cinnabar Engine.
	 *
	 * \param 		  	key			 	The key that will be associated with the TerrainModel after loading it.
	 * \param 		  	heightmapFile	A Texture to use as a heightmap to generate the terrain. The Texture must
	 * 									be square or the function will throw an error.
	 * \param 		  	len			 	The length of the terrain in world units. The terrain will extend (len / 2)
	 * 									units in the x and z directions. So a terrain with len = 600 will have the
	 * 									range [-300, 300] in the x and z directions.
	 * \param 		  	maxheight	 	The maximum height value for the terrain. White pixels in the terrain map
	 * 									will correspond to a y-value of (ytrans + maxheight), while black pixels
	 * 									will correspond to a y-value of ytrans. Gray pixels will correspond to a
	 * 									y-value in between those two values, based on how white they are.
	 * \param 		  	ytrans		 	The origin of the terrain in the y direction. The lowest possible y-value
	 * 									any point in the terrain can have.
	 * \param 		  	RepeatU		 	How many times the terrain texture should repeat horizontally.
	 * \param 		  	RepeatV		 	The many times the terrain texture should repeat vertically.
	 * \param			shd			 	The shader for the terrain to use.
	 *									\note
	 *									This function automatically computes all the normals for the terrain, so
	 *									light shaders can be used with it. However, the outer edges of the terrain
	 *									do not have their normals computed due to the overly complex math this would
	 *									require. The assumption is made that the player will never travel this close
	 *									to the edge of the terrain anyway, so make sure to keep the outer edges of
	 *									the terrain covered to prevent the player from seeing the terrain suddenly
	 *									go black at its outer edges.
	 * \param			tx			 	The texture to apply to the terrain model after its construction.
	 * 									
	 * \note The heightmap and texture files the terrain will use <b>must</b> have been previously loaded
	 * 		 with TextureManager::loadTexture() and retrieved with TextureManager::getTexture() for
	 * 		 this function to work.
	 **************************************************************************************************/

	static void loadTerrain(MapKey key, const char* heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV, ShaderObject* shd, Texture* tx);

};

#endif TERRAIN_MODEL_MANAGER