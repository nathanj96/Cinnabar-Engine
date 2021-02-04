//Singleton for rendering BSpheres

#ifndef VISUALIZER
#define VISUALIZER

#include "Vect.h"
#include "Matrix.h"
#include "CollisionVolumeBase.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"

class VisualizerAttorney;
class TerrainModel;
class CSoundGeometry;

class GraphicsObject_WireframeConstantColor;

class Visualizer : public Align16
{
	friend class VisualizerAttorney;
private:
	//Singleton design
	static Visualizer* visualizerInstance;

	Visualizer() = default;
	Visualizer(const Visualizer&) = delete;
	Visualizer& operator=(const Visualizer&) = delete;
	~Visualizer() = default;

	static Visualizer& Instance()
	{
		if (!visualizerInstance)
			visualizerInstance = new Visualizer;

		return *visualizerInstance;
	}

	static void Initialize();
	static void Terminate();

	static Vect defaultColor;

	/** \brief	Used to visualize bounding spheres. Note that there is only one instance of this; if multiple bounding spheres need to
	be rendered in the same frame, its properties are adjusted in between each one and it is rendered multiple times.*/
	GraphicsObject_WireframeConstantColor* WFUnitSphere;

	/** \brief	Used to visualize AABBs and OBBs. Note that there is only one instance of this; if multiple AABBs and/or OBBs need to
	be rendered in the same frame, its properties are adjusted in between each one and it is rendered multiple times.*/
	GraphicsObject_WireframeConstantColor* WFUnitCube;

	static void privRenderAABB(Matrix& S, const Vect& col);
	
	static void privRenderBSphere(Matrix& S, const Vect& col);

	static void privRenderOBB(Matrix& S, const Vect col);

public:

	/**********************************************************************************************//**
	 * \fn	static void Visualizer::ShowCollisionVolume(const CollisionVolumeBase& vol, const Vect& col);
	 * \ingroup VISUALIZERMETHODS
	 * \brief	Provides a wireframe render of any collision volume on the screen, using the volume vol
	 * 			and the color vector col. The user should use this function only for all volume types.
	 *
	 * \param 	vol	The volume to render.
	 * \param 	col	The color of the volume.
	 **************************************************************************************************/

	static void ShowCollisionVolume(const CollisionVolumeBase& vol, const Vect& col);

	/**********************************************************************************************//**
	 * \fn	static void Visualizer::ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col);
	 * \ingroup VISUALIZERMETHODS
	 * \brief	Displays a bounding sphere on screen defined by S and col. Rendered as a wireframe.
	 *
	 * \param 	S  	The bounding sphere to render.
	 * \param 	col	The color of the sphere.
	 **************************************************************************************************/

	static void ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col);

	/**********************************************************************************************//**
	 * \fn	static void Visualizer::ShowAABB(const CollisionVolumeAABB& a, const Vect& col);
	 * \ingroup VISUALIZERMETHODS
	 * \brief	Displays an AABB on screen defined by a and col. Rendered as a wireframe.
	 *
	 * \param 	a  	The AABB to render.
	 * \param 	col	The color of the AABB.
	 **************************************************************************************************/

	static void ShowAABB(const CollisionVolumeAABB& a, const Vect& col);

	/**********************************************************************************************//**
	 * \fn	static void Visualizer::ShowOBB(const CollisionVolumeOBB& a, const Vect& col, const Matrix& world);
	 * \ingroup VISUALIZERMETHODS
	 * \brief	Displays an OBB on screen defined by a, col, and world. Rendered as a wireframe.
	 *
	 * \param 	a	 	The OBB to render.
	 * \param 	col  	The color of the OBB.
	 * \param 	world	The location in world space to render the OBB.
	 **************************************************************************************************/

	static void ShowOBB(const CollisionVolumeOBB& a, const Vect& col, const Matrix& world);

	/**********************************************************************************************//**
	 * \fn	static void Visualizer::ShowTerrainCollision(TerrainModel* terr, int numCells, const Vect& col);
	 * \ingroup VISUALIZERMETHODS
	 * \brief	Shows the collision for every cell of a given TerrainModel.
	 *
	 * \param			terr		The TerrainModel to use.
	 * \param 		  	numCells	The number of cells in the terrain. Can be retrieved using
	 * 								TerrainModel::GetNumCells().
	 * \param 		  	col			The color to use to render the collision cells. Each collision cell
	 * 								is rendered as an individual wireframe box.
	 * 								
	 * \note <b> Use this function with caution. Using it along with a texture with a large heightmap
	 * 		 will cause considerable lag!</b>
	 **************************************************************************************************/

	static void ShowTerrainCollision(TerrainModel* terr, int numCells, const Vect& col);

	/**********************************************************************************************//**
	 * \fn	static void Visualizer::ShowTerrainCell(TerrainModel* terr, float xCoord, float zCoord, const Vect& col);
	 * \ingroup VISUALIZERMETHODS
	 * \brief	Shows the collision for one cell of a terrain at the given x and z-coordinates.
	 *
	 * \param			terr  	The TerrainModel to use.
	 * \param 		  	xCoord	The x-coordinate to use.
	 * \param 		  	zCoord	The z-coordinate to use.
	 * \param 		  	col   	The color to use to render the collision cell. It will be rendered as a wireframe box.
	 **************************************************************************************************/

	static void ShowTerrainCell(TerrainModel* terr, float xCoord, float zCoord, const Vect& col);

	static void ShowCSoundGeometry(CSoundGeometry* geo, const Vect& col, const Matrix& world);

	/**********************************************************************************************//**
	 * \fn	static void Visualizer::ShowLine(const Vect& top, const Vect& bottom, const Vect& col);
	 * \ingroup VISUALIZERMETHODS
	 * 
	 * \brief	Shows a "line" extending from points top to bottom.
	 * \note Please be aware that this "line" is actually rendered as an extremely thin unit box rather
	 * 		 than a pure line.
	 *
	 * \param 	top   	The top of the line.
	 * \param 	bottom	The bottom of the line.
	 * \param 	col   	The color to use.
	 **************************************************************************************************/

	static void ShowLine(const Vect& top, const Vect& bottom, const Vect& col);
};

#endif VISUALIZER