#ifndef REGISTER_KEY_PRESSED_COMMAND
#define REGISTER_KEY_PRESSED_COMMAND

//forward declaration
class Inputable;

#include "RegistrationCommandBase.h"
#include "Keyboard.h"

class RegisterKeyPressedCommand : public RegistrationCommandBase
{
public:
	RegisterKeyPressedCommand() = delete;
	RegisterKeyPressedCommand(const RegisterKeyPressedCommand&) = delete;
	RegisterKeyPressedCommand& operator=(const RegisterKeyPressedCommand&) = delete;
	~RegisterKeyPressedCommand() = default;

	RegisterKeyPressedCommand(Inputable* in, AZUL_KEY k);

	virtual void Execute() override;
private:
	//pointer back to inputable obj
	Inputable* inputObj;
	//which key it corresponds to
	AZUL_KEY key;
};

#endif REGISTER_KEY_PRESSED_COMMAND