#include "Alarmable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"

#include "RegistrationCommandBase.h"
#include "RegisterAlarmCommand.h"
#include "DeregisterAlarmCommand.h"

//to get current time
#include "TimeManager.h"
#include "DebugOut.h"

Alarmable::Alarmable()
{
	//create commands for each alarm
	for (int i = 0; i < AlarmableManager::TOTAL_NUM_ALARMS; i++)
	{
		regData[i].alarmRegState = RegistrationState::CURRENTLY_DEREGISTERED;
		//static cast i to get the alarm number enum
		regData[i].alarmRegistrationCmdPtr = new RegisterAlarmCommand(this, static_cast<AlarmableManager::AlarmNum>(i));
		regData[i].alarmDeregistrationCmdPtr = new DeregisterAlarmCommand(this, static_cast<AlarmableManager::AlarmNum>(i));
	}
}

void Alarmable::SubmitRegisterAlarmCommand(float t, AlarmableManager::AlarmNum alarmNumber)
{
	regData[alarmNumber].alarmRegistrationCmdPtr->setTime(t);
	assert(regData[alarmNumber].alarmRegState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::toAlarmable::submitAlarmCommand(regData[alarmNumber].alarmRegistrationCmdPtr);
	regData[alarmNumber].alarmRegState = RegistrationState::PENDING_REGISTRATION;
}

void Alarmable::SubmitDeregisterAlarmCommand(AlarmableManager::AlarmNum alarmNumber)
{
	assert(regData[alarmNumber].alarmRegState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::toAlarmable::submitAlarmCommand(regData[alarmNumber].alarmDeregistrationCmdPtr);
	regData[alarmNumber].alarmRegState = RegistrationState::PENDING_DEREGISTRATION;
}

void Alarmable::RegisterAlarm(float t, AlarmableManager::AlarmNum alarmNumber)
{
	assert(regData[alarmNumber].alarmRegState == RegistrationState::PENDING_REGISTRATION);
	//set the alarm for t seconds after the current time. Since the alarm time will be set individually for each alarm, the delta
	//time is calculated here so the user doesn't need to do it every time
	SceneAttorney::toAlarmable::registerAlarm(TimeManager::getTime() + t, this, alarmNumber);
	regData[alarmNumber].alarmRegState = RegistrationState::CURRENTLY_REGISTERED;
}

void Alarmable::DeregisterAlarm(AlarmableManager::AlarmNum alarmNumber)
{
	assert(regData[alarmNumber].alarmRegState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::toAlarmable::deregisterAlarm(this, alarmNumber);
	regData[alarmNumber].alarmRegState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Alarmable::setAlarmObjRef(AlarmableManager::AlarmNum alarmNumber, AlarmableManager::AlarmbleMapRef newRef)
{
	regData[alarmNumber].alarmMapRef = newRef;
}

AlarmableManager::AlarmbleMapRef Alarmable::getAlarmObjRef(AlarmableManager::AlarmNum alarmNumber) const
{
	return regData[alarmNumber].alarmMapRef;
}

void Alarmable::triggerAlarm(AlarmableManager::AlarmNum alarmNumber)
{
	//first mark the appropriate alarm as deregistered so it can be reregistered within the alarm event if desired
	regData[alarmNumber].alarmRegState = RegistrationState::CURRENTLY_DEREGISTERED;
	switch (alarmNumber)
	{
	case(AlarmableManager::Alarm0):
		//wrapper for alarm call allowing the alarm event to potentially set the alarm again
		Alarm0();
		break;
	case(AlarmableManager::Alarm1):
		Alarm1();
		break;
	case(AlarmableManager::Alarm2):
		Alarm2();
		break;
	case(AlarmableManager::Alarm3):
		Alarm3();
		break;
	case(AlarmableManager::Alarm4):
		Alarm4();
		break;
	default:
		DebugMsg::out("Invalid alarm number provided!\n");
		break;
	}
}

void Alarmable::PauseAlarm(AlarmableManager::AlarmNum alarmNumber)
{
	//save how much time the alarm has left to go. Need to subtract TimeManager::getTime() from it to account for
	//the engine time value that is added to the alarm's length when it is first registered
	AlarmableManager::AlarmbleMapRef ref = regData[alarmNumber].alarmMapRef;
	pausedAlarmTimes[alarmNumber] = (*ref).first - TimeManager::getTime();
	//then stop processing the alarm
	SubmitDeregisterAlarmCommand(alarmNumber);
}

void Alarmable::UnpauseAlarm(AlarmableManager::AlarmNum alarmNumber)
{
	//get how much time the alarm should have left
	float remTime = pausedAlarmTimes[alarmNumber];
	//restart the alarm w/that much time left
	SubmitRegisterAlarmCommand(remTime, alarmNumber);
}

Alarmable::~Alarmable()
{
	//delete all commands
	for (int i = 0; i < AlarmableManager::TOTAL_NUM_ALARMS; i++)
	{
		delete regData[i].alarmRegistrationCmdPtr;
		delete regData[i].alarmDeregistrationCmdPtr;
	}
}