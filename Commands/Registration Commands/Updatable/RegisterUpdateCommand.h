#ifndef REGISTER_UPDATE_COMMAND
#define REGISTER_UPDATE_COMMAND

//forward declaration
class Updatable;

#include "RegistrationCommandBase.h"

class RegisterUpdateCommand : public RegistrationCommandBase
{
public:
	RegisterUpdateCommand() = delete;
	RegisterUpdateCommand(const RegisterUpdateCommand&) = delete;
	RegisterUpdateCommand& operator=(const RegisterUpdateCommand&) = delete;
	~RegisterUpdateCommand() = default;

	RegisterUpdateCommand(Updatable* up);

	virtual void Execute() override;
private:
	Updatable* updateObj;
};

#endif REGISTER_UPDATE_COMMAND