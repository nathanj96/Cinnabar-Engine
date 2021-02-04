#include "GameRegistrationCommandBroker.h"
#include "GameRegistrationCommandBase.h"

void GameRegistrationCommandBroker::AddCommand(GameRegistrationCommandBase* cmd)
{
	registrationCommands.push_back(cmd);
}

void GameRegistrationCommandBroker::ProcessCommands()
{
	for (CommandList::iterator it = registrationCommands.begin(); it != registrationCommands.end(); it++)
	{
		(*it)->Execute();
	}
	registrationCommands.clear();
}