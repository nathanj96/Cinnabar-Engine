//Placable geometry objects that control the computation of occlusion in CAudio

#ifndef C_SOUND_GEOMETRY
#define C_SOUND_GEOMETRY

#include "fmod_studio.hpp"
#include "fmod_studio_common.h"

#include "Vect.h"

class CSoundGeometry
{
private:
	FMOD::Geometry* geoObj;
public:
	CSoundGeometry() = delete;
	CSoundGeometry(const CSoundGeometry&) = delete;
	CSoundGeometry& operator=(const CSoundGeometry&) = delete;
	~CSoundGeometry();

	/**********************************************************************************************//**
	 * \fn	CSoundGeometry::CSoundGeometry(int maxPolys, int maxVerts);
	 *
	 * \brief	Required constructor for a CSoundGeometry object, which specifies the maximum number
	 * 			of polygons and vertices it can contain.
	 *
	 * \param 	maxPolys	The maximum number of polygons.
	 * \param 	maxVerts	The maximum number of vertices.
	 **************************************************************************************************/

	CSoundGeometry(int maxPolys, int maxVerts);

	void SetActive(bool newActive);
	bool GetActive() const;

	/**********************************************************************************************//**
	 * \fn	void CSoundGeometry::SetPosition(const Vect& newPos);
	 * \ingroup CSOUNDGEOMETRYMETHODS
	 * \brief	Sets the position of the CSoundGeometry object in world space.
	 *
	 * \param 	newPos	The new position.
	 **************************************************************************************************/

	void SetPosition(const Vect& newPos);

	/**********************************************************************************************//**
	 * \fn	Vect CSoundGeometry::GetPosition() const;
	 * \ingroup CSOUNDGEOMETRYMETHODS
	 * \brief	Retrieves the position of the CSoundGeometry object in world space.
	 *
	 * \returns	The position.
	 **************************************************************************************************/

	Vect GetPosition() const;

	/**********************************************************************************************//**
	 * \fn	void CSoundGeometry::SetRotation(const Vect& newFwd, const Vect& newUp);
	 * \ingroup CSOUNDGEOMETRYMETHODS
	 * \brief	Sets the rotation of the CSoundGeometry object so that it lines up with newFwd and newUp
	 *
	 * \param 	newFwd	A forward vector for the object to align with.
	 * \param 	newUp 	An up vector for the object to align with.
	 **************************************************************************************************/

	void SetRotation(const Vect& newFwd, const Vect& newUp);

	/**********************************************************************************************//**
	 * \fn	void CSoundGeometry::GetRotation(Vect* fwd, Vect* up) const;
	 * \ingroup CSOUNDGEOMETRYMETHODS
	 * \brief	Retrieves the rotation of the CSoundGeometry object.
	 *
	 * \param [in,out]	The address of a Vect to receive the object's forward orient vector.
	 * \param [in,out]	The address of a Vect to receive the object's up orient vector.
	 **************************************************************************************************/

	void GetRotation(Vect* fwd, Vect* up) const;

	/**********************************************************************************************//**
	 * \fn	void CSoundGeometry::SetScale(const Vect& newScale);
	 * \ingroup CSOUNDGEOMETRYMETHODS
	 * \brief	Sets the scale of the CSoundGeometry object.
	 *
	 * \param 	newScale	The new scale.
	 **************************************************************************************************/

	void SetScale(const Vect& newScale);

	/**********************************************************************************************//**
	 * \fn	Vect CSoundGeometry::getScale() const;
	 * \ingroup CSOUNDGEOMETRYMETHODS
	 * \brief	Retrieves the scale of the CSoundGeometry object.
	 *
	 * \returns	The scale.
	 **************************************************************************************************/

	Vect getScale() const;

