#include "TerrainRectangleArea.h"
#include "TerrainModel.h"
#include "TRAIterator.h"
#include "Collidable.h"
#include <cmath>

TerrainRectangleArea::TerrainRectangleArea(TerrainModel* terrain, Collidable* colObj) : terr(terrain), col(colObj)
{
	//computing the index of the beginning cell of the TRA
	float rad = col->GetPartitionSphere().GetRadius();
	Vect beginPos = col->GetPartitionSphere().GetCenter() - Vect(rad, rad, rad);
	float xBegin = beginPos.X();
	float zBegin = beginPos.Z();
	beginCellIndex = terr->getCellIndexAt2DCoords(xBegin, zBegin);

	//computing the length of a row of the TRA, IN CELLS. Needed for iterator control
	//abs() to ensure the result is positive
	float TRAXDim = col->GetPartitionSphere().GetRadius() * 2.0f;
	rowCellLen = (int)(ceilf(TRAXDim / terr->getCellDim()));

	//computing the index of the end cell of the TRA
	Vect endPos = col->GetPartitionSphere().GetCenter() + Vect(rad, rad, rad);
	//these x and z positions correspond to where the next TRA row in the iterator sequence would
	//begin. Since the TRA is rectangular or square, the iteration always ends at the end of a TRA row;
	//it never ends partially through one.
	float xEnd = endPos.X() - TRAXDim;
	float zEnd = endPos.Z() + terr->getCellDim();
	//for familiarity's sake, let the "end" index be 1 after where the TRA actually ends, like STL iterators
	endCellIndex = terr->getCellIndexAt2DCoords(xEnd, zEnd);

}

TRAIterator TerrainRectangleArea::begin()
{
	TerrainModel::CellMinMaxPair c = terr->getCellAtIndex(beginCellIndex);
	return TRAIterator(this, c, beginCellIndex, rowCellLen);
}

TRAIterator TerrainRectangleArea::end()
{
	TerrainModel::CellMinMaxPair c = terr->getCellAtIndex(endCellIndex);
	return TRAIterator(this, c, endCellIndex, rowCellLen);
}

const TerrainModel::CellMinMaxPair& TerrainRectangleArea::TRAGetCellAtIndex(int index) const
{
	return terr->getCellAtIndex(index);
}

TerrainModel* TerrainRectangleArea::getTerrain() const
{
	return terr;
}