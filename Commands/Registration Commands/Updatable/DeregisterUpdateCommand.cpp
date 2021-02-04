#include "DeregisterUpdateCommand.h"
#include "UpdatableAttorney.h"

DeregisterUpdateCommand::DeregisterUpdateCommand(Updatable* up) : updateObj(up)
{
};

void DeregisterUpdateCommand::Execute()
{
	UpdatableAttorney::Registration::DeregisterUpdatable(updateObj);
}