	/**********************************************************************************************//**
	 * \fn	void CSoundGeometry::AddPolygon(float directOcclusion, float reverbOcclusion, bool doubleSided, int numVerts, Vect* verts, int* polyInd);
	 * \ingroup CSOUNDGEOMETRYMETHODS
	 * \brief	Adds a polygon to the CSoundGeometry object. The dimensions of this polygon represent an area
	 * 			in 3D space against which sound will be occluded. These dimensions are determined by verts,
	 * 			an array of Vects created before calling this function. For example, to add one face
	 * 			of a cube to the geometry:
	 *			\code
	 *				 {
	 *					//create required objects
	 *					CSoundGeometry* sndGeo1 = new CSoundGeometry(64, 256);
	 *					Vect* geoVects2 = new Vect[4];
	 *					int ind2;			 
	 *					
	 *					geoVects2[0].set(0.5f, 0.5f, -0.5f);
	 *					geoVects2[1].set(-0.5f, 0.5f, -0.5f);
	 *					geoVects2[2].set(-0.5f, -0.5f, -0.5f);
	 *					geoVects2[3].set(0.5f, -0.5f, -0.5f);
	 *					sndGeo1->AddPolygon(1.0f, 1.0f, true, 4, geoVects2, &ind2);
	 *					
	 *					//don't need the array anymore
	 *					delete[] geoVects2;
	 *					geoVects2 = nullptr;
	 *				 }
	 *			\endcode
	 * 
	 * \param 		  	directOcclusion	The direct path occlusion factor the new polygon will use.
	 * \param 		  	reverbOcclusion	The reverb path occlusion factor the new polygon will use.
	 * \param 		  	doubleSided	   	If true, both sides of the polygon will occlude sound; if false, only one
	 * 									will (which one is determined by the polygon's winding).
	 * \param 		  	numVerts	   	The number of vertices in the new polygon.
	 * \param			verts		   	An array containing the vertices for the new polygon to use. These are in
	 * 									<b>local space</b>; the resulting polygon will be placed in world space
	 * 									relative to the CSoundGeometry object's world position (retrievable with
	 * 									CSoundGeometry::GetPosition()).
	 * \param			polyInd			The address of an int to receive the index of the new polygon in the
	 * 									geometry's polygon list.
	 **************************************************************************************************/

	void AddPolygon(float directOcclusion, float reverbOcclusion, bool doubleSided, int numVerts, Vect* verts, int* polyInd);

	/**********************************************************************************************//**
	 * \fn	void CSoundGeometry::SetPolygonAttributes(int index, float directOcclusion, float reverbOcclusion, bool doubleSided);
	 * \ingroup CSOUNDGEOMETRYMETHODS
	 * \brief	Sets the attributes of a given polygon.
	 *
	 * \param 	index		   	The index of the polygon to use.
	 * \param 	directOcclusion	The direct path occlusion factor the new polygon will use.
	 * \param   reverbOcclusion	The reverb path occlusion factor the new polygon will use.
	 * \param 	doubleSided	   	If true, both sides of the polygon will occlude sound; if false, only one
	 * 									will (which one is determined by the polygon's winding).
	 **************************************************************************************************/

	void SetPolygonAttributes(int index, float directOcclusion, float reverbOcclusion, bool doubleSided);

	/**********************************************************************************************//**
	 * \fn	void CSoundGeometry::GetPolygonAttributes(int index, float* directOcclusion, float* reverbOcclusion, bool* doubleSided) const;
	 * \ingroup CSOUNDGEOMETRYMETHODS
	 * \brief	Retrieves the attributes of a given polygon.
	 *
	 * \param 		  	index		   	The index of the polygon to use.
	 * \param [in,out]	directOcclusion	The address of a float to receive the polygon's direct path occlusion factor.
	 * \param [in,out]	reverbOcclusion	The address of a float to receive the polygon's reverb path occlusion factor.
	 * \param [in,out]	doubleSided	   	The address of a bool to receive the polygon's double-sided state.
	 **************************************************************************************************/

	void GetPolygonAttributes(int index, float* directOcclusion, float* reverbOcclusion, bool* doubleSided) const;

	//debug
	void ComputePolysMinMax(Vect* min, Vect* max, const Matrix& world);
};

#endif C_SOUND_GEOMETRY