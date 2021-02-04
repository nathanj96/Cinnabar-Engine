#ifndef DEREGISTER_ALARM_COMMAND
#define DEREGISTER_ALARM_COMMAND

//forward declaration
class Alarmable;

#include "RegistrationCommandBase.h"
#include "AlarmableManager.h"

class DeregisterAlarmCommand : public RegistrationCommandBase
{
public:
	DeregisterAlarmCommand() = delete;
	DeregisterAlarmCommand(const DeregisterAlarmCommand&) = delete;
	DeregisterAlarmCommand& operator=(const DeregisterAlarmCommand&) = delete;
	~DeregisterAlarmCommand() = default;

	DeregisterAlarmCommand(Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber);

	virtual void Execute() override;
private:
	Alarmable* alarmObj;
	//which number alarm
	AlarmableManager::AlarmNum alarmNum;
};

#endif DEREGISTER_ALARM_COMMAND