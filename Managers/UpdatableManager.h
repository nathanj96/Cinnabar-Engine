//A manager for all objects that are 'updatable'. This does not strictly have to be GameObjects; rather, this can apply
//to any object that inherits from the Updatable class, though it will be used to update GameObjects

#ifndef UPDATABLE_MANAGER
#define UPDATABLE_MANAGER

//forward declaration
class Updatable;

#include <list>

class UpdatableManager
{
private:
	using UpdatableList = std::list<Updatable*>;
	UpdatableList updateList;
public:
	using UpdatableListRef = UpdatableList::iterator;
	UpdatableManager() = default;
	//don't allow more than one of the same UpdatableManager at once
	UpdatableManager(const UpdatableManager&) = delete;
	UpdatableManager& operator=(const UpdatableManager&) = delete;
	~UpdatableManager() = default;

	//public because this function will only be called on private member variables of Scene objects

	/**********************************************************************************************//**
	 * \fn	void UpdatableManager::processElements();
	 * \ingroup SCENEUPDATE
	 * \brief	Processes all necessary update calls for the frame.
	 **************************************************************************************************/

	void processElements();

	void Register(Updatable* up);
	void Deregister(Updatable* up);
};

#endif UPDATABLE_MANAGER