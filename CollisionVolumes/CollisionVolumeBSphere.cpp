#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeBase.h"
#include "CMathTools.h"
#include "Model.h"
//for MatrixRowType
#include "Enum.h"
#include "Visualizer.h"

void CollisionVolumeBSphere::ComputeData(Model* mod, const Matrix& mat)
{
	////Apply transform to center by multiplying the two (V * M since we are row major)
	center = mod->getCenter() * mat;
	////Scale the radius as needed by multiplying the radius times the scale factor of the matrix
	////First get any row, since we're in row major. Any row will work since we are assuming uniform scaling
	Vect matRow = mat.get(MatrixRowType::ROW_0);
	////the scale factor is the length of the row
	float scaleFact = matRow.mag();
	////now do the multiplication
	radius = mod->getRadius() * scaleFact;
}

void CollisionVolumeBSphere::DebugView(const Vect& col) const
{
	Visualizer::ShowBSphere(*this, col);
}

float CollisionVolumeBSphere::GetRadius() const
{
	return radius;
}

const Vect& CollisionVolumeBSphere::GetCenter() const
{
	return center;
}

bool CollisionVolumeBSphere::IntersectAccept(const CollisionVolumeBase& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return CMathTools::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return CMathTools::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return CMathTools::Intersect(*this, other);
}