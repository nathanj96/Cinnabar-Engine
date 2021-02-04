
#ifndef GAME_DEREGISTER_UPDATE_COMMAND
#define GAME_DEREGISTER_UPDATE_COMMAND

class GameUpdatable;

#include "GameRegistrationCommandBase.h"

class GameDeregisterUpdateCommand : public GameRegistrationCommandBase
{
private:
	GameUpdatable* updObj;
public:
	GameDeregisterUpdateCommand() = delete;
	GameDeregisterUpdateCommand(const GameDeregisterUpdateCommand&) = delete;
	GameDeregisterUpdateCommand& operator=(const GameDeregisterUpdateCommand&) = delete;
	~GameDeregisterUpdateCommand() = default;

	GameDeregisterUpdateCommand(GameUpdatable* upd);

	virtual void Execute() override;
};

#endif GAME_DEREGISTER_UPDATE_COMMAND