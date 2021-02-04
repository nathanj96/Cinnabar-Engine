#ifndef TERRAIN_RECTANGLE_AREA
#define TERRAIN_RECTANGLE_AREA

class TerrainModel;
class Collidable;
class TRAIterator;

#include "TerrainModel.h"

class TerrainRectangleArea
{
private:
	TerrainModel* terr;
	Collidable* col;
	//to control the iterator
	int beginCellIndex;
	int endCellIndex;
	int rowCellLen;
public:
	TerrainRectangleArea() = delete;
	TerrainRectangleArea(const TerrainRectangleArea&) = default;
	TerrainRectangleArea& operator=(const TerrainRectangleArea&) = default;
	~TerrainRectangleArea() = default;

	TerrainRectangleArea(TerrainModel* terrain, Collidable* colObj);

	TRAIterator begin();
	TRAIterator end();

	const TerrainModel::CellMinMaxPair& TRAGetCellAtIndex(int index) const;
	TerrainModel* getTerrain() const;
};

#endif TERRAIN_RECTANGLE_AREA