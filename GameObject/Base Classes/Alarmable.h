//Base class for "alarmable" objects: ones which can trigger events after a specified amount of time

#ifndef ALARMABLE
#define ALARMABLE

class AlarmableAttorney;
class RegisterAlarmCommand;
class DeregisterAlarmCommand;

#include "AlarmableManager.h"
#include "RegistrationState.h"

class Alarmable
{
	friend class AlarmableAttorney;
private:
	//stuff that each registration command must contain
	struct RegistrationData
	{
		AlarmableManager::AlarmbleMapRef alarmMapRef;
		RegistrationState alarmRegState;
		RegisterAlarmCommand* alarmRegistrationCmdPtr;
		DeregisterAlarmCommand* alarmDeregistrationCmdPtr;
	};
	RegistrationData regData[AlarmableManager::TOTAL_NUM_ALARMS];
	//used for pausing/unpausing alarms
	float pausedAlarmTimes[AlarmableManager::TOTAL_NUM_ALARMS];

	void RegisterAlarm(float time, AlarmableManager::AlarmNum alarmNumber);
	//stop alarm
	void DeregisterAlarm(AlarmableManager::AlarmNum alarmNumber);

	void triggerAlarm(AlarmableManager::AlarmNum alarmNumber);

	/**********************************************************************************************//**
	 * \fn	virtual void Alarmable::Alarm0()
	 * \ingroup GAMELOOPEVENTS
	 * \ingroup ALARMABLEMETHODS
	 * \brief	Callback when alarm 0 fires.
	 * 			
	 * \note All alarms are automatically deregistered when they fire. Repeated alarms require another
	 * 		 call to SubmitRegisterAlarmCommand() in the callback.
	 **************************************************************************************************/

	virtual void Alarm0()
	{
	};

	/**********************************************************************************************//**
	* \fn	virtual void Alarmable::Alarm1()
	* \ingroup GAMELOOPEVENTS
	* \ingroup ALARMABLEMETHODS
	* \brief	Callback when alarm 1 fires.
	*
	* \note All alarms are automatically deregistered when they fire. Repeated alarms require another
	* 		 call to SubmitRegisterAlarmCommand() in the callback.
	**************************************************************************************************/
	virtual void Alarm1()
	{
	};

	/**********************************************************************************************//**
	 * \fn	virtual void Alarmable::Alarm2()
	 * \ingroup GAMELOOPEVENTS
 	 * \ingroup ALARMABLEMETHODS
	 * \brief	Callback when alarm 2 fires.
	 *
	 * \note All alarms are automatically deregistered when they fire. Repeated alarms require another
	 * 		 call to SubmitRegisterAlarmCommand() in the callback.
	 **************************************************************************************************/
	virtual void Alarm2()
	{
	};

	/**********************************************************************************************//**
	* \fn	virtual void Alarmable::Alarm3()
	* \ingroup GAMELOOPEVENTS
	* \ingroup ALARMABLEMETHODS
	* \brief	Callback when alarm 3 fires.
	*
	* \note All alarms are automatically deregistered when they fire. Repeated alarms require another
	* 		 call to SubmitRegisterAlarmCommand() in the callback.
	**************************************************************************************************/
	virtual void Alarm3()
	{
	};

	/**********************************************************************************************//**
	 * \fn	virtual void Alarmable::Alarm4()
	 * \ingroup ALARMABLEMETHODS
	 * \brief	Callback when alarm 4 fires.
	 *
	 * \note All alarms are automatically deregistered when they fire. Repeated alarms require another
	 * 		 call to SubmitRegisterAlarmCommand() in the callback.
	 **************************************************************************************************/
	virtual void Alarm4()
	{
	};

	//for use at engine level only
	void setAlarmObjRef(AlarmableManager::AlarmNum alarmNumber, AlarmableManager::AlarmbleMapRef newRef);
protected:

	/**********************************************************************************************//**
	 * \fn	void Alarmable::SubmitRegisterAlarmCommand(float t, AlarmableManager::AlarmNum alarmNumber);
	 * \ingroup ALARMABLEREGISTRATION
	 * \brief	Call to set alarm.
	 * 			
	 * \param 	t		   	The time, in seconds, before the alarm will fire.
	 * \param 	alarmNumber	The alarm number, from 0 to 4.
	 **************************************************************************************************/

	void SubmitRegisterAlarmCommand(float t, AlarmableManager::AlarmNum alarmNumber);

	/**********************************************************************************************//**
	 * \fn	void Alarmable::SubmitDeregisterAlarmCommand(AlarmableManager::AlarmNum alarmNumber);
	 * \ingroup ALARMABLEREGISTRATION
	 * \brief	Call to cancel an alarm.
	 *
	 * \param 	alarmNumber	The alarm number, from 0 to 4.
	 **************************************************************************************************/

	void SubmitDeregisterAlarmCommand(AlarmableManager::AlarmNum alarmNumber);

	/**********************************************************************************************//**
	 * \fn	void Alarmable::PauseAlarm(AlarmableManager::AlarmNum alarmNumber);
	 * \ingroup ALARMABLEMETHODS
	 * \brief	Pauses a given alarm. Includes an error check in case the given alarm is already paused.
	 *
	 * \param 	alarmNumber	The number alarm to pause.
	 **************************************************************************************************/

	void PauseAlarm(AlarmableManager::AlarmNum alarmNumber);

	/**********************************************************************************************//**
	 * \fn	void Alarmable::UnpauseAlarm(AlarmableManager::AlarmNum alarmNumber);
	 * \ingroup ALARMABLEMETHODS
	 * \brief	Unpauses a given alarm. Includes an error check in case the given alarm is already unpaused.
	 *
	 * \param 	alarmNumber	The number alarm to pause.
	 **************************************************************************************************/

	void UnpauseAlarm(AlarmableManager::AlarmNum alarmNumber);

public:
	Alarmable();
	Alarmable(const Alarmable&) = default;
	Alarmable& operator=(const Alarmable&) = default;
	virtual ~Alarmable();

	AlarmableManager::AlarmbleMapRef getAlarmObjRef(AlarmableManager::AlarmNum alarmNumber) const;
};

#endif ALARMABLE