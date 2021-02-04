#ifndef GAME_REGISTER_UPDATE_COMMAND
#define GAME_REGISTER_UPDATE_COMMAND

class GameUpdatable;

#include "GameRegistrationCommandBase.h"

class GameRegisterUpdateCommand : public GameRegistrationCommandBase
{
private:
	GameUpdatable* updObj;
public:
	GameRegisterUpdateCommand() = delete;
	GameRegisterUpdateCommand(const GameRegisterUpdateCommand&) = delete;
	GameRegisterUpdateCommand& operator=(const GameRegisterUpdateCommand&) = delete;
	~GameRegisterUpdateCommand() = default;

	GameRegisterUpdateCommand(GameUpdatable* upd);

	virtual void Execute() override;
};

#endif GAME_REGISTER_UPDATE_COMMAND