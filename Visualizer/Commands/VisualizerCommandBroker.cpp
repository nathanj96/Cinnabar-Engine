#include "VisualizerCommandBroker.h"
#include "VisualizerCommandBase.h"
#include "VisualizerCommandFactory.h"

void VisualizerCommandBroker::AddCommand(VisualizerCommandBase* cmd)
{
	visualizerCommands.push_back(cmd);
}

void VisualizerCommandBroker::ProcessCommands()
{
	for (CommandList::iterator it = visualizerCommands.begin(); it != visualizerCommands.end(); it++)
	{
		(*it)->Execute();
		//return to factory once implemented. Do separately for each command type so they
		//are returned to the correct pool
	}
	visualizerCommands.clear();
}