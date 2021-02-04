#ifndef GAME_REGISTRATION_COMMAND_BROKER
#define GAME_REGISTRATION_COMMAND_BROKER

class GameRegistrationCommandBase;

#include <list>

class GameRegistrationCommandBroker
{
private:
	using CommandList = std::list<GameRegistrationCommandBase*>;
	CommandList registrationCommands;
public:
	GameRegistrationCommandBroker() = default;
	GameRegistrationCommandBroker(const GameRegistrationCommandBroker&) = default;
	GameRegistrationCommandBroker& operator=(const GameRegistrationCommandBroker&) = default;
	~GameRegistrationCommandBroker() = default;

	void AddCommand(GameRegistrationCommandBase* cmd);
	void ProcessCommands();
};

#endif GAME_REGISTRATION_COMMAND_BROKER