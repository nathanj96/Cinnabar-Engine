#ifndef REGISTER_DRAW_COMMAND
#define REGISTER_DRAW_COMMAND

//forward declaration
class Drawable;

#include "RegistrationCommandBase.h"

class RegisterDrawCommand : public RegistrationCommandBase
{
public:
	RegisterDrawCommand() = delete;
	RegisterDrawCommand(const RegisterDrawCommand&) = delete;
	RegisterDrawCommand& operator=(const RegisterDrawCommand&) = delete;
	~RegisterDrawCommand() = default;

	RegisterDrawCommand(Drawable* draw);

	virtual void Execute() override;
private:
	Drawable* drawObj;
};

#endif REGISTER_DRAW_COMMAND