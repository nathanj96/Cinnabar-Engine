#ifndef GAME_REGISTRATION_MANAGER_ATTORNEY
#define GAME_REGISTRATION_MANAGER_ATTORNEY

class GameRegistrationCommandBase;

#include "GameRegistrationManager.h"

class GameRegistrationManagerAttorney
{
public:
	class GameLoop
	{
		friend class CinnabarEngine;
	private:
		static void ProcessUpdates()
		{
			GameRegistrationManager::ProcessUpdates();
		}
		static void Terminate()
		{
			GameRegistrationManager::Terminate();
		}
	};
	class toGameUpdatable
	{
		friend class GameUpdatable;
	private:
		static void submitUpdateCommand(GameRegistrationCommandBase* cmd)
		{
			GameRegistrationManager::SubmitCommand(cmd);
		}
		static void registerUpdatable(GameUpdatable* upd)
		{
			GameRegistrationManager::RegisterUpdatable(upd);
		}
		static void deregisterUpdatable(GameUpdatable* upd)
		{
			GameRegistrationManager::DeregisterUpdatable(upd);
		}
	};
};

#endif GAME_REGISTRATION_MANAGER_ATTORNEY