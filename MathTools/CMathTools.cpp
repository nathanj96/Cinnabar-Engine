#include "CMathTools.h"
#include "Vect.h"
//for floating-point absolute value function
#include <cmath>

#include <string>
using namespace std;

#include "ScreenLog.h"
#include "Colors.h"

bool CMathTools::pointAxisIntervalTest(const Vect& point, float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	bool result = true;
	if (point.X() < minX || point.X() > maxX)
	{
		result = false;
	}
	else if (point.Y() < minY || point.Y() > maxY)
	{
		result = false;
	}
	else if (point.Z() < minZ || point.Z() > maxZ)
	{
		result = false;
	}
	return result;
}

bool CMathTools::Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeBSphere& b)
{
	bool result = false;

	//(c - c')
	Vect helpVect1 = a.GetCenter() - b.GetCenter();
	//(c - c') dot (c - c')
	float helpFloat1 = helpVect1.dot(helpVect1);
	//(r + r')
	float helpFloat2 = (a.GetRadius() + b.GetRadius());
	//(r + r')^2
	float helpFloat3 = helpFloat2 * helpFloat2;
	//if (c - c') dot (c - c') < (r + r')^2
	if (helpFloat1 < helpFloat3)
	{
		result = true;
	}
	return result;
}

bool CMathTools::Intersect(const CollisionVolumeBase& vol1, const CollisionVolumeBase& vol2)
{
	return vol1.IntersectAccept(vol2);
}

bool CMathTools::Intersect(const CollisionVolumeBase& vol1, const CollisionVolumeAABB& vol2)
{
	return vol1.IntersectAccept(vol2);
}

bool CMathTools::Intersect(const CollisionVolumeAABB& a, const CollisionVolumeAABB& b)
{
	bool isIntersect = true;
	//test for interval overlap between all 3 axes of both AABBs. Testing for negatives
	if (a.getMaxCorner().X() < b.getMinCorner().X())
	{
		isIntersect = false;
	}
	else if (a.getMinCorner().X() > b.getMaxCorner().X())
	{
		isIntersect = false;
	}
	else if (a.getMaxCorner().Y() < b.getMinCorner().Y())
	{
		isIntersect = false;
	}
	else if (a.getMinCorner().Y() > b.getMaxCorner().Y())
	{
		isIntersect = false;
	}
	else if (a.getMaxCorner().Z() < b.getMinCorner().Z())
	{
		isIntersect = false;
	}
	else if (a.getMinCorner().Z() > b.getMaxCorner().Z())
	{
		isIntersect = false;
	}
	return isIntersect;
}

bool CMathTools::Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeAABB& b)
{
	bool isIntersect = false;
	//saving these for readability
	Vect AABBmin = b.getMinCorner();
	Vect AABBmax = b.getMaxCorner();
	//clamp the bounding sphere's center to the AABB
	Vect cent = a.GetCenter();
	Vect centClamp = CMathTools::GetClamp3D(cent, AABBmin.X(), AABBmin.Y(), AABBmin.Z(), AABBmax.X(), AABBmax.Y(), AABBmax.Z());
	//find a vector going from the bounding sphere's center to this clamped point
	Vect radPrime = centClamp - a.GetCenter();
	//if the length of this vector is smaller than that of the bounding sphere's radius, there is an intersection
	float f1 = radPrime.mag();
	float f2 = a.GetRadius();
	if (f1 < f2)
	{
		isIntersect = true;
	}
	return isIntersect;
}

bool CMathTools::Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeOBB& b)
{
	//saving these for readability
	Vect OBBmin = b.getMinLocal();
	Vect OBBmax = b.getMaxLocal();
	//get the inverse world matrix of the OBB
	Matrix worldInv = b.getWorld().getInv();
	//use it to move the BSphere's center to the OBB's local space
	Vect centTest = a.GetCenter() * worldInv;
	//clamp this new center to the OBB
	CMathTools::Clamp3D(centTest, OBBmin.X(), OBBmax.X(), OBBmin.Y(), OBBmax.Y(), OBBmin.Z(), OBBmax.Z());
	//move clamped point back to world space
	centTest *= b.getWorld();
	//test if this point is inside the BSphere
	float rad = a.GetRadius();
	Vect radiusVect = Vect(rad, rad, rad);
	Vect BSphereMin = a.GetCenter() - radiusVect;
	Vect BSphereMax = a.GetCenter() + radiusVect;
	bool isIntersect = CMathTools::pointAxisIntervalTest(centTest, BSphereMin.X(), BSphereMax.X(), BSphereMin.Y(), BSphereMax.Y(),
		BSphereMin.Z(), BSphereMax.Z());
	return isIntersect;
}

