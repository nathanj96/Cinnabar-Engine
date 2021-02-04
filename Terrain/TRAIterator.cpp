#include "TRAIterator.h"
#include "TerrainRectangleArea.h"
#include "TerrainModel.h"

TRAIterator::TRAIterator(TerrainRectangleArea* tr, TerrainModel::CellMinMaxPair c, int ind, int MaxRow) : TR(tr), cell(c), firstCellIndex(ind), maxRow(MaxRow), curRow(0), curCol(0), currCellIndex(ind)
{
};

TRAIterator& TRAIterator::operator++()
{
	curRow++;
	if (curRow > maxRow)
	{
		curRow = 0;
		curCol++;
	}
	//subtract currRow because cells move in the x direction from positive x's to negative x's
	currCellIndex = firstCellIndex - curRow + (curCol * (TR->getTerrain()->getSideLen() - 1));
	cell = TR->TRAGetCellAtIndex(currCellIndex);
	return *this;
}

TRAIterator TRAIterator::operator++(int)
{
	TRAIterator tmp(*this);
	operator++();
	return tmp;
}

bool TRAIterator::operator==(const TRAIterator& rhs) const
{
	return ((TR == rhs.TR) && (currCellIndex == rhs.currCellIndex));
}

bool TRAIterator::operator!=(const TRAIterator& rhs) const
{
	return !((TR == rhs.TR) && (currCellIndex == rhs.currCellIndex));
}

const TerrainModel::CellMinMaxPair& TRAIterator::getCell() const
{
	return cell;
}

int TRAIterator::getCellIndex() const
{
	return currCellIndex;
}