//Class for storing and eventually processing scene registration commands

#ifndef REGISTRATION_COMMAND_BROKER
#define REGISTRATION_COMMAND_BROKER

#include <list>

//forward declaration
class RegistrationCommandBase;

class RegistrationCommandBroker
{
private:
	using CommandList = std::list<RegistrationCommandBase*>;
	CommandList cmdList;
public:
	RegistrationCommandBroker() = default;
	RegistrationCommandBroker(const RegistrationCommandBroker&) = default;
	RegistrationCommandBroker& operator=(const RegistrationCommandBroker&) = default;
	~RegistrationCommandBroker() = default;

	void addCommand(RegistrationCommandBase* cmd);

	/**********************************************************************************************//**
	 * \fn	void RegistrationCommandBroker::processCommands();
	 * \ingroup SCENEUPDATE
	 * \brief	Processes all registration change commands.
	 **************************************************************************************************/

	void processCommands();
};

#endif REGISTRATION_COMMAND_BROKER