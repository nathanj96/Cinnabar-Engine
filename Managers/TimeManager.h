//Manager for time-related data

#ifndef TIME_MANAGER
#define TIME_MANAGER

class TimeManagerAttorney;
class FreezeTime;

class TimeManager
{
	friend class TimeManagerAttorney;
private:
	float currentTime;
	float frameTime;
	float prevTime;
	static void processTime(float sys_time);

	//singleton
	static TimeManager* timeManagerInstance;

	TimeManager() = default;
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
	~TimeManager() = default;

	static TimeManager& Instance()
	{
		if (!timeManagerInstance)
			timeManagerInstance = new TimeManager;

		return *timeManagerInstance;
	}
	//debug
	static void printTimeInfo();

	static void Terminate();
	static void Initialize();

	/** \brief	Module implemented to enable time stoppage and frame advance. This only stops in-game time, not
	system time. Refer to FreezeTime documentation for more info.*/
	FreezeTime* timeFreezer;
public:

	/**********************************************************************************************//**
	 * \fn	static float TimeManager::getFrameTime();
	 *
	 * \brief	Centralized accessor for the time the previous frame took to execute.
	 *
	 * \returns	The time the previous frame took to execute.
	 **************************************************************************************************/

	static float getFrameTime();

	/**********************************************************************************************//**
	 * \fn	static float TimeManager::getTime();
	 *
	 * \brief	Centralized accessor for the current game time.
	 *
	 * \returns	The current game time.
	 **************************************************************************************************/

	static float getTime();
};

#endif TIME_MANAGER