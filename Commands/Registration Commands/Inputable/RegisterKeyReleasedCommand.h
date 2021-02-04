#ifndef REGISTER_KEY_RELEASED_COMMAND
#define REGISTER_KEY_RELEASED_COMMAND

#include "RegistrationCommandBase.h"
#include "Keyboard.h"
#include "Inputable.h"

class RegisterKeyReleasedCommand : public RegistrationCommandBase
{
public:
	RegisterKeyReleasedCommand() = delete;
	RegisterKeyReleasedCommand(const RegisterKeyReleasedCommand&) = delete;
	RegisterKeyReleasedCommand& operator=(const RegisterKeyReleasedCommand&) = delete;
	~RegisterKeyReleasedCommand() = default;

	RegisterKeyReleasedCommand(Inputable* in, AZUL_KEY k);

	virtual void Execute() override;
private:
	//pointer back to inputable obj
	Inputable* inputObj;
	//which key it corresponds to
	AZUL_KEY key;
};

#endif REGISTER_KEY_RELEASED_COMMAND