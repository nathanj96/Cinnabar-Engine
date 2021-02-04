#ifndef COLLIDABLE
#define COLLIDABLE

#include "SceneAttorney.h"
#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "RegistrationState.h"

#include "DebugOut.h"
#include "CollisionVolumeBase.h"
#include "CollisionVolumeBSphere.h"

class RegisterCollidableCommand;
class DeregisterCollidableCommand;
class CollidableAttorney;
class Model;
class TerrainModel;

class Collidable
{
	friend class CollidableAttorney;
public:

	/**********************************************************************************************//**
	 * \enum	VolumeType
	 * \ingroup COLLIDABLE
	 * \brief	When setting a collider model, these are the available bounding volumes to use.
	 **************************************************************************************************/

	enum VolumeType
	{
		BSphere,
		AABB,
		OBB
	};
private:
	CollisionManager::CTypeID myID = CollisionManager::CID_UNDEFINED;

	//registration maintenance
	RegistrationState collidableRegState;
	CollidableGroup::CollidableCollectionRef collidableObjRef;
	RegisterCollidableCommand* collidableRegistrationCmdPtr;
	DeregisterCollidableCommand* collidableDeregistrationCmdPtr;

	void RegisterCollidable();
	void DeregisterCollidable();

	//model to use for collision
	Model* pColModel;
	CollisionVolumeBase* colVolume;
	//BSphere every Collidable has, used for space partitioning
	
	CollisionVolumeBSphere partitionSphere;

	//for use by engine only
	void setCollidableObjRef(CollidableGroup::CollidableCollectionRef newRef);

protected:

	/**********************************************************************************************//**
	 * \fn	template<typename C> void Collidable::SetCollidableGroup()
	 *
	 * \brief	Collision groups are part of the engine's internal methodology for detecting collisions.
	 *			Before collisions involving a given Collidable object can be processed, this function must
	 *			be called, using the name of the Collidable object class as a template parameter.
	 *
	 * \tparam	C	The name of the Collidable object class to use.
	 **************************************************************************************************/

	template<typename C> void SetCollidableGroup()
	{
		myID = SceneAttorney::toCollidable::GetTypeID<C>();
	}

	/**********************************************************************************************//**
	 * \fn	void Collidable::SubmitRegisterCollidableCommand();
	 * \ingroup COLLIDABLEREGISTRATION
	 * \brief	On the frame after this function is called, the scene will begin collision processing for
	 * 			this object type.
	 * 			
	 * \note Collision processing will occur for <b>all</b> instances of the object type in the scene!
	 **************************************************************************************************/

	void SubmitRegisterCollidableCommand();

	/**********************************************************************************************//**
	 * \fn	void Collidable::SubmitDeregisterCollidableCommand();
	 * \ingroup COLLIDABLEREGISTRATION
	 * \brief	On the frame after this function is called, the scene will end collision processing for
	 * 			this object type.
	 **************************************************************************************************/

	void SubmitDeregisterCollidableCommand();

	//NEED TO MODIFY TO INITIALIZE VOLUME

	/**********************************************************************************************//**
	 * \fn	void Collidable::SetColliderModel(Model* mod, Collidable::VolumeType volType);
	 * \ingroup COLLIDABLEMETHODS
	 * \brief	Sets the model this object type will use for precise collision detection. To improve performance,
	 *			it may be better for this to be a different model than the one used to render the object.
	 *
	 * \param [in,out]	mod	   	The new collision model to use.
	 * \param 		  	volType	The type of bounding volume to use.
	 **************************************************************************************************/

	void SetColliderModel(Model* mod, Collidable::VolumeType volType);

	//USE VIRTUAL COLLISIONVOLUME::COMPUTEDATA()

	/**********************************************************************************************//**
	 * \fn	void Collidable::UpdateCollisionData(const Matrix& mat);
	 * \ingroup COLLIDABLEMETHODS
	 * \brief	Updates the locations and boundaries of the Collidable's bounding volumes.
	 * 			
	 * \note	In order to maintain accurate collision, this must be called every time the Collidable
	 * 			changes position, scale, and/or rotation.
	 * 
	 * \param 	mat	The matrix. Usually the same as the Collidable's world matrix.
	 **************************************************************************************************/

	void UpdateCollisionData(const Matrix& mat);

	//macgyvering a memory leak fix...
	void DeleteColVol();

public:

	Collidable();
	Collidable(const Collidable&) = default;
	Collidable& operator=(const Collidable&) = default;
	virtual ~Collidable();

	const CollidableGroup::CollidableCollectionRef& getRef() const;

	//for debug
	std::string colName;

	//this has to be public; if you try to make it private with an attorney, an unfixable include loop occurs

	/**********************************************************************************************//**
	 * \fn	virtual void Collidable::Collision(Collidable*)
	 * \ingroup GAMELOOPEVENTS
	 * \ingroup COLLIDABLEMETHODS
	 * \brief	Callback when this Collidable object type collides with another Collidable object type.
	 *
	 * \note	This will only trigger the callback on this specific Collidable type, not the other one.
	 *			This function needs to be defined in both Collidable object types in order for them to both
	 *			have a callback. For example, if a bullet hits a player, and the player should lose health
	 *			while the bullet gets destroyed, do something like this:
	 *			In the Player class:
	 *				\code
	 *					virtual void Collision(Bullet*)
	 *					 {
	 *						LoseHealth();
	 *					 }
	 *				\endcode
	 *			In the Bullet class:
	 *				\code
	 *					 virtual void Collision(Player*)
	 *					 {
	 *						DestroySelf();
	 *					 }
	*				\endcode
	 *
	 * \param	Collidable*      The class name of the other Collidable object type.
	 **************************************************************************************************/

	virtual void Collision(Collidable*)
	{
		DebugMsg::out("Collidable collided with Collidable (this shouldn't appear)\n");
	}

	virtual void CollisionTerrain()
	{
	};

	/**********************************************************************************************//**
	 * \fn	const CollisionVolumeBase& Collidable::GetCollisionVolume() const;
	 * \ingroup COLLIDABLEMETHODS
	 * \brief	Accessor for the Collidable's bounding volume. Used by the engine for collision testing.
	 * 			Note that the function returns a constant reference rather than a pointer; this is also
	 * 			for engine processing reasons.
	 * 			
	 * \returns	The Collidable's bounding volume.
	 **************************************************************************************************/

	const CollisionVolumeBase& GetCollisionVolume() const;

	//getter for BSphere used for space partitioning. Specifically named for clarity
	const CollisionVolumeBSphere& GetPartitionSphere() const;

	//given a terrain, finds all the cells in the terrain that the Collidable might collide with based on its partition sphere.
	//Probably not the best place for this...
	void findTerrainCells(TerrainModel* terr);
};

#endif COLLIDABLE