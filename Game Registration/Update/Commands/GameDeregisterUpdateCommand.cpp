#include "GameDeregisterUpdateCommand.h"
#include "GameUpdatableAttorney.h"

GameDeregisterUpdateCommand::GameDeregisterUpdateCommand(GameUpdatable* upd) : updObj(upd)
{
};

void GameDeregisterUpdateCommand::Execute()
{
	GameUpdatableAttorney::Registration::DeregisterUpdatable(updObj);
}