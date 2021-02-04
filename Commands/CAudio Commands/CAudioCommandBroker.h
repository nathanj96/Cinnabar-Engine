#ifndef C_SOUND_COMMAND_BROKER
#define C_SOUND_COMMAND_BROKER

class CAudioCommandBase;

#include <list>

class CAudioCommandBroker
{
private:
	using CommandList = std::list<CAudioCommandBase*>;
	CommandList soundCommands;
public:
	CAudioCommandBroker() = default;
	CAudioCommandBroker(const CAudioCommandBroker&) = default;
	CAudioCommandBroker& operator=(const CAudioCommandBroker&) = default;
	~CAudioCommandBroker() = default;

	void AddCommand(CAudioCommandBase* cmd);
	void ProcessCommands();
};

#endif C_SOUND_COMMAND_BROKER