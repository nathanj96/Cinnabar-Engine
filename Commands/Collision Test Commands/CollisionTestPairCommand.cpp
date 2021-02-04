#include "CollisionTestPairCommand.h"

#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "CollisionVolumeBSphere.h"
#include "Collidable.h"
#include "CMathTools.h"
#include "Colors.h"

#include "ScreenLog.h"
#include "Visualizer.h"

CollisionTestPairCommand::CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd) : ptrGrp1(g1), ptrGrp2(g2), ptrDispatch(pd)
{
};

CollisionTestPairCommand::~CollisionTestPairCommand()
{
	delete ptrDispatch;
	ptrDispatch = nullptr;
}

void CollisionTestPairCommand::Execute()
{
	//first test if the AABBs for the 2 collidable groups intersect. If not, the Collidables in them are obviously too far apart to be intersecting
	if (CMathTools::Intersect(ptrGrp1->GetGroupAABB(), ptrGrp2->GetGroupAABB()))
	{
		//Visualizer::ShowCollisionVolume(ptrGrp1->GetGroupAABB(), Colors::Red);
		//Visualizer::ShowCollisionVolume(ptrGrp2->GetGroupAABB(), Colors::Blue);
		//then, test if the bounding sphere of each Collidable in group 1 is inside the AABB of group 2. If not, the Collidable is too far away from
		//group 2 to continue testing
		const CollidableGroup::CollidableCollection& coll1 = ptrGrp1->GetColliderCollection();
		for (auto it1 = coll1.begin(); it1 != coll1.end(); it1++)
		{
			if (CMathTools::Intersect((*it1)->GetPartitionSphere(), ptrGrp2->GetGroupAABB()))
			{
				//Visualizer::ShowCollisionVolume((*it1)->GetPartitionSphere(), Colors::Green);
				//if a given Collidable in group 1 is located somewhere within the bounds of group 2, test it against the bounding spheres of every
				//Collidable in group 2. If no intersection, there is no need to test any further
				const CollidableGroup::CollidableCollection& coll2 = ptrGrp2->GetColliderCollection();
				for (auto it2 = coll2.begin(); it2 != coll2.end(); it2++)
				{
					if (CMathTools::Intersect((*it2)->GetPartitionSphere(), (*it1)->GetPartitionSphere()))
					{
						//Visualizer::ShowCollisionVolume((*it2)->GetPartitionSphere(), Colors::Yellow);
						//if the bounding spheres of the 2 Collidables intersect, then they are close enough to perform more expensive,
						//precise collision tests on
						const CollisionVolumeBase& colVol1 = (*it1)->GetCollisionVolume();
						const CollisionVolumeBase& colVol2 = (*it2)->GetCollisionVolume();
						if (CMathTools::Intersect(colVol1, colVol2))
						{
							ptrDispatch->ProcessCallbacks(*it1, *it2);
							//ScreenLog::Add("Collision detected!");
						}
					}
					else
					{
						//ScreenLog::Add("Group 1 and Group 2 Collidable BSpheres do not intersect. Ending test");
					}
				}
			}
			else
			{
				//ScreenLog::Add("Group 1 Collidable does not intersect with group 2 AABB. Ending test");
			}
		}
	}
	else
	{
		//ScreenLog::Add("Group AABBs do not intersect. Ending test");
	}
	//const CollidableGroup::CollidableCollection& coll1 = ptrGrp1->GetColliderCollection();
	//const CollidableGroup::CollidableCollection& coll2 = ptrGrp2->GetColliderCollection();

	//for (auto it1 = coll1.begin(); it1 != coll1.end(); it1++)
	//{
	//	const CollisionVolumeBase& colVol1 = (*it1)->GetCollisionVolume();
	//	for (auto it2 = coll2.begin(); it2 != coll2.end(); it2++)
	//	{
	//		const CollisionVolumeBase& colVol2 = (*it2)->GetCollisionVolume();
	//		if (CMathTools::Intersect(colVol1, colVol2))
	//		{
	//			ptrDispatch->ProcessCallbacks(*it1, *it2);
	//		}
	//	}
	//}
}