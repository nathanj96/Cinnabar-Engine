#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "Model.h"
#include "Matrix.h"
#include "CMathTools.h"
#include "Visualizer.h"

//to get CollidableCollection type alias
#include "CollidableGroup.h"
//for partition calculation
#include "CollisionVolumeBSphere.h"
#include "Collidable.h"

CollisionVolumeAABB::CollisionVolumeAABB(Model* mod)
{
	//reminder: getMaxAABB() and getMinAABB() return them in LOCAL space
	halfDiagLocal = 0.5 * (mod->getMaxAABB() - mod->getMinAABB());
}

void CollisionVolumeAABB::ComputeData(Model* mod, const Matrix& mat)
{
	//redundant, but need to use one vertex of the model as a reference point for the others to determine min/max based off of
	Vect* allVects = mod->getVectList();
	Vect vectTrans = allVects[0] * mat;
	float minX = vectTrans.X();
	float minY = vectTrans.Y();
	float minZ = vectTrans.Z();
	float maxX = vectTrans.X();
	float maxY = vectTrans.Y();
	float maxZ = vectTrans.Z();
	for (int i = 1; i < mod->getVectNum(); i++)
	{
		vectTrans = allVects[i] * mat;
		if (vectTrans.X() < minX)
		{
			minX = vectTrans.X();
		}
		if (vectTrans.X() > maxX)
		{
			maxX = vectTrans.X();
		}
		if (vectTrans.Y() < minY)
		{
			minY = vectTrans.Y();
		}
		if (vectTrans.Y() > maxY)
		{
			maxY = vectTrans.Y();
		}
		if (vectTrans.Z() < minZ)
		{
			minZ = vectTrans.Z();
		}
		if (vectTrans.Z() > maxZ)
		{
			maxZ = vectTrans.Z();
		}
	}
	minCorner.set(minX, minY, minZ);
	maxCorner.set(maxX, maxY, maxZ);

	worldTrans = mat;

	centerWorld = ((minCorner * worldTrans.getInv()) + halfDiagLocal) * worldTrans;
	scaleFactorSquared = worldTrans.get(ROW_1).magSqr();
}

void CollisionVolumeAABB::ComputeDataSoundGeometry(Vect min, Vect max)
{
	minCorner.set(min.X(), min.Y(), min.Z());
	maxCorner.set(max.X(), max.Y(), max.Z());
	//these particular AABBs aren't actually used for collision/are strictly for debug - no need to update anything else
}

void CollisionVolumeAABB::ComputeDataTerrain(Vect min, Vect max)
{
	minCorner.set(min);
	maxCorner.set(max);

	//need these to test for OBB intersection - Compute half diagonal here as we're assuming the terrain instance doesn't change
	worldTrans = Matrix(IDENTITY) * Matrix(TRANS, 0.5 * (minCorner + maxCorner));
	halfDiagLocal = 0.5 * ((max * worldTrans.getInv()) - (min * worldTrans.getInv()));
	centerWorld = ((minCorner * worldTrans.getInv()) + halfDiagLocal) * worldTrans;
	scaleFactorSquared = worldTrans.get(ROW_1).magSqr();
}

void CollisionVolumeAABB::updatePartitionAABB(CollidableGroup* colGroup)
{
	//iterate thru each Collidable in the group
	CollidableGroup::CollidableCollection colCollect = colGroup->GetColliderCollection();
	//need to make sure instances of the collidable are actually present (e.g. make sure there are bullets on-screen)
	if (colCollect.size() != 0)
	{
		CollidableGroup::CollidableCollection::iterator it = colCollect.begin();
		float rad = (*it)->GetPartitionSphere().GetRadius();
		Vect collAABBMin = (*it)->GetPartitionSphere().GetCenter() - Vect(rad, rad, rad);
		Vect collAABBMax = (*it)->GetPartitionSphere().GetCenter() + Vect(rad, rad, rad);
		//initial reference to the collidable group's AABB's max + min
		float minX = collAABBMin.X();
		float minY = collAABBMin.Y();
		float minZ = collAABBMin.Z();
		float maxX = collAABBMax.X();
		float maxY = collAABBMax.Y();
		float maxZ = collAABBMax.Z();
		it++;
		while (it != colCollect.end())
		{
			//use the center and the radius of each Collidable's bounding sphere to approximate what the min + max of the Collidable's AABB would be
			rad = (*it)->GetPartitionSphere().GetRadius();
			collAABBMin = (*it)->GetPartitionSphere().GetCenter() - Vect(rad, rad, rad);
			collAABBMax = (*it)->GetPartitionSphere().GetCenter() + Vect(rad, rad, rad);
			//if the collidable' AABB's max/min are outside that of the collidable group's AABB, update them accordingly
			if (collAABBMin.X() < minX)
			{
				minX = collAABBMin.X();
			}
			if (collAABBMin.Y() < minY)
			{
				minY = collAABBMin.Y();
			}
			if (collAABBMin.Z() < minZ)
			{
				minZ = collAABBMin.Z();
			}
			if (collAABBMax.X() > maxX)
			{
				maxX = collAABBMax.X();
			}
			if (collAABBMax.Y() > maxY)
			{
				maxY = collAABBMax.Y();
			}
			if (collAABBMax.Z() > maxZ)
			{
				maxZ = collAABBMax.Z();
			}
			it++;
		}
		//update the collidable group's AABB w/the newly found values
		minCorner.set(minX, minY, minZ);
		maxCorner.set(maxX, maxY, maxZ);
	}
}

bool CollisionVolumeAABB::IntersectAccept(const CollisionVolumeBase& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return CMathTools::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return CMathTools::Intersect(other, *this);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return CMathTools::Intersect(*this, other);
}

Vect CollisionVolumeAABB::getMinCorner() const
{
	return minCorner;
}

Vect CollisionVolumeAABB::getMaxCorner() const
{
	return maxCorner;
}

void CollisionVolumeAABB::DebugView(const Vect& col) const
{
	Visualizer::ShowAABB(*this, col);
}