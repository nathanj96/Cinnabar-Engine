//Processes all visualizer draw commands

#ifndef VISUALIZER_COMMAND_BROKER
#define VISUALIZER_COMMAND_BROKER

class VisualizerCommandBase;

#include <list>

class VisualizerCommandBroker
{
private:
	using CommandList = std::list<VisualizerCommandBase*>;
	CommandList visualizerCommands;
public:
	VisualizerCommandBroker() = default;
	VisualizerCommandBroker(const VisualizerCommandBroker&) = default;
	VisualizerCommandBroker& operator=(const VisualizerCommandBroker&) = default;
	~VisualizerCommandBroker() = default;

	void AddCommand(VisualizerCommandBase* cmd);
	void ProcessCommands();
};

#endif VISUALIZER_COMMAND_BROKER