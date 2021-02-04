#include "GameRegisterUpdateCommand.h"
#include "GameUpdatableAttorney.h"

GameRegisterUpdateCommand::GameRegisterUpdateCommand(GameUpdatable* upd) : updObj(upd)
{
};

void GameRegisterUpdateCommand::Execute()
{
	GameUpdatableAttorney::Registration::RegisterUpdatable(updObj);
}