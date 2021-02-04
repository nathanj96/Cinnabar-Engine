#ifndef REGISTER_COLLIDABLE_COMMAND
#define REGISTER_COLLIDABLE_COMMAND

#include "RegistrationCommandBase.h"

class Collidable;

class RegisterCollidableCommand : public RegistrationCommandBase
{
public:
	RegisterCollidableCommand() = delete;
	RegisterCollidableCommand(const RegisterCollidableCommand&) = delete;
	RegisterCollidableCommand& operator=(const RegisterCollidableCommand&) = delete;
	~RegisterCollidableCommand() = default;

	RegisterCollidableCommand(Collidable* col);

	virtual void Execute() override;
private:
	Collidable* colObj;
};

#endif REGISTER_COLLIDABLE_COMMAND