#ifndef TRAITERATOR
#define TRAITERATOR

class TerrainRectangleArea;

#include "TerrainModel.h"

class TRAIterator
{
private:
	TerrainRectangleArea* TR;
	TerrainModel::CellMinMaxPair cell;
	//position for the iterator to get the cell from
	int firstCellIndex;
	//to check equality
	int currCellIndex;
	//in this case, curRow and curCol are relative to the TRA, not the terrain as a whole. The TRA contains a subset of cells of the whole terrain, so
	//it has its own set of rows and columns
	//cells will be iterated through in rows first, then by columns. So based on the dimensions of the TRA, the maxRow is the number
	//of cells in 1 row of the TRA. Once this amount has been passed, move into the next column and start over.
	int curRow;
	int curCol;
	int maxRow;
public:
	TRAIterator() = delete;
	TRAIterator(const TRAIterator&) = default;
	TRAIterator& operator=(const TRAIterator&) = delete;
	~TRAIterator() = default;

	TRAIterator& operator++();
	TRAIterator operator++(int);

	TRAIterator(TerrainRectangleArea* tr, TerrainModel::CellMinMaxPair c, int ind, int MaxRow);

	bool operator==(const TRAIterator& rhs) const;
	bool operator!=(const TRAIterator& rhs) const;

	const TerrainModel::CellMinMaxPair& getCell() const;
	//debug
	int getCellIndex() const;
};

#endif TRAITERATOR