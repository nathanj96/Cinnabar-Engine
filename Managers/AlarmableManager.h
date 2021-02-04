#ifndef ALARMABLE_MANAGER
#define ALARMABLE_MANAGER

#include <map>
#include <queue>

//forward declaration
class Alarmable;
class AlarmableManagerAttorney;

class AlarmableManager
{
	friend class AlarmableManagerAttorney;
public:
	//for multiple alarms

	/**********************************************************************************************//**
	 * \enum	AlarmNum
	 *
	 * \brief	Use these to set alarms
	 **************************************************************************************************/

	enum AlarmNum
	{
		Alarm0,
		Alarm1,
		Alarm2,
		Alarm3,
		Alarm4,
	};
	static const int TOTAL_NUM_ALARMS = 5;
private:
	using AlarmEvent = std::pair<Alarmable*, AlarmNum>;
	using AlarmTriggerMap = std::multimap<float, AlarmEvent>;
	//used to remove alarms from the map after they are processed
	using AlarmQueue = std::queue<AlarmEvent>;
	AlarmTriggerMap alarmableTriggerMap;
	AlarmQueue usedAlarmsQueue;

	//for use by engine only
	/**********************************************************************************************//**
	 * \fn	void AlarmableManager::ProcessAlarms();
	 * \ingroup SCENEUPDATE
	 * \brief	Processes all necessary alarms for the frame.
	 **************************************************************************************************/
	void ProcessAlarms();
public:
	using AlarmbleMapRef = AlarmTriggerMap::iterator;

	AlarmableManager() = default;
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator=(const AlarmableManager&) = delete;
	~AlarmableManager() = default;

	void DeregisterAlarm(Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber);
	void RegisterAlarm(float t, Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber);
};

#endif ALARMABLE_MANAGER
