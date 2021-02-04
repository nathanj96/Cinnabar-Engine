#ifndef DEREGISTER_UPDATE_COMMAND
#define DEREGISTER_UPDATE_COMMAND

//forward declaration
class Updatable;

#include "RegistrationCommandBase.h"

class DeregisterUpdateCommand : public RegistrationCommandBase
{
public:
	DeregisterUpdateCommand() = delete;
	DeregisterUpdateCommand(const DeregisterUpdateCommand&) = delete;
	DeregisterUpdateCommand& operator=(const DeregisterUpdateCommand&) = delete;
	~DeregisterUpdateCommand() = default;

	DeregisterUpdateCommand(Updatable* up);

	virtual void Execute() override;
private:
	Updatable* updateObj;
};

#endif DEREGISTER_UPDATE_COMMAND