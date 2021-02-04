#ifndef GAME_UPDATABLE_ATTORNEY
#define GAME_UPDATABLE_ATTORNEY

#include "GameUpdatable.h"

class GameUpdatableAttorney
{
public:
	class GameLoop
	{
		friend class GameUpdatableManager;
	private:
		static void GameUpdate(GameUpdatable* up)
		{
			up->GameUpdate();
		}
	};
	class Registration
	{
		friend class GameRegisterUpdateCommand;
		friend class GameDeregisterUpdateCommand;
		friend class GameUpdatableManager;
	private:
		static void RegisterUpdatable(GameUpdatable* upd)
		{
			upd->RegisterUpdatable();
		}
		static void DeregisterUpdatable(GameUpdatable* upd)
		{
			upd->DeregisterUpdatable();
		}
		static void setUpdateObjRef(GameUpdatable* upd, GameUpdatableManager::UpdatableListRef ref)
		{
			upd->setUpdateObjRef(ref);
		}
	};
};

#endif GAME_UPDATABLE_ATTORNEY