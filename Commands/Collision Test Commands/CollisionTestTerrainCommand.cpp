#include "CollisionTestTerrainCommand.h"
#include "CollidableGroup.h"
#include "TerrainModel.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TerrainManager.h"
#include "TerrainRectangleArea.h"
#include "TRAIterator.h"
#include "CollisionVolumeBase.h"
#include "CollisionVolumeAABB.h"
#include "CMathTools.h"
#include "Collidable.h"
#include "ScreenLog.h"

#include "Visualizer.h"
#include "Colors.h"

CollisionTestTerrainCommand::CollisionTestTerrainCommand(CollidableGroup* g) : ptrGrp(g)
{
};

void CollisionTestTerrainCommand::Execute()
{
	TerrainModel* terr = SceneManager::GetCurrentTerrain();
	const CollidableGroup::CollidableCollection& colCollect = ptrGrp->GetColliderCollection();
	for (auto it = colCollect.begin(); it != colCollect.end(); it++)
	{
		TerrainRectangleArea cells(terr, (*it));
		for (TRAIterator itCell = cells.begin(); itCell != cells.end(); itCell++)
		{
			//grab min/max coords
			TerrainModel::CellMinMaxPair testCell = itCell.getCell();
			//make AABB w/them
			CollisionVolumeAABB cellVol;
			cellVol.ComputeDataTerrain(testCell.min, testCell.max);
			//check for bounding sphere intersection first
			if (CMathTools::Intersect((*it)->GetPartitionSphere(), cellVol))
			{
				//then do more precise collision test
				const CollisionVolumeBase& colVol1 = (*it)->GetCollisionVolume();
				if (CMathTools::Intersect(colVol1, cellVol))
				{
					//fire terrain collision callback
					(*it)->CollisionTerrain();
					//debug
					ScreenLog::Add("Intersection at cell %d", itCell.getCellIndex());
					Visualizer::ShowAABB(cellVol, Colors::Red);
				}
				else
				{
					Visualizer::ShowAABB(cellVol, Colors::Yellow);
				}
			}
			else
			{
				Visualizer::ShowAABB(cellVol, Colors::Green);
			}
		}
	}
}