#include "CollisionTestSelfCommand.h"
#include "Collidable.h"
#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "CMathTools.h"

CollisionTestSelfCommand::CollisionTestSelfCommand(CollidableGroup* g, CollisionDispatchBase* pd) : ptrGrp(g), ptrDispatch(pd)
{
};

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
	delete ptrDispatch;
	ptrDispatch = nullptr;
}

void CollisionTestSelfCommand::Execute()
{
	const CollidableGroup::CollidableCollection& coll = ptrGrp->GetColliderCollection();
	//if there is not at least 2 of the same object to check, the loop throws an error as its end condition checks the iterator after the beggining at first,
	//not the beginning itself
	if (coll.empty())
	{
		return;
	}
	for (auto it1 = coll.begin(); std::next(it1, 1) != coll.end(); it1++)
	{
		for (auto it2 = std::next(it1, 1); it2 != coll.end(); it2++)
		{
			//first check if the bounding spheres of the 2 Collidables intersect - if not, no need to go any further
			if (CMathTools::Intersect((*it2)->GetPartitionSphere(), (*it1)->GetPartitionSphere()))
			{
				//if the 2 bounding spheres intersect, the Collidables are close enough to perform more precise tests
				{
					const CollisionVolumeBase& colVol1 = (*it1)->GetCollisionVolume();
					const CollisionVolumeBase& colVol2 = (*it2)->GetCollisionVolume();
					if (CMathTools::Intersect(colVol1, colVol2))
					{
						ptrDispatch->ProcessCallbacks(*it1, *it2);
					}
				}
			}
		}
	}
}