#ifndef REGISTER_ALARM_COMMAND
#define REGISTER_ALARM_COMMAND

//forward declaration
class Alarmable;

#include "RegistrationCommandBase.h"
#include "AlarmableManager.h"

class RegisterAlarmCommand : public RegistrationCommandBase
{
public:
	RegisterAlarmCommand() = delete;
	RegisterAlarmCommand(const RegisterAlarmCommand&) = delete;
	RegisterAlarmCommand& operator=(const RegisterAlarmCommand&) = delete;
	~RegisterAlarmCommand() = default;

	RegisterAlarmCommand(Alarmable* alarm, AlarmableManager::AlarmNum num);

	void setTime(float newTime);

	virtual void Execute() override;
private:
	//time before the alarm should fire - Save it here so that the scene command broker can take this type of command without
	//needing a separate function for them
	float time;
	//pointer to alarmable object
	Alarmable* alarmObj;
	//which number alarm to trigger on command execute
	AlarmableManager::AlarmNum alarmNum;
};

#endif REGISTER_ALARM_COMMAND