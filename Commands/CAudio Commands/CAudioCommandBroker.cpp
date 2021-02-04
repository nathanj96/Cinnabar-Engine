#include "CAudioCommandBroker.h"
#include "CAudioCommandBase.h"

void CAudioCommandBroker::AddCommand(CAudioCommandBase* cmd)
{
	soundCommands.push_back(cmd);
}

void CAudioCommandBroker::ProcessCommands()
{
	for (CommandList::iterator it = soundCommands.begin(); it != soundCommands.end(); it++)
	{
		(*it)->Execute();
		//return to factory once implemented. Do separately for each command type so they
		//are returned to the correct pool
	}
	soundCommands.clear();
}