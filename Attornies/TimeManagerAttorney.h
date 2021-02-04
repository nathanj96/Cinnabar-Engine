#ifndef TIME_MANAGER_ATTORNEY
#define TIME_MANAGER_ATTORNEY

class CinnabarEngine;

#include "TimeManager.h"

class TimeManagerAttorney
{
	friend class CinnabarEngine;
private:
	static void processTime(float sys_time)
	{
		TimeManager::processTime(sys_time);
	}
	static void Initialize()
	{
		TimeManager::Initialize();
	}
	static void Terminate()
	{
		TimeManager::Terminate();
	}
};

#endif TIME_MANAGER_ATTORNEY
