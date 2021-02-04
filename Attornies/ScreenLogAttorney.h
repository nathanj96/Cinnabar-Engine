#ifndef SCREEN_LOG_ATTORNEY
#define SCREEN_LOG_ATTORNEY

#include "ScreenLog.h"

class CinnabarEngine;

class ScreenLogAttorney
{
public:
	class GameLoop
	{
		friend class CinnabarEngine;
	private:
		static void Render()
		{
			ScreenLog::Render();
		}
		static void Initialize()
		{
			ScreenLog::Initialize();
		}
		static void Terminate()
		{
			ScreenLog::Terminate();
		}
	};
};

#endif SCREEN_LOG_ATTORNEY