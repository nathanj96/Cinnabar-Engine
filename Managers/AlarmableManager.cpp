#include "AlarmableManager.h"
#include "AlarmableAttorney.h"
#include "DebugOut.h"
#include "TimeManager.h"

//need to get current game time for alarm processing
#include "../CinnabarEngine.h"

void AlarmableManager::RegisterAlarm(float t, Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber)
{
	//need to include alarm num somewhere
	AlarmEvent alarmEv = std::pair<Alarmable*, AlarmNum>(alarm, alarmNumber);
	AlarmbleMapRef mapRef = alarmableTriggerMap.insert(std::pair<float, AlarmEvent>(t, alarmEv));
	AlarmableAttorney::Registration::setAlarmObjRef(alarm, alarmNumber, mapRef);
	switch (alarmNumber)
	{
	case(AlarmableManager::Alarm0):
		//DebugMsg::out("Alarm 0 registered\n");
		break;
	case(AlarmableManager::Alarm1):
		//DebugMsg::out("Alarm 1 registered\n");
		break;
	case(AlarmableManager::Alarm2):
		//DebugMsg::out("Alarm 2 registered\n");
		break;
	case(AlarmableManager::Alarm3):
		//DebugMsg::out("Alarm 3 registered\n");
		break;
	case(AlarmableManager::Alarm4):
		//DebugMsg::out("Alarm 4 registered\n");
		break;
	default:
		//DebugMsg::out("Invalid alarm number provided!\n");
		break;
	}
}

void AlarmableManager::DeregisterAlarm(Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber)
{
	alarmableTriggerMap.erase(alarm->getAlarmObjRef(alarmNumber));
	switch (alarmNumber)
	{
	case(AlarmableManager::Alarm0):
		//DebugMsg::out("Alarm 0 deregistered\n");
		break;
	case(AlarmableManager::Alarm1):
		//DebugMsg::out("Alarm 1 deregistered\n");
		break;
	case(AlarmableManager::Alarm2):
		//DebugMsg::out("Alarm 2 deregistered\n");
		break;
	case(AlarmableManager::Alarm3):
		//DebugMsg::out("Alarm 3 deregistered\n");
		break;
	case(AlarmableManager::Alarm4):
		//DebugMsg::out("Alarm 4 deregistered\n");
		break;
	default:
		//DebugMsg::out("Invalid alarm number provided!\n");
		break;
	}
}

void AlarmableManager::ProcessAlarms()
{
	//not using the local space name for clarity
	AlarmTriggerMap::iterator it = alarmableTriggerMap.begin();
	//ends the loop at the first alarm not triggering this frame, or right away
	//if no alarms are registered
	while (it != alarmableTriggerMap.end() && (*it).first <= TimeManager::getTime())
	{
		AlarmableAttorney::GameLoop::triggerAlarm((*it).second.first, (*it).second.second);
		//DebugMsg::out("Alarm triggered\n");
		//push it on to a queue of alarms that have been used so that they can be removed from the list
		usedAlarmsQueue.push((*it).second);
		it++;
	}

	//old, inefficient code for processing - keeping as reference in case everything goes south
	//for (it = alarmableTriggerMap.begin(); it != alarmableTriggerMap.end(); it++)
	//{
	//	//if the time for an alarm has passed, trigger it and remove it from the map
	//	if ((*it).first <= TimeManager::getTime())
	//	{
	//		AlarmableAttorney::GameLoop::triggerAlarm((*it).second.first, (*it).second.second);
	//		//DebugMsg::out("Alarm triggered\n");
	//		//push it on to a queue of alarms that have been used so that they can be removed from the list
	//		usedAlarmsQueue.push((*it).second);
	//	}
	//	//otherwise break the loop, as this alarm and all subsequent ones have yet to trigger
	//	else
	//	{
	//		break;
	//	}
	//}
	//old code end

	//remove the used alarms from the list. Triggering the alarm marks its flag as deregistered, so we only need to
	//do the list removal here
	AlarmEvent al;
	while (!usedAlarmsQueue.empty())
	{
		al = usedAlarmsQueue.front();
		//al.first gives the Alarmable object, al.second gives which alarm number
		DeregisterAlarm(al.first, al.second);
		usedAlarmsQueue.pop();
	}
}