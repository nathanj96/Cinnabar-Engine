#ifndef DEREGISTER_KEY_PRESSED_COMMAND
#define DEREGISTER_KEY_PRESSED_COMMAND

//forward declaration
class Inputable;

#include "RegistrationCommandBase.h"
#include "Keyboard.h"

class DeregisterKeyPressedCommand : public RegistrationCommandBase
{
public:
	DeregisterKeyPressedCommand() = delete;
	DeregisterKeyPressedCommand(const DeregisterKeyPressedCommand&) = delete;
	DeregisterKeyPressedCommand& operator=(const DeregisterKeyPressedCommand&) = delete;
	~DeregisterKeyPressedCommand() = default;

	DeregisterKeyPressedCommand(Inputable* in, AZUL_KEY k);

	virtual void Execute() override;
private:
	//pointer back to inputable obj
	Inputable* inputObj;
	//which key it corresponds to
	AZUL_KEY key;
};

#endif DEREGISTER_KEY_PRESSED_COMMAND