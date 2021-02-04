//During development of my demo game, I realized there are some objects that need to be able to be updated as part of the game
//loop, not tied to an individual scene (e.g. in my case, a score manager that processes commands every frame), as otherwise
//registration state errors occur. This class enables the user to register such objects to update during the overall
//game loop instead

#ifndef GAME_REGISTRATION_MANAGER
#define GAME_REGISTRATION_MANAGER

class GameUpdatableManager;
class GameUpdatable;
class GameRegistrationCommandBroker;
class GameRegistrationCommandBase;
class GameRegistrationManagerAttorney;

class GameRegistrationManager
{
	friend class GameRegistrationManagerAttorney;
private:
	GameUpdatableManager* updateMgr;
	
	//singleton
	static GameRegistrationManager* gameRegistrationManagerInstance;

	GameRegistrationManager();
	GameRegistrationManager(const GameRegistrationManager&) = delete;
	GameRegistrationManager& operator=(const GameRegistrationManager&) = delete;
	~GameRegistrationManager();

	static GameRegistrationManager& Instance()
	{
		if (!gameRegistrationManagerInstance)
			gameRegistrationManagerInstance = new GameRegistrationManager;

		return *gameRegistrationManagerInstance;
	}

	static void Terminate();

	GameRegistrationCommandBroker* cmdBroker;

	static void ProcessUpdates();

	static void SubmitCommand(GameRegistrationCommandBase* cmd);
	static void RegisterUpdatable(GameUpdatable* upd);
	static void DeregisterUpdatable(GameUpdatable* upd);
};

#endif GAME_REGISTRATION_MANAGER