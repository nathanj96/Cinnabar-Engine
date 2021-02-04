#ifndef ALARMABLE_MANAGER_ATTORNEY
#define ALARMABLE_MANAGER_ATTORNEY

class Scene;
#include "AlarmableManager.h"

class AlarmableManagerAttorney
{
	friend class Scene;
private:
	static void processAlarms(AlarmableManager* mgr)
	{
		mgr->ProcessAlarms();
	}
};

#endif ALARMABLE_MANAGER_ATTORNEY