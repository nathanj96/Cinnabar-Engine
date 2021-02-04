#include "RegistrationCommandBroker.h"
#include "RegistrationCommandBase.h"

void RegistrationCommandBroker::addCommand(RegistrationCommandBase* cmd)
{
	cmdList.push_back(cmd);
}

void RegistrationCommandBroker::processCommands()
{
	for (CommandList::iterator it = cmdList.begin(); it != cmdList.end(); it++)
	{
		(*it)->Execute();
	}
	cmdList.clear();
}