void CMathTools::Clamp3D(Vect& point, float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	float tmpX = point.X();
	float tmpY = point.Y();
	float tmpZ = point.Z();
	if (tmpX < minX)
	{
		tmpX = minX;
	}
	else if (tmpX > maxX)
	{
		tmpX = maxX;
	}
	if (tmpY < minY)
	{
		tmpY = minY;
	}
	else if (tmpY > maxY)
	{
		tmpY = maxY;
	}
	if (tmpZ < minZ)
	{
		tmpZ = minZ;
	}
	else if (tmpZ > maxZ)
	{
		tmpZ = maxZ;
	}
	point.set(tmpX, tmpY, tmpZ);
}

Vect CMathTools::GetClamp3D(const Vect& point, float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
	Vect temp;
	float tmpX = point.X();
	float tmpY = point.Y();
	float tmpZ = point.Z();
	if (tmpX < minX)
	{
		tmpX = minX;
	}
	else if (tmpX > maxX)
	{
		tmpX = maxX;
	}
	if (tmpY < minY)
	{
		tmpY = minY;
	}
	else if (tmpY > maxY)
	{
		tmpY = maxY;
	}
	if (tmpZ < minZ)
	{
		tmpZ = minZ;
	}
	else if (tmpZ > maxZ)
	{
		tmpZ = maxZ;
	}
	temp.set(tmpX, tmpY, tmpZ);
	return temp;
}

float CMathTools::projLength(const Vect& a, const Vect& b)
{
	return a.dot(b) / b.mag();
}

Vect CMathTools::proj(const Vect& a, const Vect& b)
{
	return ((a.dot(b)) / (b.dot(b))) * b;
}

float CMathTools::BoundingBoxMaxProjOnAxis(const CollisionVolumeBoundingBoxBase& a, const Vect& v)
{
	Vect projAxis = v;
	//ensure the axis is a pure vector
	projAxis.set(projAxis.X(), projAxis.Y(), projAxis.Z(), 0.0f);
	//move the axis to the OBB's local space
	projAxis *= a.getWorld().getInv();
	//max projection formula
	Vect halfDiag = a.getHalfDiagLocal();
	float maxProj = (abs(projAxis.X() * halfDiag.X()) + abs(projAxis.Y() * halfDiag.Y()) + abs(projAxis.Z() * halfDiag.Z())) / v.mag();
	maxProj *= a.getScaleFactorSquared();
	return maxProj;
}

bool CMathTools::Intersect(const CollisionVolumeOBB& a, const CollisionVolumeOBB& b)
{
	bool result = true;
	//array to contain all axes to test
	Vect axesToTest[15];
	//face normals of a
	Matrix aWorld = a.getWorld();
	axesToTest[0] = aWorld.get(ROW_0);
	axesToTest[1] = aWorld.get(ROW_1);
	axesToTest[2] = aWorld.get(ROW_2);
	//face normals of b
	Matrix bWorld = b.getWorld();
	axesToTest[3] = bWorld.get(ROW_0);
	axesToTest[4] = bWorld.get(ROW_1);
	axesToTest[5] = bWorld.get(ROW_2);
	//cross products of the above 6 axes
	axesToTest[6] = axesToTest[0].cross(axesToTest[3]);
	axesToTest[7] = axesToTest[0].cross(axesToTest[4]);
	axesToTest[8] = axesToTest[0].cross(axesToTest[5]);
	axesToTest[9] = axesToTest[1].cross(axesToTest[3]);
	axesToTest[10] = axesToTest[1].cross(axesToTest[4]);
	axesToTest[11] = axesToTest[1].cross(axesToTest[5]);
	axesToTest[12] = axesToTest[2].cross(axesToTest[3]);
	axesToTest[13] = axesToTest[2].cross(axesToTest[4]);
	axesToTest[14] = axesToTest[2].cross(axesToTest[5]);

	//actual test
	for (int i = 0; i < 15; i++)
	{
		//first make sure the axis is not 0
		if (axesToTest[i].magSqr() > FLT_EPSILON)
		{
			float D = (abs((b.getCenterWorld() - a.getCenterWorld()).dot(axesToTest[i]))) / axesToTest[i].mag();
			float pA = BoundingBoxMaxProjOnAxis(a, axesToTest[i]);
			float pB = BoundingBoxMaxProjOnAxis(b, axesToTest[i]);
			if (D > pA + pB)
			{
				result = false;
				//ScreenLog::Add("Axis %i failed!", i);
				break;
			}
			//ScreenLog::Add("Axis %i passed", i);
		}
	}
	//ScreenLog::Add("Collision detected!");
	return result;
}

