//Cinnabar Math Tools

#ifndef C_MATH_TOOLS
#define C_MATH_TOOLS

#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "CollisionVolumeBase.h"
#include "CollisionVolumeBoundingBoxBase.h"

class CMathTools
{
public:

	/************************************************************************************************
	 * \fn	static bool CMathTools::Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeBSphere& b);
	 * \ingroup COLLISIONHELPERS
	 * \brief	Determines whether or not two bouding spheres intersect with one another, and fires collision 
	 * 			events for both Collidables containing them if they do.
	 * \param 	a	The first bounding sphere.
	 * \param 	b	The second bounding sphere.
	 *
	 * \returns	The result of the collision test.
	 **************************************************************************************************/

	static bool Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeBSphere& b);

	/**********************************************************************************************//**
	 * \fn	static bool CMathTools::Intersect(const CollisionVolumeAABB& a, const CollisionVolumeAABB& b);
	 * \ingroup COLLISIONHELPERS
	 * \brief	Used to check for collision between two AABBs.
	 *
	 * \param 	a	The first AABB.
	 * \param 	b	The second AABB.
	 *
	 * \returns	The result of the collision test.
	 **************************************************************************************************/

	static bool Intersect(const CollisionVolumeAABB& a, const CollisionVolumeAABB& b);

	/**********************************************************************************************//**
	 * \fn	static bool CMathTools::Intersect(const CollisionVolumeOBB& a, const CollisionVolumeOBB& b);
	 * \ingroup COLLISIONHELPERS
	 * \brief	Used to check for collision between two OBBs.
	 *
	 * \param 	a	The first OBB.
	 * \param 	b	The second OBB.
	 * \returns	The result of the collision test.
	 **************************************************************************************************/

	static bool Intersect(const CollisionVolumeOBB& a, const CollisionVolumeOBB& b);

	/**********************************************************************************************//**
	 * \fn	static bool CMathTools::Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeAABB& b);
	 * \ingroup COLLISIONHELPERS
	 * \brief	Used to check for collision between a bounding sphere and an AABB.
	 *
	 * \param 	a	The bounding sphere.
	 * \param 	b	The AABB.
	 *
	 * \returns	The result of the collision test.
	 **************************************************************************************************/

	static bool Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeAABB& b);

	/**********************************************************************************************//**
	 * \fn	static bool CMathTools::Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeOBB& b);
	 * \ingroup COLLISIONHELPERS
	 * \brief	Used to check for collision between a bounding sphere and an OOBB.
	 *
	 * \param 	a	The bounding sphere.
	 * \param 	b	The OOBB.
	 *
	 * \returns	The result of the collision test.
	 **************************************************************************************************/

	static bool Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeOBB& b);

	/**********************************************************************************************//**
	 * \fn	static bool CMathTools::Intersect(const CollisionVolumeAABB& a, const CollisionVolumeOBB& b);
	 * \ingroup COLLISIONHELPERS
	 * \brief	Used to check for collision between an AABB and an OBB.
	 *
	 * \param 	a	The AABB.
	 * \param 	b	The OBB.
	 *
	 * \returns	The result of the collision test.
	 **************************************************************************************************/

	static bool Intersect(const CollisionVolumeAABB& a, const CollisionVolumeOBB& b);

	/**********************************************************************************************//**
	 * \fn	static bool CMathTools::Intersect(const CollisionVolumeBase& vol1, const CollisionVolumeBase& vol2);
	 * \ingroup COLLISIONHELPERS
	 * \brief	Generic callback for intersection between two collision volumes. Uses a double dispatch
	 * 			to call the appropriate methods based on the specific collision volumes.
	 *
	 * \param 	vol1	A collision volume.
	 * \param 	vol2	A collision volume.
	 *
	 * \returns	The result of the collision test.
	 **************************************************************************************************/

	static bool Intersect(const CollisionVolumeBase& vol1, const CollisionVolumeBase& vol2);

	/**********************************************************************************************//**
	 * \fn	static bool CMathTools::Intersect(const CollisionVolumeBase& vol1, const CollisionVolumeAABB& vol2);
	 * \ingroup COLLISIONHELPERS
	 * \brief	Checks for intersection between a generic collision volume and an AABB. Used for terrain collision,
	 * 			since terrain collision is calculated via an AABB assigned to each of its cells.
	 *
	 * \param 	vol1	The generic volume
	 * \param 	vol2	The AABB.
	 *
	 * \returns	The result of the collision test.
	 **************************************************************************************************/

	static bool Intersect(const CollisionVolumeBase& vol1, const CollisionVolumeAABB& vol2);

	/**********************************************************************************************//**
	 * \fn	static void CMathTools::Clamp3D(Vect& point, float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	 * \ingroup CMATHTOOLS
	 * \brief	Clamps Vect point to the given intervals. Changes point.
	 *
	 * \param [in,out]	point	A reference to a Vect to be clamped..
	 * \param 		  	minX 	The minimum x coordinate.
	 * \param 		  	maxX 	The maximum x coordinate.
	 * \param 		  	minY 	The minimum y coordinate.
	 * \param 		  	maxY 	The maximum y coordinate.
	 * \param 		  	minZ 	The minimum z coordinate.
	 * \param 		  	maxZ 	The maximum z coordinate.
	 **************************************************************************************************/

	static void Clamp3D(Vect& point, float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

	/**********************************************************************************************//**
	 * \fn	static Vect CMathTools::GetClamp3D(const Vect& point, float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	 * \ingroup CMATHTOOLS
	 * \brief	Clamps Vect point to the given intervals. Returns a clamped copy of Vect.
	 *
	 * \param 	point	A point to be clamped.
	 * \param 	minX 	The minimum x coordinate.
	 * \param 	maxX 	The maximum x coordinate.
	 * \param 	minY 	The minimum y coordinate.
	 * \param 	maxY 	The maximum y coordinate.
	 * \param 	minZ 	The minimum z coordinate.
	 * \param 	maxZ 	The maximum z coordinate.
	 *
	 * \returns	The clamp 3D.
	 **************************************************************************************************/

	static Vect GetClamp3D(const Vect& point, float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

	/**********************************************************************************************//**
	 * \fn	static bool CMathTools::pointAxisIntervalTest(const Vect& point, float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	 * \ingroup COLLISIONHELPERS
	 * \brief	Checks if a point is in between the 3 given ranges on each axis, inclusive. Used for
	 * 			OOBB-BSphere intersection.
	 *
	 * \param 	point	The point to check.
	 * \param 	minX 	The minimum x coordinate.
	 * \param 	maxX 	The maximum x coordinate.
	 * \param 	minY 	The minimum y coordinate.
	 * \param 	maxY 	The maximum y coordinate.
	 * \param 	minZ 	The minimum z coordinate.
	 * \param 	maxZ 	The maximum z coordinate.
	 *
	 * \returns	The result of the test.
	 **************************************************************************************************/

	static bool pointAxisIntervalTest(const Vect& point, float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

	/**********************************************************************************************//**
	 * \fn	static float CMathTools::projLength(const Vect& a, const Vect& b);
	 * \ingroup CMATHTOOLS
	 * \brief	Returns the length of the projection of a along b.
	 *
	 * \param 	a	The projecting Vect.
	 * \param 	b	The Vect to project along.
	 *
	 * \returns	The length of the projection.
	 **************************************************************************************************/

	static float projLength(const Vect& a, const Vect& b);

	/**********************************************************************************************//**
	 * \fn	static Vect CMathTools::proj(const Vect& a, const Vect& b);
	 * \ingroup CMATHTOOLS
	 * \brief	Returns the projection of a along b.
	 *
	 * \param 	a	The projecting Vect.
	 * \param 	b	The Vect to project along.
	 *
	 * \returns The resulting projection.
	 **************************************************************************************************/

	static Vect proj(const Vect& a, const Vect& b);

	/**********************************************************************************************//**
	 * \fn	static float CMathTools::BoundingBoxMaxProjOnAxis(const CollisionVolumeBoundingBoxBase& a, const Vect& v);
	 * \ingroup COLLISIONHELPERS
	 * \brief	Returns the maximum projection of an OBB or AABB along axis v. Used for OBB-OBB and
	 * 			OBB-AABB intersection.
	 *
	 * \param 	a	An OBB or AABB to project.
	 * \param 	v	The axis to project along.
	 *
	 * \returns	The maximum projection.
	 **************************************************************************************************/

	static float BoundingBoxMaxProjOnAxis(const CollisionVolumeBoundingBoxBase& a, const Vect& v);

	/**********************************************************************************************//**
	 * \fn	static float CMathTools::interpFloat2D(const Vect& pointA, const Vect& pointB, const Vect& pointC, float pointAQuant, float pointBQuant, float pointCQuant, const Vect& pointToInterp);
	 * \ingroup CMATHTOOLS
	 * \brief	Allows for the interpolation of a float quantity inside of a triangle defined by points pointA, pointB,
	 * 			and pointC.
	 *
	 * \param 	pointA		 	One point of the triangle.
	 * \param 	pointB		 	The second point of the triangle.
	 * \param 	pointC		 	The third point of the triangle.
	 * \param 	pointAQuant  	The float quantity associated with pointA.
	 * \param 	pointBQuant  	The float quantity associated with pointB.
	 * \param 	pointCQuant  	The float quantity associated with pointC.
	 * \param 	pointToInterp	The point inside the triangle for which a new float quantity is to be interpolated.
	 *
	 * \returns	The interpolated float quantity.
	 **************************************************************************************************/

	static float interpFloat2D(const Vect& pointA, const Vect& pointB, const Vect& pointC, float pointAQuant, float pointBQuant, float pointCQuant, const Vect& pointToInterp);

	/**********************************************************************************************//**
	 * \fn	static Vect CMathTools::interpVect2D(const Vect& pointA, const Vect& pointB, const Vect& pointC, const Vect& pointAQuant, const Vect& pointBQuant, const Vect& pointCQuant, const Vect& pointToInterp);
	 * \ingroup CMATHTOOLS
	 * \brief	Allows for the interpolation of a Vect quantity inside of a triangle defined by points pointA, pointB,
	 * 			and pointC.
	 *
	 * \param 	pointA		 	One point of the triangle.
	 * \param 	pointB		 	The second point of the triangle.
	 * \param 	pointC		 	The third point of the triangle.
	 * \param 	pointAQuant  	The Vect quantity associated with pointA.
	 * \param 	pointBQuant  	The Vect quantity associated with pointB.
	 * \param 	pointCQuant  	The Vect quantity associated with pointC.
	 * \param 	pointToInterp	The point inside the triangle for which a new Vect quantity is to be interpolated.
	 *
	 * \returns	The interpolated Vect quantity.
	 **************************************************************************************************/

	static Vect interpVect2D(const Vect& pointA, const Vect& pointB, const Vect& pointC, const Vect& pointAQuant, const Vect& pointBQuant, const Vect& pointCQuant, const Vect& pointToInterp);
};

#endif C_MATH_TOOLS