#ifndef GAME_UPDATABLE
#define GAME_UPDATABLE

//A separate type of Updatable intended for Updatables whose updates need to occur relevant to the game as a whole
//rather than to a specific scene. Used mainly for singletons.

#include "GameUpdatableManager.h"

#include "RegistrationState.h"

class GameRegisterUpdateCommand;
class GameDeregisterUpdateCommand;
class GameUpdatableAttorney;

class GameUpdatable
{
	friend class GameUpdatableAttorney;
private:
	RegistrationState updateRegState;
	GameUpdatableManager::UpdatableListRef updateObjRef;
	GameRegisterUpdateCommand* updateRegistrationCmdPtr;
	GameDeregisterUpdateCommand* updateDeregistrationCmdPtr;

	void RegisterUpdatable();
	void DeregisterUpdatable();

	virtual void GameUpdate()
	{
	};

	//engine use only
	void setUpdateObjRef(GameUpdatableManager::UpdatableListRef ref);

protected:
	void SubmitRegisterUpdatableCommand();
	void SubmitDeregisterUpdatableCommand();

public:
	GameUpdatable();
	GameUpdatable(const GameUpdatable&) = default;
	GameUpdatable& operator=(const GameUpdatable&) = default;
	virtual ~GameUpdatable();

	GameUpdatableManager::UpdatableListRef getUpdateObjRef();
};

#endif GAME_UPDATABLE