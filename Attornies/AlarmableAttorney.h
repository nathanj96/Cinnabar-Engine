#ifndef ALARMABLE_ATTORNEY
#define ALARMABLE_ATTORNEY

class RegisterAlarmCommand;
class DeregisterAlarmCommand;

#include "Alarmable.h"
#include "AlarmableManager.h"

class AlarmableAttorney
{
public:
	class GameLoop
	{
		//giving access to triggerAlarm()
		friend class AlarmableManager;
	private:
		static void triggerAlarm(Alarmable* alarm, AlarmableManager::AlarmNum alarmNum)
		{
			alarm->triggerAlarm(alarmNum);
		}
	};
	class Registration
	{
		friend class RegisterAlarmCommand;
		friend class DeregisterAlarmCommand;
		friend class AlarmableManager;
	private:
		static void RegisterAlarm(Alarmable* alarm, float time, AlarmableManager::AlarmNum alarmNumber)
		{
			alarm->RegisterAlarm(time, alarmNumber);
		}
		static void DeregisterAlarm(Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber)
		{
			alarm->DeregisterAlarm(alarmNumber);
		}
		static void setAlarmObjRef(Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber, AlarmableManager::AlarmbleMapRef newRef)
		{
			alarm->setAlarmObjRef(alarmNumber, newRef);
		}
	};
};

#endif ALARMABLE_ATTORNEY