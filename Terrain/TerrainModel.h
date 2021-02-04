#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
//#include "GLTools.h"
//#include "TextureTGA.h"
#include "GpuVertTypes.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;
class ShaderObject;
class Texture;
class GraphicsObject_TextureLight;
//class GraphicsObject_WireframeConstantColor;

class TerrainModel : public Align16
{
public:
	struct CellMinMaxPair
	{
		Vect min;
		Vect max;
	};
private:
	Vect* pVect;
	TriangleIndex* pTriList;

	CellMinMaxPair* cellMinMaxPairs;
	//need to save in order to visualize them
	int numCells;

	GraphicsObject_TextureLight* terr;
	//GraphicsObject_WireframeConstantColor* terr;
	Model* pModTerrain;
	Matrix mWorld;

	//used to create the heightmap, save it to use for vertex indexing
	size_t side;
	//used for getCellAt2DCoords
	float length;
	float cellDim;

	//for sprint 5 task 4
	Vect* vertexNormals;
public:
	TerrainModel() = delete;
	TerrainModel(const TerrainModel&) = delete;
	TerrainModel& operator=(const TerrainModel&) = delete;
	~TerrainModel();

	TerrainModel(const char* heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV, ShaderObject* shd, Texture* tx);

	//int getVertexIndex(int x, int y);
	//int getPixelIndex(int x, int y);
	//int getTriIndex(int x, int y);

	//in order to pass them to the Visualizer
	CellMinMaxPair* getCellMinMaxCoords() const;

	int getCellIndexAt2DCoords(float xCoord, float zCoord) const;
	const CellMinMaxPair& getCellAtIndex(int index) const;
	const TriangleIndex& getTriAt2DCoords(float xCoord, float zCoord) const;
	const CellMinMaxPair& getCellAt2DCoords(float xCoord, float zCoord) const;

	/**********************************************************************************************//**
	 * \fn	float TerrainModel::interpHeightAt2DCoords(float xCoord, float zCoord) const;
	 * \ingroup TERRAINMODELMETHODS
	 * \brief	Interpolates the y-value of the terrain at the given x and z-coordinates.
	 *
	 * \param 	xCoord	The x-coordinate to use.
	 * \param 	zCoord	The z-coordinate to use.
	 *
	 * \returns	The interpolated y-value.
	 **************************************************************************************************/

	float interpHeightAt2DCoords(float xCoord, float zCoord) const;

	/**********************************************************************************************//**
	 * \fn	Vect TerrainModel::interpNormalAt2DCoords(float xCoord, float zCoord) const;
	 * \ingroup TERRAINMODELMETHODS
	 * \brief	Interpolates the normal of the terrain at the given x and z-coordinates.
	 *
	 * \param 	xCoord	The x-coordinate to use.
	 * \param 	zCoord	The z-coordinate to use.
	 *
	 * \returns	The interpolated normal.
	 **************************************************************************************************/

	Vect interpNormalAt2DCoords(float xCoord, float zCoord) const;

	/**********************************************************************************************//**
	 * \fn	int TerrainModel::GetNumCells() const;
	 * \ingroup TERRAINMODELMETHODS
	 * \brief	Gets the number of cells in the terrain. This value is equal to (side - 1)^2, where side
	 * 			is the dimension of the terrain's heightmap in pixels.
	 *
	 * \returns	The number of cells in the terrain.
	 **************************************************************************************************/

	int GetNumCells() const;

	//for sprint 5 task 2
	float getCellDim() const;

	//make this private once I know it works...
	virtual void TerrainRender();

	//for collision processing. Gets the amount of vertices per side
	size_t getSideLen() const;
};



#endif _TerrainModel