#ifndef REGISTER_DRAW_2D_COMMAND
#define REGISTER_DRAW_2D_COMMAND

//forward declaration
class Drawable;

#include "RegistrationCommandBase.h"

class RegisterDraw2DCommand : public RegistrationCommandBase
{
public:
	RegisterDraw2DCommand() = delete;
	RegisterDraw2DCommand(const RegisterDraw2DCommand&) = delete;
	RegisterDraw2DCommand& operator=(const RegisterDraw2DCommand&) = delete;
	~RegisterDraw2DCommand() = default;

	RegisterDraw2DCommand(Drawable* draw);

	virtual void Execute() override;
private:
	Drawable* drawObj;
};

#endif REGISTER_DRAW_2D_COMMAND