bool CMathTools::Intersect(const CollisionVolumeAABB& a, const CollisionVolumeOBB& b)
{
	bool result = true;
	//array to contain all axes to test
	Vect axesToTest[15];
	//face normals of a
	Matrix aWorld = a.getWorld();
	axesToTest[0] = aWorld.get(ROW_0);
	axesToTest[1] = aWorld.get(ROW_1);
	axesToTest[2] = aWorld.get(ROW_2);
	//face normals of b
	Matrix bWorld = b.getWorld();
	axesToTest[3] = bWorld.get(ROW_0);
	axesToTest[4] = bWorld.get(ROW_1);
	axesToTest[5] = bWorld.get(ROW_2);
	//cross products of the above 6 axes
	axesToTest[6] = axesToTest[0].cross(axesToTest[3]);
	axesToTest[7] = axesToTest[0].cross(axesToTest[4]);
	axesToTest[8] = axesToTest[0].cross(axesToTest[5]);
	axesToTest[9] = axesToTest[1].cross(axesToTest[3]);
	axesToTest[10] = axesToTest[1].cross(axesToTest[4]);
	axesToTest[11] = axesToTest[1].cross(axesToTest[5]);
	axesToTest[12] = axesToTest[2].cross(axesToTest[3]);
	axesToTest[13] = axesToTest[2].cross(axesToTest[4]);
	axesToTest[14] = axesToTest[2].cross(axesToTest[5]);

	//actual test
	for (int i = 0; i < 15; i++)
	{
		//first make sure the axis is not 0
		if (axesToTest[i].magSqr() > FLT_EPSILON)
		{
			float D = (abs((b.getCenterWorld() - a.getCenterWorld()).dot(axesToTest[i]))) / axesToTest[i].mag();
			float pA = BoundingBoxMaxProjOnAxis(a, axesToTest[i]);
			float pB = BoundingBoxMaxProjOnAxis(b, axesToTest[i]);
			if (D > pA + pB)
			{
				result = false;
				break;
			}
		}
	}
	return result;
}

float CMathTools::interpFloat2D(const Vect& pointA, const Vect& pointB, const Vect& pointC, float pointAQuant, float pointBQuant, float pointCQuant, const Vect& pointToInterp)
{
	//setup to find "beta" and "gamma" for interpolation equation
	Vect v0 = Vect(pointB.X(), 0.0f, pointB.Z()) - Vect(pointA.X(), 0.0f, pointA.Z());
	Vect v1 = Vect(pointC.X(), 0.0f, pointC.Z()) - Vect(pointB.X(), 0.0f, pointB.Z());
	Vect v2 = Vect(pointToInterp.X(), 0.0f, pointToInterp.Z()) - Vect(pointA.X(), 0.0f, pointA.Z());

	float a = v0.dot(v0);
	float b = v1.dot(v0);
	float c = v1.dot(v1);
	float d = v2.dot(v0);
	float e = v2.dot(v1);

	float beta = ((d * c) - (b * e)) / ((a * c) - (b * b));
	float gamma = ((a * e) - (d * b)) / ((a * c) - (b * b));
	return pointAQuant + (beta * (pointBQuant - pointAQuant)) + (gamma * (pointCQuant - pointBQuant));
}

Vect CMathTools::interpVect2D(const Vect& pointA, const Vect& pointB, const Vect& pointC, const Vect& pointAQuant, const Vect& pointBQuant, const Vect& pointCQuant, const Vect& pointToInterp)
{
	//setup to find "beta" and "gamma" for interpolation equation
	Vect v0 = Vect(pointB.X(), 0.0f, pointB.Z()) - Vect(pointA.X(), 0.0f, pointA.Z());
	Vect v1 = Vect(pointC.X(), 0.0f, pointC.Z()) - Vect(pointB.X(), 0.0f, pointB.Z());
	Vect v2 = Vect(pointToInterp.X(), 0.0f, pointToInterp.Z()) - Vect(pointA.X(), 0.0f, pointA.Z());

	float a = v0.dot(v0);
	float b = v1.dot(v0);
	float c = v1.dot(v1);
	float d = v2.dot(v0);
	float e = v2.dot(v1);

	float beta = ((d * c) - (b * e)) / ((a * c) - (b * b));
	float gamma = ((a * e) - (d * b)) / ((a * c) - (b * b));
	return pointAQuant + (beta * (pointBQuant - pointAQuant)) + (gamma * (pointCQuant - pointBQuant));
}