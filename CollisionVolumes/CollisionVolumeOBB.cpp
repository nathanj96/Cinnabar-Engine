#include "CollisionVolumeOBB.h"
#include "CollisionVolumeAABB.h"
#include "Model.h"
#include "Visualizer.h"
#include "CMathTools.h"

CollisionVolumeOBB::CollisionVolumeOBB(Model* mod)
{
	halfDiagLocal = 0.5 * (mod->getMaxAABB() - mod->getMinAABB());
}

void CollisionVolumeOBB::ComputeData(Model* mod, const Matrix& mat)
{
	minLocal = mod->getMinAABB();
	maxLocal = mod->getMaxAABB();
	worldTrans = mat;

	centerWorld = (minLocal + halfDiagLocal) * worldTrans;
	scaleFactorSquared = worldTrans.get(ROW_1).magSqr();
}

void CollisionVolumeOBB::DebugView(const Vect& col) const
{
	Visualizer::ShowOBB(*this, col, worldTrans);
}

const Vect& CollisionVolumeOBB::getMinLocal() const
{
	return minLocal;
}

const Vect& CollisionVolumeOBB::getMaxLocal() const
{
	return maxLocal;
}

bool CollisionVolumeOBB::IntersectAccept(const CollisionVolumeBase& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return CMathTools::Intersect(other, *this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return CMathTools::Intersect(other, *this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return CMathTools::Intersect(*this, other);
}