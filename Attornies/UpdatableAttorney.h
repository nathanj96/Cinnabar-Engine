#ifndef UPDATABLE_ATTORNEY
#define UPDATABLE_ATTORNEY

class UpdatableManager;
class RegisterUpdateCommand;
class DeregisterUpdateCommand;

#include "Updatable.h"

class UpdatableAttorney
{
public:
	class GameLoop
	{
		//giving access to Update()
		friend class UpdatableManager;
	private:
		static void Update(Updatable* up)
		{
			up->Update();
		}
	};
	class Registration
	{
		friend class RegisterUpdateCommand;
		friend class DeregisterUpdateCommand;
		friend class UpdatableManager;
	private:
		static void RegisterUpdatable(Updatable* up)
		{
			up->RegisterUpdatable();
		}
		static void DeregisterUpdatable(Updatable* up)
		{
			up->DeregisterUpdatable();
		}
		static void setUpdateObjRef(Updatable* up, UpdatableManager::UpdatableListRef ref)
		{
			up->setUpdateObjRef(ref);
		}
	};
};

#endif UPDATABLE_ATTORNEY