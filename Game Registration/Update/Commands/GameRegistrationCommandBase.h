#ifndef GAME_REGISTRATION_COMMAND_BASE
#define GAME_REGISTRATION_COMMAND_BASE

//Base class for all things that can be registered to the game loop in some way. Giving them their own base class
//so they don't get mixed up with scene registration commands

class GameRegistrationCommandBase
{
public:
	GameRegistrationCommandBase() = default;
	GameRegistrationCommandBase(const GameRegistrationCommandBase&) = default;
	GameRegistrationCommandBase& operator=(const GameRegistrationCommandBase&) = default;
	virtual ~GameRegistrationCommandBase() = default;

	virtual void Execute() = 0;
};

#endif GAME_REGISTRATION_COMMAND_BASE