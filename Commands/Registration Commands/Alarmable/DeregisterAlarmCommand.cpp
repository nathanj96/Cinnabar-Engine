#include "DeregisterAlarmCommand.h"
#include "AlarmableAttorney.h"

DeregisterAlarmCommand::DeregisterAlarmCommand(Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber) : alarmObj(alarm), alarmNum(alarmNumber)
{
};

void DeregisterAlarmCommand::Execute()
{
	AlarmableAttorney::Registration::DeregisterAlarm(alarmObj, alarmNum);
}