#ifndef DEREGISTER_COLLIDABLE_COMMAND
#define DEREGISTER_COLLIDABLE_COMMAND

#include "RegistrationCommandBase.h"

class Collidable;

class DeregisterCollidableCommand : public RegistrationCommandBase
{
public:
	DeregisterCollidableCommand() = delete;
	DeregisterCollidableCommand(const DeregisterCollidableCommand&) = delete;
	DeregisterCollidableCommand& operator=(const DeregisterCollidableCommand&) = delete;
	~DeregisterCollidableCommand() = default;

	DeregisterCollidableCommand(Collidable* col);

	virtual void Execute() override;
private:
	Collidable* colObj;
};

#endif DEREGISTER_COLLIDABLE_COMMAND