#ifndef UPDATABLE
#define UPDATABLE

class RegisterUpdateCommand;
class DeregisterUpdateCommand;
class UpdatableAttorney;

#include "UpdatableManager.h"

#include "RegistrationState.h"

//forward declaration
class RegistrationCommandBase;

class Updatable
{
	friend class UpdatableAttorney;
private:
	//used to prevent double registration
	RegistrationState updateRegState;
	//keep an iterator to this object's location in the list of the updatable manager storing it in order to enable quicker removal of it
	UpdatableManager::UpdatableListRef updateObjRef;
	RegisterUpdateCommand* updateRegistrationCmdPtr;
	DeregisterUpdateCommand* updateDeregistrationCmdPtr;
	void RegisterUpdatable();
	void DeregisterUpdatable();

	/**********************************************************************************************//**
	 * \fn	virtual void Updatable::Update()
	 * \ingroup GAMELOOPEVENTS
	 * \ingroup UPDATABLEMETHODS
	 * \brief	Update callback.
	 * 			
	 * \note This function is called <b>every</b> tick, so to improve performance, it should only contain
	 * 		 code that absolutely needs to run every tick.
	 **************************************************************************************************/

	virtual void Update()
	{
	};

	//for use by engine only
	void setUpdateObjRef(UpdatableManager::UpdatableListRef ref);
protected:

	/**********************************************************************************************//**
	 * \fn	void Updatable::SubmitRegisterUpdatableCommand();
	 * \ingroup UPDATABLEREGISTRATION
	 * \brief	On the frame after this function is called, this Updatable object type will start processing
	 * 			Update() calls every tick.
	 **************************************************************************************************/

	void SubmitRegisterUpdatableCommand();

	/**********************************************************************************************//**
	* \fn	void Updatable::SubmitDeregisterUpdatableCommand();
	* \ingroup UPDATABLEREGISTRATION
	* \brief	On the frame after this function is called, this Updatable object type will no longer process
	* 			Update() calls every tick.
	**************************************************************************************************/
	void SubmitDeregisterUpdatableCommand();


public:
	Updatable();
	Updatable(const Updatable&) = default;
	Updatable& operator=(const Updatable&) = default;
	virtual ~Updatable();

	UpdatableManager::UpdatableListRef getUpdateObjRef() const;
};

#endif UPDATABLE