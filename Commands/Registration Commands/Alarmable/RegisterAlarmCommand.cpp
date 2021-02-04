#include "RegisterAlarmCommand.h"
#include "AlarmableAttorney.h"

RegisterAlarmCommand::RegisterAlarmCommand(Alarmable* alarm, AlarmableManager::AlarmNum num) : alarmObj(alarm), time(0.0f), alarmNum(num)
{
};

void RegisterAlarmCommand::setTime(float newTime)
{
	time = newTime;
}

void RegisterAlarmCommand::Execute()
{
	AlarmableAttorney::Registration::RegisterAlarm(alarmObj, time, alarmNum);
}