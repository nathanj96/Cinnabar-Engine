#include "RegisterUpdateCommand.h"
#include "UpdatableAttorney.h"

RegisterUpdateCommand::RegisterUpdateCommand(Updatable* up) : updateObj(up)
{
};

void RegisterUpdateCommand::Execute()
{
	UpdatableAttorney::Registration::RegisterUpdatable(updateObj);
}