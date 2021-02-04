#ifndef DEREGISTER_DRAW_2D_COMMAND
#define DEREGISTER_DRAW_2D_COMMAND

//forward declaration
class Drawable;

#include "RegistrationCommandBase.h"

class DeregisterDraw2DCommand : public RegistrationCommandBase
{
public:
	DeregisterDraw2DCommand() = delete;
	DeregisterDraw2DCommand(const DeregisterDraw2DCommand&) = delete;
	DeregisterDraw2DCommand& operator=(const DeregisterDraw2DCommand&) = delete;
	~DeregisterDraw2DCommand() = default;

	DeregisterDraw2DCommand(Drawable* draw);

	virtual void Execute() override;
private:
	Drawable* drawObj;
};
#endif DEREGISTER_DRAW_2D_COMMAND