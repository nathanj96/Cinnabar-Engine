//Base class for registration commands, enabling delayed registrations so as not to break the game loop

#ifndef REGISTRATION_COMMAND_BASE
#define REGISTRATION_COMMAND_BASE

class RegistrationCommandBase
{
public:
	RegistrationCommandBase() = default;
	RegistrationCommandBase(const RegistrationCommandBase&) = default;
	RegistrationCommandBase& operator=(const RegistrationCommandBase&) = default;
	virtual ~RegistrationCommandBase() = default;

	//what needs to be done to process the command? Override in each derived class
	virtual void Execute() = 0;
};

#endif REGISTRATION_COMMAND_BASE