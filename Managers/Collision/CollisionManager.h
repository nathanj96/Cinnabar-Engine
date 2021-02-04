#ifndef COLLISION_MANAGER
#define COLLISION_MANAGER

#include "DebugOut.h"
#include <vector>
#include <list>

class CollidableGroup;

#include "CollisionTestCommandBase.h"
#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"
#include "CollisionTestTerrainCommand.h"

#include "CollisionDispatch.h"

class CollisionManager
{
public:
	using CTypeID = int;
	static const CTypeID CID_UNDEFINED = -1;
private:
	static CTypeID TypeIDNextNumber;

	//define later? placeholder value for now
	static const int MAX_COLLISION_GROUP = 255;

	using CollidableGroupCollection = std::vector<CollidableGroup*>;
	CollidableGroupCollection colGroupCollection;

	void SetGroupForTypeID(CollisionManager::CTypeID ind);

	using CollisionTestCommands = std::list<CollisionTestCommandBase*>;
	CollisionTestCommands colTestCommands;

	void UpdateGroupAABBs();
public:
	CollisionManager();
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
	~CollisionManager();

	template <typename C> CTypeID GetTypeID()
	{
		//TypeIDTextNumber gets incremented every time a new collidable class
		//calls this function for the first time, so each class gets a unique
		//ID that remains the same within each instance of that class
		static CTypeID myTypeID = TypeIDNextNumber++;

		SetGroupForTypeID(myTypeID);

		//old stuff for debugging
		//std::string out = name + " Type ID: " + std::to_string(myTypeID) + '\n';
		//const char* out_c = out.c_str();

		DebugMsg::out(" Type ID: %d\n", myTypeID);
		return myTypeID;
	}
	CollidableGroup* GetColGroup(CTypeID id);

	template<typename C1, typename C2 = C1> void SetCollisionSelf()
	{
		CollidableGroup* pg = colGroupCollection[GetTypeID<C1>()];
		CollisionDispatch<C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();
		colTestCommands.push_back(new CollisionTestSelfCommand(pg, pDispatch));
	}

	template <typename C1, typename C2> void SetCollisionPair()
	{
		CollidableGroup* pg1 = colGroupCollection[GetTypeID<C1>()];
		CollidableGroup* pg2 = colGroupCollection[GetTypeID<C2>()];

		CollisionDispatch<C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();
		colTestCommands.push_back(new CollisionTestPairCommand(pg1, pg2, pDispatch));
	}

	template <typename C1> void SetCollisionTerrain()
	{
		CollidableGroup* pg = colGroupCollection[GetTypeID<C1>()];
		colTestCommands.push_back(new CollisionTestTerrainCommand(pg));
	}

	/**********************************************************************************************//**
	 * \fn	void CollisionManager::ProcessCommands();
	 * \ingroup SCENEUPDATE
	 * \brief	Process all collision commands for the frame.
	 **************************************************************************************************/

	void ProcessCommands();

	//Collision manager tick function
	void ProcessCollision();
};

#endif COLLISION_MANAGER