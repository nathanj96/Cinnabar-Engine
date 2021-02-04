#ifndef DEREGISTER_DRAW_COMMAND
#define DEREGISTER_DRAW_COMMAND

//forward declaration
class Drawable;

#include "RegistrationCommandBase.h"

class DeregisterDrawCommand : public RegistrationCommandBase
{
public:
	DeregisterDrawCommand() = delete;
	DeregisterDrawCommand(const DeregisterDrawCommand&) = delete;
	DeregisterDrawCommand& operator=(const DeregisterDrawCommand&) = delete;
	~DeregisterDrawCommand() = default;

	DeregisterDrawCommand(Drawable* draw);

	virtual void Execute() override;
private:
	Drawable* drawObj;
};

#endif DEREGISTER_DRAW_COMMAND