#ifndef DEREGISTER_KEY_RELEASED_COMMAND
#define DEREGISTER_KEY_RELEASED_COMMAND

//forward declaration
class Inputable;

#include "RegistrationCommandBase.h"
#include "Keyboard.h"

class DeregisterKeyReleasedCommand : public RegistrationCommandBase
{
public:
	DeregisterKeyReleasedCommand() = delete;
	DeregisterKeyReleasedCommand(const DeregisterKeyReleasedCommand&) = delete;
	DeregisterKeyReleasedCommand& operator=(const DeregisterKeyReleasedCommand&) = delete;
	~DeregisterKeyReleasedCommand() = default;

	DeregisterKeyReleasedCommand(Inputable* in, AZUL_KEY k);

	virtual void Execute() override;
private:
	//pointer back to inputable obj
	Inputable* inputObj;
	//which key it corresponds to
	AZUL_KEY key;
};

#endif DEREGISTER_KEY_RELEASED_COMMAND